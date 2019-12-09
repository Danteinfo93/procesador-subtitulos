#include "lista.h"
#include <stdlib.h>
#include <string.h>

void list_init(t_list *l) {
	*l = NULL;
}

short list_find(t_list l, t_data e) {
	while(l) {
		if (l->data.indice == e.indice) return 1;
		l = l->next;
	}
	return 0;
}

short list_is_empty(t_list l) {
	return l == NULL;
}

t_data list_add(t_list *l, t_data e) {
	t_list_node *node = malloc(sizeof(t_list_node));
	node->data = e;
	node->data.texto=(char*)malloc((strlen(e.texto)+1)*sizeof(char));
	strcpy(node->data.texto,e.texto);
	node->next = NULL;
	if (*l == NULL) *l = node;
	else {
		t_list_node *n = *l;
		while (n->next) n = n->next;
		n->next = node;
	}
	return e;
}

t_list list_delete(t_list *l, t_data e) {
	if (list_find(*l,e)) {
		t_list_node *prev = NULL, *node = *l;
		while((node->data.indice != e.indice) && (node)) {
			prev = node;
			node = node->next;
		}
		if (!prev) {*l = node->next;free(node);return *l;} //si ta primero
		else {
			prev->next = node->next;//medio o ultimo
			free(node);
			return prev->next;
		}
		
	}
	return NULL;
}

/* Libera las estructuras internas usadas por este tipo de dato */
void list_free(t_list *l) {
	t_list_node *node = *l;
	while(node) {
		t_list_node *aux;
		aux = node;
		node = node->next;
		free(aux);
	}
}
