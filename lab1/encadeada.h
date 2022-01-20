#ifndef ENCADEADA_H_INCLUDED
#define ENCADEADA_H_INCLUDED

#include <stdbool.h>
typedef struct encadeada TEncadeada;
typedef struct evento_t evento_t;
typedef struct lista_eventos_t lista_eventos_t;
typedef bool (*TInsere)(evento_t *evento, lista_eventos_t **lista);
typedef void (*TImprime)(lista_eventos_t *lista);

struct evento_t {
	double tempo;
	int alvo;
	int tipo;
};
struct lista_eventos_t {
	evento_t * evento;
	lista_eventos_t *proximo;
};

struct encadeada{
    lista_eventos_t** lista;
    TInsere lista_eventos_adicionar_inicio;
    TInsere lista_eventos_adicionar_fim;
    TInsere lista_eventos_adicionar_ordenado;
    TImprime lista_eventos_listar;
};

TEncadeada* CriarLista();
#endif // ENCADEADA_H_INCLUDED