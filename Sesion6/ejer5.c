#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include <unistd.h>
#include <sys/mman.h>

int main(int argc, char* argv[]){
	struct stat atributos;
	int fd1,fd2;
	char* memory1;
	char* memory2;
	int size;

	umask(0);
	
	if (argc<3) {//controlamos los argumentos
        printf("Número de argumentos inválido.\n");
    }
	
	if((fd1=open(argv[1],O_RDONLY,S_IRWXU))==-1){
		printf("Error %d en open",errno);
		perror("Error en open");
		exit(-1);
	}

	umask(0);
	
	if((fd2=open(argv[2],O_WRONLY,S_IRWXU))==-1){
		printf("Error %d en open",errno);
		perror("Error en open");
		exit(-1);
	}
	
	stat(argv[1],&atributos);
	size=atributos.st_size;
	//Hacemos que el tamaño del segundo argumento sea igual que el del primero
	ftruncate(fd2,size);
	
	memory1=(char *) mmap(0,size,PROT_READ,MAP_SHARED,fd1,0);
	if(memory1==MAP_FAILED){
		perror("Fallo en la primera proyección");
		exit(-1);
	}
	
	memory2=((char *) mmap(0,size,PROT_WRITE,MAP_SHARED,fd2,0));
	if(memory2==MAP_FAILED){
		perror("Fallo en la segunda proyección");
		exit(-1);
	}
	
	memcpy(memory2,memory1,size);
	
	munmap(memory1,size);
	munmap(memory2,size);
	
	return 0;		
	
}
