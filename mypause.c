#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void my_pause();

int main()
{
  printf("Presiona cualquier tecla para continuar...\n");
  my_pause();
  return 0;
}

void my_pause(){
  getchar();
}