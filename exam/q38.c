/*Write a C program that will create a child process by using the fork() system call , the parent
process will print the PID of itself, as well as the PID of the child. The child process will also
print the PID of its parent as well as the PID of itself.*/

#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
	int id=fork();
	if(id==0){
		printf("Child: Process ID: %d and Parent ID: %d \n",getpid(),getppid());
	}else if(id>0){
		printf("Parent: Process ID: %d and Parent ID: %d \n",getpid(),getppid());
	}else{
		printf("Error in creating fork..");
	}
	
}
