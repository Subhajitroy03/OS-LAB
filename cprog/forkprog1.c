// to create a child process using fork
#include<stdio.h>
#include<unistd.h>

int main(){
	printf("Inside main process...\n");
	int id=fork();
	printf("Programme starts...\n");
	/// wait(some time) -> optional
	//usleep(5000);
	if(id==0){
		printf("Inside Child process...\n");
	}else if(id>0){
		printf("Inside Parent(main) process with id = %d \n",id);
	}else{
		printf("Error in creating process..\n");
	}

}
