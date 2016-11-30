/* This header file contains functions that can be used to manage pid values
   of processes	using array datastructure				   */

/*This code doesn't look good to me. But this is the best I can do as of
  now. I'll change it as soon as I use this to allocate pid to processes */

#define MIN_PID 300
#define MAX_PID 5000

int *pid_array;

int allocate_map(){
	int array[MAX_PID-MIN_PID+1];
	pid_array = array;
	return 1;	
}

int allocate_pid(){
	for(int i=0;i<MAX_PID-MIN_PID+1;i++){
		if(pid_array[i]==0){
			pid_array[i]=1;
			return i+MIN_PID;
		}
	}	
	return -1;
}

void release_pid(int pid){
	pid_array[pid-MIN_PID]=0;
}
