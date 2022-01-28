#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include <stdbool.h>
#include "encadeada.h"

typedef struct tabela_hash_t tabela_hash_t;
typedef bool (*TInsereHash)(pessoa_t *pessoa, tabela_hash_t* tabela_hash);
typedef int (*THash)(pessoa_t *pessoa, tabela_hash_t* tabela_hash);
typedef void (*TImprimeHash)(tabela_hash_t* tabela_hash);

struct tabela_hash_t {
    TEncadeada** hash;
    int tabela_hash_tam;
    THash tabela_hash_pessoas_funcao;
    TInsereHash tabela_hash_pessoas_adicionar;
    TImprimeHash tabela_hash_pessoas_listar;
};

tabela_hash_t* tabela_hash_pessoas_criar(int tamanho);
#endif // HASH_H_INCLUDED