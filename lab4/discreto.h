#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <stdbool.h>


// LISTA TIPOS
typedef struct evento_t evento_t;
typedef struct lista_eventos_t lista_eventos_t;

struct evento_t {
	double tempo;
	int alvo;
	int tipo;
};
struct lista_eventos_t {
	evento_t * evento;
	lista_eventos_t *proximo;
};

// GRAFO TIPOS
typedef struct grafo_t grafo_t;
typedef struct no_t no_t;
typedef struct lista_vizinhos_t lista_vizinhos_t;
typedef void (*TAtualiza)(grafo_t* grafo);
typedef void (*TImprime)(grafo_t* grafo);

struct no_t{
    int id;
    double pos_x;
    double pos_y;
    bool pacote_enviado;
    lista_vizinhos_t* lista_vizinhos;
};

struct lista_vizinhos_t {
	int id;
	lista_vizinhos_t *proximo;
};

struct grafo_t{
    no_t** dados;
    int tamanho;
    double raio_comunicacao;
    TImprime grafo_imprimir;
    TAtualiza grafo_atualizar_vizinhos;
};

grafo_t* grafo_criar(int tamanho, double raio_comunicacao);
#endif // GRAFO_H_INCLUDED