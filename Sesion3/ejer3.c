#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

/*
Jerarquía de procesos tipo 1
*/

	int main(int argc, char *argv[]){
	pid_t childpid;
	int nprocs=20,i,j,k;
	if(setvbuf(stdout,NULL,_IONBF,0)) {
		perror("\nError en setvbuf");
	}
//Un padre crea un hijo, este crea otro hijo, este otro y así sucesivamente
	for (i=1; i < nprocs; i++) {           
		if ((childpid= fork()) == -1) { 
			fprintf(stderr, "Could not create child %d: %d\n",i,strerror(errno));
			exit(-1);
		}       
	  if (childpid){
			printf("Jerarq1. Mi PID es %d y el de mi padre %d.\n",getpid(),getppid()); 
			break;
		}
	}
	
	wait(); 
	
	
	/*
	Jerarquía de procesos tipo 2
	*/

//Un padre crea muchos hijos.
	for (j=0; j < nprocs; j++) {           
	  if ((childpid= fork()) == -1) { 
		fprintf(stderr, "Could not create child %d: %d\n",j,strerror(errno));
		exit(-1);
	  }       
	  
	  if (!childpid){
		printf("Jerarquia2. Mi PID es %d y el de mi padre %d.\n",getpid(),getppid());
	    break;
		}
	}
for(k=0; k<nprocs; k++) wait();
}
