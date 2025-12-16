/*Write a C program to create two threads. One thread will take input of an array and 2nd thread
prints those numbers in reverse order. ( Apply semaphore)*/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include <stdlib.h>
#include<semaphore.h>
#define MAX 100

int arr[MAX];
int n;
sem_t lock;

void* input_array(void* a){
	sem_wait(&lock);
	printf("Enter the number of element: ");
	scanf("%d",&n);
	int element;
	for(int i=0;i<n;i++){
		printf("Enter the element at %d : ",i);
		scanf("%d",&element);
		arr[i]=element;
	}
	sem_post(&lock);
	pthread_exit(NULL);

}
void* reverse(void* a){  
	sem_wait(&lock);
	
	for(int i=n-1;i>=0;i--){
		printf("%d\t",arr[i]);
	}
	
	sem_post(&lock);
	pthread_exit(NULL);
}


int main(){
	sem_init(&lock,0,1);
	pthread_t t1,t2;
	pthread_create(&t1,NULL,&input_array,NULL);  
	pthread_create(&t2,NULL,&reverse,NULL); 
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	sem_destroy(&lock);
	return 0;
}
