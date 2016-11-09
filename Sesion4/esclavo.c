#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <string.h>
#include <math.h>


int main(int argc, char* argv[]){
	int inicio, fin,i,j;
	double lim;
	int primo;
	char imprime[10];
	
	if(argc!=3){
		printf("uso: ./esclavo <inicio> <fin>");
		exit(0);
	}

	inicio = atoi(argv[1]);
	fin = atoi(argv[2]);
	
	for(i=inicio; i<fin; i++){
		lim=sqrt(i);
		primo=1;
		for (j = 2; j <= lim && primo; j++)
			if (i % j == 0)
				primo = 0;
		if(primo){
			sprintf(imprime,"%d ",i);
			write(STDOUT_FILENO,imprime,strlen(imprime)+1);

		}

	}
	exit(0);
}
