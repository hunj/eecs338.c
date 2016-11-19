/**
  Hun Jae Lee (hxl224)
  EECS338 HW7
  Due 161026

  Description:
    - multithreaded program where one is a producer and another a consumer.
    - Create a shared, circular buffer (array). 
    - Create a second array with N values, where N is larger than the buffer. 
    - The producer should insert all N values individually into the buffer and then terminate. 
    - The consumer should concurrently retrieve each buffer value individually, printing out each value retrieved. 
    - NO process synchronization, i.e. the producer and consumer do not wait for each other and do not check for a full or empty buffer.
    
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// global environment settings
#define BUFFER_SIZE 4
#define N 10
int buffer[] = {0, 0, 0, 0}; // 4
int counter = 0;

// consumer thread
void *consumer(void *param);

int main(int argc, char *argv[]) {
  // set up & create consumer thread
  pthread_t tid;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_create(&tid, &attr, consumer, NULL);

  /**
  Producer:
    - inserts all N values individually into the buffer and then terminate.
      where N = {10, 20, 30, ..., 100} and inserted in order.
  */
  int in = 0, next_produced;
  for (next_produced = 10; next_produced <= 100; next_produced += 10) {
    // halting is NOT necessary
    // while (counter == BUFFER_SIZE);
    buffer[in] = next_produced;
    in = (in + 1) % BUFFER_SIZE;
    counter++;
  }

  pthread_join(tid, NULL);
  return 0;
}

/**
Consumer:
  - concurrently retrieve each buffer value individually, printing out each value retrieved.
*/
void *consumer(void *param) {
  int i, out = 0, next_consumed = 0;
  for (i = 0; i < N; i++) {
    // halting is NOT necessary
    // while (counter == 0);
    next_consumed = buffer[out];
    printf("%d\n", buffer[out]);
    fflush(stdout);
    buffer[out] = 0;  // consume it (mark as zero)
    out = (out + 1) % BUFFER_SIZE; 
    counter--;

  }

  pthread_exit(0);
}
