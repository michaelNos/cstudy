#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define P 0.5
/**
 * @brief Performs a grid-based raycast using Bresenham's algorithm.
 * 
 * The ray starts at (0,0) and travels in the specified angle
 * and distance. Each grid cell has size `cell_size_m`. Requires stdlib.h, math.h
 * Variable out_cells is dynamically allocated memory, don't forget to free() it after the use.
 * 
 * @param angle_deg   Angle of the ray (in degrees)
 * @param distance_m  Length of the ray (in meters)
 * @param cell_size_m Size of one grid cell (in meters)
 * @param out_cells   Pointer to store dynamically allocated 2D array [N][2] of grid coords, undefined on failure
 * @param out_count   Pointer to store number of cells (N), undefined on failure
 * @return            1 on success, 0 on failure (e.g., allocation failure, 'distance_m' is less than 'cell_size_m')
 */
int raycast(double angle_deg, double distance_m, double cell_size_m, int ***out_cells, int *out_count)
{
    if (!out_cells || !out_count || distance_m < cell_size_m) {
        return 0;
    }
 
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
    if (!cells) {
        return 0;
    }
 
    int count = 0;
 
    while (1) {
        cells[count] = malloc(2 * sizeof(int));
        if (!cells[count]) {
            // Clean up previously allocated memory
            for (int i = 0; i < count; i++) {
                free(cells[i]);
                cells[i] = NULL;
            }
            free(cells);
            cells = NULL;
            return 0;
        }
        cells[count][0] = x0;
        cells[count][1] = y0;
        count++;
 
        if (x0 == x1 && y0 == y1) {
            break;
        }
 
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
 
    *out_cells = cells;
    *out_count = count;
    return 1;
}

void draw_grid(int **cells, int count, int grid_size_h, int grid_size_w, int half_grid)
{
    char grid[grid_size_h][grid_size_w];

    for (int y = 0; y < grid_size_h; y++) {
        for (int x = 0; x < grid_size_w; x++) {
            grid[y][x] = '-';
        }
    }

    for (int i = 0; i < count; i++) {
        int gx = cells[i][0];
        int gy = cells[i][1];
        int px = gx + half_grid+1;
        int py = gy + half_grid+1;

        if (px >= 0 && px < grid_size_h && py >= 0 && py < grid_size_w) {
            if (i == count - 1) {
                grid[py][px] = '#';  // Mark the end point
            } else {
                grid[py][px] = ' ';
            }
        }
    }

    grid[half_grid+1][half_grid+1] = '*';  // Mark the origin

    for (int y = grid_size_h - 1; y >= 0; y--) {
        for (int x = 0; x < grid_size_w; x++) {
            putchar(grid[y][x]);
        }
        putchar('\n');
    }

}

/**
 * @brief Frees the memory allocated by `raycast` and sets the pointer to NULL.
 *
 * @param cells_ptr Pointer to the 2D array pointer returned by `raycast`.
 * @param count     Number of cells in the array.
 */
void free_raycast_result(int ***cells_ptr, int count)
{
    if (!cells_ptr || !*cells_ptr) return;

    int **cells = *cells_ptr;
    for (int i = 0; i < count; i++) {
        free(cells[i]);
    }
    free(cells);

    *cells_ptr = NULL;  // avoid dangling pointer
}

double for_one(double p) {
    return (0.8 * p) / ((0.8 * p) + (0.2 * (1 - p)));
}

double for_nul(double p) {
    return (0.2 * p) / ((0.2 * p) + (0.8 * (1 - p)));
}

int main(int argc, char **argv) {
    if (argc == 7) {
        int H = atoi(argv[1]); 
        int W = atoi(argv[2]);
        float cell_size = atof(argv[3]); 
        float x_robot = atof(argv[4]);
        float y_robot = atof(argv[5]); 
        float alpha_robot = atof(argv[6]);
        float occupancy_grid[H][W];
        int N_h = ceil(H/cell_size);
        int N_w = ceil(W/cell_size);
        // printf("Arguments: H = %i, W = %i, cell_size = %.1f, x_robot = %.1f, y_robot = %.1f, alpha_robot = %.1f\n", H, W, cell_size, x_robot, y_robot, alpha_robot);
        for (int i = 0; i < N_h; i++) {
            for (int j = 0; j < N_w; j++) {
                occupancy_grid[i][j] = 0.5f;
                float cell = occupancy_grid[i][j];
                // printf("%.1f ", cell);
            }
            // printf("\n");
        }
        float angle, distance, alpha_map = 0.0;
        while (1) {
            int r = scanf("%f %f", &angle, &distance);

            if (r == 2) {
                // printf("Angle = %.2f°, Distance = %.2f m\n", angle, distance);
                alpha_map = angle + alpha_robot;
                int **cells = NULL;
                int count = 0;

                raycast(alpha_map, distance, cell_size, &cells, &count);
                draw_grid(cells, count, N_h, N_w, (N_h)/2);
                
                free_raycast_result(&cells, count);
            } 
            else {
                printf("ERROR: invalid sensor data.\n");
                return 102;
            }
        }
        // for (int i = 1; i < argc; ++i) {
        //     fprintf(stdout, "Arg: %d is \"%s\"\n", i, argv[i]);
        // }

        return 0;
    } else {
        fprintf(stdout, "ERROR: invalid arguments.\n");
        return 103;
    }
    // if (argc < 2) return 0;

    // double P = 0.5;

    // for (int i = 1; i < argc; ++i) {
    //     int m = atoi(argv[i]);
    //     if (m == 0)
    //         P = for_nul(P);
    //     else if (m == 1)
    //         P = for_one(P);
    //     else {
    //         printf("Error: Invalid input.\n");
    //         return 1;
    //     }

    //     printf("%.5f", P);
    //     if (i < argc - 1) printf(" ");
    // }

    // printf("\n");
    // return 0;
}
