#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

void *writer(void *arg);
void *reader(void *arg);
sem_t mutex;
sem_t wrt;
int readcount = 0, nwt, nrd;

int main()
{
    long int i;
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    printf("\nEnter number of readers: ");
    scanf("%d", &nrd);
    printf("\nEnter number of writers: ");
    scanf("%d", &nwt);
    pthread_t reader_threads[nrd], writer_threads[nwt];
    int writer_ids[nwt], reader_ids[nrd];

    for (i = 0; i < nwt; i++)
    {
        writer_ids[i] = i +1;
        pthread_create(&writer_threads[i], NULL, writer, writer_ids[i]);
    }

    for (i = 0; i < nrd; i++)
    {
        reader_ids[i] = i +1;
        pthread_create(&reader_threads[i], NULL, reader, reader_ids[i]);
    }

    for (i = 0; i < nwt; i++)
    {
        pthread_join(writer_threads[i], NULL);
    }

    for (i = 0; i < nrd; i++)
    {
        pthread_join(reader_threads[i], NULL);
    }

    sem_destroy(&wrt);
    sem_destroy(&mutex);

    pthread_exit(NULL); // Exit the main thread gracefully
}

void *reader(void *arg)
{
    int id = *((int *)arg);
 

    printf("\nReader %d is trying to enter the database for reading.", id);
    sem_wait(&mutex);
    readcount++;
    if (readcount == 1)
        sem_wait(&wrt);
    sem_post(&mutex);

    printf("\nReader %d is now reading in the database.", id);

    sem_wait(&mutex);
    readcount--;
    if (readcount == 0)
        sem_post(&wrt);
    sem_post(&mutex);

    printf("\nReader %d has left the database.\n", id);
    sleep(3);
    pthread_exit(NULL);
}

void *writer(void *arg)
{
    int id =*((int *)arg);
 

    printf("\nWriter %d is trying to enter the database for modifying data.", id);
    sem_wait(&wrt);
    printf("\nWriter %d is writing in the database.", id);
    sleep(3);
    printf("\nWriter %d is leaving the database.\n", id);
    sem_post(&wrt);
    pthread_exit(NULL);
}