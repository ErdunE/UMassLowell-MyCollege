#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define SUGAR 0
#define MILK 1
#define LEMON 2

#define RANGE 1000000000
#define BASE 500000000
#define CUPPAS 1000

int range = RANGE;
int base = BASE;

sem_t drinkerSems[3], motherSem, mutex;
char *name[] = {"Sugar", "Milk", "Lemon"};
char *needs[] = {"milk and lemon", "sugar and lemon", "sugar and milk"};

void *motherChores(void *arg) {
	printf("Mother has entered the room\n");
	srand(100);
	int cuppas = 0;
	while (cuppas++ < CUPPAS) {
		int drinker = rand() % 3;
		sem_wait(&mutex);
		switch (drinker) {
		case SUGAR:
			printf("Mother puts %s on table", needs[SUGAR]);
			sem_post(&drinkerSems[SUGAR]);
			break;
		case MILK:
			printf("Mother puts %s on table", needs[MILK]);
			sem_post(&drinkerSems[MILK]);
			break;
		case LEMON:
			printf("Mother puts %s on table", needs[LEMON]);
			sem_post(&drinkerSems[LEMON]);
			break;
		default:
			printf("should not get here\n");
		}
		printf(" for cuppa %d\n", cuppas);
		sem_post(&mutex);
		sem_wait(&motherSem);
	}
}

void *drinker(void *args) {
	int me = *((int *) args);
	printf("%s has entered the room\n", name[me]);
	while (1) {
		sem_wait(&drinkerSems[me]);
		sem_wait(&mutex);

		printf("%s takes %s from table\n", 
				name[me], needs[me]);

		sem_post(&motherSem);
		sem_post(&mutex);
		printf("%s enjoys a nice cuppa\n", 
			name[me], needs[me]);
		struct timespec t;
		t.tv_sec = 0;
		t.tv_nsec = rand() % range + base;
		nanosleep(&t, 0);
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
	

	pthread_t drinkers[3], mother;
	sem_init(&motherSem, 0, 0);
	sem_init(&drinkerSems[SUGAR], 0, 0);
	sem_init(&drinkerSems[MILK], 0, 0);
	sem_init(&drinkerSems[LEMON], 0, 0);
	sem_init (&mutex, 0, 1);

	pthread_create(&mother, 0, motherChores, (void *)0);
	int s = SUGAR;
	pthread_create(&drinkers[SUGAR], 0, drinker, &s);
	int m = MILK;
	pthread_create(&drinkers[MILK], 0, drinker, &m);
	int l = LEMON;
	pthread_create(&drinkers[LEMON], 0, drinker, &l);

	pthread_join(mother, 0);
	pthread_cancel(drinkers[SUGAR]);
	pthread_cancel(drinkers[MILK]);
	pthread_cancel(drinkers[LEMON]);
}
