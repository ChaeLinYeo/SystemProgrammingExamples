#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
	char *ptr;

	if(chdir("/tmp") < 0){
		perror("chdir failed");
		exit(1);
	}

	if((ptr = getcwd(NULL, 0)) == NULL){
		perror("getcwd failed");
		exit(1);
	}

	printf("cwd = %s\n", ptr);
	exit(0);
}
