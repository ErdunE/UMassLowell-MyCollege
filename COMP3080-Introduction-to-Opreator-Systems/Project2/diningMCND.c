// Dining philosophers solution using Pthreads with mutex and condition variables
// Deadlock prevention by limiting concurrent eaters to only four out of five 
// philosophers

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
pthread_cond_t	forks[5];
int		inUse[5];
pthread_cond_t room;
int		roomCnt;

void *phil(void *args) {
	int id = *((int *) args);
	srand(100);
	struct timespec t;		
	while (1) {
		printf("Philosopher %d will think\n", id);
		t.tv_sec = 0;
		t.tv_nsec = (rand() % range) + base;
		nanosleep(&t, 0);
		printf("Philosopher %d is hungry; going to dining room\n", id);
		pthread_mutex_lock(&m);
		roomCnt++;
		while(roomCnt > 4)
			pthread_cond_wait(&room, &m);
		printf("Philosopher %d will try for right fork\n", id);
		while(inUse[id])
			pthread_cond_wait(&forks[id], &m);
		inUse[id] = 1;
		printf("Philosopher %d will try for left fork\n", id);
		while(inUse[(id+1)%5])
			pthread_cond_wait(&forks[(id+1)%5], &m);
		inUse[(id+1)%5] = 1;
		pthread_mutex_unlock(&m);
		printf("Philosopher %d has forks; will eat\n", id);
		t.tv_sec = 0;
		t.tv_nsec = (rand() % range) + base;
		nanosleep(&t, 0);
		pthread_mutex_lock(&m);
		printf("Philosopher %d finished eating; releasing forks\n", id);
		inUse[id] = 0;
		pthread_cond_signal(&forks[id]);
		printf("Philosopher %d released right fork\n", id);
		inUse[(id+1)%5] = 0;
		pthread_cond_signal(&forks[(id+1)%5]);
		printf("Philosopher %d released left fork\n", id);
		roomCnt--;
		pthread_cond_signal(&room);
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
		pthread_cond_init(&forks[i], 0);
		inUse[0] = 0;
	}
	pthread_cond_init(&room, 0);
	roomCnt = 0;
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
