/**
  Hun Jae Lee (hxl224)
  EECS338 HW8
  Due 161109

  Description:
  	- Multithreaded program using pthreads for reader/writers solution from Section 5.7.2.
		- Writer periodically changes the buffer
		- Readers continuously check for changes and print them out, if changed.
		- Threads share: a string buffer, an integer, and synchronization variables.
		- One parent writer and two child reader threads
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
int version = 0, read_count = 0;
sem_t rw_mutex, mutex;

// two reader threads
void *reader1(void*);
void *reader2(void*);

// prototype
void set_buffer_string_to(char str[]);


int main(int argc, char *argv[]) {
	// semaphore setup
	if (sem_init(&rw_mutex, 0, 1) < 0) { // 0 = multithreaded
    fprintf(stderr, "ERROR: could not initialize rw_mutex semaphore.\n");
    return -1;
  }
  if (sem_init(&mutex, 0, 1) < 0) { // 0 = multithreaded
    fprintf(stderr, "ERROR: could not initialize mutex semaphore.\n");
    return -1;
  }

  // thread setup
	pthread_t tid1, tid2; /* the thread identifiers */
	pthread_attr_t attr; /* set of attributes for the thread */
	pthread_attr_init(&attr);
	pthread_create(&tid1, &attr, reader1, NULL);
	pthread_create(&tid2, &attr, reader2, NULL);

	// Parent
	sem_wait(&rw_mutex);
	set_buffer_string_to("1st sentence");	// sorry i'm boring
	sem_post(&rw_mutex);
	sleep(1); // let the child read

	sem_wait(&rw_mutex);
	set_buffer_string_to("2nd sentence");
	sem_post(&rw_mutex);
	sleep(1); 

	sem_wait(&rw_mutex);
	set_buffer_string_to("3rd sentence");
	sem_post(&rw_mutex);
	sleep(1); 

	sem_wait(&rw_mutex);
	set_buffer_string_to("4th sentence");
	sem_post(&rw_mutex);

	// Wait for both children to be done
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	// housekeeping
	sem_destroy(&rw_mutex);
	sem_destroy(&mutex);

	// exit
	return 0;
}

void set_buffer_string_to(char str[]) {
	sprintf(buffer, "%s", str);
	version++;
}

void *reader1(void* param) {
	int read_version = 1;

	while (read_version <= 4) {
		sem_wait(&mutex);
		read_count++;
		if (read_count == 1) 
			sem_wait(&rw_mutex);
		sem_post(&mutex);

		if (read_version <= version) {
			read_version++;
			printf("%d(1): %s\n", pthread_self(), buffer);
		}
		
		sem_wait(&mutex);
		read_count--;
		if (read_count == 0) 
			sem_post(&rw_mutex);
		sem_post(&mutex);
	}

	pthread_exit(0);
}

void *reader2(void* param) {
	int read_version = 1;

	while (read_version <= 4) {
		sem_wait(&mutex);
		read_count++;
		if (read_count == 1) 
			sem_wait(&rw_mutex);
		sem_post(&mutex);

		if (read_version <= version) {
			read_version++;
			printf("%d(2): %s\n", pthread_self(), buffer);
		}
		
		sem_wait(&mutex);
		read_count--;
		if (read_count == 0) 
			sem_post(&rw_mutex);
		sem_post(&mutex);
	}

	pthread_exit(0);
}