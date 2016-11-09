#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>

pid_t hijo;
int main(int argc, char *argv[]){
	pid_t childpid;
	int NUM_HIJOS=5,j,k;
	pid_t vec[NUM_HIJOS];

	if(setvbuf(stdout,NULL,_IONBF,0)) {
		perror("\nError en setvbuf");
	}	


	for (j=0; j < NUM_HIJOS; j++) {           
		if((vec[j] = fork()) == -1) { 
			fprintf(stderr, "No se pudo crear el hijo %d: %d\n",j,strerror(errno));
			return -1;
		  }       
		 
		if (vec[j]==0){
			printf(" Soy el hijo %d\n",getpid());
			return -1;	
		}
	}
	
	for(k=0; k<NUM_HIJOS; k++){
		waitpid(vec[k]);
		printf("Acaba de finalizar mi hijo con %d\n", vec[k]);
		printf("Solo me quedan %d hijos vivos\n",NUM_HIJOS-k-1);
	}
	
	return -1;

}
