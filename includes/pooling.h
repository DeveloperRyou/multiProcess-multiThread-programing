#ifndef POOLING_H
# define POOLING_H

#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// io.c
void stdin_info(int *H, int *W, int *N);
void stdin_array(int **array, int H, int W);
void stdin_array_st(int **array, int N, int W, int start, int max_width);
void stdout_time(clock_t start, clock_t end);
void stdout_array(int **array, int H, int W);
void stdout_info(int H, int W, int N);
void stdout_array_st(int **array, int N, int W, int start, int max_width);

// malloc_array.c
int **malloc_array_2D(int H, int W);
pid_t *malloc_array_pid(int W);
pthread_t *malloc_array_pthread(int W);
void free_array_2D(int **array, int H);
void free_array(void *array);

// pooling.c
void pooling(int **pooled_array, int **array, int y, int x, int N, char *type);
void pooling_thread(int **pooled_array, int **array, int start, int y, int x, int N, char *type);

#endif