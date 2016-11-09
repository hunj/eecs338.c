/**
  Hun Jae Lee (hxl224)
  EECS338 HW8
  Due 161109

  Description:
  	- Multithreaded program using pthreads for reader/writers solution from Section 5.7.2.
		- Writer periodically changes the buffer
		- Readers continuously check for changes and print them out, if changed.
		- Threads share: a string buffer, an integer, and synchronization variables.
		- One parent and two child threads work like:
			- Parent is the writer and write two or more strings to the buffer, sleeping between each buffer update.
*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>     
#include <sys/types.h>  
#include <stdlib.h>     
#include <semaphore.h>  
#include <string.h>
#define BUFFER_SIZE 256

/* Global variables are shared by the thread(s) */
char buffer[BUFFER_SIZE];
int version_no = 0;

// two reader threads
void *reader1();
void *reader2();

int main(int argc, char *argv[]) {
	pthread_t tid1, tid2; /* the thread identifiers */
	pthread_attr_t attr; /* set of attributes for the thread */
	pthread_attr_init(&attr);
	pthread_create(&tid1, &attr, reader1, NULL);
	pthread_create(&tid2, &attr, reader2, NULL);

	// Parent
	
	// the four strings are the first verse of the South Korean national anthem.
	// had to use this because of the whole issue going on 
	sprintf(buffer, "%s", "Until that day when Mt. Baekdu is worn away ");
	version_no++; // 1
	sprintf(buffer, "%s", "and the East Sea's waters run dry, ");
	version_no++; // 2
	sprintf(buffer, "%s", "May God preserve our country, ");
	version_no++; // 3
	sprintf(buffer, "%s", "our long-living homeland!");
	version_no++; // 4

	printf("%d", version_no);

	// Wait for both children to be done
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	return 0;
}

void *reader1() {
	while (version_no < 4) {
		printf("%d: %s\n", (int)pthread_self(), buffer);
	}
	pthread_exit(0);
}

void *reader2() {
	sleep(1); // Wait for parent to write to buffer (poor synchronization, but this is only a demo)
	pthread_t tid = pthread_self();
	// printf("My thread ID is %d, and the buffer contains: %s.\n", tid, buffer);
	pthread_exit(0);
}