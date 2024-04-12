#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>

sem_t sem1, sem2, sem3;

void *thread1(void *arg){
  for(int i = 0; i < 10; i++) {
    printf("A");
    sem_post(&sem2);
    sem_wait(&sem1);
  }

  return NULL;
}

void *thread2(void *arg) {
  for(int i = 0; i < 10; i++)
  {
    sem_wait(&sem2);
    printf("B");
    sem_post(&sem3);
  }

  return NULL;
}

void *thread3(void *arg) {
  for(int i = 0; i < 10; i++) 
  {
    sem_wait(&sem3);
    printf("C");
    sem_post(&sem1);
  }

  return NULL;
}

int main()
{
  pthread_t t1, t2, t3;
  
  sem_init(&sem1, 0, 0);
  sem_init(&sem2, 0, 0);
  sem_init(&sem3, 0, 0);

  pthread_create(&t1, NULL, thread1, NULL);
  pthread_create(&t2, NULL, thread2, NULL);
  pthread_create(&t3, NULL, thread3, NULL);

  // Join
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);

  printf("\n");

  return 0;
}
