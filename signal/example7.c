#include <signal.h> 
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

void pr_mask(const char *str)
{
     sigset_t sigset;

     if (sigprocmask(0, NULL, &sigset) < 0) {
          perror("sigprocmask error");
          exit(1);
     }
     printf("%s", str);
     if (sigismember(&sigset, SIGINT))
          printf(" SIGINT");
     if (sigismember(&sigset, SIGQUIT))
          printf(" SIGQUIT");
     if (sigismember(&sigset, SIGUSR1))
          printf(" SIGUSR1");
     if (sigismember(&sigset, SIGALRM))
          printf(" SIGALRM");

     /* remaining signals can go here */

     printf("\n");
}


int main() 
{ 
	sigset_t set1, set2; 

	/* 시그널 집합을 완전히 채운다. */ 
	sigfillset (&set1); 

	/* SIGINT와 SIGQUIT를 포함하지 않는 시그널 집합을 생성한다. */ 
	sigfillset (&set2); 
	sigdelset (&set2, SIGINT); 
	sigdelset (&set2, SIGQUIT); 
	
	/* 중대하지 않은 코드를 수행 ... */

	/* 봉쇄를 설정한다. */
	sigprocmask(SIG_SETMASK, &set1, NULL);
	pr_mask("Sig Set Mask SET 1:");

	/* 극도로 중대한 코드를 수행한다. */

	/* 하나의 봉쇄를 제거한다. */
	sigprocmask(SIG_UNBLOCK, &set2, NULL);
	pr_mask("Sig Unblock SET 2:");

	/* 덜 중대한 코드를 수행한다 ... */

	/* 모든 시그널 봉쇄를 제거한다. */
	sigprocmask(SIG_UNBLOCK, &set1, NULL);
	pr_mask("Sig Unblock SET 1:");
}

