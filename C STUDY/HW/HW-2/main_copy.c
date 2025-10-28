#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PRIOR_P 0.5

double for_one(double p) {
    return (0.8 * p) / ((0.8 * p) + (0.2 * (1 - p)));
}

double for_nul(double p) {
    return (0.2 * p) / ((0.2 * p) + (0.8 * (1 - p)));
}

/**
 * @brief Performs a grid-based raycast using Bresenham's algorithm.
 */
int raycast(double angle_deg, double distance_m, double cell_size_m, int ***out_cells, int *out_count)
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
    int **cells = malloc(max_cells * sizeof(int *));
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
        if (e2 < dx) { err += dx; y0 += sy; }
    }

    *out_cells = cells;
    *out_count = count;
    return 1;
}

/**
 * @brief Frees the memory allocated by `raycast`.
 */
void free_raycast_result(int ***cells_ptr, int count)
{
    if (!cells_ptr || !*cells_ptr) return;
    for (int i = 0; i < count; i++) free((*cells_ptr)[i]);
    free(*cells_ptr);
    *cells_ptr = NULL;
}

int main(int argc, char **argv)
{
    if (argc != 7) {
        fprintf(stderr, "ERROR: invalid arguments\n");
        return 103;
    }

    double H = atof(argv[1]);
    double W = atof(argv[2]);
    double cell_size = atof(argv[3]);
    double x_robot = atof(argv[4]);
    double y_robot = atof(argv[5]);
    double alpha_robot = atof(argv[6]);

    if (H <= 0 || W <= 0 || cell_size <= 0) {
        fprintf(stderr, "ERROR: invalid arguments\n");
        return 103;
    }

    int N_h = (int)ceil(H / cell_size);
    int N_w = (int)ceil(W / cell_size);

    double occupancy_grid[N_h][N_w];
    for (int i = 0; i < N_h; i++)
        for (int j = 0; j < N_w; j++)
            occupancy_grid[i][j] = PRIOR_P;

    int rx = (int)(x_robot / cell_size);
    int ry = (int)(y_robot / cell_size);

    float angle, distance;
    while (scanf("%f %f", &angle, &distance) == 2) {
        double alpha_map = alpha_robot + angle;

        int **cells = NULL;
        int count = 0;
        if (!raycast(alpha_map, distance, cell_size, &cells, &count)) {
            fprintf(stderr, "ERROR: raycast failure\n");
            return 101;
        }

        for (int i = 0; i < count; i++) {
            int row = (N_h - 1) - (ry + cells[i][1]);
            int col = rx + cells[i][0];
            if (row >= 0 && row < N_h && col >= 0 && col < N_w) {
                double p = occupancy_grid[row][col];
                p = (i == count - 1) ? for_one(p) : for_nul(p);
                occupancy_grid[row][col] = p;
            }
        }
        free_raycast_result(&cells, count);
    }

    for (int r = 0; r < N_h; r++) {
        for (int c = 0; c < N_w; c++) {
            char ch;
            double p = occupancy_grid[r][c];
            if (fabs(p - 0.5) < 1e-6)
                ch = '-';
            else if (p > 0.5)
                ch = '#';
            else
                ch = ' ';
            if (r == (N_h - 1 - ry) && c == rx)
                ch = '*';
            putchar(ch);
        }
        putchar('\n');
    }

    return 0;
}
