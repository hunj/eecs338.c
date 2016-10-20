/**
  Hun Jae Lee (hxl224)
  EECS338 HW5
  Due 161017

  Description:
    Finds the minimum value of the Shubert function, 
      using OpenMP directives and the "reduction (min:variable)" clause.
    Uses integers for outer loop and compute the necessary double values.

*/

#include <stdio.h>
#include <omp.h>
#include "shubert.c"

#define NUM_THREADS 4

int main() {
  int nthreads, tid;
  int i;
  double x, y, z, global_min = 0;

  #pragma omp parallel for private(tid) reduction(min:global_min)
  for (i = -2; i < 2; i++) {
    tid = omp_get_thread_num();
    for (x = i; x < i + 1; x += 0.25) {
      for (y = -2.0; y < 2.0; y += 0.25) {
        z = shubert(x, y);
        if (z < global_min) {
          global_min = z;
        }
      }
    }
    if (tid == 0 && i == 1) {
      nthreads = omp_get_num_threads();
      printf("%d threads.\n", nthreads);
    }
    /* All threads join master thread and terminate */ 
    if (nthreads > NUM_THREADS) {
      printf("ERROR: nthreads exceeds NUM_THREADS\n");
    }
  }
  printf("Global min = %f\n", global_min);
  return 0;
}
