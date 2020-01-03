#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
static void sig_usr(int signo)
{
     if (signo == SIGUSR1)
          printf("received SIGUSR1\n");
     else if (signo == SIGUSR2)
          printf("received SIGUSR2\n");
     else {
          fprintf(stderr, "recevied signal %d\n", signo);
          fflush(stderr);
          abort();
     }
     return;
}
int main(void)
{
     if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
          perror("can't catch SIGUER1");
          exit(1);
     }
     if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
          perror("can't catch SIGUER2");
          exit(1);
     }

     for(;;)
          pause();
}

