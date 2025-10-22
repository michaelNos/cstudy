#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define GRID_SIZE 21    // number of cells per side (must be odd)
#define HALF_GRID (GRID_SIZE / 2)

int raycast(double angle_deg, double distance_m, double cell_size_m, int ***out_cells, int *out_count);

void draw_grid(int **cells, int count);

void free_raycast_result(int ***cells, int count);

/**
 * @brief Entry point for the ASCII raycast test program.
 *
 * This program performs a raycast from the origin (0,0) using parameters
 * provided via command-line arguments, and prints an ASCII grid showing
 * the path of the ray.
 *
 * @param argc Number of command-line arguments. Must be 4.
 * @param argv Array of command-line arguments. doubles: angle, distance, cell size
 *
 * @return int Returns 0 on success, 1 on failure (e.g., invalid arguments or memory allocation failure).
 *
 * @note Example usage:
 *       ./hw02_raycast 45 10 1
 */
int main(int argc, char **argv)
{
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <angle_deg> <distance_m> <cell_size_m>\n", argv[0]);
        return EXIT_FAILURE;
    }
    double angle_deg = atof(argv[1]);
    double distance_m = atof(argv[2]);
    double cell_size_m = atof(argv[3]);

    int **cells = NULL;
    int count = 0;

    raycast(angle_deg, distance_m, cell_size_m, &cells, &count);

    printf("Ray angle = %.2f°, distance = %.2f m\n", angle_deg, distance_m);
    printf("Grid view (%dx%d):\n\n", GRID_SIZE, GRID_SIZE);

    draw_grid(cells, count);

    free_raycast_result(&cells, count);
    return EXIT_SUCCESS;
}

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
 * @return            1 on success, 0 on failure (e.g., allocation failure)
 */
int raycast(double angle_deg, double distance_m, double cell_size_m, int ***out_cells, int *out_count)
{
    if (!out_cells || !out_count) {
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

/**
 * @brief Draws an ASCII grid with the ray path highlighted.
 *
 * Origin (0,0) is marked as 'O', the cells traversed by the ray
 * are marked as 'X', and empty cells as '.'.
 *
 * @param cells Pointer to the 2D array of grid coordinates returned by `raycast`.
 * @param count Number of cells in the array.
 */
void draw_grid(int **cells, int count)
{
    char grid[GRID_SIZE][GRID_SIZE];

    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            grid[y][x] = '-';
        }
    }

    for (int i = 0; i < count; i++) {
        int gx = cells[i][0];
        int gy = cells[i][1];
        int px = gx + HALF_GRID;
        int py = gy + HALF_GRID;

        if (px >= 0 && px < GRID_SIZE && py >= 0 && py < GRID_SIZE) {
            grid[py][px] = 'X';
        }
    }

    grid[HALF_GRID][HALF_GRID] = 'O';

    for (int y = GRID_SIZE - 1; y >= 0; y--) {
        for (int x = 0; x < GRID_SIZE; x++) {
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
