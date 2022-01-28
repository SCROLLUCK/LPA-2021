#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "encadeada.h"


bool lista_pessoas_adicionar(pessoa_t *pessoa, lista_pessoas_t **lista){
	lista_pessoas_t *item_novo = malloc(sizeof(lista_pessoas_t)); // Aloca o novo item
	if(!item_novo){
		perror("Erro ao alocar memória para um elemento da Lista!\n");
		exit(1);
	}
	item_novo->pessoa = pessoa; // Seta o novo item
	item_novo->proximo = *lista; // O próximo do novo item será a lista
	*lista = item_novo; // Aqui, estamos mudando o ponteiro da lista
	return true;
}

void lista_pessoas_listar(lista_pessoas_t *lista){
	lista_pessoas_t * aux = lista;
	while(aux){
		printf("- %s\t%lld\t%d\n",aux->pessoa->nome,aux->pessoa->cpf, aux->pessoa->idade);
		aux = aux->proximo;
	}
}


TEncadeada* CriarLista(){
	
	TEncadeada* nova_lista = malloc(sizeof(TEncadeada));
	if(!nova_lista){
		perror("Erro ao alocar memória para a Lista!\n");
		exit(1);
	}
	
	nova_lista->lista = malloc(sizeof(lista_pessoas_t**));
	if(!nova_lista->lista){
		perror("Erro ao alocar memória para a Lista!\n");
		exit(1);
	}

	*nova_lista->lista = NULL;
	nova_lista->lista_pessoas_adicionar = lista_pessoas_adicionar;
	nova_lista->lista_pessoas_listar = lista_pessoas_listar;

	return nova_lista;
}