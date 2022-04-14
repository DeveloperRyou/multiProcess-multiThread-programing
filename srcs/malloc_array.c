#include <stdlib.h>
#include <unistd.h>

int **malloc_array_2D(int H, int W)
{
	int **array;

	array = (int **)malloc(sizeof(int *) * H);
	for (int i=0;i<H;i++)
		array[i] = (int *)malloc(sizeof(int) * W);
	return array;
}

pid_t *malloc_array_pid(int W)
{
	pid_t *array;

	array = (pid_t *)malloc(sizeof(pid_t) * W);
	return array;
}

pthread_t *malloc_array_pthread(int W)
{
	pthread_t *array;

	array = (pthread_t *)malloc(sizeof(pthread_t) * W);
	return array;
}

void free_array_2D(int **array, int H)
{
	for (int i=0;i<H;i++)
		free(array[i]);
	free(array);
}

void free_array(void *array)
{
	free(array);
}
