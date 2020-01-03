#include "p31-example5.h"
#define IFLAGS (IPC_CREAT|IPC_EXCL)
#define ERR ((struct databuf*) -1)

static int shmid1, shmid2, semid;

//getseg: create, attach shared memory segments
int getseg(struct databuf **p1, struct databuf **p2){
	// create shared memory segments
	if((shmid1 = shmget(SHMKEY1, sizeof(struct databuf), 0600|IFLAGS)) < 0){
		perror("shmget1");
		exit(1);
	}
	if((shmid2 = shmget(SHMKEY2, sizeof(struct databuf), 0600|IFLAGS)) < 0){
		perror("shmget2");
		exit(1);
	}
	// attach shared memory segments
	if((*p1 = (struct databuf*) shmat(shmid1, 0, 0)) == ERR){
		perror("shmat");
		exit(1);
	}
	if((*p2 = (struct databuf*) shmat(shmid2, 0, 0)) == ERR){
		perror("shmat");
		exit(1);
	}
}

// getsem: get semaphore set
int getsem(void){
	int errno;
	// create two semaphore set
	if((semid = semget(SEMKEY, 2, 0600|IFLAGS)) < 0){
		if(errno == EEXIST){
			semid = semget(SEMKEY, 2, 0);
		}else{
			perror("semget");
			exit(1);
		}
	}
	// set initial values
	if(semctl(semid, 0, SETVAL, 0) < 0){
		perror("semctl");
		exit(1);
	}
	if(semctl(semid, 1, SETVAL, 0) < 0){
		perror("semctl");
		exit(1);
	}
	return semid;
}

// remove: remove shared memory identifiers, sem set id
int removes(void){
	if(shmctl(shmid1, IPC_RMID, (struct shmid_ds*)0) < 0){
		perror("shmctl");
		exit(1);
	}
	if(shmctl(shmid2, IPC_RMID, (struct shmid_ds*)0) < 0){
		perror("shmctl");
		exit(1);
	}
	if(semctl(semid,0, IPC_RMID) < 0){
		perror("semctl");
		exit(1);
	}
}

// these define p() and v() for semaphores
struct sembuf p1 = {0, -1, 0}, p2 = {1, -1, 0};
struct sembuf v1 = {0, 1, 0}, v2 = {1, 1, 0};

void reader(int semid, struct databuf *buf1, struct databuf *buf2){
	for(;;){
		// read into buffer buf1
		buf1 -> d_nread = read(0, buf1->d_buf, SIZ);
		// synchronization point
		semop(semid, &v1, 1);
		semop(semid, &p2, 1);
		// test here to avoid writer sleeping
		if(buf1->d_nread <= 0) return;

		buf2 -> d_nread = read(0, buf2->d_buf, SIZ);
		semop(semid, &v1, 1);
		semop(semid, &p2, 1);
		if(buf2->d_nread <= 0) return;
	}
}

void writer(int semid, struct databuf *buf1, struct databuf *buf2){
	for(;;){
		semop(semid, &p1, 1);
		semop(semid, &v2, 1);
		if(buf1->d_nread <= 0) return;

		write(1, buf1->d_buf, buf1->d_nread);

		semop(semid, &p1, 1);
		semop(semid, &v2, 1);

		if(buf2->d_nread <= 0) return;

		write(1, buf2->d_buf, buf2->d_nread);
	}
}

void main(void){
	int semid, pid;
	struct databuf *buf1, *buf2;
	semid = getsem();
	getseg(&buf1, &buf2);

	switch(pid = fork()){
		case -1:
			perror("fork");
			exit(1);
		case 0: // child
			writer(semid, buf1, buf2);
			removes();
			break;
		default: // parent
			reader(semid, buf1, buf2);
			break;
	}
	exit(0);
}
