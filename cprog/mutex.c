#include<stdio.h>
#include<pthread.h>
#include <unistd.h>
pthread_mutex_t mutex;   //declaring a mutex var
void* routine(){
	pthread_mutex_lock(&mutex); //lock before entering critical section..
	printf("Executing the critical section..\n");
	pthread_mutex_unlock(&mutex); //unlock after the work
}
int main(){
	pthread_t t1,t2;
	pthread_mutex_init(&mutex,NULL);  //initialisation 
	pthread_create(&t1,NULL,&routine,NULL);
	pthread_create(&t2,NULL,&routine,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL); 
	pthread_mutex_destroy(&mutex);  //destroy
	
	return 0;
}
