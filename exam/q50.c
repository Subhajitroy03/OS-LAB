/*Write a C program to create two threads. One thread will take input of an array and 2nd thread
performs the linear search operation. ( Apply semaphore)*/

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
void* linear_search(void* a){
	int element=*(int*)a;  
	sem_wait(&lock);
	for(int i=0;i<n;i++){
		if(arr[i]==element){
			printf("The element is found at index: %d",i);
			sem_post(&lock);
			pthread_exit(NULL);
		}
	}
	printf("The element is not found");
	sem_post(&lock);
	pthread_exit(NULL);
}


int main(){
	sem_init(&lock,0,1);
	pthread_t t1,t2;
	int element;
	printf("Enter the element to search: ");
	scanf("%d",&element);
	pthread_create(&t1,NULL,&input_array,NULL);  
	pthread_create(&t2,NULL,&linear_search,&element); 
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	sem_destroy(&lock);
	return 0;
}
