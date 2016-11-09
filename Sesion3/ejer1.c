#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>



int main(int argc, char *argv[]){
	if(argc!=2){
		printf("Numero de argumentos invalido.");
		exit(-1);
	}
	else{
		int num=atoi(argv[1]);
		pid_t pid;

		if( (pid=fork())<0) {
			perror("\nError en el fork");
			exit(-1);
		}
		else if(pid==0){
			if(num%2==0)
				printf("El numero es par.\n");
			else
				printf("El numero es impar\n.");
		}else{
			if(num%4==0)
				printf("El numero es divisible por 4.\n");
			else
				printf("El numero no es divisible por 4.\n");
		}
	}
}
		
