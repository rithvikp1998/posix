/* The parent reads from a file and writes it to a pipe. The child reads from pipe and 
   writes to another file							*/

/* !--- For the program to execute, read_file and write_file should exist and to execute,
   use './a.out input.txt output.txt'					---! */

/* The code has bug(s), currently it writes extra characters at the end of output file */

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<string.h>

#define read_end 0
#define write_end 1

int main(int argc, char *argv[]){
	char read_file[4];
	char write_file[4];
	strcpy(read_file, argv[1]);
	strcpy(write_file, argv[2]);
	char read_buf[4];
	char write_buf[4];
	int fd[2];
	pipe(fd);	
	pid_t pid=fork();
	if(pid==0){
		close(fd[write_end]);
		int fd_write = open(write_file, O_RDWR);
		ssize_t bytes_received=read(fd[read_end], write_buf, 4);
		while(bytes_received!=0){
			printf("%s \n", write_buf);
			write(fd_write, write_buf, bytes_received);
			bytes_received=read(fd[read_end], write_buf, 4);
		}
		close(fd[read_end]);
		close(fd_write);
		return 0;
	}
	else{
		close(fd[read_end]);
		int fd_read = open(read_file, O_RDONLY);
		ssize_t bytes_read=read(fd_read, read_buf, 4);
		while(bytes_read!=0){
			write(fd[write_end], read_buf, bytes_read);
			bytes_read=read(fd_read, read_buf, 4);
		}
		close(fd[write_end]);
		close(fd_read);
		wait(NULL);
	}
	return 0;
}
