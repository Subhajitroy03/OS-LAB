/*Write a C program where parent process send a number to child process using PIPE and child
process compute whether that number is Armstrong number or not.*/

#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<math.h>

int count_digit(int n){
	if(n==0) return 1;
	int count=0;
	while(n!=0){
		n=n/10;
		count++;
	}
	return count;
}
int power(int base,int power){
	int result=1;
	for(int i=1;i<=power;i++){
		result=result*base;
	}
	return result;
}
void Armstrong(int n){
	int count=count_digit(n);
	int n1=n;	
	int num=0;
	while(n!=0){
		num=num+ power(n%10,count);
		n=n/10;
	}
	if(n1==num){
		printf("Yes the number is Armstrong \n");
	}else{
		printf("No the number is not Armstrong \n");
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
		Armstrong(y);
		close(fd[0]);
	}
	/// pipe , fork , write , read everyone returns -1 when error , handle it better
}
