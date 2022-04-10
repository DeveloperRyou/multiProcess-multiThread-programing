#ifndef POOLING_H
# define POOLING_H

#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// io.c
void stdin_info(int *H, int *W, int *N);
void stdin_array(int **array, int H, int W);
void pipein_array_st(FILE *fp, int **array, int N, int W, int start, int max_width);
void stdout_time(clock_t start, clock_t end);
void stdout_array(int **array, int H, int W);
void pipeout_info(FILE *fp, int H, int W, int N);
void pipeout_array_st(FILE *fp, int **array, int N, int W, int start, int max_width);

// malloc_array.c
int **malloc_array_2D(int H, int W);
pid_t *malloc_array_pid(int W);
void free_array_2D(int **array, int H);
void free_array(int *array);

// pooling.c
void pooling(int **pooled_array, int **array, int y, int x, int N, char *type);

#endif