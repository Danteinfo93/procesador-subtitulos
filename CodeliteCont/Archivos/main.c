#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
	FILE *fp;
	double d = 12.23;
	int i = 101;
	long l = 123023;
	double d2;
	int i2;
	long l2;
	
	if (fp=(fopen("prueba", "wb+"))) {
		fwrite(&d, sizeof(double),1, fp);
		fwrite(&i, sizeof(int),1, fp);
		fwrite(&l, sizeof(long),1, fp);
		rewind(fp);
		fread(&d2, sizeof(double),1, fp);
		fread(&i2, sizeof(int),1, fp);
		fread(&l2, sizeof(long),1, fp);
		printf("%f %d %ld \n", d2, i2, l2);
	} else fputs("ERROR. No se pudo abrir la entrada", stderr);
}
