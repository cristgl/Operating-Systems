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

void bloq(int dbloqueo,int bd){
	struct flock cerrojo;
	cerrojo.l_type=bd;
	cerrojo.l_whence=SEEK_SET;
	cerrojo.l_start=0;
	cerrojo.l_len=0;
	
	if(fcntl(dbloqueo,F_SETLKW,&cerrojo)==-1){
		perror("Error en bloq");
		exit(1);
	}
}

int main(int argc, char* argv[]){
	char buf[1024];
	FILE *tmp=tmpfile(); //almacena todo el documento
	int num_leidos,dbloqueo;
	char cfifo[100];
	
	//Tengo que leer y escribir
	while((num_leidos=read(STDIN_FILENO,buf,1024))>0)
		fwrite(buf,sizeof(char),num_leidos,tmp);
	
	rewind(tmp);
	
	if((dbloqueo=open("blockfile",O_RDWR))<0){
		perror("Error en el bloqueo");
		exit(-1);
	}
	
	bloq(dbloqueo,F_WRLCK);
	int num_leidos;
	while(!feof(tmp)){
		num_leidos=fread(buf,sizeof(char),1024,tmp);
		write(STDOUT_FILENO,buf,num_leidos);
	}
	
	bloq(dbloqueo,F_UNLCK);
	
	// cerrar el fifo que ha creado el servidor
	sprintf(cfifo,"fifo.%d",getpid());
	unlink(cfifo);
	
	exit(0);		

}
