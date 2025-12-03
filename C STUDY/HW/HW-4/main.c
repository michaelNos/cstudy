#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>

#include "simage.h"
#include "robot.h"

#define PRIOR_P 0.5

// allocate initial map of given size, all cells PRIOR_P
static int map_alloc(Map *m, int w, int h)
{
    m->width  = w;
    m->height = h;
    m->cells  = malloc((size_t)w * (size_t)h * sizeof(double));
    if (!m->cells) return 0;
    for (int i = 0; i < w * h; ++i)
        m->cells[i] = PRIOR_P;
    return 1;
}

// grow map only in +X/+Y directions to at least new_w x new_h
int map_resize_up(Map *m, int new_w, int new_h)
{
    if (new_w <= m->width && new_h <= m->height)
        return 1; // nothing to do

    if (new_w < m->width)  new_w = m->width;
    if (new_h < m->height) new_h = m->height;

    double *new_cells = malloc((size_t)new_w * (size_t)new_h * sizeof(double));
    if (!new_cells) return 0;

    // initialise everything to PRIOR_P
    for (int i = 0; i < new_w * new_h; ++i)
        new_cells[i] = PRIOR_P;

    // copy existing cells to same logical coordinates
    for (int y = 0; y < m->height; ++y) {
        for (int x = 0; x < m->width; ++x) {
            int old_idx = (m->height - 1 - y) * m->width + x;
            int new_idx = (new_h   - 1 - y) * new_w      + x;
            new_cells[new_idx] = m->cells[old_idx];
        }
    }

    free(m->cells);
    m->cells  = new_cells;
    m->width  = new_w;
    m->height = new_h;
    return 1;
}

static void map_free(Map *m)
{
    free(m->cells);
    m->cells = NULL;
    m->width = m->height = 0;
}

typedef struct {
    int x;
    int y;
    double alpha_deg;
} StartPose;

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "ERROR: invalid arguments\n");
        return 103;
    }

    char *endptr = NULL;
    double cell_size = strtod(argv[1], &endptr);
    if (!endptr || *endptr != '\0' || cell_size <= 0.0) {
        fprintf(stderr, "ERROR: invalid arguments\n");
        return 103;
    }
    const char *basename = argv[2];

    // read starting poses from stdin (until EOF)
    StartPose *poses = NULL;
    int pose_cap = 0;
    int pose_cnt = 0;

    while (1) {
        StartPose sp;
        int r = scanf("%d %d %lf", &sp.x, &sp.y, &sp.alpha_deg);
        if (r == EOF)
            break; // end of input
        if (r != 3 || sp.x < 0 || sp.y < 0 ||
            sp.alpha_deg < 0.0 || sp.alpha_deg > 360.0) {
            free(poses);
            fprintf(stderr, "ERROR: invalid stdin data\n");
            return 104;
        }
        if (pose_cnt == pose_cap) {
            int new_cap = pose_cap ? pose_cap * 2 : 4;
            StartPose *tmp = realloc(poses, (size_t)new_cap * sizeof(StartPose));
            if (!tmp) {
                free(poses);
                fprintf(stderr, "ERROR: unknown\n");
                return 100;
            }
            poses = tmp;
            pose_cap = new_cap;
        }
        poses[pose_cnt++] = sp;
    }

    int N = pose_cnt;
    if (N <= 0) {
        // no robots – still output a 2x2 unknown map
        Map map = {0};
        if (!map_alloc(&map, 2, 2)) {
            fprintf(stderr, "ERROR: unknown\n");
            return 100;
        }
        for (int i = 0; i < map.width * map.height; ++i) {
            double p = map.cells[i];
            if (p > 0.5)      map.cells[i] = 1.0;
            else if (p < 0.5) map.cells[i] = 0.0;
            else              map.cells[i] = 0.5;
        }
        if (saveMapAsImage1D("out.bmp", map.cells, map.height, map.width) != 0) {
            fprintf(stderr, "ERROR: BMP image export failure\n");
            map_free(&map);
            return 106;
        }
        map_free(&map);
        return 0;
    }

    Map shared_map = (Map){0};
    if (!map_alloc(&shared_map, 2, 2)) {
        free(poses);
        fprintf(stderr, "ERROR: unknown\n");
        return 100;
    }

    pthread_mutex_t map_mutex;
    if (pthread_mutex_init(&map_mutex, NULL) != 0) {
        free(poses);
        map_free(&shared_map);
        fprintf(stderr, "ERROR: unknown\n");
        return 100;
    }

    pthread_t *threads = malloc((size_t)N * sizeof(pthread_t));
    RobotArgs *args    = malloc((size_t)N * sizeof(RobotArgs));
    if (!threads || !args) {
        free(threads);
        free(args);
        free(poses);
        map_free(&shared_map);
        pthread_mutex_destroy(&map_mutex);
        fprintf(stderr, "ERROR: unknown\n");
        return 100;
    }

    // prepare thread arguments and create threads
    for (int i = 0; i < N; ++i) {
        args[i].id         = i;
        args[i].x          = poses[i].x;
        args[i].y          = poses[i].y;
        args[i].alpha_deg  = poses[i].alpha_deg;
        args[i].cell_size  = cell_size;
        args[i].basename   = basename;
        args[i].map        = &shared_map;
        args[i].map_mutex  = &map_mutex;

        if (pthread_create(&threads[i], NULL, robot_thread, &args[i]) != 0) {
            fprintf(stderr, "ERROR: unknown\n");
            free(threads);
            free(args);
            free(poses);
            map_free(&shared_map);
            pthread_mutex_destroy(&map_mutex);
            return 100;
        }
    }

    // wait for all robots
    for (int i = 0; i < N; ++i)
        pthread_join(threads[i], NULL);

    free(threads);
    free(args);
    free(poses);

    // threshold shared map and export BMP
    for (int i = 0; i < shared_map.width * shared_map.height; ++i) {
        double p = shared_map.cells[i];
        if (p > 0.5)      shared_map.cells[i] = 1.0;
        else if (p < 0.5) shared_map.cells[i] = 0.0;
        else              shared_map.cells[i] = 0.5;
    }

    if (saveMapAsImage1D("out.bmp", shared_map.cells,
                         shared_map.height, shared_map.width) != 0) {
        fprintf(stderr, "ERROR: BMP image export failure\n");
        map_free(&shared_map);
        pthread_mutex_destroy(&map_mutex);
        return 106;
    }

    map_free(&shared_map);
    pthread_mutex_destroy(&map_mutex);
    return 0;
}
