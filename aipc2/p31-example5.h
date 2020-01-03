#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <errno.h>

#define SHMKEY1 (key_t)0x10 // shared mem key 1
#define SHMKEY2 (key_t)0x15 // shared mem key 2
#define SEMKEY (key_t)0x20  // semaphore key

#define SIZ 5*BUFSIZ	// buffer size for reads and writes

struct databuf{
	int d_nread;
	char d_buf[SIZ];
};

int getseg(struct databuf **p1, struct databuf **p2);
int getsem(void);
int removes(void);
void reader(int semid, struct databuf *buf1, struct databuf *buf2);
void writer(int semid, struct databuf *buf1, struct databuf *buf2);
