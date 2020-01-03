#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BSIZE 1024 // buffer size
#define FPERM 0644 // file permission

int main(int argc, char *argv[]){
	int fd1, fd2, n;
	char buf[BSIZE];

	if(argc < 3){
		fprintf(stderr, "Usage: %s src dest\n", argv[0]);
		exit(1);
	}

	if((fd1 = open(argv[1], O_RDONLY)) < 0){
		perror("file open error");
		exit(1);
	}

	if((fd2 = creat(argv[2], FPERM)) < 0){
		perror("file creation error");
		exit(1);
	}

	while((n=read(fd1, buf, BSIZE)) > 0){
		write(fd2, buf, n);
	}

	close(fd1);
	close(fd2);
}
