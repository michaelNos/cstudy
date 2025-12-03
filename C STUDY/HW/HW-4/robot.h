#ifndef ROBOT_H
#define ROBOT_H

#include <pthread.h>

typedef struct {
    int width;
    int height;
    double *cells;
} Map;

typedef struct {
    int id;
    int x;
    int y;
    double alpha_deg;          // robot orientation in degrees (0–360)
    double cell_size;          // size of one cell in meters
    const char *basename;      // base name of per-robot files
    Map *map;                  // shared occupancy map
    pthread_mutex_t *map_mutex; // mutex protecting the shared map
} RobotArgs;

// convert logical (x,y) with origin at bottom-left to linear index
static inline int map_index(const Map *m, int x, int y)
{
    // rows stored from top (max y) to bottom (y = 0)
    return (m->height - 1 - y) * m->width + x;
}

// implemented in main.c, grows map in +X/+Y directions (keeps old data)
int map_resize_up(Map *m, int new_w, int new_h);

// thread entry function
void *robot_thread(void *arg);

#endif
