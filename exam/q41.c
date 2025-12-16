/*Write a C program to create two threads. One thread will take input of an array and 2nd thread
will perform the bubble sort to sort those numbers.( Apply mutex lock and unlock)*/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include <stdlib.h>
#define MAX 100
int arr[MAX];
int n;
pthread_mutex_t lock;

void* input_array(void* a){
	pthread_mutex_lock(&lock);
	printf("Enter the number of element: ");
	scanf("%d",&n);
	int element;
	for(int i=0;i<n;i++){
		printf("Enter the element at %d : ",i);
		scanf("%d",&element);
		arr[i]=element;
	}
	pthread_mutex_unlock(&lock);
	pthread_exit(NULL);

}
void* bubblesort(void* a){  
	pthread_mutex_lock(&lock);
	for(int i=0;i<n-1;i++){
		for(int j=0;j<n-i-1;j++){
			if(arr[j]>arr[j+1]){
				int temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
	
	for(int i=0;i<n;i++){
		printf("%d\t",arr[i]);
	}
	
	pthread_mutex_unlock(&lock);
	pthread_exit(NULL);
}


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
