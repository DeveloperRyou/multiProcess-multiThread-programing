#include "pooling.h"

int main(int argc, char **argv)
{
	// called from shell or process
	if (argc == 2 || argc == 3)
	{
		/** Standard input **/
		// input infomation from standard
		int H, W, N;
		stdin_info(&H, &W, &N);
		if (H == 0 || W == 0 || N == 0)
			return 0;

		// malloc memory to store array
		int **array;
		array = malloc_array_2D(H, W);
		if (array == 0)
		{
			printf("[ERROR] : Map Malloc Error\n");
			exit(1);
		}

		// input array from standard
		stdin_array(array, 0, H, W);

		/** Process Data **/
		// malloc memory to store array after pooling
		int **pooled_array;
		pooled_array = malloc_array_2D(H/N, W/N);
		if (pooled_array == 0)
		{
			printf("[ERROR] : Map Malloc Error\n");
			exit(1);
		}

		// set clock after stdin
		struct timespec st, ed;
		if (argc == 2)
			clock_gettime(CLOCK_MONOTONIC, &st);
		
		// do pooling
		pooling(pooled_array, array, 0, H/N, W/N, N, argv[1]);
		
		/** Standard output **/
		// output array after pooling
		if (argc == 2)
		{
			clock_gettime(CLOCK_MONOTONIC, &ed);
			stdout_time(st, ed);
		}
		stdout_array(pooled_array, 0, H/N, W/N);
		
		// free array
		free_array_2D(array, H);
		free_array_2D(pooled_array, H/N);
	}
	return 0;
}