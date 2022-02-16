#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// COMANDO PARA COMPILAR PROGRAMA: gcc *.c -o dicionario
// COMANDO PARA EXECUTAR PROGRAMA: ./dicionario <tamanho desejado> <alfabeto disponível>
//	Aluno: Lucas de Lima Castro MAT: 21551892

char* concat(char* str, char c){
    size_t len = strlen(str);
    char *str2 = malloc(len + 1 + 1);
    strcpy(str2, str);
    str2[len] = c;
    str2[len + 1] = '\0';
    return str2;
}

void GenerateAllPasswords(char *alfa, char* pwd, int pos, int siz){
    if(pos < strlen(alfa)){
       for(int i=0; i<strlen(alfa); i++){
           GenerateAllPasswords(alfa,concat(pwd,alfa[i]), pos + 1, siz);
       }
    }
    if(strlen(pwd) < siz+1 && strlen(pwd) > 0) printf("%s\n",pwd);
}


int main(int argc, char **argv) {
    char* pwd = "";
    GenerateAllPasswords(argv[2],pwd,0,atoi(argv[1]));
}

