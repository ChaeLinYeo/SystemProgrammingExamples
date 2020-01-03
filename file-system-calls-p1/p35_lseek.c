#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void){
	int fd;

	if((fd = creat("file.hole", 0640)) < 0){
		perror("creat error");
		exit(1);
	}

	if(write(fd, buf1, 10) != 10){
		perror("buf1 write error");
		exit(1);
	} // offset is 10 now

	if(lseek(fd, 40, SEEK_SET) == -1){
		perror("lseek error");
		exit(1);
	} // offset is 40 now

	if(write(fd, buf2, 10) != 10){
		perror("buf2 write error");
		exit(1);
	} // offset is 50 now
	
	exit(0);
}
