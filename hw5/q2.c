/**
  Hun Jae Lee (hxl224)
  EECS338 HW5
  Due 161017

  Description:
    Finds the minimum value of the Shubert function, 
      using OpenMP directives BUT WITHOUT the "reduction (min:variable)" clause.
    Uses integers for outer loop and compute the necessary double values.

*/

#include <stdio.h>
#include <omp.h>
#include "shubert.c"

#define NUM_THREADS 4

int main() {
  int nthreads, tid;
  int i;
  double x, y, z;
  double min[NUM_THREADS] = {0, 0, 0, 0}; // All mins

  #pragma omp parallel for private(tid)
  for (i = -2; i < 2; i++) {
    tid = omp_get_thread_num();
    for (x = i; x < i + 1; x += 0.25) {
      for (y = -2.0; y < 2.0; y += 0.25) {
        z = shubert(x, y);
        if (z < min[tid]) {
          min[tid] = z;
        }
      }
    }
    if (tid == 0 && i == 1) {
      nthreads = omp_get_num_threads();
      printf("Number of threads = %d\n", nthreads); 
    }
  }
  /* All threads join master thread and terminate */ 
  if (nthreads > NUM_THREADS) {
    printf("ERROR: nthreads exceeds NUM_THREADS\n");
  } 
  double global_min = 0.0;
  for (i = 0; i < NUM_THREADS; i++) {
    if (min[i] < global_min) {
      global_min = min[i];
    }
  }
  printf("Global min: %f\n", global_min);
  return 0;
}
