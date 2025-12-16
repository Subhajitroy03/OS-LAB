/*Write a C program to create multiple threads and check the memory address of a variable before
and after modification by all the threads. Synchronize the threads using mutex lock-unlock.*/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include <stdlib.h>
#define MAX 100
int arr[MAX];
int n;
pthread_mutex_t lock;

void* 
int main(){
	pthread_t t1,t2;
	pthread_mutex_init(&lock,NULL);
	pthread_create(&t1,NULL,&input_array,NULL);  
	pthread_create(&t2,NULL,&bubblesort,NULL); 
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_mutex_destroy(&lock);
	return 0;
}
