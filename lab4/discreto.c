#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "discreto.h"

// COMANDO PARA COMPILAR PROGRAMA: gcc *.c *.h -o discreto -lm
// COMANDO PARA EXECUTAR PROGRAMA: ./discreto <nome do arquivo>
//	Aluno: Lucas de Lima Castro MAT: 21551892

static bool lista_eventos_adicionar_ordenado(evento_t *evento, lista_eventos_t **lista){
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

static void grafo_atualizar_vizinhos(grafo_t* grafo){
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
        i++;
	}
    grafo->grafo_atualizar_vizinhos(grafo);

    lista_eventos_t** eventos = malloc(sizeof(lista_vizinhos_t*));
    if(!eventos){
        perror("Erro ao alocar memória para lista de eventos!\n");
        exit(1);
    } 
    evento_t* evento_zero = malloc(sizeof(evento_t));
    if(!evento_zero){
        perror("Erro ao alocar memória para evento zero!\n");
        exit(1);
    } 
    evento_zero->alvo = 0;
    evento_zero->tempo = 1.0;
    evento_zero->tipo = 1;
    lista_eventos_adicionar_ordenado(evento_zero,eventos);

    while(*eventos){
        lista_eventos_t* evento_atual = *eventos;
        *eventos = evento_atual->proximo;
        printf("[%3.6f] Nó %d recebeu pacote.\n",evento_atual->evento->tempo,evento_atual->evento->alvo);
        if(!grafo->dados[evento_atual->evento->alvo]->pacote_enviado){
            lista_vizinhos_t* vizinho = grafo->dados[evento_atual->evento->alvo]->lista_vizinhos;
            while(vizinho){
                evento_t* novo_evento = malloc(sizeof(evento_t));
                if(!novo_evento){
                    perror("Erro ao alocar memória para novo evento!\n");
                    exit(1);
                }
                novo_evento->alvo = vizinho->id;
                novo_evento->tempo = evento_atual->evento->tempo + (0.1 + (vizinho->id * 0.01));
                novo_evento->tipo = 1;
                lista_eventos_adicionar_ordenado(novo_evento, eventos);
                printf("\t--> Repassando pacote para o nó %d ...\n", vizinho->id);
                vizinho = vizinho->proximo;
            }
            grafo->dados[evento_atual->evento->alvo]->pacote_enviado = true;
        }
    }

}