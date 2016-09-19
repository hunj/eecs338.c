/**
	Hun Jae Lee (hxl224)
	EECS338: Homework #3 Question 1
	Due 160921 Wed

	- Description:
	A simple custom shell program, as described in the assignment.
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE	80			// 80x24 is the way to go :)

int main() {
	char line[50];				// command line has max 40 arguments
	char *args[MAX_LINE/2 + 1];	// maximum arguments
	int should_run = 1;			// a sentinel int value
	int pid;					// pid variable to use later when forking

	while (should_run) {
		printf("hsh> ");		// hsh stands for Hunjae SHell
		fflush(stdout);

		// 1. read user input; parse the command & arguments.
		gets(line);
		if (*line == NULL) {
			printf("No command entered.\n");
			exit(-1);
		}
		args[0] = strtok(line, " ");
		int i = 0;
		while (args[i] != NULL) {
			args[++i] = strtok(NULL, " ");
		}

		// If the command was "exit", exit.
		if (!strcmp(args[0], "exit")) {
			should_run = 0;
			printf("...Good bye!\n");
			fflush(stdout);
			return 0;
		}

		// 2. fork a child process. child process invokes execvp()
		pid = fork();
		if (pid < 0) {
			// 2-1. fork failed
			fprintf(stderr, "Fork failed!\n");
			return -1;
		} else if (pid == 0) {
			// 2-2. fork successful, child executes the command
			execvp(args[0], args);
		} else {
			// 2-3. fork successful, parent waits
			wait(NULL);
		}

		// 3. child executes execvp()
	}
}