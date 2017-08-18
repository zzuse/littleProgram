#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t mutex, empty, full;
const unsigned int BUFFER=10;
int buffer[10]={0,0,0,0,0,0,0,0,0,0};
int indexProducer=0;
int indexConsumer=0;

void printBuffer(char *who,int pos);

void produce(void)
{
    sleep(5);
    printf("produce one\n");
}

void consume(void)
{
    sleep(10);
    printf("consume one\n");
}

void* producer(void* arg) {
    while(1) {
        produce();
        sem_wait(&empty);
        sem_wait(&mutex);
        indexProducer=indexProducer%BUFFER;
        buffer[indexProducer]=1;
        indexProducer++;
        printBuffer("produce to buffer",indexProducer-1);
        sem_post(&mutex);
        sem_post(&full);
    }
}

void* consumer(void* arg) {
    while(1){
        sem_wait(&full);
        sem_wait(&mutex);
        indexConsumer=indexConsumer%BUFFER;
        buffer[indexConsumer]=0;
        indexConsumer++;
        printBuffer("consume from buffer",indexConsumer-1);
        sem_post(&mutex);
        sem_post(&empty);
        consume();
    }
}

int main(int argc, char *argv[]) {
    pthread_t producerThread,consumerThread;
    const unsigned int n=BUFFER;
    sem_init(&empty,0,n);
    sem_init(&full,0,0);
    sem_init(&mutex,0,1);
    if(pthread_create(&producerThread,NULL,producer,NULL))
    {
        printf("producer create failed\n");
        exit(1);
    }
    if(pthread_create(&consumerThread,NULL,consumer,NULL))
    {
        printf("consumer create failed\n");
        exit(1);
    }   
    pthread_join(producerThread,NULL);
    pthread_join(consumerThread,NULL);
    return 0;
}

void printBuffer(char * who,int pos)
{
    int i;
    printf("%s accessed %d:\n",who,pos);
    for(i=0;i<BUFFER;i++)
    {
        printf("___");
    }
    printf("\n");
    for(i=0;i<BUFFER;i++)
        printf("|%d|",buffer[i]);
    printf("\n");
    for(i=0;i<BUFFER;i++)
    {
        printf("———");
    }
    printf("\n");
}

