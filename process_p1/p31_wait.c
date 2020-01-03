#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
	
	pid_t pid;
	int status;

	if((pid = fork()) == 0){ // child
		printf("I am a child\n");
		exit(123);
	}

	// parent
	pid = wait(&status);
	printf("parent: child(pid = %d) is terminated with status (%d)\n",
			pid, WEXITSTATUS(status));
}
