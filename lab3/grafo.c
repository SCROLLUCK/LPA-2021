#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "grafo.h"

// COMANDO PARA COMPILAR PROGRAMA: gcc *.c *.h -o grafo -lm
// COMANDO PARA EXECUTAR PROGRAMA: ./grafo <nome do arquivo>
//	Aluno: Lucas de Lima Castro MAT: 21551892

static bool lista_vizinhos_adicionar(int vizinho, lista_vizinhos_t **lista){
	lista_vizinhos_t *item_novo = malloc(sizeof(lista_vizinhos_t)); // Aloca o novo item
	if (item_novo == NULL) return false; // Falta memória?
	item_novo->id = vizinho; // Seta o novo item
	item_novo->proximo = *lista; // O próximo do novo item será a lista
	*lista = item_novo; // Aqui, estamos mudando o ponteiro da lista
	return true;
}

static void lista_vizinhos_imprimir(lista_vizinhos_t *lista){
	lista_vizinhos_t * aux = lista;
	while(aux){
		printf("%d ",aux->id);
		aux = aux->proximo;
	}
	printf("\n");
}

void grafo_atualizar_vizinhos(grafo_t* grafo){
    for(int i =0;i<grafo->tamanho; i++){
        for(int j=0;j < grafo->tamanho; j++){
            if(i != j){
                double distancia = sqrt(pow((grafo->dados[i]->pos_x - grafo->dados[j]->pos_x), 2) + pow((grafo->dados[i]->pos_y - grafo->dados[j]->pos_y), 2));
                if(distancia < grafo->raio_comunicacao){
                    lista_vizinhos_adicionar(grafo->dados[i]->id,&grafo->dados[j]->lista_vizinhos);
                }
            }
        }
    }
}

void grafo_imprimir(grafo_t* grafo){
    for(int i=0;i<grafo->tamanho; i++){
        printf("NÓ: %d: ",i);
        lista_vizinhos_imprimir(grafo->dados[i]->lista_vizinhos);
    }
}

grafo_t* grafo_criar(int tamanho, double radio_comunicacao){
	
    grafo_t* novo_grafo = malloc(sizeof(grafo_t));
    if(!novo_grafo){
        perror("Erro ao alocar memória para o grafo");
        exit(1);
    }

    novo_grafo->dados = malloc(sizeof(no_t)*tamanho);
    if(!novo_grafo->dados){
        perror("Erro ao alocar memória para o grafo");
        exit(1);
    }
    novo_grafo->tamanho = tamanho;
    novo_grafo->raio_comunicacao = radio_comunicacao;
    novo_grafo->grafo_atualizar_vizinhos = grafo_atualizar_vizinhos;
    novo_grafo->grafo_imprimir = grafo_imprimir;
	return novo_grafo;
}

int main(int argc, char **argv){
    int tamanho;
    double raio_comunicacao;
    FILE * f = fopen("arquivo_entrada.txt","r");
	if(!f){
        perror("arquivo não encontrado!\n");
        exit(1);
    } 
    fscanf(f,"%d\t%lf\n",&tamanho,&raio_comunicacao);
    grafo_t* grafo = grafo_criar(tamanho,raio_comunicacao);

    int i=0;
	while(!feof(f)){
        no_t* novo_no = malloc(sizeof(no_t));
		if(!novo_no){ 
            perror("erro ao alocar novo nó");
            exit(1);
        }
        novo_no->lista_vizinhos = NULL;
		fscanf(f,"%d\t%lf\t%lf\n",&novo_no->id, &novo_no->pos_x, &novo_no->pos_y);
        grafo->dados[i] = novo_no;
        // printf("%d\t%lf\t%lf\n",novo_no->id, novo_no->pos_x, novo_no->pos_y);
        i++;
	}
    grafo->grafo_atualizar_vizinhos(grafo);
    grafo->grafo_imprimir(grafo);
}