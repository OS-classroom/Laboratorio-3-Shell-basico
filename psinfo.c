#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//Se crea la estructura proceso
struct Proceso {
  char nombre[40];
  char estatus[25];
  char numeroProceso[10];	
  char iTamano[15];
  char tamanoText[15];
  char tamanoData[15];
  char tamanoStack[15];
  char numeroCamVolun[12];
  char numeroCamInvol[12];
};

//Se le asigna un alias
typedef struct Proceso Proceso;

//Funciones que me ayudaran a realizar lo requerido
void genereArchivo(int j, Proceso *aux);
int guardarProcesos(Proceso *array, int cantProcesos, char *procesos[]);
void escribirConsola(Proceso *array,int j);


//Main del programa
int main(int argc, char *argv[]){
	int j=0;
	//Arreglo que guardara los procesos con su respectiva informacion
	//Se le asigna el tamaño de la cantidad de identificador de procesos que entra
        Proceso prueba[argc];

	//Se hacen las respectivas validaciones
	if(argv[1]==NULL)
		printf("Ingrese una opcion adecuada: -r o -l\n");
	else{
		if(argv[2]==NULL)
				printf("Hacen falta parametros!!!!!!\n");
		else{
				j=guardarProcesos(prueba,argc,argv);
			//Para escribir en consola
			if(strcmp(argv[1],"-l")==0){
				escribirConsola(prueba,j-1);
			}			
			//Para generar el archivo .info
			else if(strcmp(argv[1],"-r")==0)
				genereArchivo((j-1),prueba);
			else
				printf("Ha ingresa una opcion incorrecta\n");
		}
	}
}


////////////////////////////////////////////////////////////////////////////////////
//se Implementan la funciones necesarias

//Generara el arreglo con los procesos
int guardarProcesos(Proceso *array, int cantProcesos, char *procesos[]){
	//Apuntador para leer el archivo
	FILE *iF;
        char line[201];
        char fullname [161];
	int fila;
	//El indice j me asegura que se empezara a tomar de los parametros de entrada (procesos)
	//Desde el identificador de los procesos que sean pasados
	int i,j=2;
	//Se resta 2 para que no me tome los dos primeros parametros los cuales serian
	//el nombre de la accion y "-r" o "-l" segun el caso
	cantProcesos=cantProcesos-2;
	//While que controlara cuantos procesos entran como parametro
	while(cantProcesos>0){
		
		//Inicializa de manera ciclica las variables auxiliares
		fila=1;
		strcpy(fullname, "");
		//Esto se hace para limpiar de posible basura los espacios en memoria pedidos para este arreglo de procesos
		strcpy((*array).nombre,"");
		strcpy((*array).estatus,"");
		strcpy((*array).numeroProceso,procesos[j]);
		strcpy((*array).iTamano,"");
		strcpy((*array).tamanoText,"");
		strcpy((*array).tamanoData,"");
		strcpy((*array).tamanoStack,"");
		strcpy((*array).numeroCamVolun,"");
		strcpy((*array).numeroCamInvol, "");
		//Se concatena el numero de proceso que va a buscarse                   
		strcat(fullname,"/proc/");
		strcat(fullname,procesos[j]);
		strcat(fullname,"/status");
	
		iF=fopen(fullname, "r");
		
		if(iF==NULL){
			
			printf("No se puede encontrar el proceso: %s\n", (*array).numeroProceso);
			//Se usa para cuando se vaya a escribir el archivo, este detecte que el proceso no existe y lance un aviso
			//Se usan ":" como señal para indicar este posible hecho
			strcat((*array).nombre,":");
			
									
		
		}else{
			
			//En este ciclo se lee fila por fila la informacion obtenida y se obtiene la pedida	
			      while(fgets(line, 201, iF)!=NULL){
			//Se enumero cada fila de alli se encontro que
			//dado que las filas necesarias son solo la 1(name),3(status),17(VmPeak),26(VmData),27(VmStk),28(VmExe)
			//53(voluntary_ctxt_switches) y 54(nonvoluntary_ctxt_switches:)
			//con este switch se asegura obtener solo estas

					switch(fila){
			//Los mini ciclos de cada caso, tienen la funcion de dejarme el indice i en ":" de la fila para	
			//Proceder a tomar lo que esta despues de ellos
						case 1:	
							i=0;
							while(line[i]!=58)
								i++;
							strcat((*array).nombre, &line[i+1]);							
							fila++;
							break;
						case 3:
							i=0;
						        while(line[i]!=58)
						                i++;
							strcat((*array).estatus, &line[i+1]);						        
						        fila++;
						        break;
						case 17:
						       i=0;
						        while(line[i]!=58)
						                i++;				
						        strcat((*array).iTamano, &line[i+1]);
							fila++;
						        break;
						case 28:
						       i=0;
						        while(line[i]!=58)
						                i++;
						        strcat((*array).tamanoText, &line[i+1]);
							fila++;
						        break;
						case 26:
						       i=0;
						        while(line[i]!=58)
						                i++;
						        strcat((*array).tamanoData, &line[i+1]);
							 
						        fila++;
						        break;
						case 27:
						       i=0;
						        while(line[i]!=58)
						                i++;
						        strcat((*array).tamanoStack, &line[i+1]);
							
			 
						        fila++;
						        break;
						case 53:
						       i=0;
						        while(line[i]!=58)
						                i++;
						        strcat((*array).numeroCamVolun, &line[i+1]);
							
			 
						        fila++;
						        break;
						case 54:
							i=0;
						        while(line[i]!=58)
						                i++;
						        strcat((*array).numeroCamInvol, &line[i+1]);
							fila++;
						        break;
						default:
							fila++;		
						} 
				
				}
			
		
		
		
		}
			
			
			printf("\n");
			cantProcesos=cantProcesos-1;
			array++;
			j++;
	}
	//Se reduce a 1 dado que si se deja tal cual ocasionaria un error, esto para reutilazar el inidice j	
	j=j-1;	
	//fclose(iF);
	return j;
}

////////////////////////////////////////////////
//Escribe en consola los datos del proceso
void escribirConsola(Proceso *array, int j){
	int i=0;
	
	while(i<j){
		if(strcmp((*array).nombre,":")==0)
			printf("El proceso %s es inexistente\n", (*array).numeroProceso);
		else{
			printf("PID:%s\n",(*array).numeroProceso);
			printf("Nombre del proceso:%s",(*array).nombre);
			printf("Estado:%s",(*array).estatus);
			printf("Tamaño total de la imagen de memoria:%s",(*array).iTamano);
			printf("Tamaño de la memoria en la región TEXT:%s",(*array).tamanoText);
			printf("Tamaño de la memoria en la región DATA:%s",(*array).tamanoData);
			printf("Tamaño de la memoria en la región Stack:%s",(*array).tamanoStack);
			printf("Número de cambios de contexto realizados voluntarios%s",(*array).numeroCamVolun);
			printf("Número de cambios de contexto realizados involuntarios%s",(*array).numeroCamInvol);
			

		}
		i++;
		array++;	
	}

}

////////////////////////////////////////////////////////
//Generara el archivo salida

void genereArchivo(int j, Proceso *aux){
	int i=1;
	FILE *outFile;
	Proceso *aux2=aux;
	char archivosalida[168]="";
	strcat(archivosalida,"psinfo-report-");
	while(i<=j){
		strcat(archivosalida,(*aux2).numeroProceso);
		aux2++;
		i++;
		if(i<=j)
			 strcat(archivosalida,"-");
	}
	i=1;
	strcat(archivosalida,".info");
	outFile=fopen(archivosalida, "w");
	//Con este ciclo se ira escribiendo en el archivo salida los datos de cada proceso.
	while(i<=j){
		//Recibe la señal, si esta son dos puntos, lanza un aviso de que el proceso no existe
		if(strcmp((*aux).nombre,":")==0)
			fprintf(outFile,"--El proceso %s no existe\n!!!",(*aux).numeroProceso);
		else{
		fprintf(outFile,"\n--Informacion Recolectada!!!\nPID:%s\n",(*aux).numeroProceso);
		fprintf(outFile,"Nombre del proceso:%s",(*aux).nombre);
		fprintf(outFile,"Estado:%s",(*aux).estatus);
		fprintf(outFile,"Tamaño total de la imagen de memoria:%s",(*aux).iTamano);
		fprintf(outFile,"Tamaño de la memoria en la región TEXT:%s",(*aux).tamanoText);
		fprintf(outFile,"Tamaño de la memoria en la región DATA:%s",(*aux).tamanoData);
		fprintf(outFile,"Tamaño de la memoria en la región STACK:%s",(*aux).tamanoStack);
		fprintf(outFile,"Número de cambios de contexto realizados voluntarios:%s",(*aux).numeroCamVolun);
		fprintf(outFile,"Número de cambios de contexto realizados involuntarios:%s\n",(*aux).numeroCamInvol);
		}
		aux++;
		i++;
	}
	printf("Se creo exitosamente el archivo: %s!!!\n",archivosalida);
}
