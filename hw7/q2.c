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
    - Process is synchronized, i.e. the producer and consumer do wait for each other and do check for a full or empty buffer.
    - Process is synchronized using semaphores
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>  

// global environment settings
#define BUFFER_SIZE 4
#define NUM_VALUES 10
int buffer[] = {0, 0, 0, 0}; // 4
int counter = 0;

sem_t mutex;
sem_t empty;
sem_t full;

// consumer thread
void *consumer(void *param);

int main(int argc, char *argv[]) {

  // semaphore setup
  if (sem_init(&mutex, 0, 1) < 0) { // 0 = multithreaded
    fprintf(stderr, "ERROR: could not initialize mutex semaphore.\n");
    return 0;
  }
  if (sem_init(&empty, 0, BUFFER_SIZE) < 0) { // 0 = multithreaded
    fprintf(stderr, "ERROR: could not initialize empty semaphore.\n");
    return 0;
  }
  if (sem_init(&full, 0, 0) < 0) { // 0 = multithreaded
    fprintf(stderr, "ERROR: could not initialize full semaphore.\n");
    return 0;
  }

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
    sem_wait(&empty);
    sem_wait(&mutex);

    buffer[in] = next_produced;
    in = (in + 1) % BUFFER_SIZE;
    counter++;

    sem_post(&mutex);
    sem_post(&full);
  }

  pthread_join(tid, NULL);
  sem_destroy(&mutex);
  sem_destroy(&empty);
  sem_destroy(&full);
  return 0;
}

/**
Consumer:
  - concurrently retrieve each buffer value individually, printing out each value retrieved.
*/
void *consumer(void *param) {
  int i, out = 0, next_consumed = 0;
  for (i = 0; i < NUM_VALUES; i++) {
    sem_wait(&full); 
    sem_wait(&mutex);

    next_consumed = buffer[out];
    printf("%d\n", buffer[out]);
    fflush(stdout);
    buffer[out] = 0;  // consume it (mark as zero)
    out = (out + 1) % BUFFER_SIZE; 
    counter--;

    sem_post(&mutex); 
    sem_post(&empty);
  }

  pthread_exit(0);
}
