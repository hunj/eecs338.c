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
#include <math.h>
#include <sys/time.h>

double shubert(double x1, double x2);

int main() {
  int nthreads, tid;
  int i;
  double x, y, z, global_min = 0;

  struct timeval start_time, stop_time, elapsed_time;  // timers

  gettimeofday(&start_time,NULL); // Unix timer
  #pragma omp parallel for reduction(min: global_min)
  for (i = -2; i < 2; i++) {
    tid = omp_get_thread_num();
    for (x = i; x < i + 1; x += 0.01) {
      for (y = -2.0; y < 2.0; y += 0.01) {
        z = shubert(x, y);
        if (z < global_min) {
          global_min = z;
        }
      }
    }
    gettimeofday(&stop_time,NULL);
    if (tid == 0 && i == -2) {
      nthreads = omp_get_num_threads();
      printf("%d threads.\n", nthreads);
    }
  }
  timersub(&stop_time, &start_time, &elapsed_time); // Unix time subtract routine
  printf("Total time was %f seconds.\n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);
  printf("min = %f\n", global_min);
  return 0;
}


double shubert(double x1, double x2) {
  double sum1 = 0; 
  double sum2 = 0;
  int i;
  for (i = 1; i <= 5; i++) {
    sum1 += i * cos((i + 1) * x1 + i);
    sum2 += i * cos((i + 1) * x2 + i);
  }
  return sum1 * sum2;
}

