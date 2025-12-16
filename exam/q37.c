/*Write a C program where the parent process sends a number to child process using PIPE and
child process computes the factors of that number.*/

#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
void factors(int n){
	for(int i=1;i<=n;i++){
		if(n%i==0){
			printf("%d \t",i);
		}
	}
}
int main(){ 
	int fd[2];  // fd[0] for read and fd[1] for write
	pipe(fd);  //creating a pipe and pipe needs an array of size 2
	int id=fork(); // fork will create separate fd for child and parent , both are independent fd
	if(id==0){  //child
		close(fd[0]);  //child doesnot need read , so close
		int x;
		printf("Enter a number to child : ");
		scanf("%d",&x);
		write(fd[1],&x,sizeof(x)); 
		close(fd[1]); //close write now
	}else{
		close(fd[1]); //same , parent donot need write so close it
		int y;
		read(fd[0],&y,sizeof(y));
		printf("Factors are: ");
		factors(y);
		close(fd[0]);
	}
	/// pipe , fork , write , read everyone returns -1 when error , handle it better
}
