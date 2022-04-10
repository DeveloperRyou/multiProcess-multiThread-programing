#include "pooling.h"
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc == 3)
	{
		// set clock
		clock_t start, end;
		start = clock();

		// set process number
		int process_num;
		process_num = atoi(argv[2]);

		// set process array
		pid_t *pids;
		pids = malloc_array(process_num);

		// set pipe array
		int **pipes;
		pipes = malloc_array_2D(process_num, 2);
		for (int i=0;i<process_num;i++)
			if (pipe(pipes[i]) == -1)
				exit(1);

		// make child process
		for (int process_index=0;process_index<process_num;process_index++)
		{
			pids[process_index] = fork();
			if (pids[process_index] < 0)
				return -1;
			else if (pids[process_index] == 0) // child process
			{
				// change standard io to pipe
				dup2(pipes[process_index][0], STDIN_FILENO);
				dup2(pipes[process_index][1], STDOUT_FILENO);
				execl("./program1", "./program1", argv[1], "childProcess"); // execute program 1
				exit(1);
			}
		}

		// input infomation from standard
		int H, W, N;
		stdin_info(&H, &W, &N);

		// malloc memory to store array
		int **array;
		array = malloc_array_2D(H, W);

		// input array from standard
		stdin_array(array, H, W);

		// malloc memory to store array after pooling
		int **pooled_array;
		pooled_array = malloc_array_2D(H/N, W/N);

		// set values to distribute
		int process_node_size;
		process_node_size = (H/N)*(W/N);

		// send data to child process
		int processed_node;
		processed_node = 0;
		for (int process_index=0;process_index<process_num;process_index++)
		{
			// set width of array to process in current process
			int width;
			width = (process_node_size - processed_node) / (process_num - process_index);
			// change standard io to pipe
			dup2(pipes[process_index][1], STDOUT_FILENO);
			stdout_info(N, width * N, N);
			stdout_array_st(array, N, width * N, processed_node, W); // if width == 0, child process will finish
			processed_node += width;
		}

		// receive data to child process
		processed_node = 0;
		for (int process_index=0;process_index<process_num;process_index++)
		{
			// set width of array
			int width;
			width = (process_node_size - processed_node) / (process_num - process_index);
			if (width == 0)
				continue;
			// change standard io to pipe
			dup2(pipes[process_index][0], STDIN_FILENO);
			stdin_arrayline_st(pooled_array, N, width, processed_node, W/N);
			processed_node += width;
		}

		// output array after pooling
		dup2(0, STDIN_FILENO);
		dup2(1, STDOUT_FILENO);
		end = clock();
		stdout_time(start, end);
		stdout_array(pooled_array, H/N, W/N);

		// free array
		free_array(pids);
		free_array_2D(pipes, process_num);
		free_array_2D(array, H);
		free_array_2D(pooled_array, H);
	}
	return 0;
}