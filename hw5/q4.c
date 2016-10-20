/**
  Hun Jae Lee (hxl224)
  EECS338 HW5
  Due 161017

  Description:
    A forked program with one parent and one child that the _parent increments while the child decrements a global counter variable_ many times. 
    
    Uses a private counter variable in each process for comparison. 
    
    Displays the final values of all three counter variables. 
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

#define ITERATIONS 100000000

int main() {
  // shared memory environment settings
  const int SIZE = 1;
  const char *name = "hxl224";
  int shm_fd;
  int *ptr;

  // fork environment settings
  pid_t pid;

  // open up shared memory segment
  shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
  ftruncate(shm_fd,SIZE);
  ptr = (int*)mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if (ptr == MAP_FAILED) {
    printf("Map failed\n");
    return -1;
  }

  ptr[0] = 0;

  pid = fork();
  if (pid < 0) {
    fprintf(stderr, "fork failed\n");
    return -1;
  } else if (pid == 0) {
    // child process
    int child_counter;
    for (child_counter = 0; child_counter > -1*ITERATIONS; child_counter--) {
      ptr[0] = ptr[0] - 1;
    }
    printf("child counter:\t%d\n", child_counter);
  } else {
    // parent process
    int parent_counter;
    for (parent_counter = 0; parent_counter < ITERATIONS; parent_counter++) {
      ptr[0] = ptr[0] + 1;
    }
    printf("parent counter:\t%d\n", parent_counter);

    // wait for the child to be done
    wait(NULL);

    // safely remove the shared memory segment, since both parent and child are
    // done messing around with it.
    if (shm_unlink(name) == -1) {
      printf("Error removing %s\n",name);
      exit(-1);
    }
    printf("global counter:\t%d\n", ptr[0]);
  }
  return 0;
}
