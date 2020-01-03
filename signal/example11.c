#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define TIMEOUT 5      /* in seconds */
#define MAXTRIES 5
#define LINESIZE 1024
#define CTRL_G '\007'  /* ASCII Bell */
#define TRUE 1
#define FALSE 0

/* used to see if timeout has occured */
static int timed_out;

/* will hold input line */
static char in_line[LINESIZE];
char *quickreply(char *prompt)
{
     void (*was)(int);
     void catch(int); 
     int ntries;
     char *answer;

     /* catch SIGALRM + save previous action */
     was = signal(SIGALRM, catch);

     for(ntries = 0; ntries < MAXTRIES; ntries++) {
          timed_out = FALSE;
          printf("\n%s > ", prompt);
          
          /* set alarm clock */
          alarm(TIMEOUT);
          
          /* get input line */
          gets(in_line);
          /* turn off alarm */
          alarm(0);

          /* if timed_out TRUE, then no reply */
          if(!timed_out)
               break;
     }

     /* restore old action */
     signal(SIGALRM, was);

     /* return appropriate value */
     return (ntries == MAXTRIES ? ((char *) 0) : in_line);
}
/* executed when SIGALRM received */
void catch(int signo)
{
     /* set timeout flag */
     timed_out = TRUE;

     /* ring a bell */
     putchar(CTRL_G);

	 puts("beep-");

}
int main(void)
{
     char *name;

     if ((name = quickreply("Please enter your name")) != NULL)
          printf("Thank you, your name is %s\n", name);
     else
          printf("I give up!\n");
}
