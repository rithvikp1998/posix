#include<stdio.h>
#include<pthread.h>

int avg,min,max;

void *average(void *param){
	int *arr= (int *)param;
	avg=0;
	for(int i=0;i<5;i++)
		avg+=arr[i];
	avg/=5;	
	pthread_exit(0);
}

void *minimum(void *param){
	int *arr= (int *)param;
	min=arr[0];
	for(int i=1;i<5;i++)
		if(arr[i]<min)
			min=arr[i];
	pthread_exit(0);
}

void *maximum(void *param){
	int *arr= (int *)param;
	max=arr[0];
	for(int i=1;i<5;i++)
		if(arr[i]>max)
			max=arr[i];
	pthread_exit(0);
}

int main(){
	int arr[5]={1,2,3,4,5};
	pthread_t tid[3];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&tid[0],&attr,average,arr);
	pthread_create(&tid[1],&attr,minimum,arr);
	pthread_create(&tid[2],&attr,maximum,arr);
	for(int i=0;i<3;i++)
		pthread_join(tid[i],NULL);
	printf("Average: %d\nMinimum: %d\nMaximum: %d\n", avg,min,max);	
	return 0;

}
