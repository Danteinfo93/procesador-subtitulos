#include "manipulador.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void inc_tiempo(t_tiempo *com,int millis) {
	int resto;
	while(millis>=1000) {
		if((com->SS+1)<60)com->SS=com->SS+1;
		else {
			com->SS=0;
			if((com->MM+1)<60)com->MM=com->MM+1;
			else {
				com->MM=0;
				com->HH=com->HH+1;
			}
		}
		millis=millis-1000;
	}
	if((com->mmm+millis)<1000) com->mmm = com->mmm+millis;
	else {
		resto= ((com->mmm+millis)-1000);
		com->mmm=resto;
		if((com->SS+1)<60)com->SS=com->SS+1;
		else {
			com->SS=0;
			if((com->MM+1)<60)com->MM=com->MM+1;
			else {
				com->MM=0;
				com->HH=com->HH+1;
			}
		}
	}
}

void decrementar_tiempo(t_tiempo *com,int millis) {
	int resto;
	while(millis>1000) {
		if((com->SS-1)>=0)com->SS=com->SS-1;
		else {
			com->SS=59;
			if((com->MM-1)>=0)com->MM=com->MM-1;
			else {
				com->MM=59;
				com->HH=com->HH-1;
			}
			millis=millis-1000;
		}
	}
	if((com->mmm-millis)>=0) com->mmm = com->mmm-millis;
	else {
		resto=((com->mmm+1000)-millis);
		com->mmm=resto;
		if((com->SS-1)>=0)com->SS=com->SS-1;
		else {
			com->SS=59;
			if((com->MM-1)>=0)com->MM=com->MM-1;
			else {
				com->MM=59;
				com->HH=com->HH-1;
			}
		}
	}
}

int cmp_tiempo(t_tiempo t1,t_tiempo t2) { // devuelve menor, igual o mayor a 0.. correspondiendose a la diferencia de t1 - t2
	int aux[4];
	int i,n=0;

	aux[0]= t1.HH - t2.HH;
	aux[1]= t1.MM - t2.MM;
	aux[2]= t1.SS - t2.SS;
	aux[3]= t1.mmm - t2.mmm;
	n=n+(aux[0]*3600000);
	n=n+(aux[1]*60000);
	n=n+(aux[2]*1000);
	n=n+(aux[3]);
	return n;
}

void corregir_indices(t_list l,int n){
	while(l){
		l->data.indice=l->data.indice + n;
		l=l->next;
	}
}

t_tiempo convertir_a_tiempo(int t){
	t_tiempo aux;
	
	aux.HH=0;
	aux.MM=0;
	aux.SS=0;
	aux.mmm=0;
	while(t>1000){
		t=t-1000;
		inc_tiempo(&aux,1000);
	}
	inc_tiempo(&aux,t);
	return aux;
}


/*--------------------------------------------------------------------------*/
void desplazar_subs(t_list l,int millis) {
	while(l) {
		inc_tiempo(&(l->data.comienzo),millis);
		inc_tiempo(&(l->data.fin),millis);
		l=l->next;
		
	}
}

void separar_solapados(t_list l) {
	while(l) {
		if(l->next) {
			if(cmp_tiempo(l->next->data.comienzo, l->data.fin)<=0) { //si el el final del primer subt es mayor q el comienzo del segundo.
				l->data.fin=l->next->data.comienzo; //igualo el final del primer sub cn el cmienzo del segundo
				decrementar_tiempo(&(l->data.fin), 500);
			}
		}//y le resto 500 milis para q no queden superpuestos
		l=l->next;
	}
}

void borrar(t_list *l,int indice){
	t_data aux;
	t_list ptr=NULL;
	
	aux.indice=indice;
	ptr=list_delete(l, aux);
	corregir_indices(ptr,-1);
}

void insertar_sub(t_list *l,int com,int fin,char* texto){
	t_list_node *nodo=malloc(sizeof(t_list_node));
	nodo->data.texto=malloc((strlen(texto)+7)*sizeof(char));
	strcpy(nodo->data.texto, texto);
	strcat(nodo->data.texto,"\r\n\r\n");
	nodo->data.comienzo=convertir_a_tiempo(com);
	nodo->data.fin=convertir_a_tiempo(fin);
	nodo->next=NULL;
	int cont=1; //para controlar indice del nuevo nodo
	t_list_node *ant=NULL,*act=*l;
	
	while(act &&((cmp_tiempo(nodo->data.comienzo, act->data.fin)>=0)||(cmp_tiempo(nodo->data.comienzo, act->data.comienzo)>=0))){
		ant=act;
		act=act->next;
		cont++;
	}
	if(!ant) {nodo->next=*l;nodo->data.indice=1;*l=nodo;corregir_indices(nodo->next,1);}
	else{
		nodo->data.indice=cont;
		ant->next=nodo;
		nodo->next=act;
		corregir_indices(nodo->next,1);
	}
		
}

void duracion_min(t_list l,int n) {
	t_tiempo time_act,time_min,aux;
	int dif;
	while(l) {
		if(cmp_tiempo(l->data.fin,l->data.comienzo)<n) {
			time_act=convertir_a_tiempo(cmp_tiempo(l->data.fin,l->data.comienzo));//lo que dura,en tiempo, un sub
			time_min=convertir_a_tiempo(n);
			dif=cmp_tiempo(time_min,time_act);
			aux=l->data.fin;
			inc_tiempo(&(aux),dif);//sumo lo que le falta al tiempo del sub actual, para q cumpla cn el tiempo minimo
			if(l->next && (cmp_tiempo(l->next->data.comienzo,aux)>=75)) { // si tiene minimamente 75 mmm de distancia cn el sig sub
				inc_tiempo(&(l->data.fin),dif);   // se modifica el tiempo del sub en la lista sumandole la dif
			} else {
				if(l->next) {//sino, se modifica el tiempo del sub para q quede a 75mmm del siguiente sub
					l->data.fin=l->next->data.comienzo;
					decrementar_tiempo(&(l->data.fin),75);
				} else {//en el ultimo sub se suma nomas la diferencia
					inc_tiempo(&(l->data.fin),dif);
				}
			}
		}
		l=l->next;
	}
}

void aumentar_duracion(t_list l){
	int n;
	t_tiempo time_act,time_min,aux;
	int dif;
	
	while(l) {
		n=(strlen(l->data.texto)/25)*1000;//25 cps
		n=n+((strlen(l->data.texto)%25)*40);//"modulo" cada caracter valdria 40mmm (1000/25)
		printf("dur tiempo: %d  , dur min sub: %d \n",cmp_tiempo(l->data.fin,l->data.comienzo),n );
		if(cmp_tiempo(l->data.fin,l->data.comienzo)<n) {
			time_act=convertir_a_tiempo(cmp_tiempo(l->data.fin,l->data.comienzo));//lo que dura,en tiempo, un sub
			time_min=convertir_a_tiempo(n);
			dif=cmp_tiempo(time_min,time_act);
			aux=l->data.fin;
			inc_tiempo(&(aux),dif);//sumo lo que le falta al tiempo del sub actual, para q cumpla cn el tiempo minimo
			if(l->next && (cmp_tiempo(l->next->data.comienzo,aux)>=75)) { // si tiene minimamente 75 mmm de distancia cn el sig sub
				inc_tiempo(&(l->data.fin),dif);   // se modifica el tiempo del sub en la lista sumandole la dif
			} else {
				if(l->next) {//sino, se modifica el tiempo del sub para q quede a 75mmm del siguiente sub
					l->data.fin=l->next->data.comienzo;
					decrementar_tiempo(&(l->data.fin),75);
				} else {//en el ultimo sub se suma nomas la diferencia
					inc_tiempo(&(l->data.fin),dif);
				}
			}
		}
		l=l->next;
	}
}

void reducir(t_list l, int n){
	t_tiempo aux;
	
	while(l) {
		if(cmp_tiempo(l->data.fin,l->data.comienzo)>n) {
			aux=l->data.comienzo;
			inc_tiempo(&(aux),n);
			l->data.fin=aux;
		}
		l=l->next;
	}
}

void validar(t_list l){
	int  indice,
	solapado,menos1seg,mas7seg,
	lineaslargas,demasiadoscps,
	mas2lineas, pocaseparacion,
	cont_ind,n,i,cont_lineas;
	
	if(l && l->data.indice!=1) printf("El archivo de subtitulos no comienza en 1\n");
	cont_ind=1;
	while(l){
		indice=0;solapado=0;  //inicializo los boleans por cada pasada
		menos1seg=0;mas7seg=0;
		lineaslargas=0;demasiadoscps=0;
		mas2lineas=0; pocaseparacion=0;
		cont_lineas=0;
		
		if(cont_ind != l->data.indice) indice=1;  //les voy dando su correspondiente estados
		if(l->next && (cmp_tiempo(l->next->data.comienzo, l->data.fin)<=0)) solapado=1;
		if(cmp_tiempo(l->data.fin,l->data.comienzo)<1000) menos1seg=1;
		if(cmp_tiempo(l->data.fin,l->data.comienzo)>7000) mas7seg=1;
		if(strlen(l->data.texto)>36) lineaslargas=1;
		n=(strlen(l->data.texto)/25)*1000;//25 cps
		n=n+((strlen(l->data.texto)%25)*40);//restos pd:40mmm x car 
		if(cmp_tiempo(l->data.fin,l->data.comienzo)<n) demasiadoscps=1;
		for(i=0; l->data.texto[i];i++){
			if(l->data.texto[i]=='\n')
				cont_lineas++;
		}
		if(cont_lineas>3) mas2lineas=1; //pd:3 porq ai q sumarle el espacio en blanco
		if(l->next && (cmp_tiempo(l->next->data.comienzo, l->data.fin)<75)) pocaseparacion=1;
		cont_ind++;
		
		if(indice) printf("El indice num: %d (tendria q ser : %d) no es un consecutivo ordenado\n", l->data.indice,cont_ind-1); //imprimo lo q corresponde segun los boleans 
		if(solapado) printf("el sub n: %d esta superpuesto con el siguiente\n",l->data.indice);
		if(menos1seg) printf("el sub n: %d dura menos de 1 seg, es corto\n",l->data.indice);
		if(mas7seg) printf("el sub n: %d dura mas de 7 seg, es largo\n",l->data.indice);
		if(lineaslargas) printf("el sub n: %d tiene texto con mas de 36 caracteres\n",l->data.indice);
		if(demasiadoscps) printf("el sub n: %d tiene demasiados cps (mas de 25)\n",l->data.indice);
		if(mas2lineas) printf("el sub n: %d tiene mas de 2 lineas\n",l->data.indice);
		if(!solapado && pocaseparacion) printf("el sub n: %d esta a menos de 75mmm del sig sub\n",l->data.indice);
		
		l=l->next;
	}
}
	