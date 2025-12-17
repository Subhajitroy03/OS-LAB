/*Write a C program to implement reader-writer problem using Semaphore. (Writer has the highest
priority).*/

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

int rc=0;
sem_t mutex;
sem_t db;

sem_t turnstile;  
void* reader_func(void* a){
	int id=*(int*)a;
	while(1){
	 	sem_wait(&turnstile);
	 	sem_post(&turnstile);
     	// wait your turn
		sem_wait(&mutex);
		rc++;
		if(rc==1)
			sem_wait(&db);
		sem_post(&mutex);
		printf("Reader %d is reading..\n",id);
		sleep(2);

		sem_wait(&mutex);
		rc--;
		if(rc==0){
			sem_post(&db);
		}
		sem_post(&mutex);
		printf("Reader %d has finished reading..\n",id);
		sleep(2);
		
	}
	return NULL;
	
}
void* writer_func(void* b){
	int id=*(int*)b;
	while(1){
		sem_wait(&turnstile);     // block readers behind me
        sem_wait(&db);
        
		printf("Writer %d is writing..\n",id);
		sleep(3);
		sem_post(&db);
		sem_post(&turnstile);
		usleep(1000);
	}
	return NULL;
	
}

int main(){
	
	sem_init(&mutex,0,1);
	sem_init(&db,0,1);
	sem_init(&turnstile, 0, 1);
	
	pthread_t reader[10],writer[20];
	int rid[10],wid[20];
	
	for(int i=0;i<10;i++){
		rid[i]=i;
		pthread_create(&reader[i],NULL,&reader_func,&rid[i]);
	}
	for(int i=0;i<20;i++){
		wid[i]=i;
		pthread_create(&writer[i],NULL,&writer_func,&wid[i]);
	}
	for(int i=0;i<10;i++){
		pthread_join(reader[i],NULL);
	}
	for(int i=0;i<20;i++){
		pthread_join(writer[i],NULL);
	}
	
	sem_destroy(&mutex);
	sem_destroy(&db);
	sem_destroy(&turnstile);
	
}
