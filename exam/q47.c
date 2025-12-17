/*Write a C program to create three threads. A shared variable will be increased by all of them
such that no race condition will arise. ( Apply mutex lock and unlock)*/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include <stdlib.h>

int n=5;
pthread_mutex_t lock;

void* routine(void* a){
	pthread_mutex_lock(&lock);
	n++;
	printf("Variable of variable after increment : %d\n",n);
	pthread_mutex_unlock(&lock);
	pthread_exit(NULL);
}
int main(){
	pthread_t t[3];
	pthread_mutex_init(&lock,NULL);
	printf("Variable value before starting : %d\n",n);
	for(int i=0;i<3;i++){
		pthread_create(&t[i],NULL,&routine,NULL); 
	}
	for(int i=0;i<3;i++){
		pthread_join(t[i],NULL); 
	}
	pthread_mutex_destroy(&lock);
	return 0;
}
