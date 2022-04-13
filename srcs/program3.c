#include "pooling.h"
#include <pthread.h>

// set global variable for thread (memory share)
static int H, W, N;
static int **array;
static int **pooled_array;
static char *type;

// thread function
void* thread_excute(void *thread_argv)
{
	int width = ((int *)thread_argv)[0];
	int processed_node = ((int *)thread_argv)[1];

	// do pooling in thread
	pooling_thread(pooled_array, array, N, width, processed_node, W/N, type);
}

int main(int argc, char **argv)
{
	// called from shell or process
	if (argc == 3)
	{
		// set clock
		clock_t start, end;
		start = clock();

		// set type
		type = argv[1];

		// input infomation from standard
		stdin_info(&H, &W, &N);
		if (H == 0 || W == 0 || N == 0)
			return 0;

		// malloc memory to store array
		array = malloc_array_2D(H, W);

		// input array from standard
		stdin_array(array, H, W);

		// malloc memory to store array after pooling
		pooled_array = malloc_array_2D(H/N, W/N);

		// set thread number
		int thread_num;
		thread_num = atoi(argv[2]);

		// set thread array
		pthread_t *pthreads;
		pthreads = malloc_array_pthread(thread_num);

		// malloc argument to pass to thread
		int **thread_argv;
		thread_argv = malloc_array_2D(thread_num, 2);

		// set values to distribute
		int process_node_size;
		process_node_size = (H/N)*(W/N);

		// make thread and send argument to thread
		int processed_node;
		processed_node = 0;
		for (int thread_index=0;thread_index<thread_num;thread_index++)
		{
			// set width and processed_node of array to process in current thread
			thread_argv[thread_index][0] = (process_node_size - processed_node) / (thread_num - thread_index);
			thread_argv[thread_index][1] = processed_node;
			if (pthread_create(&pthreads[thread_index], 0, thread_excute, (void *)thread_argv[thread_index]) < 0)
			{
				printf("[ERROR] : Thread Create Error\n");
				exit(1);
			}
			processed_node += thread_argv[thread_index][0];
		}

		// wait for thread until finished
		for (int thread_index=0;thread_index<thread_num;thread_index++)
		{
			void **res;
			pthread_join(pthreads[thread_index], res);
		}

		// output array after pooling
		end = clock();
		stdout_time(start, end);
		stdout_array(pooled_array, H/N, W/N);
		
		// free array
		free_array_2D(thread_argv, thread_num);
		free_array_2D(array, H);
		free_array_2D(pooled_array, H/N);
	}
	return 0;
}