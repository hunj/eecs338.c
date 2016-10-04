/**
	Hun Jae Lee (hxl224)
	EECS338 HW4
	Due 161003

	Description:
	Shubert function to find the minimum value for -2.0 ≤ x1, x2 ≤ 2.0
	Using fork() with pipe communication
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include "shubert.c"

#define BUFFER_SIZE 64
#define READ_END	0
#define WRITE_END	1

double shubert(double x1, double x2);

int main(int argc, char* argv[]) {
	// variable setup for shubert function
	double x1, x2, y;	// y = shubert(x1, x2)
	double parent_min, child_min;

	// pipe environment setup
	int fd[2];
	char write_value[BUFFER_SIZE];
	char read_value[BUFFER_SIZE];

	// fork environment setup
	pid_t pid;

	// set up pipe for comms
	if (pipe(fd) == -1) {
		fprintf(stderr, "Pipe failed");
		return -1;
	}
	
	// fork a process
	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Fork failed");
		return -1;
	} else if (pid == 0) {
		// chile process uses -2.0 ≤ x2 ≤ 0.0
		for (x1 = -2; x1 <= 2; x1 += 0.05) {
			for (x2 = -2; x2 <= 0; x2 += 0.05) {
				y = shubert(x1, x2);
				if (y < child_min)
					child_min = y;
			}
		}
		printf("Child:\t%f\n", child_min);

		// close the unused end of the pipe
		close(fd[READ_END]);
		sprintf(write_value, "%f", child_min);

		// write to the pipe
		write(fd[WRITE_END], write_value, strlen(write_value)+1);

		// close the write end of the pipe
		close(fd[WRITE_END]);

	} else {
		// parent process uses 0.0 ≤ x2 ≤ 2.0
		for (x1 = -2; x1 <= 2; x1 += 0.05) {
			for (x2 = 0; x2 <= 2; x2 += 0.05) {
				y = shubert(x1, x2);
				if (y < parent_min)
					parent_min = y;
			}
		}
		printf("Parent:\t%f\n", parent_min);

		// once the child process writes to the pipe and terminates,
		// compare with parent's min and print out the global min
		wait(NULL);

		// close the unused end of the pipe
		close(fd[WRITE_END]);

		// read data & close the pipe
		read(fd[READ_END], read_value, BUFFER_SIZE);
		close(fd[READ_END]);

		child_min = atof(read_value);

		if (parent_min <= child_min)
			printf("MIN:\t%f\n", parent_min);
		else 
			printf("MIN:\t%f\n", child_min);
	}

	return 0;
}
