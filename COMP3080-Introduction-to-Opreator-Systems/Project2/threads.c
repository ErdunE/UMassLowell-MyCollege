#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define NUM_THREADS 5
int keepGoing[30];

void *runit(void *args) {

	int me = *((int *) args);
	int i = 0;

	while(keepGoing[me]) {
		i++;
		sleep(rand() % 20 + 5);
		printf("Thread %d here\n", me);
	}
}

int main(int argc, char **argv) {
	
	pthread_t threads[NUM_THREADS];

	int i;

	int id[NUM_THREADS];

	for(i = 0; i < NUM_THREADS; i++) {
		keepGoing[i] = 1;
		id[i] = i;
		pthread_create(&threads[i], 0, runit, &id[i]);
	}

	for (i = 0; i < NUM_THREADS; i++)
		pthread_join(threads[i], 0);

} 
