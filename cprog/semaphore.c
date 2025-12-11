#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
sem_t semaphore;  
void* routine(){
	sem_wait(&semaphore); //down op
	printf("Executing the critical section..\n");
	sem_post(&semaphore); //up op
}
int main(){
	pthread_t t[5];
	sem_init(&semaphore,0,1);  
	// 0 → semaphore is shared only between threads of the same process, if multiprocess, use 1
	// 1 → initial value (1 = binary semaphore/acts like a mutex) and >1 means counting semaphore
	for(int i=0;i<5;i++){
		pthread_create(&t[i],NULL,&routine,NULL); 
		// dont include both create and join in a same loop , else it will create and stop (become single threaded)
	}
	for(int i=0;i<5;i++){
		pthread_join(t[i],NULL); 
	}
	sem_destroy(&semaphore);  
	return 0;
}
