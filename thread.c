/*The following code creates 10 threads and all the threads perform the same function: 
  sleep, print before exiting, exit 						*/

/* !--- To compile, use 'gcc thread.c -pthread' 				*/

#include<pthread.h>
#include<stdio.h>
#include<unistd.h>

int sum;

void *runner(void *param){
	int n=*((int *)param);//Getting int from void *param
	sleep(3*n);
	printf("Thread %d exited\n", n);
	pthread_exit(0);
}
int main(){
	pthread_t workers[10];
	int ns[10];	//Contains parameters, i.e. 'n's in our case
	for(int i=0;i<10;i++){
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		ns[i]=i;
		pthread_create(&workers[i],&attr,runner,&ns[i]);
	}
	for(int i=0;i<10;i++){
		pthread_join(workers[i], NULL);
		printf("Thread %d joined\n",i);
	}
	return 0;
}
