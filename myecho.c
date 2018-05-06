#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
 
int main(int argc,char* argv[])
{
if(argc>=2){
//for(i =1;i<argc;i++){
     if(strcmp(argv[1],"")){
	write(1,argv[1],strlen(argv[1]));
     }else{
	char errMes[] ="Numero de parametros invalido!\n";
	write(1,errMes,sizeof(errMes));
     }
	//write(1," ",4);
//}
}
else{
	char errMes[] ="Numero de parametros invalido!\n";
	write(1,errMes,sizeof(errMes));
}
    return 0;
}