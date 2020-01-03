#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
	pid_t pid;
	int status, exit_status;

	if((pid = fork()) < 0) { // on error
		perror("fork error");
		exit(1);
	} else if (pid == 0) { // child
		printf("Child %d sleeping...\n", getpid());
		sleep(4);
		exit(5);
	}

	// parent
	while(waitpid(pid, &status, WNOHANG) == 0){
		printf("Still waiting... \n");
		sleep(1);
	}

	if(WIFEXITED(status)){
		exit_status = WEXITSTATUS(status);
		printf("Exit status from %d was %d\n",
				pid, exit_status);
	}

	exit(0);
}

