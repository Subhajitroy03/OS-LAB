/*Write a C program to create a child process. Parent process send a string to child process using
PIPE then child process will calculate how many, alphabet, numeric and special characters (#, &)
are there?*/

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
void string_count(char s[]){
	int i=0;
	int num=0;
	int alpha=0;
	int spec=0;
	while(s[i]!='\0'){
		if(s[i]>=48 && s[i]<=57){
			num++;
		}else if((s[i]>=65 && s[i]<=90) || (s[i]>=97 && s[i]<=122)){
			alpha++;
		}else{
			spec++;
		}
		i++;
	}
	printf("No of Alphabets: %d \nNo of Numerics: %d \nNo of Special Characters: %d ",alpha,num,spec);
}
int main(){
    int fd[2];
    pipe(fd);
    int id=fork();
    if (id>0){
        char inputstr[100];
        close(fd[0]);
        printf("Enter a str: ");
        scanf("%s",inputstr);
        write(fd[1],inputstr,sizeof(inputstr));
        close(fd[1]);
    }
    else if(id==0){
        char str[100];
        close(fd[1]);
        read(fd[0],str,sizeof(str));
        close(fd[0]);
        string_count(str);
    }
    
}

