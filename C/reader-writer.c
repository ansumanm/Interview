#include <pthread.h>
// #include <semaphore.h>
#include <stdatomic.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  reader-writer.c
  Problem statement:
  There are readers and writer accessing critical data. Write a logic
  so that writers are give priority over readers.

  Solution:
  1) We use rwlock instead of mutex. rwlock allows parallel reads but
  exclusive writes. 
*/

// Macro for atomic increment
#define ATOMIC_INCREMENT(var) atomic_fetch_add_explicit((var), 1, memory_order_seq_cst)

// Macro for atomic decrement
#define ATOMIC_DECREMENT(var) atomic_fetch_sub_explicit((var), 1, memory_order_seq_cst)

// Macro to check to atomically check if a atomic_int is 0.
#define ATOMIC_TEST_AND_SET_ZERO_EXPLICIT(obj) \
    ({ \
        int expected = 0; \
        atomic_compare_exchange_strong_explicit((obj), &expected, 0, memory_order_seq_cst, memory_order_seq_cst); \
    })



atomic_int writers_waiting = ATOMIC_VAR_INIT(0);
int expected_value = 0;
#define writers_waiting_increment() atomic_fetch_add(&writers_waiting, 1)
#define writers_waiting_decrement() atomic_fetch_sub(&writers_waiting, 1)
#define writers_are_waiting() (atomic_compare_exchange_strong(&writers_waiting, &expected_value, 0) ? false : true)

long unsigned int critical_data;
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

atomic_bool data_available = ATOMIC_VAR_INIT(false);

void set_data_available(atomic_bool *flag)
{
  atomic_store(flag, true);
}

void clear_data_available(atomic_bool *flag)
{
  atomic_store(flag, false);
}

bool data_is_available(atomic_bool *flag)
{
  // Atomically check if the flag is set, but don't modify it.
  bool expected = true;
  bool new_value = true;

  if (atomic_compare_exchange_strong(flag, &expected, new_value)) {
    return true;
  } else {
    return false;
  }
}

bool data_is_not_available(atomic_bool *flag)
{
  bool expected = false;
  bool new_value = false;

  if (atomic_compare_exchange_strong(flag, &expected, new_value)) {
    return true;
  } else {
    return false;
  }
}
// sem_t data_available;

// atomic_flag binary_semaphore = ATOMIC_FLAG_INIT;

// void binary_semaphore_wait(atomic_flag *sem)
// {
//   pthread_t tid = pthread_self();
//   while (atomic_flag_test_and_set(sem))
//   {
//     // printf("(%lu) Waiting...\n", tid);
//     // sleep(1);
//   }
// }

// void binary_semaphore_post(atomic_flag *sem)
// {
//   atomic_flag_clear(sem);
// }



void random_sleep() {
  int sleep_time = rand() % 3;

  // printf("Sleeping for %d secs.\n", sleep_time);
  // sleep(sleep_time);
  usleep(sleep_time*1000);
}

void *reader_func(void *arg)
{
  long int tid = (long int)arg;
  while(data_is_not_available(&data_available)) {

  }
  // sem_wait(&data_available);
  // int sem_val;
  // binary_semaphore_wait(&binary_semaphore);

  for (int i = 0; i < 5; i++)
  {
    while(ATOMIC_TEST_AND_SET_ZERO_EXPLICIT(&writers_waiting) != false) {
      printf("(Reader-%ld) Writers are waiting.\n", tid);
    }

    pthread_rwlock_rdlock(&rwlock);
    // sem_getvalue(&data_available, &sem_val);
    // printf("(%lu) <<<<<<<<<<< Reading critical data: %lu  sem: %d\n", pthread_self(), critical_data, sem_val);
    printf("(Reader-%ld) <<<<<<<<<<< Reading critical data: %lu. \n", tid, critical_data);
    pthread_rwlock_unlock(&rwlock);
    random_sleep();
  }

  return NULL;
}

void *writer_func(void *arg)
{
  // pthread_t thread_id = pthread_self();
  long int tid;
  
  tid = (long int)arg;

  // printf("Spawning writer thread no. %ld\n", tid);

  // int sem_val;

  for (int i = 0; i < 5; i++)
  {
    // writers_waiting_increment();
    ATOMIC_INCREMENT(&writers_waiting);
    pthread_rwlock_wrlock(&rwlock);
    ATOMIC_DECREMENT(&writers_waiting);
    // writers_waiting_decrement();
    // sem_getvalue(&data_available, &sem_val);
    // printf("(%lu) >>>>>>>>>>  Writing critical data. Sem: %d \n", thread_id, sem_val);
    printf("(Writer-%ld) >>>>>>>>>>  Writing critical data: %ld \n", tid, tid);
    critical_data = tid;
    pthread_rwlock_unlock(&rwlock);
    // binary_semaphore_post(&binary_semaphore);
    // sem_post(&data_available);
    set_data_available(&data_available);
    random_sleep();
  }
}

int main()
{
  // Create 5 reader threads and 3 writer threads
  pthread_t rd_thread[10];
  pthread_t wt_thread[10];
  int error;
  srand(time(NULL));

  pthread_rwlock_init(&rwlock, NULL);
  // sem_init(&data_available, 0, 0);

  // Initialize it to set.
  // The writer will clear it when it posts.
  // atomic_flag_test_and_set(&binary_semaphore);

  // Create reader threads
  for (long int i = 0; i < sizeof(rd_thread) / sizeof(rd_thread[0]); i++)
  {
    if (error = pthread_create(&rd_thread[i], NULL, reader_func, (long int *)i) != 0)
    {
      perror((strerror(error)));
    };
  }

  // Create writer threads
  for (long int i = 0; i < sizeof(wt_thread) / sizeof(wt_thread[0]); i++)
  {
    // printf("Creating writer thread no. %ld\n", i);
    if (error = pthread_create(&wt_thread[i], NULL, writer_func, (long int *)i) != 0)
    {
      perror(strerror(error));
    }
  }

  // Wait for thread to finish
  for (int i = 0; i < sizeof(rd_thread) / sizeof(rd_thread[0]); i++)
  {
    pthread_join(rd_thread[i], NULL);
  }

  for (int i = 0; i < sizeof(wt_thread) / sizeof(wt_thread[0]); i++)
  {
    pthread_join(wt_thread[i], NULL);
  }

  pthread_rwlock_destroy(&rwlock);
  // sem_destroy(&data_available);

  return 0;
}
