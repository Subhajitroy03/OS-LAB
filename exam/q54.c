//Write a C program to implement Producer-Consumer problem using Semaphore.
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
#define buffer_size 10

int producer_number=5;
int consumer_number=4;


sem_t empty;
sem_t full;
pthread_mutex_t mutex; // or sem_t binary_sem;


int buffer[buffer_size];

int in=0;
int out=0;

void* producer(){
	while(1){
		int x=rand()%100;
	
		sem_wait(&empty);
		pthread_mutex_lock(&mutex); //sem_wait(&binary_sem);
		
		buffer[in]=x;
		
		in=(in+1)%buffer_size;
				
		pthread_mutex_unlock(&mutex); //sem_post(&binary_sem);
		sem_post(&full);
		
		printf("Producer produced: %d \n",x);
		sleep(1);	
	}
	
}

void* consumer(){
	while(1){
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		
		int y=buffer[out];
		out=(out+1)%buffer_size;
		
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);	
		
		printf("Consumer consumed %d \n",y);
		sleep(2);
	}
		
}

int main(){
	srand(time(NULL));
	
	sem_init(&empty,0,buffer_size);
	sem_init(&full,0,0);
	pthread_mutex_init(&mutex,NULL); //sem_init(&binary_sem,1);
	
	pthread_t cons[consumer_number];
	pthread_t prod[producer_number];
	
	for(int i=0;i<producer_number;i++){
		pthread_create(&prod[i],NULL,&producer,NULL);
	}
	for(int i=0;i<consumer_number;i++){
		pthread_create(&cons[i],NULL,&consumer,NULL);
	}
	
	for(int i=0;i<producer_number;i++){
		pthread_join(prod[i],NULL);
	}
	for(int i=0;i<consumer_number;i++){
		pthread_join(cons[i],NULL);
	}
	
	pthread_mutex_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);
	
	return 0;
}
