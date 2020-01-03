#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <signal.h> 
#include <unistd.h> 
#define TRUE	1 
#define FALSE	0 
#define BELLS	"\007\007\007"	/*ASCII bells */ 

int alarm_flag = FALSE; 

/* SIGALRM을 처리할 루틴 */ 
void setflag (int sig) {
	alarm_flag = TRUE; 
}

int main (int argc, char **argv) {

	int nsecs, j;
	pid_t pid; 
	static struct sigaction act; 

	if ( argc<=2 ) {
		fprintf (stderr, "Usage:  tml #minutes message\n");
		exit (1);
	} 

	if ((nsecs=atoi (argv[1]) *60) <= 0) {
		fprintf (stderr, " tml : invalid time\n");
		exit (2);
	} 

	/* 얼람을 위한 행동을 지정한다. */ 
	act.sa_handler = setflag; 
	sigaction (SIGALRM, &act, NULL); 

	/* 백그라운드 프로세스를 생성하기 위해 fork한다. */ 

	switch (pid = fork()) { 
		case -1: /* 오류 */
			perror ("tml");
			exit (1); 
		case 0: /* 자식 */
			break; 
		default: /* 부모 */ 
			printf ("tml process­id %d\n", pid); 
			exit (0); 
	} 

	/* 얼람 시계를 켠다. */ 
	alarm (nsecs); 

	/* 시그널이 올 때까지 중단(pause) ... */ 
	pause(); 

	/* 만일 시그널이 SIGALRM이면 메시지를 프린트하라. */
	if (alarm_flag == TRUE) { 
		printf (BELLS);
		for (j = 2; j < argc; j++) 
			printf ("%s", argv[j]); 
		printf ("\n");
	} 

	exit (0); 
} 


