/* The following code uses OpenMP, a set of compiler directives, to parallelise the 
   'for loop' which implements monte carlo technique to calculate pi. OpenMP divides the 
   work contained in 'for loop' among the threads it creates. The number of threads created
   is equal to the number of processing cores					*/

#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<time.h> 
int main(){
	/* Seq. code*/
	float pi;
	time_t t;
	srand((unsigned) time(&t));
	int count=0;
	#pragma omp parallel for
	{
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
	}
	pi=(4*count)/100000000.0;
	printf("The value of pi is: %f\n", pi);
	return 0;
}
