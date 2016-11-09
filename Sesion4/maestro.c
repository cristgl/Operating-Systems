#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<math.h>

int main(int argc, char* argv[]){
	pid_t esclavo1, esclavo2;
	int intervalo[2],intesc1[2],intesc2[2];
	int fd1[2];
	int fd2[2], bl1,bl2;
	char ini[10],fin[10];
	char buf1[10000],buf2[10000];
	if(argc != 3){
		printf("uso: ./maestro <inicio> <fin>\n");
		exit(0);
	}
	if(setvbuf(stdout,NULL,_IONBF,0)) {
		perror("\nError en setvbuf");
	}
	intervalo[0]=atoi(argv[1]);
	intervalo[1]=atoi(argv[2]);
	intesc1[0]=intervalo[0];
	intesc1[1]=(intervalo[0]+intervalo[1])/2;
	intesc2[0]=(intervalo[0]+intervalo[1])/2+1;
	intesc2[1]=intervalo[1];

	
	pipe(fd1);
	pipe(fd2);
	
	printf("Los números en el intervalo [%d,%d] son:\n",intesc1[0],intesc1[1]);

	if ((esclavo1=fork())<0) {
		perror("\Error en fork");
		exit(0);
	}
	
	if(esclavo1==0){
		close(fd1[0]);//cierro lectura
		close(1);
		dup(fd1[1]);
		sprintf(ini,"%d",intesc1[0]);
		sprintf(fin,"%d",intesc1[1]);
		if(execl("./esclavo", "esclavo", ini, fin, NULL) < 0) {
			perror("\nError en el execl");
			exit(-1);
		}
	}else{
		close(fd1[1]);
		while((read(fd1[0],&buf1,sizeof(int)))>0)
			printf("%s",buf1);
		close(fd1[0]);
		
		printf(" ");
	
		printf("Los números en el intervalo [%d,%d] son:\n",intesc2[0],intesc2[1]);

		if ((esclavo2=fork())<0) {
			perror("\Error en fork");
			exit(0);
		}
		if(esclavo2==0){
			close(STDOUT_FILENO);
			close(fd2[0]);
			dup(fd2[1]);
			sprintf(ini,"%d",intesc2[0]);
			sprintf(fin,"%d",intesc2[1]);
			execl("./esclavo","esclavo",ini,fin,NULL);
		}else{
			close(fd2[1]);
			while((read(fd2[0],&buf2,sizeof(int)))>0)
				printf("%s",buf2);
		
			printf("\n");
			close(fd2[0]);
		}
	}
	printf(" ");
	exit(0);
}
