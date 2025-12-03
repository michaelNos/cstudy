#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>

#include "robot.h"

#define PRIOR_P 0.5

// ----- Bayesian update helpers -----
static inline double bayes_occ(double p)
{
    return (0.8 * p) / ((0.8 * p) + (0.2 * (1.0 - p)));
}

static inline double bayes_free(double p)
{
    return (0.2 * p) / ((0.2 * p) + (0.8 * (1.0 - p)));
}

// ----- Raycast from previous assignment (Bresenham in grid) -----
int raycast(double angle_deg, double distance_m, double cell_size_m,
            int ***out_cells, int *out_count)
{
    if (!out_cells || !out_count || distance_m < cell_size_m) return 0;

    double angle_rad = angle_deg * 3.14159265358979323846 / 180.0;
    double end_x = distance_m * cos(angle_rad);
    double end_y = distance_m * sin(angle_rad);

    int x0 = 0, y0 = 0;
    int x1 = (int)(end_x / cell_size_m);
    int y1 = (int)(end_y / cell_size_m);

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    int max_cells = dx + dy + 1;
    int **cells = malloc((size_t)max_cells * sizeof(int *));
    if (!cells) return 0;

    int count = 0;
    while (1) {
        cells[count] = malloc(2 * sizeof(int));
        if (!cells[count]) {
            for (int i = 0; i < count; i++) free(cells[i]);
            free(cells);
            return 0;
        }
        cells[count][0] = x0;
        cells[count][1] = y0;
        count++;

        if (x0 == x1 && y0 == y1) break;

        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 <  dx) { err += dx; y0 += sy; }
    }

    *out_cells = cells;
    *out_count = count;
    return 1;
}

void free_raycast_result(int ***cells_ptr, int count)
{
    if (!cells_ptr || !*cells_ptr) return;
    for (int i = 0; i < count; i++) free((*cells_ptr)[i]);
    free(*cells_ptr);
    *cells_ptr = NULL;
}

// ----- Thread entry -----
void *robot_thread(void *arg)
{
    RobotArgs *ra = (RobotArgs *)arg;

    char filename[256];
    snprintf(filename, sizeof(filename), "%s_%d.txt", ra->basename, ra->id);

    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "ERROR: missing sensor data file\n");
        exit(105);
    }

    // Ensure starting position is inside map and mark as free
    pthread_mutex_lock(ra->map_mutex);
    int need_w = ra->x + 1;
    int need_h = ra->y + 1;
    if (!map_resize_up(ra->map, need_w, need_h)) {
        pthread_mutex_unlock(ra->map_mutex);
        fprintf(stderr, "ERROR: unknown\n");
        fclose(f);
        exit(100);
    }
    int idx0 = map_index(ra->map, ra->x, ra->y);
    ra->map->cells[idx0] = 0.0;
    pthread_mutex_unlock(ra->map_mutex);

    char token[64];
    while (fscanf(f, "%63s", token) == 1) {

        // ---------------- movement command ----------------
        if (strcmp(token, "right") == 0 ||
            strcmp(token, "left")  == 0 ||
            strcmp(token, "up")    == 0 ||
            strcmp(token, "down")  == 0) {

            if (strcmp(token, "right") == 0)      ra->x += 1;
            else if (strcmp(token, "left") == 0)  ra->x -= 1;
            else if (strcmp(token, "up") == 0)    ra->y += 1;
            else if (strcmp(token, "down") == 0)  ra->y -= 1;

            pthread_mutex_lock(ra->map_mutex);
            need_w = ra->x + 1;
            need_h = ra->y + 1;
            if (!map_resize_up(ra->map, need_w, need_h)) {
                pthread_mutex_unlock(ra->map_mutex);
                fprintf(stderr, "ERROR: unknown\n");
                fclose(f);
                exit(100);
            }
            int idx = map_index(ra->map, ra->x, ra->y);
            ra->map->cells[idx] = 0.0; // known free
            pthread_mutex_unlock(ra->map_mutex);

        // ---------------- sensor measurement ----------------
        } else {
            char *endptr = NULL;
            double rel_angle = strtod(token, &endptr);
            if (!endptr || *endptr != '\0') {
                fprintf(stderr, "ERROR: invalid sensor data\n");
                fclose(f);
                exit(102);
            }

            double distance;
            if (fscanf(f, "%lf", &distance) != 1) {
                fprintf(stderr, "ERROR: invalid sensor data\n");
                fclose(f);
                exit(102);
            }

            double alpha_map = ra->alpha_deg + rel_angle;

            int **cells = NULL;
            int count = 0;
            if (!raycast(alpha_map, distance, ra->cell_size, &cells, &count)) {
                fprintf(stderr, "ERROR: raycast failure\n");
                fclose(f);
                exit(101);
            }

            // determine max coordinates of the beam (global)
            int max_x = ra->x;
            int max_y = ra->y;
            for (int i = 0; i < count; ++i) {
                int gx = ra->x + cells[i][0];
                int gy = ra->y + cells[i][1];
                if (gx > max_x) max_x = gx;
                if (gy > max_y) max_y = gy;
            }

            pthread_mutex_lock(ra->map_mutex);
            if (!map_resize_up(ra->map, max_x + 1, max_y + 1)) {
                pthread_mutex_unlock(ra->map_mutex);
                free_raycast_result(&cells, count);
                fprintf(stderr, "ERROR: unknown\n");
                fclose(f);
                exit(100);
            }

            // Bayes update: all along ray free, last cell occupied
            for (int i = 0; i < count; ++i) {
                int gx = ra->x + cells[i][0];
                int gy = ra->y + cells[i][1];
                int idx = map_index(ra->map, gx, gy);
                double p = ra->map->cells[idx];
                if (i == count - 1)
                    p = bayes_occ(p);   // hit
                else
                    p = bayes_free(p);  // free space
                ra->map->cells[idx] = p;
            }
            pthread_mutex_unlock(ra->map_mutex);

            free_raycast_result(&cells, count);
        }
    }

    if (ferror(f)) {
        fprintf(stderr, "ERROR: invalid sensor data\n");
        fclose(f);
        exit(102);
    }

    fclose(f);
    return NULL;
}
