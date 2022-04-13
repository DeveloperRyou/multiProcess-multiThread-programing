#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc == 4)
	{
		int H, W, N;
		H = atoi(argv[1]);
		W = atoi(argv[2]);
		N = atoi(argv[3]);
		printf("%d %d %d\n", H, W, N);
		srand(time(0));
		int num;
		for (int i=0;i<H;i++)
		{
			num = rand() % 1000;
			printf("%d", num);
			for (int j=1;j<W;j++)
			{
				num = rand() % 1000;
				printf(" %d", num);
			}
			printf("\n");
		}
	}
}