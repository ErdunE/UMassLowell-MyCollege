#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t TA_wake, Student_wait, mutex;
int chairs = 3;
int TABusy = 0;
void *student(void *args) {
	int sn = *((int *) args);
	int noChairs;
	sleep(rand() % 10+2);
	while(1) {
		sem_wait(&mutex);
		
		if(chairs == 0) {
			printf("Student %d: No chairs, not waiting\n", sn);
			sem_post(&mutex);
			sleep(rand() % 10+5);
		} else {
			printf("Student %d: %d chairs left\n", sn, chairs);
			if(TABusy) {
				printf("Student %d: TA Busy, taking a seat\n", sn);
				chairs--;
			} else {
				printf("Student %d: TA is not busy\n", sn);
				TABusy = 1;
			}
			sem_post(&TA_wake);
			sem_post(&mutex);
			sem_wait(&Student_wait);
			printf("Student %d: Got all the help I need for now!\n", sn);
			sem_wait(&mutex);
			if(chairs < 3)
				chairs++;
			sem_post(&mutex);
			sleep(rand() % 10+5);
		}
	}
}

void *TA(void *args) {
	while(1) {
		sem_wait(&TA_wake);
		printf("TA: Student is here for help\n");
		sleep(rand() % 8+1);
		sem_post(&mutex);
		printf("Finished helping this student\n");
		sem_post(&Student_wait);
		if(chairs == 3) {
			printf("No students waiting; taking a nap\n");
			TABusy = 0;
		}
		sem_post(&mutex);
	}
}

int main (int argc, char **args) {
	
	pthread_t ta, students[5];
	sem_init(&TA_wake, 0, 0);
	sem_init(&Student_wait, 0, 0);
	sem_init(&mutex, 0 , 1);
	
	pthread_create(&ta, 0, TA, 0);
	int i;
	int sn[5];
	for(i = 0; i < 5; i++) {
		sn[i] = i+1;
		pthread_create(&students[i], 0, student, &sn[i]);
	}
	
	for(i = 0; i < 5; i++)
		pthread_join(students[i], 0);
}