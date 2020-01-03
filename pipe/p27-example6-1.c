#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define MSGSIZE 63

char *fifo = "fifo";
void fatal(char *);

int main(int argc, char **argv){
	int fd, j, nwrite;
	char msgbuf[MSGSIZE+1];
	if(argc < 2){
		fprintf(stderr, "Usage: %s msg... \n", argv[0]+2);
		exit(1);
	}

	if((fd = open(fifo, O_WRONLY | O_NONBLOCK)) < 0)
		fatal("fifo open failed");
	for(j=1; j<argc; j++){
		if(strlen(argv[j]) > MSGSIZE){
			fprintf(stderr, "message too long %s\n", argv[j]);
			continue;
		}
		strcpy(msgbuf, argv[j]);
		if((nwrite = write(fd, msgbuf, MSGSIZE+1)) == -1)
			fatal("message write failed");
	}
	exit(0);
}

void fatal(char *str){
	perror(str);
	exit(1);
}
