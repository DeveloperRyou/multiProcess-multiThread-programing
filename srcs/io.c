#include "pooling.h"

void stdin_info(int *H, int *W, int *N)
{
	scanf("%d %d %d", H, W, N);
}

void stdin_array(int **array, int start, int H, int W)
{
	for (int i=0;i<H;i++)
		for (int j=0;j<W;j++)
			scanf("%d", &array[start+i][j]);
}

void stdout_time(clock_t start, clock_t end)
{
	printf("%lld\n", 1000 * (end - start) / CLOCKS_PER_SEC);
}

void stdout_array(int **array, int start, int H, int W)
{
	for (int i=0;i<H;i++)
	{
		for (int j=0;j<W;j++)
			printf("%d ", array[start+i][j]);
		printf("\n");
	}
}

void stdout_info(int H, int W, int N)
{
	printf("%d %d %d\n", H, W, N);
}
