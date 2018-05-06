#include <syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>


int main(int argc,int args[]){
   long size;
   char *buf;
   char *ptr;
   size = pathconf(".", _PC_PATH_MAX); // toma el maximo tamaño de una direccion
   ptr = getcwd(buf, (size_t)size); // ejecuta el system call que obtiene el directorio actual
    printf("%s\n",ptr); // imprime la ruta generada
	return 0;
}
