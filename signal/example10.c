#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <signal.h> 
#include <sys/types.h>

int ntimes = 0; 

int main(){

	pid_t pid, ppid; 
	void p_action (int), c_action (int); 
	static struct sigaction pact, cact; 

	/* 부모를 위해 SIGUSR1 행동을 지정한다. */ 
	pact.sa_handler = p_action; 
	sigaction (SIGUSR1, &pact, NULL); 
	switch (pid = fork()){
		case -1:			/* 오류 */
			perror ("synchro");
			exit (1);
		case 0:				/* 자식 */
		/* 자식을 위해 행동을 지정 */
			cact.sa_handler = c_action;
			sigaction (SIGUSR1, &cact, NULL);
			/* 부모의 프로세스 식별번호를 얻음. */
			ppid = getppid();
			for (;;){
				sleep (1);
				kill (ppid, SIGUSR1);
				pause();
			}/* 결코 퇴장(exit) 않음. */
		
		default:	/*  부모 */ 
			for(;;){
				pause(); 
				sleep (1); 
				kill (pid, SIGUSR1); 
			}  /* 결코 퇴장(exit) 않음 */ 
	}
} 

void p_action (int sig){ 
	printf ("Parent caught signal #%d\n", ++ntimes); 
} 

void c_action (int sig){ 
	printf ("Child caught signal #%d\n", ++ntimes); 
} 



