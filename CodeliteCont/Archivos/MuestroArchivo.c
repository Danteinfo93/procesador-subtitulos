#include <stdio.h>
#include "Alumno.h"

int main(){
	FILE *archi;
	Alumno alu;
	
	if(archi=fopen("alumnos.dat","r")){
		fread(&alu, sizeof(Alumno),1,archi);
		while(!feof(archi)){
			printf("nombre: %s\n legajo: %i\n",alu.nombre,alu.legajo);
			fread(&alu, sizeof(Alumno),1,archi);
		}
	fclose(archi);	
	}
return 0;
}

