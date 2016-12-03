/* The following code has a parent and a child and two ordinary pipes between them. The child writes a message to pipe 1. The parent reads the msg from pipe 1, prints it, toggles the case of characters(lower case to upper case and vice versa) and writes it to pipe 2. The child now reads message from pipe 2, prints it and terminates. The parent also terminates 
P.S. The read function waits until it finds a message				 */
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>

#define read_end 0
#define write_end 1

int main(){
	char write_msg1[25]="HelloWorld";
	char read_msg1[25];
	char write_msg2[25];
	char read_msg2[25];
	int fd1[2]; //Pipe from child to parent
	int fd2[2];// Pipe from parent to child
	if(pipe(fd1)==-1 || pipe(fd2)==-1)
		printf("Error in creating pipes");
	pid_t pid=fork();
	if(pid<0)
		printf("Error in creating child");
	else if(pid==0){
		write(fd1[write_end], write_msg1, strlen(write_msg1)+1);
		read(fd2[read_end], read_msg1, 25);
		printf("%s \n",read_msg1);
		return 0;
	}
	else{
		read(fd1[read_end], read_msg2, 25);
		printf("%s \n", read_msg2);
		for(int i=0;i<strlen(read_msg2)+1;i++){
			if(read_msg2[i]>='A' && read_msg2[i]<='Z')
				write_msg2[i]=read_msg2[i]-'A'+'a';
			else if(read_msg2[i]>='a' && read_msg2[i]<='z')
				write_msg2[i]=read_msg2[i]-'a'+'A';
			else
				write_msg2[i]=read_msg2[i];
		}
		write(fd2[write_end], write_msg2, strlen(write_msg2)+1);
		wait(NULL);
	}
	return 0;
}
