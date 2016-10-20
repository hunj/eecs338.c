/**
  Hun Jae Lee (hxl224)
  EECS338 HW5
  Due 161017

  Description:
    A multithreaded program with one parent and one child that the _parent increments while the child decrements a global counter variable_ many times. 
    
    Uses a private counter variable in each process for comparison. 
    
    Displays the final values of all three counter variables. 

    If no conflict occurs, the global counter would have a final value of zero, due to equal numbers of increments (by the parent) and decrements (by the child). 
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define ITERATIONS 100000000

void *decrement(void *param);

int global_counter = 0;

int main(int argc, char *argv[]) {
  pthread_t tid; /* the thread identifier */
  pthread_attr_t attr; /* set of attributes for the thread */

  /* get the default attributes */
  pthread_attr_init(&attr);

  /* create the thread */
  pthread_create(&tid, &attr, decrement, NULL);

  // this is what the master thread should do while child thread is working
  int parent_counter;
  for (parent_counter = 0; parent_counter < ITERATIONS; parent_counter++) {
    global_counter++;
  }
  printf("parent_counter:\t%d\n", parent_counter);

  /* now wait for the thread to exit */
  pthread_join(tid, NULL);

  printf("global_counter:\t%d\n", global_counter);

  return 0;
}

void *decrement(void *param) {
  int child_counter;
  for (child_counter = 0; child_counter > -1*ITERATIONS; child_counter--) {
    global_counter--;
  }
  printf("child_counter:\t%d\n", child_counter);
  return 0;
}
