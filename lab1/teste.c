#include <stdio.h>
#include <stdlib.h>
#include "encadeada.h"

// COMANDO PARA COMPILAR PROGRAMA: gcc *.c *.h -o teste
// COMANDO PARA EXECUTAR PROGRAMA: ./teste 
//	Aluno: Lucas de Lima Castro MAT: 21551892

void insere(int tipo){
	TEncadeada* Encadeada = CriarLista();
	FILE * f = fopen("teste.txt","r");
	if(!f) perror("arquivo não encontrado!\n");

	while(!feof(f)){
		evento_t *novo_evento = malloc(sizeof(evento_t)); // Aloca o novo evento
		if(!novo_evento) perror("erro ao alocar novo evento");
		fscanf(f,"%lf\t%d\t%d\n",&novo_evento->tempo, &novo_evento->alvo, &novo_evento->tipo);
		if(tipo == 1) Encadeada->lista_eventos_adicionar_inicio(novo_evento,Encadeada->lista);
		if(tipo == 2) Encadeada->lista_eventos_adicionar_fim(novo_evento,Encadeada->lista);
		if(tipo == 3) Encadeada->lista_eventos_adicionar_ordenado(novo_evento,Encadeada->lista);
	
	}
	Encadeada->lista_eventos_listar(*Encadeada->lista);
	free(Encadeada);
}
int main() {
   
	printf("Questao 1: Insere no inicio\n\n");
	insere(1);
	printf("Questao 2: Insere no fim\n\n");
	insere(2);
	printf("Questao 3: Insere ordenado\n\n");
	insere(3);
}

