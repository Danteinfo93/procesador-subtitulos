#include <stdio.h>
#include "alumno.h"
int main(int argc, char *argv[]){
Alumno alu;
FILE *archi;
if ( (archi=fopen("alumnos.dat", "r"))!=NULL){
      printf("\nNombre: ");
      while (!feof(archi)){
       	fread(&alu, sizeof(Alumno), 1, archi);
      	printf("\n%20s--(%d)", alu.nombre, alu.legajo);
      }
      fclose(archi);
}
else fprintf(stderr, "No se pudo abrir el archivo");
return 0;
}
