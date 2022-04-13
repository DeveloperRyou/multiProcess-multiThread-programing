#include <string.h>

int pooling_avg(int **array, int y, int x, int N)
{
	long long avg;

	avg = 0;
	for (int i=0;i<N;i++)
		for (int j=0;j<N;j++)
			avg += array[y*N + i][x*N + j];
	avg = avg/(N*N);
	return (int)avg;
}

int pooling_min(int **array, int y, int x, int N)
{
	int min;

	min = 2147483647;
	for (int i=0;i<N;i++)
		for (int j=0;j<N;j++)
			if (min > array[y*N + i][x*N + j])
				min = array[y*N + i][x*N + j];
	return min;
}

int pooling_max(int **array, int y, int x, int N)
{
	int max;

	max = -1;
	for (int i=0;i<N;i++)
		for (int j=0;j<N;j++)
			if (max < array[y*N + i][x*N + j])
				max = array[y*N + i][x*N + j];
	return max;

}

void pooling(int **pooled_array, int **array, int y, int x, int N, char *type)
{
	for (int i=0;i<y;i++)
	{
		for (int j=0;j<x;j++)
		{
			if (strcmp("avg", type) == 0) // avg pooling
				pooled_array[i][j] = pooling_avg(array, i, j, N);
			else if (strcmp("min", type) == 0) // min pooling
				pooled_array[i][j] = pooling_min(array, i, j, N);
			else if (strcmp("max", type) == 0) // max pooling
				pooled_array[i][j] = pooling_max(array, i, j, N);
			else // exception handing
				pooled_array[i][j] = 0;
		}
	}
}

void pooling_thread(int **pooled_array, int **array, int N, int W, int start, int max_width, char *type)
{
	for (int i=0;i<W;i++)
	{
		int x, y;
		x = (start + i) % max_width;
		y = (start + i) / max_width;
		if (strcmp("avg", type) == 0) // avg pooling
			pooled_array[y][x] = pooling_avg(array, y, x, N);
		else if (strcmp("min", type) == 0) // min pooling
			pooled_array[y][x] = pooling_min(array, y, x, N);
		else if (strcmp("max", type) == 0) // max pooling
			pooled_array[y][x] = pooling_max(array, y, x, N);
		else // exception handing
			pooled_array[y][x] = 0;
	}
}