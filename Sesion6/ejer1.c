#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include<errno.h>
#include <stdlib.h>

int main (int argc, char * argv[]){
	if(argc!=4){
		printf("Numero de arg. invalido");
		exit(0);
	}

	int fd;
	
	if(!strcmp(argv[2],"<")){ // redireccionar la entrada de la orden desde el archivo
		fd = open(argv[3],O_RDONLY);
		close(STDIN_FILENO);
		fcntl(fd,F_DUPFD,STDIN_FILENO);
		execlp(argv[1],argv[1],NULL);
	}else if (!strcmp(argv[2],">")){ // redireccionar la salida de la orden al archivo
		fd = open(argv[3],O_WRONLY);
		close(STDOUT_FILENO);
		fcntl(fd,F_DUPFD,STDOUT_FILENO);
		execlp(argv[1],argv[1],NULL);
	} else{
		printf("Argumento invalido");
		exit(0);
	}
}
