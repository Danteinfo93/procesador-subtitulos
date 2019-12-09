#ifndef _TIPO_LISTA
#define _TIPO_LISTA

typedef struct t_tiempo {
	int HH;
	int MM;
	int SS;
	int mmm;
} t_tiempo;

typedef struct t_data {
	unsigned int indice;
	t_tiempo comienzo;
	t_tiempo fin;
	char *texto;
} t_data;

#endif
