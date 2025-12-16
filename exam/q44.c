/*Write a C program where parent process send a number to child process using PIPE and child
process compute the Fibonacci series upto that number..*/

#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
void fibonacci(int n){
	int a=0;
	int b=1;
	int c;
	printf("%d\t%d\t",a,b);
	for(int i=0;i<n-2;i++){
		c=a+b;
		printf("%d\t",c);
		a=b;
		b=c;
	}
}
int main(){ 
	int fd[2];  
	pipe(fd);  
	int id=fork(); 
	if(id>0){  
		close(fd[0]);  
		int x;
		printf("Enter a number to parent : ");
		scanf("%d",&x);
		write(fd[1],&x,sizeof(x)); 
		close(fd[1]); 
	}else{
		close(fd[1]); 
		int y;
		read(fd[0],&y,sizeof(y));
		fibonacci(y);
		close(fd[0]);
	}
}
