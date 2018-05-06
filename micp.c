#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <errno.h>

#ifndef BUF_SIZE /* Allow "cc -D" to override definition */
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[])
{
    int inputFd;
    int outputFd;
    int openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buf[BUF_SIZE];

    /* check for the inputs */
    int arg_count=0;
    //for (arg_count; arg_count < argc; arg_count++)
        //printf("argv[%d] = %s\n", arg_count, argv[arg_count]);

    if (argc != 3 || strcmp(argv[1], "--help") == 0)
        printf("%s origen destino\n", argv[0]);

    /* open input and outpu files */
    inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1)
        printf("No se pudo abrir el archivo %s\n", argv[1]);

    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; /*rw-rw-rw*/

    outputFd = open(argv[2], openFlags, filePerms);

    if (outputFd == -1)
        printf("No se pudo abrir el archivo %s\n", argv[2]);

    /* transfer data until we encounter end of input or an error */

    while ((numRead = read(inputFd, buf, sizeof(buf))) > 0)
    {
        if (write(outputFd, buf, numRead) != numRead)
            printf("couldn't write whole buffer\n");
    }
    
    if(numRead == 0)
	printf("Archivo copiado exitosamente\n");
    
    if (numRead == -1)
        printf("Error de lectura\n");

    if (close(inputFd) == -1)
        printf("Error al cerrar archivo\n");
    if (close(outputFd) == -1)
        printf("Error al cerrar archivo\n");

    exit(EXIT_SUCCESS);
}
