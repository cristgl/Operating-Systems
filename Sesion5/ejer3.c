#include <stdio.h>
#include <signal.h>

int main(){
	sigset_t set;
	
	sigfillset(&set);
	sigdelset(&set,SIGUSR1);
	sigsuspend(&set);
}


