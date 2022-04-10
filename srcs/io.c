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
			scanf("%d ", &array[i][j]);
}

void pipein_array_st(FILE *fp, int **array, int N, int W, int start, int max_width)
{
	int y, x;
	y = start / (max_width / N);
	x = start % (max_width / N);
	for (int i=0;i<W;i++)
		fscanf(fp, "%d ", &array[y + (x + i) / max_width][(x + i) % max_width]);
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

void pipeout_info(FILE *fp, int H, int W, int N)
{
	fprintf(fp, "%d %d %d\n", H, W, N);
}

void pipeout_array_st(FILE *fp, int **array, int N, int W, int start, int max_width)
{
	int y, x;
	y = (start / (max_width / N)) * N;
	x = (start % (max_width / N)) * N;
	for (int i=0;i<N;i++)
	{
		for (int j=0;j<W;j++)
			fprintf(fp, "%d ", array[y + i + (x + j) / max_width][(x + j) % max_width]);
		fprintf(fp, "\n");
	}
}