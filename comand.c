#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include "parser.h"

#define TAM 100 // maximo tamaño de argumentos
#define BUFFERSIZE 200 // Tamano buffer de cd
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
void cargarCiclo(); // funcion para hacer ciclico el prompt
int ejecutarComando(char* comando,char* arg[],int argc); // funcion que ejecuta el comando mipwd


char cwd[BUFFERSIZE];

int main (void){	
        cargarCiclo();
	return 0;
}

void cargarCiclo(){
	struct sigaction my_action;

/* Part I: Catch SIGINT */

        getcwd(cwd,sizeof(cwd));
	char ** items;
	int i, num, background;
	char expresion[TAM];
	printf(ANSI_COLOR_MAGENTA "prompt>:~" ANSI_COLOR_RESET " ");
	printf(ANSI_COLOR_GREEN "%s$" ANSI_COLOR_RESET " ", cwd);
	fgets (expresion, TAM, stdin);
	num = separaItems (expresion, &items, &background);
	 if (num<=0){ // verifica si se digito algun comando
	  	cargarCiclo();
	  }else	if(strcmp(items[0],"myexit")==0){ // compara si el comando es igual a miexit
		liberaItems (items); // libera recursos y sale del progama
		printf("has salido...\n");
		exit(0);
		}else if(strcmp(items[0],"mypwd")==0){ // compara si el comando es igual a mipwd
			ejecutarComando("mypwd",NULL,num); // ejecuta la funcion respectiva
			cargarCiclo(); // carga el prompt de nuevo
		}else if(strcmp(items[0],"myecho")==0){ // compara si el comando es igual a miecho
			ejecutarComando("myecho",items,num); // ejecuta la funcion respectiva
			printf("\n");
			cargarCiclo(); // carga el prompt de nuevo
		}else if(strcmp(items[0],"mypause")==0){ // compara si el comando es igual a mipause
			int pause(void);
			ejecutarComando("mypause",NULL,num); // ejecuta la funcion respectiva			
			cargarCiclo(); // carga el prompt de nuevo
			// carga el promt de nuevo en caso de no coincidir con ningun comando
		}else if(strcmp(items[0],"mygrep")==0){ 
			ejecutarComando("mygrep",items,num);// ejecuta la funcion respectiva
			cargarCiclo(); // carga el prompt de nuevo
		}else if(strcmp(items[0],"psinfo")==0){ 
			ejecutarComando("psinfo",items,num);
			cargarCiclo(); // carga el promt de nuevo en caso de no coincidir con ningun comando
		}else if(strcmp(items[0],"mykill")==0){ //compara si el comando es mikill
			ejecutarComando("mykill",items,num);// ejecuta la funcion respectiva y envia los paramentros necesarios		
			cargarCiclo(); // carga el promt de nuevo en caso de no coincidir con ningun comando
		}else if(strcmp(items[0],"myclr")==0){// compara si el comando es miclr
			ejecutarComando("myclr",NULL,num);//ejecuta la funcion respectiva			
			cargarCiclo(); // carga el promt de nuevo en caso de no coincidir con ningun comando
		}else if(strcmp(items[0],"myps")==0){
			ejecutarComando("myps",NULL,num);			
			cargarCiclo(); // carga el promt de nuevo en caso de no coincidir con ningun comando
		}else if(strcmp(items[0],"micp")==0){
			ejecutarComando("micp",items,num);			
			cargarCiclo(); // carga el promt de nuevo en caso de no coincidir con ningun comando
		}else if(strcmp(items[0],"mytime")==0){
			ejecutarComando("mytime",NULL,num);			
			cargarCiclo(); // carga el promt de nuevo en caso de no coincidir con ningun comando
		}else{ // en caso de no digitar nada carga nuevamente el prompt
			cargarCiclo();
		}
}

int ejecutarComando(char* comando,char* arg[],int argc){
	int status;
	pid_t miproceso = fork();
	if(miproceso == 0){
		if(strcmp(comando,"mypwd")==0){
		char* aux=(char*)malloc(sizeof(char)*BUFFERSIZE); //reserva memoria
		aux=cwd; //asigna temporal
		strcat(aux,"/pw"); //comcatena comando parala direccion final
		execl(aux,"pw.out",NULL); // ejecuta el archivo externo para obtener el directorio
		free(aux);// libera el espacio reservado
		exit(0);
		}
		if(strcmp(comando,"myecho")==0){
		int i;
		char *mensaje =(char*)malloc(sizeof(char)*1000); // reserva espacio para el mensaje que enviara
		for (i=1; i<argc; i++){// concatena los items para formar el mensaje a enviar
		    strcat(mensaje,arg[i]);
	       	    strcat(mensaje," ");
		    
		}		 

		char* aux=(char*)malloc(sizeof(char)*BUFFERSIZE); //reserva memoria
		aux=cwd; //asigna temporal
		strcat(aux,"/myecho"); //comcatena comando parala direccion final
		execl(aux,"myecho.out",mensaje,NULL); // ejecuta el archivo externo para mostrar un mensaje en pantalla
		free(mensaje);// libera el espacio reservado
		free(aux);// libera el espacio reservado
		exit(0);
		}
		if(strcmp(comando,"mypause")==0){
		char* aux=(char*)malloc(sizeof(char)*BUFFERSIZE); //reserva memoria
		aux=cwd; //asigna temporal
		strcat(aux,"/pause"); //comcatena comando parala direccion final
		execl(aux,"pause.out",NULL); // ejecuta el archivo externo para realizar la pausa del comand
		kill(getppid(),SIGSTOP);
		free(aux);
		exit(0);
		}
		if(strcmp(comando,"mygrep")==0){
		char coma[50]="grep";
		strcat(coma, " ");
		if((arg[1]==NULL) || (arg[2]==NULL) ){
			printf("Falta de argumentos\n");
			exit(0);
		}else{
		strcat(coma, arg[1]);
		strcat(coma, " ");
		strcat(coma, arg[2]);
		system(coma);
		exit(0);
		}}
		if(strcmp(comando,"mykill")==0){
		char* aux=(char*)malloc(sizeof(char)*BUFFERSIZE); //reserva memoria
		aux=cwd; //asigna temporal
		strcat(aux,"/kill"); //comcatena comando parala direccion final
		execl(aux,"kill.out",arg[1],arg[2],NULL);
		free(aux);
		exit(0);
		}
		if(strcmp(comando,"psinfo")==0){
		char* aux=(char*)malloc(sizeof(char)*BUFFERSIZE); //reserva memoria
		aux=cwd; //asigna temporal
		strcat(aux,"/psinfo"); //comcatena comando parala direccion final
		execl(aux,"psinfo.out",arg[1],arg[2],NULL);
		free(aux);
		exit(0);
		}
		if(strcmp(comando,"myclr")==0){	
			char* aux=(char*)malloc(sizeof(char)*BUFFERSIZE); //reserva memoria
			aux=cwd; //asigna temporal
			strcat(aux,"/clr"); //comcatena comando parala direccion final	
			execl(aux,"clr.out",NULL); // ejecuta el archivo externo para obtener los archivos
			free(aux);
		        exit(0);
		}
		if(strcmp(comando,"myps")==0){
			system("ps");
			exit(0);
		}
		if(strcmp(comando,"mytime")==0){
			system("date");
			exit(0);
		}
		if(strcmp(comando,"micp")==0){
		char* aux=(char*)malloc(sizeof(char)*BUFFERSIZE); //reserva memoria
		aux=cwd; //asigna temporal
		strcat(aux,"/cp"); //comcatena comando parala direccion final
			execl(aux,"cp.out",arg[1],arg[2],NULL);
			free(aux);
			exit(0);
		}
	}else{
		wait(&status);
	}
}




