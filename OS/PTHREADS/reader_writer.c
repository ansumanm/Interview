#include<stdio.h> 
#include<string.h> 
#include<pthread.h> 
#include<stdlib.h> 
#include<unistd.h> 

#define NO_OF_THREADS 5
pthread_t tid[NO_OF_THREADS]; 
int counter; 

pthread_mutex_t lock; 
pthread_mutex_t reader_ready_lock; 

volatile int readers_waiting; // Shared protected data

int sum_of_digits(long int t) {
	long int remainder;
	long int sum = 0;

	while (t != 0)
	{
		remainder = t % (long int)10;
		sum       = sum + remainder;
		t         = t / 10;
	}

	return sum;
}

int protected_increment_readers_waiting()
{
	int r_w;

	pthread_mutex_lock(&reader_ready_lock);
	r_w = ++readers_waiting;
	pthread_mutex_unlock(&reader_ready_lock);

	return r_w;
}

int protected_decrement_readers_waiting()
{
	int r_w;

	pthread_mutex_lock(&reader_ready_lock);
	r_w = --readers_waiting;
	pthread_mutex_unlock(&reader_ready_lock);

	return r_w;
}

int readers_are_waiting() 
{
	int r_w;
	pthread_mutex_lock(&reader_ready_lock);
	r_w = readers_waiting;
	pthread_mutex_unlock(&reader_ready_lock);

	return r_w;
}

void get_resource(int reader)
{
	volatile int r_w;
	pthread_t tid = pthread_self();
	printf("\n %s(%ld) requesting data..\n", (reader ? "reader" : "writer"), tid); 

	if (reader) {
		r_w = protected_increment_readers_waiting();
		printf("(%ld)Readers in queue = %d\n", tid, r_w);

		pthread_mutex_lock(&lock);
		printf("READER(%ld) gets access to resource\n", tid);
		sleep(1); // Hold the resource for 1 sec
		pthread_mutex_unlock(&lock);

		r_w = protected_decrement_readers_waiting();
		printf("(%ld)Readers in queue = %d\n", tid, r_w);
	} else {
		// Block till all readers are flushed out.
		while(1) {
			// Loop infinitely till we get a chance to write.
			while(readers_are_waiting());

			if (pthread_mutex_trylock(&lock) == 0) {
				printf("Finally WRITER(%ld) gets access to resource. Readers in queue %d\n",
					       	tid, readers_are_waiting());
				sleep(1); // Hold the resource for 1 sec
				pthread_mutex_unlock(&lock);
				break; // from the while loop
			} else {
				printf("WRITER(%ld): Trylock failed.\n", tid);
				usleep(1000); // sleep for 1000 micro seconds.
			}
		}
	}
}

void *trythis(void *arg)
{
	pthread_t mytid = *(pthread_t *)arg;
	int reader;
	int sum;
	int count;

	sum = sum_of_digits(mytid);

	reader = (sum % 2 == 0);

	for(count = 1; count < 5; count++)
	{
		get_resource(reader);
	}
}
#if 0
void* trythis(void *arg) 
{ 
	pthread_mutex_lock(&lock); 

	unsigned long i = 0; 
	counter += 1; 
	printf("\n Job %d has started\n", counter); 

	for(i=0; i<(0xFFFF);i++); 

	printf("\n Job %d has finished\n", counter); 

	pthread_mutex_unlock(&lock); 

	return NULL; 
} 
#endif

int main(void) 
{ 
	int i = 0; 
	int error; 

	if (pthread_mutex_init(&lock, NULL) != 0) 
	{ 
		printf("\n mutex init has failed\n"); 
		return 1; 
	} 

	if (pthread_mutex_init(&reader_ready_lock, NULL) != 0) 
	{ 
		printf("\n mutex init has failed\n"); 
		return 1; 
	} 

	while(i < NO_OF_THREADS) 
	{ 
		error = pthread_create(&(tid[i]), NULL, &trythis, &(tid[i])); 
		if (error != 0) 
			printf("\nThread can't be created :[%s]", strerror(error)); 
		i++; 
	} 

	
	i = 0;
	while(i < NO_OF_THREADS)  {
		pthread_join(tid[i], NULL); 
		i++; 
	}

	pthread_mutex_destroy(&lock); 
	pthread_mutex_destroy(&reader_ready_lock); 

	return 0; 
} 

