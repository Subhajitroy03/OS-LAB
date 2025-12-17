/*Write a C program to create multiple threads and check the memory address of a variable before
and after modification by all the threads. Synchronize the threads using mutex lock-unlock.*/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include <stdlib.h>

int n;
pthread_mutex_t lock;

void* routine(void* a){
	pthread_mutex_lock(&lock);
	printf("Variable address before modification : %p\n ",&n);
	n++;
	printf("Variable address after modification : %p\n ",&n);
	pthread_mutex_unlock(&lock);
	pthread_exit(NULL);
}
int main(){
	pthread_t t[10];
	pthread_mutex_init(&lock,NULL);
	printf("Variable address before starting : %p\n",&n);
	for(int i=0;i<10;i++){
		pthread_create(&t[i],NULL,&routine,NULL); 
	}
	for(int i=0;i<10;i++){
		pthread_join(t[i],NULL); 
	}
	pthread_mutex_destroy(&lock);
	return 0;
}
