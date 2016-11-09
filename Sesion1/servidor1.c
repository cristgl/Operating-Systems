#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<signal.h>

#define tamano 1024
#define longnombre 50
#define MAX_CLIENTS 100

static void signal_handler(int sigNum){
	pid_t pid;
	char fifoproxy[longnombre];
	pid=wait(NULL);
}

int main(int argc,char *argv[]){
	int fde,fds,fdc,tmp_cli;
	char nombrefifoe[longnombre];
	char nombrefifos[longnombre];
	char fifoproxy[longnombre];
	int leidos,proxypid;
	pid_t pid;
	
	if(argc!=2){
		printf("Uso: Servidor<nombre_fifo>");
		exit(-1);
	}
	
	signal(SIGCHLD,signal_handler);
	
	sprintf(nombrefifos,"%ss",argv[1]);
	sprintf(nombrefifoe,"%se",argv[1]);
	
	umask(0);
	mkfifo(nombrefifoe,0666);
	mkfifo(nombrefifos,0666);
	
	if((fds=open(nombrefifos,O_RDWR))<0){
		perror("\nNo se pudo abrir el archivo fifo del servidor.");
		exit(-1);
	}
	
	if((fde=open(nombrefifoe,O_RDWR)) < 0){
		perror("\nNo se pudo abrir el archivo fifo del cliente.");
		exit(-1);
	}
	
	umask(0);
	if((fdc=open("blockfile",O_CREAT,0666))<0){
		printf("\nError al crear el archivo de bloqueo");
		exit(-1);
	}
	
	while((leidos=read(fde,&tmp_cli,sizeof(int)))!=0){
		pid=fork();
		if(pid==0){
			proxypid=getpid();
			sprintf(fifoproxy,"fifo.%d",proxypid);
			umask(0);
			mkfifo(fifoproxy,0666);
			write(fds,&proxypid,sizeof(int));
			int fifo=open(fifoproxy,O_RDONLY);
			dup2(fifo,STDIN_FILENO);
			execlp("./proxy","proxy",NULL);
			exit(0);
		}
	}
	
	return 0;	
	
}
