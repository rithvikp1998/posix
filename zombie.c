/* In this code, we create a child process. The child process gets created and
   all it does in wait for 10 seconds. At the same time, the child was created,
   the parent process starts its 30 second sleep. If the child was created at 
   t=0, the child exits at t=10 and becomes a zombie. Since the parent is sleeping
   till t=30, the zombie gets destroyed at t=30. Please note that both the child 
   and the parent start sleeping at t=0						*/

#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

int main(){
	pid_t pid;
	pid = fork();

	if(pid<0)
		printf("Fork failed");
	else if(pid==0){
		printf("Child created with pid: %d \n", pid);
		sleep(10);
		printf("Child exiting... \n");
		return 1;
	}
	else{
		printf("PID of child: %d \n", pid);
		sleep(30);
		wait(NULL);
		printf("Child complete\n");
	}
	return 0;
}
