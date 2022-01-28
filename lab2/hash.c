#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "encadeada.h"
#include <syscall.h>

static int tabela_hash_pessoas_funcao(pessoa_t *pessoa,tabela_hash_t* tabela_hash){
    return pessoa->cpf%tabela_hash->tabela_hash_tam;
}
bool tabela_hash_pessoas_adicionar(pessoa_t *pessoa, tabela_hash_t* tabela_hash){
    int chave = tabela_hash_pessoas_funcao(pessoa,tabela_hash);
    TEncadeada* encadeada = (TEncadeada*) tabela_hash->hash[chave];
    return encadeada->lista_pessoas_adicionar(pessoa, encadeada->lista);
}
void tabela_hash_pessoas_listar(tabela_hash_t* tabela_hash){
    for(int i = 0; i < tabela_hash->tabela_hash_tam; i++){
        printf("POSIÇÃO %d DA TABELA HASH:\n",i);
        TEncadeada* encadeada = (TEncadeada*) tabela_hash->hash[i];
        encadeada->lista_pessoas_listar(*encadeada->lista);
    }
}

tabela_hash_t* tabela_hash_pessoas_criar(int tamanho){
    tabela_hash_t* nova_hash = malloc(sizeof(tabela_hash_t));
    if(!nova_hash){
        perror("Erro ao alocar memória para a Hash\n");
        exit(1);
    }

    nova_hash->hash = malloc(sizeof(TEncadeada)*tamanho);
    if(!nova_hash->hash){
        perror("Erro ao alocar memória para a Hash\n");
        exit(1);
    }
    nova_hash->tabela_hash_tam = tamanho;
    for(int i =0; i < nova_hash->tabela_hash_tam; i++){
        nova_hash->hash[i] = CriarLista();
    }
    
    nova_hash->tabela_hash_pessoas_funcao = tabela_hash_pessoas_funcao;
    nova_hash->tabela_hash_pessoas_adicionar = tabela_hash_pessoas_adicionar;
    nova_hash->tabela_hash_pessoas_listar = tabela_hash_pessoas_listar;

    return nova_hash;
}