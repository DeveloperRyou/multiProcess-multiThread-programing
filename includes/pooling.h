#ifndef POOLING_H
# define POOLING_H

#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#define MAX_THREAD 200
#define MAX_PROCESS 200

// io.c
void stdin_info(int *H, int *W, int *N);
void stdin_array(int **array, int start, int H, int W);
void stdout_time(struct timespec start, struct timespec end);
void stdout_array(int **array, int start, int H, int W);
void stdout_info(int H, int W, int N);

// malloc_array.c
int **malloc_array_2D(int H, int W);
pid_t *malloc_array_pid(int W);
pthread_t *malloc_array_pthread(int W);
void free_array_2D(int **array, int H);
void free_array(void *array);

// pooling.c
void pooling(int **pooled_array, int **array, int start, int y, int x, int N, char *type);

#endif