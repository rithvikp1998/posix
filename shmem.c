/* !---- Use 'gcc shmem.c -lrt' to compile ----! */

/* The parent creates a shared memory object and creates a child. The child then writes
   values in collatz conjecture to this shared memory object and then terminates. After
   the child is terminated, the parent prints out the values in shared memory object and 
   unlinks the object									*/

#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<sys/mman.h>
#include<fcntl.h> 		/* for O_CREAT, O_RDWR */
int main(){
	const char *shm_name = "Shared";
	int shm_fd = shm_open(shm_name, O_CREAT|O_RDWR, 0);
	if(shm_fd==-1)
		printf("Error in shm_open"); 
	int ftrunc_res = ftruncate(shm_fd, 64);	/* 512 is length of memory */
	if(ftrunc_res==-1)
		printf("Error in ftruncate");
	int *sh_mm = mmap(0, 64, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if(sh_mm==MAP_FAILED)
		printf("Error in mmap");	
	pid_t pid=fork();
	if(pid<0)
		printf("Fork failed \n");
	else if(pid==0){
		printf("Child created \nPlease enter a positive integer: ");
		int n;
		scanf("%d",&n);
		sh_mm[0]=n;
		int i=1;
		while(n>1){
			if(n%2==0){
				sh_mm[i]=n/2;
				n=n/2;
				i++;
			}
			else{
				sh_mm[i]=3*n+1;
				n=3*n+1;
				i++;
			}
		}
		sh_mm[i]=-1;
		return 0;
	}
	else{
		wait(NULL);
		printf("Child terminated \nShowing Collatz conjecture... ");
		int i=0;
		while(sh_mm[i]!=-1){
			printf("%d ",sh_mm[i]);
			i++;
		}
		int res=shm_unlink(shm_name);
		if(res==0)
			printf("\nShared memory unlinked \n");
		else
			printf("Error while unlinking shared memory \n");
	}
	return 0;
}
