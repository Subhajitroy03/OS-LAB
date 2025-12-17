/*Write a C program to create three threads. A value will be taken by one thread. 2nd thread will
calculate the factorial of that number and third thread will calculate that the number is prime
number or not. No race condition should arise. (Apply mutex lock and unlock)*/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include <stdlib.h>

int n;
pthread_mutex_t lock;

void* input(void* a){
	pthread_mutex_lock(&lock);
	printf("Enter the value of n: ");
	scanf("%d",&n);
	pthread_mutex_unlock(&lock);
	pthread_exit(NULL);
}
void* factorial(void* a){
	pthread_mutex_lock(&lock);
	int fac=1;
	for(int i=1;i<=n;i++){
		fac=fac*i;
	}
	printf("Factorial of the number: %d\n",fac);
	pthread_mutex_unlock(&lock);
	pthread_exit(NULL);
}
void* is_prime(void* a){
	pthread_mutex_lock(&lock);
	int flag=1;
	for(int i=2;i<n;i++){
		if(n%i==0){
			flag=0;
			break;
		}
	}
	
	if(flag){
		printf("%d is prime number..\n",n);
	}else{
		printf("%d is not a prime number..\n",n);
	}
	
	pthread_mutex_unlock(&lock);
	pthread_exit(NULL);
}

int main(){
	pthread_t t1,t2,t3;
	pthread_mutex_init(&lock,NULL);
	pthread_create(&t1,NULL,&input,NULL);
	pthread_join(t1,NULL);
	pthread_create(&t2,NULL,&factorial,NULL);
	pthread_create(&t3,NULL,&is_prime,NULL);
	pthread_join(t2,NULL); 
	pthread_join(t3,NULL); 
	pthread_mutex_destroy(&lock);
	return 0;
}
