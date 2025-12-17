/* Write a C program to create two threads. 1st thread will take input of two matrixes and 2nd
thread will perform the multiplication of those matrices. (Apply mutex lock and unlock)*/

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#define r1 3
#define c1 2
#define r2 2
#define c2 3

int arr1[r1][c1];
int arr2[r2][c2];
int result[r1][c2];

pthread_mutex_t lock;
void* input(void* a){
	pthread_mutex_lock(&lock);
	printf("For Array 1\n");
	for(int i=0;i<r1;i++){
		for(int j=0;j<c1;j++){
			printf("Enter element (%d,%d): ",i,j);
			scanf("%d",&arr1[i][j]);
		}
	}
	printf("For Array 2\n");
	for(int i=0;i<r2;i++){
		for(int j=0;j<c2;j++){
			printf("Enter element (%d,%d): ",i,j);
			scanf("%d",&arr2[i][j]);
		}
	}
	pthread_mutex_unlock(&lock);
	pthread_exit(NULL);
	
}

void* multiplication(void* a){
	if(c1!=r2){
		printf("Multiplication not possible \n");
		pthread_exit(NULL);
	}
	
	pthread_mutex_lock(&lock);
	///multiplication
	for(int i=0;i<r1;i++){
		for(int j=0;j<c2;j++){
			result[i][j]=0;
			for(int k=0;k<r2;k++){
				result[i][j]=result[i][j]+(arr1[i][k]*arr2[k][j]);
			}
		}
		
	}
	printf("Result: \n");
	for(int i=0;i<r1;i++){
		for(int j=0;j<c2;j++){
			printf("%d\t",result[i][j]);
		}
		printf("\n");
	}
	pthread_mutex_unlock(&lock);
	pthread_exit(NULL);
	
}

int main(void){
	pthread_mutex_init(&lock,NULL);
	pthread_t t1,t2;
	pthread_create(&t1,NULL,&input,NULL);
	pthread_join(t1,NULL);
	pthread_create(&t2,NULL,&multiplication,NULL);
	pthread_join(t2,NULL);
	pthread_mutex_destroy(&lock);
}
