#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

// to compile -> gcc -pthread <filename>.c
/*
pthread_create(&t1,NULL,&routine,NULL);
First argument → where the thread ID is stored.
Second argument → thread attributes (NULL = default).
Third argument → function pointer (which thread will run).
Fourth argument → argument passed to the routine (NULL here).

*/
void* routine(){
	printf("Hello from threads..\n");
	sleep(2);
	printf("Ending thread...\n");
}
int main(){
	pthread_t t1,t2;
	pthread_create(&t1,NULL,&routine,NULL);
	pthread_create(&t2,NULL,&routine,NULL);
	pthread_join(t1,NULL); 
	pthread_join(t2,NULL);
	//This blocks the main thread until t1 and t2 finish.If you don't join: main may exit early → threads may get killed mid-execution.
	return 0;
}
