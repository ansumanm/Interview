
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    sem_unlink("sem_odd");
    sem_unlink("sem_even");

    return 0;
}
