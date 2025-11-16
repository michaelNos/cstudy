#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PRIOR_P 0.5f

// ---------- Bayes updates ----------
static inline float upd_occ(float p){ return (0.8f*p)/((0.8f*p)+(0.2f*(1.0f-p))); }
static inline float upd_free(float p){ return (0.2f*p)/((0.2f*p)+(0.8f*(1.0f-p))); }

// ---------- Raycast (given) ----------
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
    int **cells = (int**)malloc(max_cells * sizeof(int*));
    if (!cells) return 0;

    int count = 0;
    while (1) {
        cells[count] = (int*)malloc(2 * sizeof(int));
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

static void free_raycast_result(int ***cells_ptr, int count){
    if (!cells_ptr || !*cells_ptr) return;
    for (int i = 0; i < count; i++) free((*cells_ptr)[i]);
    free(*cells_ptr);
    *cells_ptr = NULL;
}

// ---------- Dynamic map (heap) ----------
typedef struct {
    int h, w;        // rows, cols
    float **a;       // top row = index 0
} Map;

static int map_alloc(Map *m, int h, int w){
    m->h = h; m->w = w;
    m->a = (float**)malloc(h * sizeof(float*));
    if (!m->a) return 0;
    for (int r = 0; r < h; r++){
        m->a[r] = (float*)malloc(w * sizeof(float));
        if (!m->a[r]) {
            for (int k = 0; k < r; k++) free(m->a[k]);
            free(m->a);
            m->a = NULL;
            return 0;
        }
        for (int c = 0; c < w; c++) m->a[r][c] = PRIOR_P;
    }
    return 1;
}

static void map_free(Map *m){
    if (!m->a) return;
    for (int r = 0; r < m->h; r++) free(m->a[r]);
    free(m->a);
    m->a = NULL; m->h = m->w = 0;
}

// ensure map size >= (new_h x new_w); keep bottom fixed (grow adds rows on top)
static int map_ensure(Map *m, int new_h, int new_w){
    if (new_h <= m->h && new_w <= m->w) return 1;

    int H = (new_h > m->h) ? new_h : m->h;
    int W = (new_w > m->w) ? new_w : m->w;

    Map nm = {0};
    if (!map_alloc(&nm, H, W)) return 0;

    // copy old into bottom-left: old row r -> new row (offset + r), offset = H - m->h
    int roff = H - m->h;
    for (int r = 0; r < m->h; r++){
        for (int c = 0; c < m->w; c++){
            nm.a[roff + r][c] = m->a[r][c];
        }
    }

    map_free(m);
    *m = nm;
    return 1;
}

// convert (gx,gy) bottom-left coords -> array indices
static inline int row_from_gy(const Map *m, int gy){ return (m->h - 1) - gy; }

// ---------- Main ----------
int main(int argc, char **argv){
    if (argc != 3){
        fprintf(stderr, "ERROR: invalid arguments\n");
        return 103;
    }

    double cell_size = atof(argv[1]);
    double alpha_robot = atof(argv[2]);
    if (cell_size <= 0.0 || alpha_robot < 0.0 || alpha_robot > 360.0){
        fprintf(stderr, "ERROR: invalid arguments\n");
        return 103;
    }

    // initial 2x2 map
    Map M = {0};
    if (!map_alloc(&M, 2, 2)){
        fprintf(stderr, "ERROR: unknown\n");
        return 100;
    }

    // robot at (1,1)
    int rx = 1, ry = 1;
    // init values:
    // (0,0)=1.0, (0,1)=1.0, (1,0)=1.0, robot (1,1)=0.0
    M.a[row_from_gy(&M, 0)][0] = 1.0f; // (0,0)
    M.a[row_from_gy(&M, 1)][0] = 1.0f; // (0,1)
    M.a[row_from_gy(&M, 0)][1] = 1.0f; // (1,0)
    M.a[row_from_gy(&M, 1)][1] = 0.0f; // (1,1) robot cell

    // input parsing: tokens separated by spaces until EOF
    char tok[64];
    while (1){
        int s = scanf("%63s", tok);
        if (s == EOF) break;
        if (s != 1){ fprintf(stderr, "ERROR: invalid sensor data\n"); map_free(&M); return 102; }

        if (!strcmp(tok, "right") || !strcmp(tok, "left") || !strcmp(tok, "up") || !strcmp(tok, "down")){
            // move robot by one cell
            if (!strcmp(tok, "right")) rx += 1;
            else if (!strcmp(tok, "left")) rx -= 1;
            else if (!strcmp(tok, "up")) ry += 1;
            else ry -= 1; // "down"

            if (rx < 0 || ry < 0){
                // spec says moves are valid; negative would violate "grows only positive"
                fprintf(stderr, "ERROR: invalid sensor data\n");
                map_free(&M);
                return 102;
            }
            // ensure map can include robot cell
            if (!map_ensure(&M, ry + 1, rx + 1)){
                fprintf(stderr, "ERROR: unknown\n");
                map_free(&M);
                return 100;
            }
            // mark robot cell as known free
            M.a[row_from_gy(&M, ry)][rx] = 0.0f;
        } else {
            // token should be angle (float), next token is distance (float)
            char *endp = NULL;
            double angle = strtod(tok, &endp);
            if (!tok[0] || *endp != '\0'){ fprintf(stderr, "ERROR: invalid sensor data\n"); map_free(&M); return 102; }

            if (scanf("%63s", tok) != 1){ fprintf(stderr, "ERROR: invalid sensor data\n"); map_free(&M); return 102; }
            double distance = strtod(tok, &endp);
            if (!tok[0] || *endp != '\0'){ fprintf(stderr, "ERROR: invalid sensor data\n"); map_free(&M); return 102; }

            double alpha_map = alpha_robot + angle;

            int **cells = NULL;
            int count = 0;
            if (!raycast(alpha_map, distance, cell_size, &cells, &count)){
                fprintf(stderr, "ERROR: raycast failure\n");
                map_free(&M);
                return 101;
            }

            // ensure map can hold all gx,gy
            int need_w = M.w, need_h = M.h;
            for (int i = 0; i < count; i++){
                int gx = rx + cells[i][0];
                int gy = ry + cells[i][1];
                if (gx < 0 || gy < 0){ free_raycast_result(&cells, count); fprintf(stderr, "ERROR: invalid sensor data\n"); map_free(&M); return 102; }
                if (gx + 1 > need_w) need_w = gx + 1;
                if (gy + 1 > need_h) need_h = gy + 1;
            }
            if (!map_ensure(&M, need_h, need_w)){
                fprintf(stderr, "ERROR: unknown\n");
                free_raycast_result(&cells, count);
                map_free(&M);
                return 100;
            }

            // apply Bayesian updates
            for (int i = 0; i < count; i++){
                int gx = rx + cells[i][0];
                int gy = ry + cells[i][1];
                int row = row_from_gy(&M, gy);
                int col = gx;
                float p = M.a[row][col];
                M.a[row][col] = (i == count - 1) ? upd_occ(p) : upd_free(p);
            }

            free_raycast_result(&cells, count);
        }
    }

    // write out.txt
    FILE *f = fopen("out.txt", "w");
    if (!f){ fprintf(stderr, "ERROR: unknown\n"); map_free(&M); return 100; }

    int robot_row = row_from_gy(&M, ry), robot_col = rx;
    for (int r = 0; r < M.h; r++){
        for (int c = 0; c < M.w; c++){
            if (r == robot_row && c == robot_col){ fputc('*', f); continue; }
            float p = M.a[r][c];
            if (fabsf(p - 0.5f) < 1e-6f) fputc('-', f);
            else if (p > 0.5f)          fputc('#', f);
            else                        fputc(' ', f);
        }
        fputc('\n', f);
    }
    fclose(f);
    map_free(&M);
    return 0;
}
