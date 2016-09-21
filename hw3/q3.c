/**
	Hun Jae Lee (hxl224)
	EECS338: Homework #3 Question 3
	Due 160921 Wed

	- Description:
	1. Creates shared memory for a string
	2. Forks a child process that writes a string to the shared memory
	3. Parent process then reads/prints the value created by the child.
	
	Note:	Memory is created & unlinked in the parent process.
			The child can automatically have the same pointer.
*/

// Required libraries
#include <unistd.h>
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main() {
	// environment & dummy string setup
	const int SIZE = 4096;
	const char *name = "hunjae_memory";
	const char *message = "Lorem ipsum dolor sit amet...";

	int shm_fd;
	void *ptr;

	/// 1. Create, configure size, and map shared memory segment
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd,SIZE);

	ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed!");
		return -1;
	}

	/// 2. Fork a child that writes a string to the shared memory
	pid_t pid;

	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Fork failed, aborting.\n");
		return -1;
	} else if (pid == 0) {
		// child process

		// open the shared memory segment
		shm_fd = shm_open(name, O_RDONLY, 0666);
		if (shm_fd == -1) {
			fprintf(stderr, "Shared memory failed\n");
			return -1;
		}

		// write message to shared memory
		sprintf(ptr, "%s", message);
		printf("Child process (%d) wrote message.\n", getpid());
		ptr += strlen(message);
	} else {
		// parent process
		// once child is done, safely unlink the shared memory segment

		wait(NULL);

		/// 3. Read/print the value created by the child
		printf("Parent process (%d) reads: %s\n", getpid(), ptr);
		if (shm_unlink(name) == -1) {
			printf("Error removing %s\n",name);
			return -1;
		}
		printf("Shared memory closed.\n");

	}

	

	return 0;
}