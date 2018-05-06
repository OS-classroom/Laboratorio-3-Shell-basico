#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>

int main (int args, char *arg[]){
	
	char comando[50]="grep";
		printf("esta mierda no funciona");
		strcat(comando, " ");
		strcat(comando, arg[1]);
		strcat(comando, " ");
		strcat(comando, arg[2]);
		system(comando);
}
