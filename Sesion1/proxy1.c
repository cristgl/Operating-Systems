#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#define BLOCK_FILE "blockfile"

void bloqueodesbloqueo(int dbloqueo,int orden){
	struct flock cerrojo;
	// Inicializamos todo el cerrojo para bloquear todo el archivo
	cerrojo.l_type=orden;
	cerrojo.l_whence=SEEK_SET;
	cerrojo.l_start=0;
	cerrojo.l_len=0;
	
	// Si vamos a bloquearlo y ya lo esta, entonces el proceso duerme
	if(fcntl(dbloqueo,F_SETLKW,&cerrojo)==-1){
		perror("Proxy: problemas al bloquear para impresión");
		exit(1);
	}
}

int main(int argc, char* argv[]){
	char buffer[1024];
	int nbytes,dbloqueo;
	FILE *tmp=tmpfile();
	char fifoproxy[256];
	
	while((nbytes=read(STDIN_FILENO,buffer,1024))>0){
		fwrite(buffer,sizeof(char),nbytes,tmp);
	}
	rewind(tmp);
	if((dbloqueo=open(BLOCK_FILE,O_RDWR))==-1)
		printf("Error al abrir blockfile\n");

	bloqueodesbloqueo(dbloqueo,F_WRLCK);
	while(!feof(tmp)){
		fread(buffer,sizeof(char),1024,tmp);
		write(STDOUT_FILENO,buffer,1024);
	}
	
	bloqueodesbloqueo(dbloqueo,F_UNLCK);
	
	sprintf(fifoproxy,"fifo.%d",getpid());
	unlink(fifoproxy);
	
	exit(0);
}
