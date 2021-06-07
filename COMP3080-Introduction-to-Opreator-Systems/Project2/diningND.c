// Dining philosopher solution using Pthreads and POSIX semaphores
// Deadlock prevention by limiting concurrent eaters to only four out of five 
// philosophers

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#define RANGE 1000000000
#define BASE   500000000
int range = RANGE;
int base = BASE;

sem_t	  forks[5];
sem_t	  room;

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
		sem_wait(&room);
		printf("Philosopher %d will try for right fork\n", id);
		sem_wait(&forks[id]);
		printf("Philosopher %d  will try for left fork\n", id);
		sem_wait(&forks[(id+1)%5]);
		printf("Philosopher %d has forks; will eat\n", id);
		t.tv_sec = 0;
		t.tv_nsec = (rand() % range) + base;
		nanosleep(&t, 0);
		printf("Philosopher %d finished eating; releasing forks\n", id);
		sem_post(&forks[id]);
		printf("Philosopher %d released right fork\n", id);
		sem_post(&forks[(id+1)%5]);
		printf("Philosopher %d released left fork\n", id);
		sem_post(&room);
		printf("Philosopher %d left dining room\n", id);
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

	for(i = 0; i < 5; i++)
		sem_init(&forks[i], 0, 1);
	sem_init(&room, 0, 4);

	int id[5];
	for(i = 0; i < 5; i++) {
		id[i] = i;
		if (pthread_create(&phils[i], 0, phil, &id[i]) != 0)
			perror("Pthread_create error");
	}
	for(i = 0; i < 5; i++)
		pthread_join(phils[i], 0);
}  
