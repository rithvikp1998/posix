/* Collatz conjecture states that for any positive integer n, if you perform
   the following operation, it will eventually lead to 1

   The operation is this: n=n/2 if n is even
			  n=3*n+1 if n is odd			*/


#include<sys/wait.h>
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
	pid_t pid;
	pid=fork();
	if(pid<0)
		printf("Fork failed \n");
	else if(pid==0){	/*Child*/
		printf("Child created \n");
		printf("Please enter a positive integer: ");
		int n;
		scanf("%d",&n);
		if(n<=0)
			printf("Please enter a positive integer ");
		else{
			printf("Showing Collatz conjecture... ");
			printf("%d ",n);
			while(n>1){
				if(n%2==0)
					n=n/2;
				else
					n=3*n+1;
				printf("%d ",n);
			}
		}
		return 0;
	}
	else{
		wait(NULL);
		printf("\n Child exited \n");
	}
	return 0;
}
