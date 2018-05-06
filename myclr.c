#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

int main(int argc,int args[]){
	fprintf(stdout, "\33[2J");
	fprintf(stdout, "\33[1;1H");
	return EXIT_SUCCESS;
}
