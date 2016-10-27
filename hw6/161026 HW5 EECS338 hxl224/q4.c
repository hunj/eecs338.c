/**
  Hun Jae Lee (hxl224)
  EECS338 HW6
  Due 161026

  Description:
    - Counter program experimenting with global and local counters.
    - Semaphores and fork with shared memory design.
    - Here we use two shared memory segments, one for semaphore and another for global counter.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h> 

#define COUNT 100000000 // 10^8

int main(int argc, char *argv[]) {
  // shared memory environment settings
  const int SIZE = 1;
  const char *name_ctr = "hxl224_shm_ctr";
  const char *name_sem = "hxl224_shm_sem";
  int shm_fd_counter, shm_fd_semaphore;
  int *counter;
  sem_t *sem;

  // open up shared memory segment for counter
  shm_fd_counter = shm_open(name_ctr, O_CREAT | O_RDWR, 0666);
  ftruncate(shm_fd_counter,SIZE);
  counter = (int*)mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd_counter, 0);
  if (counter == MAP_FAILED) {
    printf("Map failed\n");
    return -1;
  }

  // open up shared memory segment for semaphore
  shm_fd_semaphore = shm_open(name_sem, O_CREAT | O_RDWR, 0666);
  ftruncate(shm_fd_semaphore,SIZE);
  sem = (sem_t*)mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd_semaphore, 0);
  if (sem == MAP_FAILED) {
    printf("Map failed\n");
    return -1;
  }

  // initialize counter & set up semaphore
  counter[0] = 0;
  if (sem_init(sem, 1, 1) < 0) { // 1 = multiprocess
    fprintf(stderr, "ERROR: could not initialize semaphore.\n");
    return -1;
  }

  // fork
  pid_t pid;
  pid = fork();
  if (pid < 0) {
    fprintf(stderr, "fork failed\n");
    return -1;
  } else if (pid == 0) {  // child process
    // wait for semaphore
    sem_wait(sem);

    // run child counting & report
    int child_counter;
    for (child_counter = 0; child_counter > -1*COUNT; child_counter--) {
      counter[0] = counter[0] - 1;
    }
    printf("child counter:\t%d\n", child_counter);

    fflush(stdout);

    // post signal
    sem_post(sem);
  } else {  // parent process
    // wait for signal
    sem_wait(sem);

    // run parent counting
    int parent_counter;
    for (parent_counter = 0; parent_counter < COUNT; parent_counter++) {
      counter[0] = counter[0] + 1;
    }
    printf("parent counter:\t%d\n", parent_counter);

    fflush(stdout);

    // post signal
    sem_post(sem);
    // wait for the child to be done
    wait(NULL);
    // destroy the semaphore
    sem_destroy(sem);

    // report global counter
    printf("global counter:\t%d\n", counter[0]);

    // safely remove the shared memory segment, since both parent and child are
    // done messing around with it.
    if (shm_unlink(name_sem) == -1 || shm_unlink(name_ctr) == -1) {
      printf("Error removing %s or %s\n", name_sem, name_ctr);
      return -1;
    }
  }
  return 0;
}
