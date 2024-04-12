#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

int buffer = -1;
int data_available = 0;

// Mutex and condition variables
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

// Producer thread function
void *producer(void *arg) {
  for(int i = 0; i < 5; i++) {
    pthread_mutex_lock(&mutex);

    while (data_available == 1) {
      pthread_cond_wait(&cond, &mutex);
    }

    // Produce data
    buffer = i;
    printf("Produced: %d\n", i);

    data_available = 1;

    // Signal the consumer that the data is available
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

void *consumer(void *arg) {
  for (int i = 0; i < 5; i++) {
    pthread_mutex_lock(&mutex);

    while (data_available == 0) {
      pthread_cond_wait(&cond, &mutex);
    }

    // Consume data
    printf("Consumed buffer %d\n", buffer);
    data_available = 0;

    pthread_cond_signal(&cond);

    pthread_mutex_unlock(&mutex);
  }
}

int main()
{
  pthread_t prod, cons;

  pthread_create(&prod, NULL, producer, NULL);
  pthread_create(&cons, NULL, consumer, NULL);

  pthread_join(prod, NULL);
  pthread_join(cons, NULL);

  // Cleanup
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);

  return 0;
}