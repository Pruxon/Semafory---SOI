#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define MAX 3

int buforek1 [MAX];
int buforek2 [MAX];
int buforek3 [MAX];
int buforek4 [MAX];
int buforek5 [MAX];

int size1;
int size2;
int size3;
int size4;
int size5;

int MAX_TIME = 10000;
int PROD_TIME = 1;
int CONS_TIME = 100;

sem_t empty[5];

sem_t full[5];

sem_t mutex[5];

pthread_t *producer_;
pthread_t *consumer_1;
pthread_t *consumer_2;
pthread_t *consumer_3;
pthread_t *consumer_4;
pthread_t *consumer_5;

int produce(int q_nr)
{
    int p = 1 +rand()%100;
    printf ("Producer produced number: %d and put it to %d buffer\n", p, q_nr);
    return p;
}
void consume(int p, int q_nr)
{
    printf ("Consumer consumed %d from %d buffer\n", p, q_nr);
}
void* producer(void *args)
{
    int i;
    for (i = 0; i < MAX_TIME; i++)
    {
        if (i%PROD_TIME == 0)
            {
                int buf_nr = rand()%5;
                if (buf_nr == 0)
                {
                    int p = produce(1);
                    sem_wait(&empty[0]);
                    sem_wait(&mutex[0]);
                    size1++;
                    buforek1[size1] = p;
                    sem_post(&mutex[0]);
                    sem_post(&full[0]);
                }
                else if (buf_nr == 1)
                {
                    int p = produce(2);
                    sem_wait(&empty[1]);
                    sem_wait(&mutex[1]);
                    size2++;
                    buforek2[size2] = p;
                    sem_post(&mutex[1]);
                    sem_post(&full[1]);
                }
                else if (buf_nr == 2)
                {
                    int p = produce(3);
                    sem_wait(&empty[2]);
                    sem_wait(&mutex[2]);
                    size3++;
                    buforek3[size3] = p;
                    sem_post(&mutex[2]);
                    sem_post(&full[2]);
                }
                else if (buf_nr == 3)
                {
                    int p = produce(4);
                    sem_wait(&empty[3]);
                    sem_wait(&mutex[3]);
                    size4++;
                    buforek4[size4] = p;
                    sem_post(&mutex[3]);
                    sem_post(&full[3]);
                }
                else if (buf_nr == 4)
                {
                    int p = produce(5);
                    sem_wait(&empty[4]);
                    sem_wait(&mutex[4]);
                    size5++;
                    buforek5[size5] = p;
                    sem_post(&mutex[4]);
                    sem_post(&full[4]);
                }
            }
            sleep(1);
    }
    return NULL;
}
void* consumer1(void* args)
{
    int c, i;
    for (i = 0; i < MAX_TIME; i++)
    {
    if (i%CONS_TIME == 0){
        sem_wait(&full[0]);
        sem_wait(&mutex[0]);
        c = buforek1[0];
        consume (c, 1);
        size1--;
        int j;
        for (j = 0; j < size1+1; j++)
            buforek1[j] = buforek1[j+1];
        sem_post(&mutex[0]);
        sem_post(&empty[0]);
        sleep(2);
    }
    }
    return NULL;
}
void* consumer2(void* args)
{
    int c, i;
    for (i = 0; i < MAX_TIME; i++)
    {
    if (i%CONS_TIME == 0){
        sem_wait(&full[1]);
        sem_wait(&mutex[1]);
        c = buforek2[0];
        consume (c, 2);
        size2--;
        int j;
        for (j = 0; j < size2+1; j++)
            buforek2[j] = buforek2[j+1];
        sem_post(&mutex[1]);
        sem_post(&empty[1]);
        sleep(4);
    }
    }
    return NULL;
}
void* consumer3(void* args)
{
    int c, i;
    for (i = 0; i < MAX_TIME; i++)
    {
    if (i%CONS_TIME == 0){
        sem_wait(&full[2]);
        sem_wait(&mutex[2]);
        c = buforek3[0];
        consume (c, 3);
        size3--;
        int j;
        for (j = 0; j < size3+1; j++)
            buforek3[j] = buforek3[j+1];
        sem_post(&mutex[2]);
        sem_post(&empty[2]);
        sleep(6);
    }
    }
    return NULL;
}
void* consumer4(void* args)
{
    int c, i;
    for (i = 0; i < MAX_TIME; i++)
    {
    if (i%CONS_TIME == 0){
        sem_wait(&full[3]);
        sem_wait(&mutex[3]);
        c = buforek4[0];
        consume (c, 4);
        size4--;
        int j;
        for (j = 0; j < size4+1; j++)
            buforek4[j] = buforek4[j+1];
        sem_post(&mutex[3]);
        sem_post(&empty[3]);
        sleep(8);
    }
    }
    return NULL;
}
void* consumer5(void* args)
{
    int c, i;
    for (i = 0; i < MAX_TIME; i++)
    {
        sem_wait(&full[4]);
        sem_wait(&mutex[4]);
        c = buforek5[0];
        consume (c, 5);
        size5--;
        int j;
        for (j = 0; j < size5+1; j++)
            buforek5[j] = buforek5[j+1];
        printf("bufor 5 po konsumencie: ");
        for (j = 0; j < size5+1; j++)
            printf ("%d ", buforek5[j]);
        printf("\n");
        sem_post(&mutex[4]);
        sem_post(&empty[4]);
        sleep(10);
    }
    return NULL;
}
int main()
{

    srand(time(NULL));

    size1 = -1;
    size2 = -1;
    size3 = -1;
    size4 = -1;
    size5 = -1;

    int i;


    producer_ = (pthread_t*) malloc(sizeof(pthread_t));
    consumer_1 = (pthread_t*) malloc(sizeof(pthread_t));
    consumer_2 = (pthread_t*) malloc(sizeof(pthread_t));
    consumer_3 = (pthread_t*) malloc(sizeof(pthread_t));
    consumer_4 = (pthread_t*) malloc(sizeof(pthread_t));
    consumer_5 = (pthread_t*) malloc(sizeof(pthread_t));

    for (i = 0; i < 5; i++)
    {
        sem_init(&empty[i], 0, MAX);
        sem_init(&full[i], 0, 0);
        sem_init(&mutex[i], 0, 1);
    }


    pthread_create(producer_, NULL, &producer, NULL);
    pthread_create(consumer_1, NULL, &consumer1, NULL);
    pthread_create(consumer_2, NULL, &consumer2, NULL);
    pthread_create(consumer_3, NULL, &consumer3, NULL);
    pthread_create(consumer_4, NULL, &consumer4, NULL);
    pthread_create(consumer_5, NULL, &consumer5, NULL);

    pthread_join(*producer_, NULL);
    pthread_join(*consumer_1, NULL);
    pthread_join(*consumer_2, NULL);
    pthread_join(*consumer_3, NULL);
    pthread_join(*consumer_4, NULL);
    pthread_join(*consumer_5, NULL);

    return 0;
}




