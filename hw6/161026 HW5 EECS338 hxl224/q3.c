/**
  Hun Jae Lee (hxl224)
  EECS338 HW6
  Due 161026

  Description:
    - Counter program experimenting with global and local counters.
    - Semaphores and multithreaded design.
*/

#include <stdio.h>
#include <math.h>
#include <unistd.h>     
#include <sys/types.h>  
#include <errno.h>      
#include <stdlib.h>     
#include <pthread.h>    
#include <semaphore.h>  

#define COUNT 100000000 // 10^8

// Global variables
int global_counter = 0;
sem_t sem;

// Child Thread
void *child();

int main(int argc, char *argv[]) {
  if (sem_init(&sem, 0, 1) < 0) { // 0 for multithreaded
    fprintf(stderr, "ERROR: could not initialize &semaphore.\n");
    return -1;
  }

  // Generate child thread
  pthread_t tid; 
  pthread_attr_t attr; 
  pthread_attr_init(&attr);
  pthread_create(&tid, &attr, child, NULL);

  // wait for the child to be done
  sem_wait(&sem);

  // parent's turn
  int i;
  for (i = 0; i < COUNT; i++) {
    global_counter++;
  }
  printf("parent counter:\t%d\n", i);
  fflush(stdout);

  // end parent turn
  sem_post(&sem);
  pthread_join(tid, NULL);
  sem_destroy(&sem);

  printf("global counter:\t%d\n", global_counter);
  return 0;
}

void *child() {
  sem_wait(&sem);

  // child turn
  int i;
  for (i = 0; i > -1*COUNT; i--) {
    global_counter--;
  }
  printf("child counter:\t%d\n", i);
  fflush(stdout);

  // end child turn
  sem_post(&sem);
  pthread_exit(0);
}
