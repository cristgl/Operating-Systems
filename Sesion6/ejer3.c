#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
int main (int argc, char * argv[])
{
    char nada[5];
    struct flock cerrojo;
    int i,fd;
    for( i=1; i<argc; i++) {

        if ((fd=open(argv[i], O_RDWR)) == -1 ) {
            perror("open fallo");
            continue;
        }
		
		cerrojo.l_type=F_WRLCK;
        cerrojo.l_whence=SEEK_SET;
        cerrojo.l_start=0;	  
        cerrojo.l_len=0;	  


        if((fcntl (fd, F_SETLKW, &cerrojo) )== -1) 
            if(errno==EDEADLK)
                printf("ha detectado interbloqueo EDEADLK\n");

        
        
        printf ("cerrojo puesto sobre el archivo %s\n",argv[i]);
        printf ("pulse cualquier tecla\n");
        scanf("%s",nada);

        

        cerrojo.l_type=F_UNLCK;
        cerrojo.l_whence=SEEK_SET;
        cerrojo.l_start=0;
        cerrojo.l_len=0;
        if (fcntl (fd, F_SETLKW, &cerrojo) == -1) 
        	perror ("Desbloqueo");
        
    }
    return 0;
}
