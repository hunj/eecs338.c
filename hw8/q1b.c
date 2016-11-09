/**
  Hun Jae Lee (hxl224)
  EECS338 HW8
  Due 161109

  Description:
    - a multithreaded program using OpenMP and “parallel for”, where exactly half of the threads increment a global counter variable, and the other half decrement the counter. 
    - with “critical” clause for the critical region.
*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>     
#include <sys/types.h>  
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define OMP_MAX_THREADS 8

/* Global variables are shared by the thread(s) */
int results[100];

void *decrement(void* param); /* child thread */
void print_result_array();

int main(int argc, char *argv[]) {
  // set up a child thread & start
  pthread_t tid;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_create(&tid, &attr, decrement, NULL);
  
  // Parent thread increments the number
  int i;
  for (i = 0; i < 100; i++) {
    int j;
    #pragma omp parallel for
    for (j = 0; j < 50; j++) {
      // #pragma omp critical
      results[i]++;
    }
  }

  // Join
  pthread_join(tid, NULL);

  print_result_array();

  return 0;
}

// print all results, with 10 results in each line
void print_result_array() {
  int iter;
  for (iter = 0; iter < 100; iter++) {
    printf("%d ", results[iter]);
    if (iter % 10 == 9) {
      printf("\n");
    }
  }
  printf("\n");
}

// Child thread decrements the number
void *decrement(void* param) {
  int i;
  for (i = 0; i < 100; i++) {
    int j;
    #pragma omp parallel for
    for (j = 0; j < 50; j++) {
      // #pragma omp critical
      results[i]--;
    }
  }

  pthread_exit(0);
}
