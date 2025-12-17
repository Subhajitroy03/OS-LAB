/*Write a C program to create two threads. 1st thread will take input of two matrixes and 2nd
thread will perform addition operation of those two matrices. (Apply semaphore)*/

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#define r 3
#define c 2

int arr1[r][c];
int arr2[r][c];
int result[r][c];

sem_t lock;
void* input(void* a){
	sem_wait(&lock);
	printf("For Array 1\n");
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			printf("Enter element (%d,%d): ",i,j);
			scanf("%d",&arr1[i][j]);
		}
	}
	printf("For Array 2\n");
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			printf("Enter element (%d,%d): ",i,j);
			scanf("%d",&arr2[i][j]);
		}
	}
	sem_post(&lock);
	pthread_exit(NULL);
	
}

void* addition(void* a){
	sem_wait(&lock);
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			result[i][j]=arr1[i][j]+arr2[i][j];
		}
	}
	printf("Result: \n");
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			printf("%d\t",result[i][j]);
		}
		printf("\n");
	}
	sem_post(&lock);
	pthread_exit(NULL);
	
}

int main(void){
	sem_init(&lock,0,1);
	pthread_t t1,t2;
	pthread_create(&t1,NULL,&input,NULL);
	pthread_join(t1,NULL);
	pthread_create(&t2,NULL,&addition,NULL);
	pthread_join(t2,NULL);
	sem_destroy(&lock);
}
