/**
  Hun Jae Lee (hxl224)
  EECS338 HW6
  Due 161026

  Description:
    - Counter program experimenting with global and local counters.
    - Peterson’s solution and multithreading.
*/

#include <pthread.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h> // For sleep

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
  flag[PARENT] = 1;
  turn = CHILD;
  while (flag[CHILD] && turn == CHILD);

  // parent's turn
  int i;
  for (i = 0; i < COUNT; i++) {
    global_counter++;
  }
  printf("parent counter:\t%d", i);

  // end parent turn
  flag[PARENT] = 0;
  pthread_join(tid, NULL);

  printf("global counter:\t%d", global_counter);
  return 0;
}

void *child() {
  // receive turn signal
  flag[CHILD] = 1;
  turn = PARENT;
  while (flag[PARENT] && turn == PARENT);

  // child turn
  int i;
  for (i = 0; i > -1*COUNT; i--) {
    global_counter--;
  }
  printf("child counter:\t%d", i);
  fflush(stdout);

  // end child turn
  flag[CHILD] = 0;
  pthread_exit(0);
}
