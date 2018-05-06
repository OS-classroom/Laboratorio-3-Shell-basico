#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main(int argc,int args[]){
	int pid,signal;
	printf("Escribe el numero de la señal que deseas implementar: ");
	scanf("%d",&signal);
	printf("Escribe el PID del proceso que deseas matar: ");
	scanf("%d",&pid);
	kill(pid,signal);
	return 0;
}
