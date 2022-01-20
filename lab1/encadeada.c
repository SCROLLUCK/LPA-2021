#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "encadeada.h"

bool lista_eventos_adicionar_inicio(evento_t *evento, lista_eventos_t **lista){
	lista_eventos_t *item_novo = malloc(sizeof(lista_eventos_t)); // Aloca o novo item
	if (item_novo == NULL) return false; // Falta memória?
	item_novo->evento = evento; // Seta o novo item
	item_novo->proximo = *lista; // O próximo do novo item será a lista
	*lista = item_novo; // Aqui, estamos mudando o ponteiro da lista
	return true;
}

bool lista_eventos_adicionar_fim(evento_t *evento, lista_eventos_t **lista){
	lista_eventos_t *item_novo = malloc(sizeof(lista_eventos_t)); // Aloca o novo item
	if (item_novo == NULL) return false; // Falta memória?

	item_novo->evento = evento; // Seta o novo item
	item_novo->proximo = NULL;
	
	if(*lista == NULL) *lista = item_novo; 
	else{
		lista_eventos_t * aux = *lista;
		while(aux->proximo != NULL) aux = aux->proximo;
		aux->proximo = item_novo;
	}
	return true;
}

bool lista_eventos_adicionar_ordenado(evento_t *evento, lista_eventos_t **lista){
	lista_eventos_t *item_novo = malloc(sizeof(lista_eventos_t)); // Aloca o novo item
	if (item_novo == NULL) return false; // Falta memória?

	item_novo->evento = evento; // Seta o novo item
	item_novo->proximo = NULL;
	
	if(*lista == NULL) *lista = item_novo;
	else if(evento->tempo < (*lista)->evento->tempo){
		item_novo->proximo = *lista;
		*lista = item_novo;
	}else{
		lista_eventos_t* aux = *lista;
		while(aux->proximo != NULL && aux->proximo->evento->tempo < evento->tempo) aux = aux->proximo;
		item_novo->proximo = aux->proximo;
		aux->proximo = item_novo;
	}
	return true;
}

void lista_eventos_listar(lista_eventos_t *lista){
	lista_eventos_t * aux = lista;
	while(aux){
		printf("TEMPO: %3.6f, ALVO: %d, TIPO: %d\n",aux->evento->tempo,aux->evento->alvo, aux->evento->tipo);
		aux = aux->proximo;
	}
	printf("\n");
}

TEncadeada* CriarLista(){
	TEncadeada* nova_lista = malloc(sizeof(TEncadeada));
	if(nova_lista){
		nova_lista->lista = malloc(sizeof(lista_eventos_t**));
		*nova_lista->lista = NULL;
		nova_lista->lista_eventos_adicionar_fim = lista_eventos_adicionar_fim;
		nova_lista->lista_eventos_adicionar_inicio = lista_eventos_adicionar_inicio;
		nova_lista->lista_eventos_adicionar_ordenado = lista_eventos_adicionar_ordenado;
		nova_lista->lista_eventos_listar = lista_eventos_listar;
	}
	return nova_lista;
}