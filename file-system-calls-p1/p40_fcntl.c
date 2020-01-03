#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void set_fl(int fd, int flags){
	int val;

	if((val = fcntl(fd, F_GETFL, 0)) < 0){
		perror("fcntl F_GETFL error");
		exit(1);
	}

	val |= flags; // turn on flags

	if(fcntl(fd, F_SETFL, val) < 0){
		perror("fcntl F_SETFL error");
		exit(1);
	}
}

int main(int argc, char *argv[]){
	int accmode, val, fd;

	if(argc != 2){
		fprintf(stderr, "usage: %s <descriptor #>", argv[0]);
		exit(1);
	}

	if((fd = open(argv[1], O_RDWR)) < 0){
		perror("fcntl error for fd");
		exit(1);
	}

	if((val = fcntl(fd, F_GETFL, 0)) , 0){
		perror("fcntl error for fd");
		exit(1);
	}

	accmode = val & O_ACCMODE;

	if(accmode == O_RDONLY) 
		printf("read only");
	else if(accmode == O_WRONLY) 
		printf("write only");
	else if(accmode == O_RDWR) 
		printf("read write");
	else{
		fprintf(stderr, "unknown access mode");
		exit(1);
	}

	if(val & O_APPEND) 
		printf(", append");
	if(val & O_NONBLOCK) 
		printf(", nonblocking");
	if(val & O_SYNC) 
		printf(", synchronous writes");
	printf("\n");
	exit(0);
}

