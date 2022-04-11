#include <stdio.h>
#include <time.h>

void stdin_info(int *H, int *W, int *N)
{
	scanf("%d %d %d", H, W, N);
}

void stdin_array(int **array, int H, int W)
{
	for (int i=0;i<H;i++)
		for (int j=0;j<W;j++)
			scanf("%d", &array[i][j]);
}

void stdin_array_st(int **array, int N, int W, int start, int max_width)
{
	// scan linear array -> array 2D
	int y, x;
	y = start / max_width;
	x = start % max_width;
	for (int i=0;i<W;i++)
		scanf("%d", &array[y + (x + i) / max_width][(x + i) % max_width]);
}

void stdout_time(clock_t start, clock_t end)
{
	printf("%d\n", start - end);
}

void stdout_array(int **array, int H, int W)
{
	for (int i=0;i<H;i++)
	{
		for (int j=0;j<W;j++)
			printf("%d ", array[i][j]);
		printf("\n");
	}
}

void stdout_info(int H, int W, int N)
{
	printf("%d %d %d\n", H, W, N);
}

void stdout_array_st(int **array, int N, int W, int start, int max_width)
{
	// print array 2D -> linear array
	int y, x;
	y = (start / (max_width / N)) * N;
	x = (start % (max_width / N)) * N;
	for (int i=0;i<N;i++)
	{
		for (int j=0;j<W;j++)
			printf("%d ", array[y + i + ((x + j) / max_width) * N][(x + j) % max_width]);
		printf("\n");
	}
}