#include <stdio.h>
#include <stdlib.h>
#include "Alumno.h"

int main() {
	FILE *archi;
	Alumno alu;

	if((archi=fopen("alumnos.dat","w"))!=NULL) {
		printf("Legajo? \n");
		scanf("%i",&(alu.legajo));
		while(alu.legajo != -1) {
			printf("Nombre?\n");
			scanf("%s",alu.nombre);
			fwrite(&alu,sizeof(Alumno),1,archi);
			printf("Legajo?\n");
			scanf("%i",&(alu.legajo));
		}
		fclose(archi);
	} else printf("ERROR. no se pudo crear el archivo");
	return 0;
	}
