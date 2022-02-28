#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

// COMANDO PARA COMPILAR PROGRAMA: gcc *.c -o read_png
// COMANDO PARA EXECUTAR PROGRAMA: ./read_png <nome do arquivo>
//	Aluno: Lucas de Lima Castro MAT: 21551892

struct png_chunk {
    int length;
    char type[4];
} __attribute__ ((packed));

struct chunk_IHDR {
    int width;
    int height;
    char bit_depth;
    char colour_type;
    char compression_method;
    char filter_method;
    char interlace_method;
} __attribute__ ((packed));

int main(int argc, char **argv){

    FILE *png_file = fopen(argv[1], "rb");
    if(!png_file){
        perror("Erro ao abrir arquivo!\n");
        exit(1);
    }

    struct png_chunk * png_chunk = malloc(sizeof(struct png_chunk));
    if(!png_chunk){
        perror("Erro ao alocar memória para o chunk!\n");
        exit(1);
    }
    
    struct chunk_IHDR * chunk_IHDR = malloc(sizeof(struct chunk_IHDR));
    if(!chunk_IHDR){
        perror("Erro ao alocar memória para o chunk IHDR!\n");
        exit(1);
    }

    fseek(png_file,8, SEEK_CUR);
    int i=1;
    while(!feof(png_file)){
        printf("Lendo chunk %d ..\n",i);
        
        fread(png_chunk, sizeof(struct png_chunk), 1, png_file);
        printf("\t--> Tamanho:\t%d\n", ntohl(png_chunk->length));
        printf("\t--> Tipo:\t%s\n",png_chunk->type);
        
        if(strcmp(png_chunk->type,"IHDR") == 0){
            
            fread(chunk_IHDR, sizeof(struct chunk_IHDR), 1, png_file);
            printf("\t\t--> Largura: %d\n",ntohl(chunk_IHDR->width));
            printf("\t\t--> Altura: %d\n",ntohl(chunk_IHDR->height));
            fseek(png_file, 4, SEEK_CUR);
        
        }else if(strcmp(png_chunk->type,"IEND") == 0) break;
        else fseek(png_file, ntohl(png_chunk->length) +4, SEEK_CUR);

        i++;
    }
    free(png_chunk);
    free(chunk_IHDR);
    exit(0);
}   