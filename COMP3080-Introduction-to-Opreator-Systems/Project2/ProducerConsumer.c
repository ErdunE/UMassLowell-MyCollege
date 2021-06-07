#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 26
char buffer[SIZE];
int head, tail;
sem_t mx, full, empty;
FILE *fd[5];

void *producer(void *arg) {
    char item = 'a';

    while (1) {
        sem_wait(&empty);
        sem_wait(&mx);
        
        buffer[tail] = item++;
        tail = (tail + 1) % SIZE;
        if (item >'z') {
            item = 'a';
        }
    
        sem_post(&mx);
        sem_post(&full);

        usleep(90000);
    }
}

void *consumer(void *arg) {
    char item;
    int f = *(int *)arg;
    int num = 0;
    char tag = '0';
    while(num < 30) {

        sem_wait(&full);
        sem_wait(&mx);
        item = buffer[head];
        if (num++ % 30 == 0) {
            if (num != 1)
                putc('\n', fd[f]);
            putc(tag+f, fd[f]);
            putc(':', fd[f]);
            putc(' ', fd[f]);
        }

        usleep(150000);
        buffer[head] = ' ';

        usleep(150000);
    

        head = (head + 1) % SIZE;
        putc(item, fd[f]); putc(' ',fd[f]);
        fflush(fd[f]);

        sem_post(&mx);
        sem_post(&empty);
//        usleep(90000);
    }
    putc('\n', fd[f]);
}

int main (int argc, char **argv) {

    sem_init(&mx,  0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, SIZE);
    head = tail = 0;

    if (argc < 3) {
        fprintf(stderr, "Usage: ProducerConsumer <# prod> <#cons>\n");
        exit(-1);
    }

    int nprod = atoi(argv[1]);
    int ncons = atoi(argv[2]);
    if (nprod > 5 || ncons > 5) {
        fprintf(stderr, "You are only allowd five of each\n");
        exit(-1);
    }
    int i;
    for (i = 0; i < SIZE; i++)
        buffer[i] = ' ';
    char *c = (char *) malloc(strlen("output ")+1);
    strncpy(c, "output ", strlen("output ")+1);
    char ci = '0';
    int f[ncons];
    for(i = 0; i < ncons; i++) {
        c[6] = ci++;
        fd[i] = fopen(c, "w");
        f[i] = i;
    }
    pthread_t p[nprod], ct[ncons];
    for (i = 0; i < ncons; i++)
        pthread_create(&ct[i], 0, consumer, &f[i]);
    for (i = 0; i <nprod; i++)
        pthread_create(&p[i], 0, producer, 0);

    for (i = 0; i < ncons; i++) {
        pthread_join(ct[i], 0);
        fclose(fd[i]);
    }
}
        
        
