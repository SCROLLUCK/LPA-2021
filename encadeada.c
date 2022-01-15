#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct evento_t {
	double tempo;
	int alvo;
	int tipo;
}evento_t;

typedef struct lista_eventos_t lista_eventos_t;
struct lista_eventos_t {
	evento_t * evento;
	lista_eventos_t *proximo;
};

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
		while(evento->tempo > aux->evento->tempo && aux->proximo != NULL) aux = aux->proximo;
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
}

int main() {

	lista_eventos_t *lista = NULL;

	FILE * f = fopen("teste.txt","r");
	if(!f) perror("arquivo não encontrado!");

	while(!feof(f)){
		evento_t *novo_evento = malloc(sizeof(evento_t)); // Aloca o novo evento
		if(!novo_evento) perror("erro ao alocar novo evento");
		
		fscanf(f,"%lf\t%d\t%d\n",&novo_evento->tempo, &novo_evento->alvo, &novo_evento->tipo);
		// lista_eventos_adicionar_inicio(novo_evento,&lista);
		// lista_eventos_adicionar_fim(novo_evento,&lista);
		lista_eventos_adicionar_ordenado(novo_evento, &lista);
	
	}

	lista_eventos_listar(lista);
}