#include "pooling.h"

int main(int argc, char **argv)
{
	// called from shell or process
	if (argc == 2 || argc == 3)
	{
		// set clock
		clock_t start, end;
		if (argc == 2)
			start = clock();

		// input infomation from standard
		int H, W, N;
		stdin_info(&H, &W, &N);
		if (H == 0 || W == 0 || N == 0)
			return 0;

		// malloc memory to store array
		int **array;
		array = malloc_array_2D(H, W);

		// input array from standard
		stdin_array(array, H, W);

		// malloc memory to store array after pooling
		int **pooled_array;
		pooled_array = malloc_array_2D(H/N, W/N);

		// do pooling
		pooling(pooled_array, array, H/N, W/N, N, argv[1]);

		// output array after pooling
		if (argc == 2)
		{
			end = clock();
			stdout_time(start, end);
		}
		stdout_array(pooled_array, H/N, W/N);
		
		// free array
		free_array_2D(array, H);
		free_array_2D(pooled_array, H/N);
	}
	return 0;
}