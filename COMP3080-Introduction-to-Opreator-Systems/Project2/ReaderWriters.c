#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

// These are the globals shared by all threads, including main
#define RANGE 1000000000
#define BASE 500000000
int rICrange = RANGE;
int rICbase = BASE;
int rOOCrange = RANGE;
int rOOCbase = BASE;
int wICrange = RANGE;
int wICbase = BASE;
int wOOCrange = RANGE;
int wOOCbase = BASE;
int keepgoing = 1;
int totalReads = 0;
int totalWrites = 0;

// The global area must include semaphore declarations and
// declarations of any state variables (reader counts,
// total number of readers and writers).

// semaphore for reader-writer
sem_t rw_mutex;
// semaphore for reader
sem_t mutex;
// how many reader are in critical section
int reader_count = 0;

// Use this function to sleep within the threads
void threadSleep(int range, int base) {
    struct timespec t;
    t.tv_sec = 0;
    t.tv_nsec = (rand() % range) + base;
    nanosleep(&t, 0);
}

// safe sem wait
void Sem_wait(sem_t* sem) {
    if (sem_wait(sem) < 0) {
        perror("sem_wait failed");
        exit(EXIT_FAILURE);
    }
}

// safe sem post
void Sem_post(sem_t* sem) {
    if (sem_post(sem) < 0) {
        perror("sem_post failed");
        exit(EXIT_FAILURE);
    }
}

// reader thread function
void *readers(void *args) {
    int id = *((int *) args);
    threadSleep(rOOCrange, rOOCbase);
    while (keepgoing) {
        // Add code for each reader to enter the
        // reading area.
        // The reader_count variable must be
        // incremented just before entering the
        // reader area.

        // reader wants to enter the critical section
        Sem_wait(&mutex);
        // increase reader count
        ++reader_count;
        // there is at least one reader in the critical section
        if (reader_count == 1) {
            // ensure no writer can enter critical section
            Sem_wait(&rw_mutex);
        }
        // record a read
        ++totalReads;
        // other readers can enter while current reader is in critical section
        Sem_post(&mutex);

        // start reading
        printf("Reader %d starting to read\n", id);
        threadSleep(rICrange, rICbase);
        // finish reading
        printf("Reader %d finishing reading\n", id);

        // Add code for each reader to leave the
        // reading area.
        // the reader wants to leave
        Sem_wait(&mutex);
        // decrease the reader count
        --reader_count;
        // there is no reader in critical section
        if (reader_count == 0) {
            // the writer can write now
            Sem_post(&rw_mutex);
        }
        // the reader leaved
        Sem_post(&mutex);

        threadSleep(rOOCrange, rOOCbase);
    }
    printf("Reader %d quitting\n", id);

    return NULL;
}

void *writers(void *args) {
    int id = *((int *) args);
    threadSleep(wOOCrange, wOOCbase);
    while (keepgoing) {
        // Add code for each writer to enter
        // the writing area.

        // the writer want to enter critical section
        // when the writer in critical section, no other writers nor readers can enter
        Sem_wait(&rw_mutex);

        // record a writes
        ++totalWrites;

        // start writing
        printf("Writer %d starting to write\n", id);
        threadSleep(wICrange, wICbase);
        // finish writing
        printf("Writer %d finishing writing\n", id);

        // Add code for each writer to leave
        // the writing area.
        // the writer is leaving critical section
        Sem_post(&rw_mutex);

        threadSleep(wOOCrange, wOOCbase);
    }
    printf("Writer %d quitting\n", id);

    return NULL;
}

int main(int argc, char **argv) {
    int numRThreads = 0;
    int numWThreads = 0;
    if (argc == 11) {
        rICrange = atoi(argv[1]);
        rICbase = atoi(argv[2]);
        rOOCrange = atoi(argv[3]);
        rOOCbase = atoi(argv[4]);
        wICrange = atoi(argv[5]);
        wICbase = atoi(argv[6]);
        wOOCrange = atoi(argv[7]);
        wOOCbase = atoi(argv[8]);
        numRThreads = atoi(argv[9]);
        numWThreads = atoi(argv[10]);
    } else {
        printf("Usage: %s <reader in critical section sleep range> <reader in"
               "critical section sleep base> \n\t <reader out of critical section sleep range> <reader out"
               "of critical section sleep base> \n\t <writer in critical section sleep range> <writer in"
               "critical section sleep base> \n\t <writer out of critical section sleep range> <writer"
               "out of critical section sleep base> \n\t <number of readers> <number of writers>\n",
               argv[0]);
        exit(-1);
    }
    // Add declarations for pthread arrays, one for reader threads and
    // one for writer threads.
    // reader and writer thread ids
    pthread_t reader_tids[numRThreads];
    pthread_t writer_tids[numWThreads];

    // Add declarations for arrays for reader and writer thread identities. As in the
    // dining philosopher problem, arrays of int are used.
    // reader and writer ids
    int reader_ids[numRThreads];
    int writer_ids[numWThreads];

    // Add code to initialize the binary semaphores used by the readers and writers.
    // init reader-writer mutex
    if (sem_init(&rw_mutex, 0, 1) < 0) {
        perror("sem_init failed");
        exit(EXIT_FAILURE);
    }

    // init reader mutex
    if (sem_init(&mutex, 0, 1) < 0) {
        perror("sem_init failed");
        exit(EXIT_FAILURE);
    }

    // Add a for loop to create numRThread reader threads.
    for (int i = 0; i < numRThreads; ++i) {
        reader_ids[i] = i + 1;
        // create reader threads
        if (pthread_create(&reader_tids[i], NULL, readers, &reader_ids[i]) < 0) {
            perror("pthread_create failed");
            exit(EXIT_FAILURE);
        }
    }

    // Add a for loop to create numWThread writer threads.
    for (int i = 0; i < numWThreads; ++i) {
        writer_ids[i] = i + 1;
        // create writer threads
        if (pthread_create(&writer_tids[i], NULL, writers, &writer_ids[i]) < 0 ) {
            perror("pthread_create failed");
            exit(EXIT_FAILURE);
        }
    }

    // These statements wait for the user to type a character and press
    // the Enter key. Then, keepgoing will be set to 0, which will cause
    // the reader and writer threads to quit.
    char buf[256];
    scanf("%s", &buf);
    keepgoing = 0;

    // Add two for loops using pthread_join in order to wait for the reader
    // and writer threads to quit.
    for (int i = 0; i < numRThreads; ++i) {
        void* ret;
        // wait readers finish
        if (pthread_join(reader_tids[i], &ret) < 0) {
            perror("pthread_join failed");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < numWThreads; ++i) {
        void* ret;
        // wait writers finish
        if (pthread_join(writer_tids[i], &ret) < 0) {
            perror("pthread_join failed");
            exit(EXIT_FAILURE);
        }
    }

    printf("Total number of reads: %d\nTotal number of writes: %d\n",
           totalReads, totalWrites);
}
