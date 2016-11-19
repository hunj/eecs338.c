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

/* Global variables are shared by the thread(s) */
int results[100];

void print_result_array();

int main(int argc, char *argv[]) {
  int n_threads;
  
  int trial, iteration, thread_id, curr_thread_num;
  for (trial = 0; trial < 100; trial++) {
    #pragma omp parallel for
    for (iteration = 0; iteration < 500; iteration++) {
      // #pragma omp critical
      if (omp_get_thread_num() % 2) {
        results[trial]++;
      } else {
        results[trial]--;
      }
    }
  }

  // I like my main methods pretty and clean.
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