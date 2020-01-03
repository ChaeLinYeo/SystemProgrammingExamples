#include <p15-example4.h>

int initsem(key_t semkey){
	int status =0, semid;

	if((semid = semget(semkey, 1, SEMPERM|IPC_CREAT|IPC_EXCL)) == -1){
		if(errno == EEXIST) semid = semget(semkey, 1, 0);
	} else {
		union semun{
			int val;
			struct semid_ds *buf;
			unsigned short int *arrary;
		} arg;
		arg.val = 1;
		status = semctl(semid, 0, SETVAL, arg);
	}
	if(semid == -1||status == -1){
		perror("initsem failed");
		printf("\n%d %d\n", semid, status);
		return -1;
	} else {
		return semid;
	}
}

int p(int semid){
	struct sembuf p_buf;
	p_buf.sem_num = 0;
	p_buf.sem_op = -1;
	p_buf.sem_flg = SEM_UNDO;

	if(semop(semid, &p_buf, 1) == -1){
		perror("p(semid) failed");
		exit(1);
	} else {
		return 0;
	}
}

int v(int semid){
	struct sembuf v_buf;
	v_buf.sem_num = 0;
	v_buf.sem_op = 1;
	v_buf.sem_flg = SEM_UNDO;

	if(semop(semid, &v_buf, 1) == -1){
		perror("v(semid) failed");
		exit(1);
	} else {
		return 0;
	}
}

int handlesem(key_t skey){
	int semid, pid = getpid();
	if((semid = initsem(skey)) < 0) exit(1);
	printf("\nprocess %d before critical section\n", pid);
	p(semid);
	printf("process %d in critical section\n", pid);
	sleep(10);
	printf("process %d leaving critical section\n", pid);
	v(semid);
	printf("process %d exiting\n", pid);
	exit(0);
}

void main(){
	key_t semkey = 0x200;

	if(fork() == 0) handlesem(semkey);
	if(fork() == 0) handlesem(semkey);
	if(fork() == 0) handlesem(semkey);
}

