#ifndef _MANIPULADOR_H
#define _MANUPULADOR_H
#include "lista.h"
#include "iterador.h"

/* ESTE ARCHIVO ENCABEZADO SOLO TIENE PROT. DE OPERACIONES NO DEFINE TIPO DE DATO
 lo hice solo para q quede mas ordenado*/

/*Desplaza todos los subtitulos int milisegundos*/
void desplazar_subs(t_list ,int);
/*Separa los subtitulos que esten solapados*/
void separar_solapados(t_list );
/*Borra un elemento con indice int*/
void borrar(t_list *,int);
/*Inserta un subtitulo en el tiempo(millis) especificado  */
void insertar_sub(t_list *,int,int,char*);
/*Establece una duracion minima de los subtitulos, o hasta q este a 75mmm del siguiente*/
void duracion_min(t_list ,int);
/*Aumenta la duracion de los subtitulos que tengan demasiados caracteres por segundo
 hasta que tengan 25 cps o menos. O hasta que este a 75 milisegundos
  del subtitulo siguiente(lo que suceda primero)*/
void aumentar_duracion(t_list);
/*Reduce el tiempo de los subtitulos que duren mas de int milisegundos*/
void reducir(t_list, int );
/*Valida los subtitulos buscando errores. Imprime una descripcion por error encontrado*/
void validar(t_list );


#endif