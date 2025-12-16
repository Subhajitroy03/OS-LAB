/* Write a C program where parent process send a number to child process using PIPE and child
process compute all the prime numbers from 1 to that number.*/

#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>

int is_prime(int n){

	for(int i=2;i<=n/2;i++){
		if(n%i==0){
			return 0; //not prime
		}
	}
	return 1; //prime
}
void prime_range(int n){
	for(int i=2;i<=n;i++){
		if(is_prime(i)){
			printf("%d \t",i);
		}
	}
}

int main(){ 
	int fd[2];  // fd[0] for read and fd[1] for write
	pipe(fd);  //creating a pipe and pipe needs an array of size 2
	int id=fork(); // fork will create separate fd for child and parent , both are independent fd
	if(id>0){  
		close(fd[0]);  
		int x;
		printf("Enter a number to child : ");
		scanf("%d",&x);
		write(fd[1],&x,sizeof(x)); 
		close(fd[1]); 
	}else{
		close(fd[1]); 
		int y;
		read(fd[0],&y,sizeof(y));
		prime_range(y);
		close(fd[0]);
	}
	/// pipe , fork , write , read everyone returns -1 when error , handle it better
}
