#include "pooling.h"

int main(int argc, char **argv)
{
	if (argc == 3)
	{
		/** Make Processes **/
		// set process number
		int process_num;
		process_num = atoi(argv[2]);
		if (process_num <= 0)
			return 0;
		if (process_num > MAX_PROCESS)
			process_num = MAX_PROCESS;

		// set process array
		pid_t *pids;
		pids = malloc_array_pid(process_num);
		if (pids == 0)
		{
			printf("[ERROR] : Pids Malloc Error\n");
			exit(1);
		}

		// set pipe array
		int **pipes_input;
		int **pipes_output;
		pipes_input = malloc_array_2D(process_num, 2);
		pipes_output = malloc_array_2D(process_num, 2);
		if (pipes_input == 0 || pipes_output == 0)
		{
			printf("[ERROR] : Pipes Malloc Error\n");
			exit(1);
		}
		for (int i=0;i<process_num;i++)
		{
			if (pipe(pipes_input[i]) == -1 || pipe(pipes_output[i]) == -1)
			{
				printf("[ERROR] : Pipe Create Error\n");
				exit(1);
			}
		}

		// make child process
		for (int process_index=0;process_index<process_num;process_index++)
		{
			pids[process_index] = fork();
			if (pids[process_index] < 0)
			{
				printf("[ERROR] : Process Create Error\n");
				exit(1);
			}
			else if (pids[process_index] == 0) // child process
			{
				// change standard io to pipe
				dup2(pipes_output[process_index][0], STDIN_FILENO);
				dup2(pipes_input[process_index][1], STDOUT_FILENO);
				execl("./program1", "./program1", argv[1], "childProcess", NULL); // execute program 1
				printf("[ERROR] : Execute Error\n");
				exit(1);
			}
		}

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
		if (array == 0)
		{
			printf("[ERROR] : Map Malloc Error\n");
			exit(1);
		}
		
		// set clock after stdin
		clock_t start, end;
		start = clock();

		// save standard io
		int temp_stdin = dup(STDIN_FILENO);
		int temp_stdout = dup(STDOUT_FILENO);

		// send data to child process
		int processed_line = 0;
		for (int process_index=0;process_index<process_num;process_index++)
		{
			// set width of array to process in current process
			int height = (H/N - processed_line) / (process_num - process_index);
			// change standard io to pipe
			dup2(pipes_output[process_index][1], STDOUT_FILENO);
			stdout_info(height*N, W, N);
			stdout_array(array, processed_line*N, height*N, W); // if height == 0, child process will finish
			fflush(stdout);
			processed_line += height;
		}

		// receive data to child process
		processed_line = 0;
		for (int process_index=0;process_index<process_num;process_index++)
		{
			// set width of array
			int height = (H/N - processed_line) / (process_num - process_index);
			if (height == 0)
				continue;
			// change standard io to pipe
			dup2(pipes_input[process_index][0], STDIN_FILENO);
			stdin_array(pooled_array, processed_line, height, W/N);
			processed_line += height;
		}

		/** Standard ouput **/
		// output array after pooling
		dup2(temp_stdin, STDIN_FILENO);
		dup2(temp_stdout, STDOUT_FILENO);
		end = clock();
		stdout_time(start, end);
		stdout_array(pooled_array, 0, H/N, W/N);

		// close fd
		for (int i=0;i<process_num;i++)
		{
			close(pipes_input[i][0]);
			close(pipes_input[i][1]);
			close(pipes_output[i][0]);
			close(pipes_output[i][1]);
		}

		// free array
		free_array(pids);
		free_array_2D(pipes_input, process_num);
		free_array_2D(pipes_output, process_num);
		free_array_2D(array, H);
		free_array_2D(pooled_array, H/N);
	}
	return 0;
}