/* 
Use OpenMP directives and the “reduction (min:variable)” clause to find the minimum value of the Shubert function, as described in HW #4. This is very similar to shubert.c from lecture, except that . Be sure to include omp.h and compile using the “-fopenmp” option. You do not need to print the thread IDs or number of threads, but you may want to in order to explore how the work is divided. Note: you will need to using integers for the outer loop and compute the necessary double values.
*/

/**
  Hun Jae Lee (hxl224)
  EECS338 HW4
  Due 161017

  Description:
    Finds the minimum value of the Shubert function, 
      using OpenMP directives and the "reduction (min:variable)" clause.

*/

#include <stdio.h>
#include "shubert.c"

int main() {
  int nthreads, tid;
  int i, j;
  double y;

  #pragma omp parallel for private(tid) reduction(min:y) {
    for (i = -2; i <= 2; i++) {
      for (j = -2.0; j <= 2.0; j += 0.01) {
        tid = omp_get_thread_num();
        printf("Thread %d\n", tid);
        y = shubert(i, j);

        if (tid == 0 && i == 1) {
          nthreads = omp_get_num_threads();
          printf("Number of threads: %d\n", nthreads);
        }
      }
    } 
    /* All threads join master thread and terminate */ 
    return 0;
  }
}
