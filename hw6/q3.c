/**
  Hun Jae Lee (hxl224)
  EECS338 HW6
  Due 161026

  Description:
    - Counter program experimenting with global and local counters.
    - Semaphores and multithreaded design.
*/

#include <pthread.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h> // For sleep
#include <semaphore.h>  

#define N 1
#define PARENT 0
#define CHILD 1
#define COUNT 100000000 // 10^8

/* These variables are shared by the thread(s) */
int flag[2], turn = PARENT;

int global_counter = 0;

void *child(); /* child thread */

int main(int argc, char *argv[])
{
  // thread environment settings
  pthread_t tid; 
  pthread_attr_t attr; 

  // generate threads
  pthread_attr_init(&attr);
  pthread_create(&tid, &attr, child, NULL);

  // give the turn to child

  // parent's turn
  int i;
  for (i = 0; i < COUNT; i++) {
    global_counter++;
  }
  printf("parent counter:\t%d\n", i);
  fflush(stdout);

  // end parent turn

  pthread_join(tid, NULL);

  printf("global counter:\t%d\n", global_counter);
  return 0;
}

void *child() {
  // receive turn signal

  // child turn
  int i;
  for (i = 0; i > -1*COUNT; i--) {
    global_counter--;
  }
  printf("child counter:\t%d\n", i);
  fflush(stdout);

  // end child turn

  pthread_exit(0);
}
