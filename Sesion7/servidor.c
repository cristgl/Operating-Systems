#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <errno.h>

static void mimanejador(int senal){
	pid_t pid;
	char fifoproxy[100];
	pid=wait(NULL);
}

int main(int argc, char* argv[]){
	char nombrefifoe[100],nombrefifos[100],fifop[100];
	int ent,sal,num_leidos,tmp,fd,mipid;
	pid_t pid;
	char *buf[1024];
	
	if (argc != 2) {
		printf("Uso Servidor: servidor<nombre_fifo>");
		exit(-1);
	}		
	
	signal(SIGCHLD,mimanejador);
	
	sprintf(nombrefifoe,"%se",argv[1]);
	sprintf(nombrefifos,"%ss",argv[1]);
	
	umask(0);
	mkfifo(nombrefifoe,0666);
	mkfifo(nombrefifos,0666);
	
	if((ent=open(nombrefifoe,O_RDWR))<0){
		perror("Error entrada");
		exit(-1);
	}
	
	if((sal=open(nombrefifos,O_RDWR))<0){
		perror("Error salida");
		exit(-1);
	}
	
	umask(0);
	if((fd=open("blockfile",O_CREAT,0666))<0){
		printf("\nError al crear el archivo de bloqueo de proxy");
		exit(-1);
	}
	
	while((num_leidos=read(ent,&tmp,sizeof(int)))!=0){
		//fork para lanzar el hijo, sprintf para escribir el nombresito y crearlo
		pid=fork();
		if(pid==0){
			sprintf(fifop,"fifo.%d",getpid());
			umask(0);
			mkfifo(fifop,0666);
			// escribir el pidproxy
			mipid=getpid();
			write(sal,&mipid,sizeof(int));
			int fifo=open(fifop, O_RDONLY);
			
			dup2(fifo,STDIN_FILENO);
			
			execlp("./proxy","proxy",NULL);
			exit(0);
		}
	}
	return 0;	
}
