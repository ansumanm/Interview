/*
Synchronize reader threads and writer threads such that
writers are given priority over readers.

Solution: Use pthread conditional variables to check that there
are no writers waiting.
*/
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdio.h>

/* Shared buffer. */
int critical_data = 0;

sem_t readers_lock;

// Synchronize between writers
pthread_mutex_t writers_sync = PTHREAD_MUTEX_INITIALIZER;
int num_writers = 0;

// Synchronize between readers and writers
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int writers_waiting = 1;

void *reader(void *arg)
{
  long unsigned int tid = (long unsigned int)arg;
  printf("(R-%ld) spawned..\n", tid);

  for (int i = 0; i < 1; i++)
  {
    printf("(R-%lu) waiting...\n", tid);
    pthread_mutex_lock(&lock);
    while (writers_waiting)
    {
      printf("(R-%lu) writers are waiting -------------------------\n", tid);
      pthread_cond_wait(&cond, &lock);
    }

    printf("(R-%lu) reading %d\n", tid, critical_data);
    pthread_mutex_unlock(&lock);

    usleep(50);
  }

  printf("(R-%lu) EXIT..\n", tid);
}

void *writer(void *arg)
{
  long unsigned int tid = (long unsigned int)arg;
  printf("(W-%lu) spawned...\n", tid);

  for (int i = 0; i < 1; i++)
  {
    printf("(W-%lu) waiting...\n", tid);
    pthread_mutex_lock(&writers_sync);
    num_writers++;
    writers_waiting = 1;
    pthread_mutex_unlock(&writers_sync);

    // Take the rwlock
    // Write critical data
    pthread_mutex_lock(&lock);

    critical_data++;
    printf("(W-%lu) data %d \n", tid, critical_data);
    pthread_mutex_unlock(&lock);

    /* Decrease the waiting writers count and signal the threads. */
    pthread_mutex_lock(&writers_sync);
    num_writers--;
    if (num_writers == 0)
    {
      // sem_post(&readers_lock);
      writers_waiting = 0;
      printf("(W-%lu) Signal (R)\n", tid);
      pthread_cond_signal(&cond);
    }
    pthread_mutex_unlock(&writers_sync);

    usleep(10);
  }
  printf("(W-%lu) EXIT...\n", tid);
}

int main(int argc, char *argv[])
{
  pthread_t readers[10];
  pthread_t writers[10];

  sem_init(&readers_lock, 0, 0);

  for (long unsigned int i = 0; i < sizeof(readers) / sizeof(readers[0]); i++)
  {
    pthread_create(&readers[i], NULL, reader, (int *)i);
  }

  for (long unsigned int i = 0; i < sizeof(writers) / sizeof(writers[0]); i++)
  {
    pthread_create(&writers[i], NULL, writer, (int *)i);
  }

  // Join
  for (int i = 0; i < sizeof(readers) / sizeof(readers); i++)
  {
    pthread_join(readers[i], NULL);
  }

  for (int i = 0; i < sizeof(writers) / sizeof(writers[0]); i++)
  {
    pthread_join(writers[i], NULL);
  }

  return 0;
}