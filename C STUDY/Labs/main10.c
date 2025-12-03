#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/************************************************************
 * EXERCISE 1 – pthread_join()
 ************************************************************/
void* ex1_thread(void *arg) {
    printf("[Ex1] Thread running.\n");
    return NULL;
}

void run_exercise_1() {
    pthread_t t;
    pthread_create(&t, NULL, ex1_thread, NULL);

    printf("[Ex1] Main thread.\n");

    // Uncomment to see difference:
    pthread_join(t, NULL);
}

/************************************************************
 * EXERCISE 2 – Create 5 threads printing index
 ************************************************************/
void* ex2_printIndex(void *arg) {
    int id = *(int*)arg;
    printf("[Ex2] Thread index: %d\n", id);
    return NULL;
}

void run_exercise_2() {
    pthread_t threads[5];
    int ids[5];

    for (int i = 0; i < 5; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, ex2_printIndex, &ids[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }
}

/************************************************************
 * TASK 3.1 – Global max + global mutex
 ************************************************************/
int t31_numbers[] = {4, 7, 1, 9, 2};
int t31_globalMax = 0;
pthread_mutex_t t31_lock;

void* t31_updateMax(void* arg) {
    int *v = (int*)arg;

    pthread_mutex_lock(&t31_lock);
    if (*v > t31_globalMax)
        t31_globalMax = *v;
    pthread_mutex_unlock(&t31_lock);

    return NULL;
}

void run_task_31() {
    pthread_t threads[5];
    pthread_mutex_init(&t31_lock, NULL);

    for (int i = 0; i < 5; i++)
        pthread_create(&threads[i], NULL, t31_updateMax, &t31_numbers[i]);

    for (int i = 0; i < 5; i++)
        pthread_join(threads[i], NULL);

    printf("[3.1] Final max = %d\n", t31_globalMax);
    pthread_mutex_destroy(&t31_lock);
}

/************************************************************
 * TASK 3.2 – Using struct ThreadArgs
 ************************************************************/
typedef struct {
    int value;
    int* globalMaxPtr;
    pthread_mutex_t* lockPtr;
} ThreadArgs;

void* t32_updateMax(void* arg) {
    ThreadArgs* a = (ThreadArgs*)arg;

    pthread_mutex_lock(a->lockPtr);
    if (a->value > *(a->globalMaxPtr))
        *(a->globalMaxPtr) = a->value;
    pthread_mutex_unlock(a->lockPtr);

    free(a);
    return NULL;
}

void run_task_32() {
    int numbers[] = {4, 7, 1, 9, 2};
    int globalMax = 0;
    pthread_mutex_t lock;
    pthread_t threads[5];

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < 5; i++) {
        ThreadArgs* args = malloc(sizeof(ThreadArgs));
        args->value = numbers[i];
        args->globalMaxPtr = &globalMax;
        args->lockPtr = &lock;

        pthread_create(&threads[i], NULL, t32_updateMax, args);
    }

    for (int i = 0; i < 5; i++)
        pthread_join(threads[i], NULL);

    printf("[3.2] Final max = %d\n", globalMax);
    pthread_mutex_destroy(&lock);
}

/************************************************************
 * TASK 3.3 – Returning a value from each thread
 ************************************************************/
void* t33_updateMax(void* arg) {
    ThreadArgs* a = (ThreadArgs*)arg;

    pthread_mutex_lock(a->lockPtr);
    if (a->value > *(a->globalMaxPtr))
        *(a->globalMaxPtr) = a->value;
    pthread_mutex_unlock(a->lockPtr);

    int* result = malloc(sizeof(int));
    *result = a->value;

    free(a);
    return result;
}

void run_task_33() {
    int numbers[] = {4, 7, 1, 9, 2};
    int globalMax = 0;
    pthread_mutex_t lock;
    pthread_t threads[5];
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < 5; i++) {
        ThreadArgs* args = malloc(sizeof(ThreadArgs));
        args->value = numbers[i];
        args->globalMaxPtr = &globalMax;
        args->lockPtr = &lock;

        pthread_create(&threads[i], NULL, t33_updateMax, args);
    }

    for (int i = 0; i < 5; i++) {
        void *ret;
        pthread_join(threads[i], &ret);

        int* val = (int*)ret;
        printf("[3.3] Thread for %d returned %d\n", numbers[i], *val);
        free(val);
    }

    printf("[3.3] Final max = %d\n", globalMax);
    pthread_mutex_destroy(&lock);
}

/************************************************************
 * MAIN – run all parts
 ************************************************************/
int main() {
    printf("\n--- EXERCISE 1 ---\n");
    run_exercise_1();

    printf("\n--- EXERCISE 2 ---\n");
    run_exercise_2();

    printf("\n--- TASK 3.1 ---\n");
    run_task_31();

    printf("\n--- TASK 3.2 ---\n");
    run_task_32();

    printf("\n--- TASK 3.3 ---\n");
    run_task_33();

    return 0;
}
