#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void){
	pid_t pid;
	int status;

	if((pid = fork()) == 0) { // child
		execlp("ls", "ls", "-al", NULL);
	} else { // parent
		wait(&status);
		printf("exit status of child = %d\n",
				WEXITSTATUS(status));
	}
}
