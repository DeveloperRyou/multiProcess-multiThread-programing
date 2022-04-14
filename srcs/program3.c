#include "pooling.h"

// set global variable for thread (memory share)
static int H, W, N;
static int **array;
static int **pooled_array;
static char *type;

// thread function
void* thread_excute(void *thread_argv)
{
	int start = ((int *)thread_argv)[0];
	int height = ((int *)thread_argv)[1];
	if (height == 0)
		return 0;

	// do pooling in thread
	pooling(pooled_array, array, start, height, W/N, N, type);
	return 0;
}

int main(int argc, char **argv)
{
	// called from shell or process
	if (argc == 3)
	{	
		/** Standard input **/
		// input infomation from standard
		stdin_info(&H, &W, &N);
		if (H == 0 || W == 0 || N == 0)
			return 0;

		// malloc memory to store array
		array = malloc_array_2D(H, W);
		if (array == 0)
		{
			printf("[ERROR] : Map Malloc Error\n");
			exit(1);
		}

		// input array from standard
		stdin_array(array, 0, H, W);

		// malloc memory to store array after pooling
		pooled_array = malloc_array_2D(H/N, W/N);
		if (array == 0)
		{
			printf("[ERROR] : Map Malloc Error\n");
			exit(1);
		}

		/** Make Threads **/
		// set thread number
		int thread_num;
		thread_num = atoi(argv[2]);
		if (thread_num <= 0)
			return 0;

		// set thread array
		pthread_t *pthreads;
		pthreads = malloc_array_pthread(thread_num);
		if (array == 0)
		{
			printf("[ERROR] : Pthreads Malloc Error\n");
			exit(1);
		}

		// malloc argument to pass to thread
		int **thread_argv;
		thread_argv = malloc_array_2D(thread_num, 2);
		if (array == 0)
		{
			printf("[ERROR] : Pthread_argv Malloc Error\n");
			exit(1);
		}
			
		// set clock after stdin
		clock_t start, end;
		start = clock();
		
		// set type
		type = argv[1];

		// make thread and send argument to thread
		int processed_line = 0;
		for (int thread_index=0;thread_index<thread_num;thread_index++)
		{
			// set width and processed_node of array to process in current thread
			thread_argv[thread_index][0] = processed_line;
			thread_argv[thread_index][1] = (H/N - processed_line) / (thread_num - thread_index);
			if (pthread_create(&pthreads[thread_index], 0, thread_excute, (void *)thread_argv[thread_index]) != 0)
			{
				printf("[ERROR] : Thread Create Error\n");
				exit(1);
			}
			processed_line += (H/N - processed_line) / (thread_num - thread_index);
		}

		// wait for thread until finished
		for (int thread_index=0;thread_index<thread_num;thread_index++)
		{
			if (pthread_join(pthreads[thread_index], 0) != 0)
			{
				printf("[ERROR] : Thread Join Error\n");
				exit(1);
			}
		}

		/** Standard output **/
		// output array after pooling
		end = clock();
		stdout_time(start, end);
		stdout_array(pooled_array, 0, H/N, W/N);
		
		// free array
		free_array(pthreads);
		free_array_2D(thread_argv, thread_num);
		free_array_2D(array, H);
		free_array_2D(pooled_array, H/N);
	}
	return 0;
}