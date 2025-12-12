#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>

#define philosopher_no 10

sem_t forks[philosopher_no];

void* philosopher(void* n){
	int id=*(int*)n;
	int left=id;
	int right=(id+1)%philosopher_no;
	printf("Philosopher %d is thinking...\n",id);
	
	//deadlock prevention --> change the order of fork picking for the last philosopher...
	while(1){
		if(left<right){
			sem_wait(&forks[left]);
			sem_wait(&forks[right]);
			printf("Philosopher %d is eating with forks %d and %d \n",id,left,right);
			sleep(3);
			sem_post(&forks[right]);
			sem_post(&forks[left]);		
		}else{
			sem_wait(&forks[right]);
			sem_wait(&forks[left]);
			printf("Philosopher %d is eating with forks %d and %d \n",id,left,right);
			sleep(3);
			sem_post(&forks[left]);
			sem_post(&forks[right]);
		}
		
	}
	
}

int main(){
	
	for(int i=0;i<philosopher_no;i++){
		sem_init(&forks[i],0,1);
	}
	
	pthread_t philosophers[philosopher_no];
	int ids[philosopher_no];
	
	for(int i=0;i<philosopher_no;i++){
		ids[i]=i;
		pthread_create(&philosophers[i],NULL,&philosopher,&ids[i]);
		
	}
	
	for(int i=0;i<philosopher_no;i++){
		pthread_join(philosophers[i],NULL);
	}
	
	for(int i=0;i<philosopher_no;i++){
		sem_destroy(&forks[i]);
	}
	return 0;
}
