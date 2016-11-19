/**
  Hun Jae Lee (hxl224)
  EECS338: Homework #3 Question 2
  Due 160921 Wed

  - Description:
  Parallel computation example that does the following:
  1. Takes NUM_PROCS N (where 1 <= N <= 4)
  2. Fork N processes, parallelly count up to 1,000,000,000 using N processes
  3. Each process reports the time taken to count

  The parent process (this program) does NOT compute anything. Note that it is the child process(es) that does the computing!
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define N           1000000000
#define NUM_PROCS   1

// make arrays for timevals with the size of NUM_PROCS

int main(int argc, char *argv[]) {
  // environment setup
  long int i;
  long int processes;
  long long int x = 0, sum_time;
  int target_sum, process_index = 1;
  pid_t pid;
  struct timeval start_time, stop_time, elapsed_time;  // timers

  for (processes = 2; processes <= NUM_PROCS; processes++) {
    pid = fork();
    if (pid == 0) {
      process_index = processes;
      break;
    }
  }
  
  gettimeofday(&start_time, NULL);
  for (i = 0, x = 0; i < N/NUM_PROCS; i++) {
    x = x + 1;
  }
  gettimeofday(&stop_time, NULL);
  timersub(&stop_time, &start_time, &elapsed_time);

  for (i = 0; i < NUM_PROCS; i++) {
    wait(NULL);
  }

  if (process_index == 1) {
    printf("%d processes, sampled total time: %f seconds.\n", NUM_PROCS, elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);
  }

  return 0;
}