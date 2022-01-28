#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "encadeada.h"
#include <syscall.h>

// COMANDO PARA COMPILAR PROGRAMA: gcc *.c *.h -o teste
// COMANDO PARA EXECUTAR PROGRAMA: ./teste <tamanho da hash> <nome do arquivo>
//	Aluno: Lucas de Lima Castro MAT: 21551892

int main(int argc, char **argv){

    int tamanho_hash = atoi(argv[1]);
    char* nome_arquivo = argv[2];

    printf("Questao 1: \n");
    printf("Tamanho hash: %d\n",tamanho_hash);
    printf("Nome do arquivo: %s\n\n",nome_arquivo);

    tabela_hash_t* hash = tabela_hash_pessoas_criar(tamanho_hash);

    FILE* f = fopen(nome_arquivo, "r");
    if(!f){
        perror("Arquivo não encontrado!");
        exit(1);
    }

    while(!feof(f)){
        pessoa_t* pessoa = malloc(sizeof(pessoa_t));
        if(!pessoa) {
            perror("Erro ao alocar memória para uma nova pessoa!");
            exit(1);
        }
        fscanf(f, "%50[^\t]\t%lld\t%d\n",(char*) &pessoa->nome, &pessoa->cpf, &pessoa->idade);
        hash->tabela_hash_pessoas_adicionar(pessoa,hash);
        // printf("- %s\t%lld\t%d\n",pessoa->nome, pessoa->cpf, pessoa->idade);
    }

    hash->tabela_hash_pessoas_listar(hash);

}