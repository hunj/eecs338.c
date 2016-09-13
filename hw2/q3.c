/**
	Hun Jae Lee (hxl224)
	EECS338: Homework #2 Question 3
	Due 160914 Wed

	- Description:
	Creates three processes, where the 2nd process is the child of the 1st, and the parent of the 3rd.
	Process IDs are displayed in _REVERSE_ of created order.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	pid_t pid1, pid2;

	/* fork a child process */
	pid1 = fork();
	
	// Assignment does not require fork error check (pid < 0)
	if (pid1 == 0) {
		// fork!
		pid2 = fork();
		sleep(1);

		if (pid2 < 0) {
			fprintf(stderr, "Fork failed!\n");
			return -1;
		} else if (pid2 == 0) {
			printf("Process 3: %d\tParent: %d\n", getpid(), getppid());
			fflush(stdout);
		}
		else {
			wait(NULL);
			printf("Process 2: %d\tParent: %d\n", getpid(), getppid());
			fflush(stdout);
		}
	}
	else {
		wait(NULL);
		printf("Process 1: %d\tParent: %d\n", getpid(), getppid());
		fflush(stdout);
	}
	
    return 0;
}
