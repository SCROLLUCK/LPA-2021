#include <stdbool.h>
#ifndef ENCADEADA_H_INCLUDED
#define ENCADEADA_H_INCLUDED

typedef struct encadeada TEncadeada;
typedef struct pessoa_t pessoa_t;
typedef struct lista_pessoas_t lista_pessoas_t;
typedef bool (*TInsere)(pessoa_t *pessoa, lista_pessoas_t **lista);
typedef void (*TImprime)(lista_pessoas_t *lista);

struct pessoa_t {
	char nome[50];
	long long int cpf;
	int idade;
};

struct lista_pessoas_t {
	pessoa_t * pessoa;
	lista_pessoas_t *proximo;
};

struct encadeada{
    lista_pessoas_t** lista;
    TInsere lista_pessoas_adicionar;
    TImprime lista_pessoas_listar;
};

TEncadeada* CriarLista();
#endif // ENCADEADA_H_INCLUDED