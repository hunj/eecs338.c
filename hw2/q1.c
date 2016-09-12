/**
	Hun Jae Lee (hxl224)
	EECS338: Homework #2 Question 1
	Due 160914 Wed

	- Description:
	Creates one parent with two childrens, and display the IDs in the order in which the processes are created.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	pid_t pid1, pid2;

	printf("Process 0: %d\tParent: %d\n", getpid(), getppid());
	fflush(stdout);

	/* fork a child process */
	pid1 = fork();	
	pid2 = fork();
	
	// Assignment does not require fork error check (pid < 0)
	if (pid1 == 0 && pid2 != 0) { 
		printf("Process 1: %d\tParent: %d\n", getpid(), getppid());
		fflush(stdout);

	}
	else if (pid1 != 0 && pid2 == 0) {
		printf("Process 2: %d\tParent: %d\n", getpid(), getppid());
		fflush(stdout);
	}
	else {
		wait(NULL);
	}
    return 0;
}
