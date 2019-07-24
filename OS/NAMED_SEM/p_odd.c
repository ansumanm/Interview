#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    sem_t *sem_odd, *sem_even;
    int i;

    sem_odd = sem_open("sem_odd", O_CREAT, 0600, 0);
    sem_even = sem_open("sem_even", O_CREAT, 0600, 0);

    if( 
	    (sem_odd == SEM_FAILED) ||
	    (sem_even == SEM_FAILED)
      ) {
        perror("parent sem_open");
        return 0;
    }

    for(i = 1; i < 200; i+=2) {
	    printf("%d \n", i);


	    if (sem_post(sem_odd) < 0) {
		    perror("sem_post");
	    }

	    if(sem_wait(sem_even) < 0) {
		    perror("sem_wait");
	    }
    }

    return 0;
}
