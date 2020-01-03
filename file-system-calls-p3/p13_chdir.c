#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
	if(chdir("/tmp") < 0){
		perror("chdir failed");
		exit(1);
	}

	printf("chdir to /tmp succeeded\n");
	exit(0);
}
