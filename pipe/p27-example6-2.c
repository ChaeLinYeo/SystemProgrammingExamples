#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MSGSIZE 63

char *fifo = "fifo";
void fatal(char *);

int main(int argc, char **argv){
	int fd;
	char msgbuf[MSGSIZE+1];

	if(mkfifo(fifo, 0666) == -1){
		if(errno != EEXIST)
			fatal("receiver: mkfifo");
	}

	if((fd = open(fifo, O_RDWR)) < 0)
		fatal("fifo open failed");

	for(;;){
		if(read(fd, msgbuf, MSGSIZE+1) < 0)
			fatal("message read failed");
		printf("message received: %s\n", msgbuf);
	}
}

void fatal(char *str){
	perror(str);
	exit(1);
}
