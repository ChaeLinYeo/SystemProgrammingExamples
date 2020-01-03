#include <stdio.h>
#include <signal.h> 
#include <stdlib.h>
#include <unistd.h>

void catchint (int signo) 
{ 
	printf ("\nCATCHINT: signo=%d\n", signo); 
	printf("CATCHINT: returning\n\n"); 
} 

int main() 
{ 
	static struct sigaction act; 

	act.sa_handler = SIG_IGN; 

	sigfillset(&(act.sa_mask)); 
	sigaction(SIG_IGN, &act, NULL); 
	
	printf ("sleep call #1\n"); 
	sleep (1); 
	printf ("sleep call #2\n"); 
	sleep (1); 
	printf ("sleep call #3\n"); 
	sleep (1); 
	printf ("sleep call #4\n"); 
	sleep (1); 
	printf ("Exiting\n"); 
	exit (0); 
} 

