#include<pthread.h>
#include<stdio.h>

int main(){
  pthread_t wt_thread[3];

  printf("%ld\n", sizeof(wt_thread)/sizeof(wt_thread[0]));

  return 0;
}