#include <stdio.h>
#include <signal.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>

	static int contador[100];
	static void handler (int i){
		contador[i]++;
		printf("\n La señal %d se ha recibido %d veces. ",i,contador[i]);
	}

int main()
{
	struct sigaction sa;
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	
	printf("No puedo manejar la señal SIGKILL.\n");
	printf("No puedo manejar la señal SIGSTOP.\n");
	
	sa.sa_flags = SA_RESTART;
	
	int j,i;
	for (j=1;j<=100;j++)
		contador[j] = 0;

	for (i=1;i<=100;i++)
		sigaction(i, &sa, NULL); 
	
	while(1);
	
}
