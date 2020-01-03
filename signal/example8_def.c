#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void pr_mask(const char *str)
{
     sigset_t sigset;

     if (sigprocmask(0, NULL, &sigset) < 0) {
          perror("sigprocmask error");
          exit(1);
     }
     printf("%s", str);
 	 int i;
	 for(i=1; i<32; i++){
	     if (sigismember(&sigset, i))
	          printf(" %d", i);
	 }
     printf("\n");
}

void main(){
	pr_mask("Default mask:");
}
