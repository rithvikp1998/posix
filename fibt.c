/* The following code takes a positive integer 'n' as input, creates a thread that writes 
   first 'n' fibonacci numbers to an array. The parent thread waits for the child thread 
   to complete, then prints out the values in the array				*/

/* !--- Use "gcc fibt.c -pthread" to compile ---! */

#include<stdio.h>
#include<pthread.h>

int fibarr[1000];

void *fib(void *param){
	int n=*((int *)param);
	fibarr[0]=1;
	fibarr[1]=1;
	for(int i=2;i<n;i++)
		fibarr[i]=fibarr[i-1]+fibarr[i-2];
	pthread_exit(0);
}

int main(){
	int n;
	printf("Enter a number: ");
	scanf("%d",&n);
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&tid,&attr,fib,&n);
	pthread_join(tid,NULL);
	for(int i=0;i<n;i++)
		printf("%d ",fibarr[i]);
	printf("\n");
	return 0;
}
