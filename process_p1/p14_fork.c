#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
	
	pid_t pid;

	printf("Hello, my pid is %d\n", getpid());

	if((pid = vfork()) == 0){ // child	
		printf("child: pid = %d, ppid = %d\n", getpid(), getppid());
	} else { // parent
		printf("parent: I created child with pid = %d\n", pid);
	}

	// Following line is executed by both parent and child
	
	printf("Bye, my pid is %d\n", getpid());
	exit(0);
}
