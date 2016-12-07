/* The following code creates a thread that generates random x and y in [-1,1] and checks
   if (x,y) is inside a circle of radius 1, centred at origin. And then calculates pi 
   using "pi = 4 * (Number of points in circle)/(Total number of points)". As expected,
   the accuracy of calculated pi depends on total number of points and the random 
   number generator used							*/

/* !--- Use "gcc monte.c -pthread" to compile ---! */

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

float pi;

void *monte(void *param){
	time_t t;
	srand((unsigned) time(&t));
	int count=0;
	for(int i=0;i<100000000;i++){
		float x=rand()%20001;
		x/=10000;
		x-=1;
		float y=rand()%20001;
		y/=10000;
		y-=1;
		if(x*x+y*y<=1)
			count++;
	}
	pi=(4*count)/100000000.0;

}
int main(){
	pthread_t tid;
	pthread_create(&tid,NULL,monte,NULL);
	pthread_join(tid,NULL);
	printf("The value of pi is: %f\n", pi);
	return 0;
}
