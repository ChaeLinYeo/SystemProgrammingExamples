#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int glob = 6;

int main(void){
	
	pid_t pid;
	int var;

	var = 88;
	printf("before vfork\n");

	// we don't flush stdio
	
	if((pid = vfork()) < 0){ // on error 
		perror("vfork error");
		exit(1);
	} else if(pid == 0) { // child
		glob++;	// modifies global variable.
		var++;	// modifies parent's variable.
		_exit(0);	// child terminates.
	}

	// parent
	printf("pid = %d, glob = %d, var = %d\n",
			getpid(), glob, var);
	exit(0);
}

