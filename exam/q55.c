/*Write C program to take n integer numbers as input of an array through one thread and find the
prime numbers from the array by another thread using Semaphore.*/

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
int isprime(int n){
	if(n<=1){
		return 0;
	}
	for(int i=2;i<n;i++){
		if(n%i==0){
			return 0;
		}
	}
	return 1;
}
void* prime(void* a){
	sem_wait(&lock);
	printf("List of primes: ");
	for(int i=0;i<n;i++){
		if(isprime(arr[i])){
			printf("%d ",arr[i]);
		}
	}
	sem_post(&lock);
	pthread_exit(NULL);
}


int main(){
	sem_init(&lock,0,1);
	pthread_t t1,t2;
	pthread_create(&t1,NULL,&input_array,NULL);  
	pthread_create(&t2,NULL,&prime,NULL); 
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	sem_destroy(&lock);
	return 0;
}
