#include<fcntl.h>    // Has definition of open
#include<unistd.h>  //  Has definitions of read, write, close
#include<stdio.h>  //   Has definitions of scanf, printf

int main(){
	char input[10];                 // Contains name of file to be copied
	scanf("%s", input);
	int input_fd;                 //   Contains file descriptor of 'input'
	if(access(input, F_OK)==-1){
		printf("The file doesn't exist!\n");
		return 0;
	}
	else{
		input_fd = open(input, O_RDONLY);
	}
	char output[10];             // Contains name of file to be written
	scanf("%s", output);
	int output_fd;             //   Contains file descriptor of 'output'
	if(access(output, F_OK)==-1){
		output_fd = open(output, O_WRONLY | O_CREAT);
	}
	else{
		printf("The file already exists!\n");
		return 0;
	}
	char buf[4]; size_t max_bytes=4; ssize_t bytes_read;
	bytes_read = read(input_fd, buf, max_bytes);
	while(bytes_read!=0){
		write(output_fd, buf, bytes_read);
		bytes_read = read(input_fd, buf, max_bytes);
	}
	close(input_fd);
	close(output_fd);	
	return 0;
}
