/**
  Hun Jae Lee (hxl224)
  EECS338 HW6
  Due 161026

  Description:
    - Counter program experimenting with global and local counters.
    - Semaphores and fork with shared memory design.
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

#define N 1
#define PARENT 0
#define CHILD 1

#define COUNT 100000000 // 10^8

int main(int argc, char *argv[]) {
  // fork environment settings;
  pid_t pid;

  struct shm_contents {
    int flag[2];
    int turn;
    int counter;
  };

  sem_t *sem;

  // shared memory environment settings
  const int SIZE = 1;
  const char *name = "hxl224_shm";
  int shm_fd;
  struct shm_contents *ptr;

  // open up shared memory segment
  shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
  ftruncate(shm_fd,SIZE);
  ptr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if (ptr == MAP_FAILED) {
    printf("Map failed\n");
    return -1;
  }

  ptr->counter = 0;

  pid = fork();
  if (pid < 0) {
    fprintf(stderr, "fork failed\n");
    return -1;
  } else if (pid == 0) {
    // child process

    // receive the signal
    ptr->flag[CHILD] = 1;

    // give the signal
    ptr->turn = PARENT;
    while (ptr->flag[PARENT] && ptr->turn == PARENT);

    // run child counting
    int child_counter;
    for (child_counter = 0; child_counter > -1*COUNT; child_counter--) {
      ptr->counter--;
    }
    printf("child counter:\t%d\n", child_counter);
  } else {
    // parent process
    ptr->flag[PARENT] = 1;

    // give the signal
    ptr->turn = CHILD;
    while (ptr->flag[CHILD] && ptr->turn == CHILD);

    // run parent counting
    int parent_counter;
    for (parent_counter = 0; parent_counter < COUNT; parent_counter++) {
      ptr->counter++;
    }
    printf("parent counter:\t%d\n", parent_counter);

    // wait for the child to be done
    ptr->flag[PARENT] = 0;
    wait(NULL);

    // safely remove the shared memory segment, since both parent and child are
    // done messing around with it.
    if (shm_unlink(name) == -1) {
      printf("Error removing %s\n",name);
      exit(-1);
    }
    printf("global counter:\t%d\n", ptr->counter);
  }
  return 0;
}
