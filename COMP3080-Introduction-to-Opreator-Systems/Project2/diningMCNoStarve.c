// Dining philosophers solution using Pthreads with mutex and condition variables
// Deadlock prevention by having each philosopher take both forks simulataneously
// Additional state to prevent starvation.

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#define RANGE 1000000000
#define BASE   500000000
int range = RANGE;
int base = BASE;

pthread_mutex_t	  m;
pthread_cond_t	philoPickup[5];
int		inUse[5];      
// next defintion for starvation control
// zero indicates philosopher i is not waiting on its forks
// one indicates philosopher i is waiting on its forks
int philoWaiting[5];

void *phil(void *args) {
	int id = *((int *) args);
	srand(100);
	struct timespec t;	
	int neighborCnt[2];
	neighborCnt[0] = neighborCnt[1] = 0;	
	while (1) {
		printf("Philosopher %d will think\n", id);
		t.tv_sec = 0;
		t.tv_nsec = (rand() % range) + base;
		nanosleep(&t, 0);
		printf("Philosopher %d is hungry; eat now\n", id);
		pthread_mutex_lock(&m);
		printf("Philosopher %d will try for left and right fork\n", id);
		philoWaiting[id] = 1;
		while((inUse[id] || inUse[(id+1)%5]) && 
				(neighborCnt[0] > 5 || neighborCnt[1] > 5)) {
			neighborCnt[0] = philoWaiting[id] ? (neighborCnt[0] + 1) : 0;
			neighborCnt[1] = philoWaiting[(id+1)%5] ? (neighborCnt[1] + 1) : 0;
			pthread_cond_wait(&philoPickup[id], &m);
		}
		inUse[id] = 1;
		inUse[(id+1)%5] = 1;
		philoWaiting[id] = 0;
		pthread_mutex_unlock(&m);
		printf("Philosopher %d has forks; will eat\n", id);
		t.tv_sec = 0;
		t.tv_nsec = (rand() % range) + base;
		nanosleep(&t, 0);
		pthread_mutex_lock(&m);
		printf("Philosopher %d finished eating; releasing forks\n", id);
		inUse[id] = 0;
		pthread_cond_signal(&philoPickup[id]);
		printf("Philosopher %d released right fork\n", id);
		inUse[(id+1)%5] = 0;
		pthread_cond_signal(&philoPickup[(id+1)%5]);
		printf("Philosopher %d released left fork\n", id);
		pthread_mutex_unlock(&m);
	}
}

int main(int argc, char **argv) {
	if(argc == 3) {
		range = atoi(argv[1]);
		base = atoi(argv[2]);
	}
	else if (argc !=3 && argc != 1) {
		printf("Usage: %s range base\n", argv[0]);
		exit(-1);
	}

	pthread_t phils[5];

	int i;
	
	for(i = 0; i < 5; i++) {
		pthread_cond_init(&philoPickup[i], 0);
		inUse[0] = 0;
		philoWaiting[i] = 0;
	}
	pthread_mutex_init(&m, 0);
	

	int id[5];
	for(i = 0; i < 5; i++) {
		id[i] = i;
		if (pthread_create(&phils[i], 0, phil, &id[i]) != 0)
			perror("Pthread_create error");
	}
	for(i = 0; i < 5; i++)
		pthread_join(phils[i], 0);
}  
