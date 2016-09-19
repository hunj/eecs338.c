/**
	Hun Jae Lee (hxl224)
	EECS338: Homework #3 Question 2
	Due 160921 Wed

	- Description:
	Parallel computation example that does the following:
	1. Takes input N (where 1 <= N <= 4)
	2. Fork N processes, parallelly count up to 1,000,000,000 using N processes
	3. Each process reports the time taken to count
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define N 1000000000

int main() {
	// environment setup
	long int i;
	long int processes;
	long long int x = 0;
	int target_sum;
	int input = 1;
	pid_t pid;
	struct timeval start_time[4], stop_time[4], elapsed_time[4];  // timers

	// ask user for number of processes
	char line[50];
	printf("How many processes? ");
	gets(line);
	input = atoi(line);
	
	// validate input
	if (input < 1 && 4 < input) {
		fprintf(stderr, "Number of processes must be from 1 to 4! Aborting..\n");
		return -1;
	}

	for (processes = 1; processes <= input; processes++) {
		pid = fork();
		if (pid < 0) {
			fprintf(stderr, "Fork failed! Aborting..\n");
			return -1;
		} else if (pid == 0) {
			// child process
			printf("Process %ld (%d) started.\n", processes, getpid());
			fflush(stdout);
			
			// record starttime, compute, record endtime, subtract time diff
			gettimeofday(&start_time[processes-1],NULL);
			for (i = 0, x = 0; i < N/input; i++) {
				x = x + 1;
			}
			gettimeofday(&stop_time[processes-1],NULL);
			timersub(&stop_time[processes-1], &start_time[processes-1], &elapsed_time[processes-1]);

			// give user pretty message
			printf("Process %ld (%d) total time was %f seconds. x = %lld.\n", processes, getpid(), elapsed_time[processes-1].tv_sec+elapsed_time[processes-1].tv_usec/1000000.0, x);
			fflush(stdout);
			break;
		} else {
			continue;
		}
		
	}
	wait(NULL);
	return 0;
}