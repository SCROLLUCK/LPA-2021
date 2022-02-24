#include <stdio.h>
#include <stdlib.h>

// COMANDO PARA COMPILAR PROGRAMA: gcc *.c -o read_zip
// COMANDO PARA EXECUTAR PROGRAMA: ./read_zip <nome do arquivo zip>
//	Aluno: Lucas de Lima Castro MAT: 21551892

struct zip_file_hdr {
    int signature;
    short version;
    short flags;
    short compression;
    short mod_time;
    short mod_date;
    int crc;
    int compressed_size;
    int uncompressed_size;
    short name_length;
    short extra_field_length;
} __attribute__ ((packed));

int main(int argc, char **argv){

    FILE *zip_file = fopen(argv[1], "rb");
    if(!zip_file){
        perror("Erro ao abrir arquivo!\n");
        exit(1);
    }
    struct zip_file_hdr *file_hdr = malloc(sizeof(struct zip_file_hdr));
    if(!file_hdr){
        perror("Erro ao alocar memoria para o arquivo!\n");
        exit(1);
    }
    int i=1;
    while(!feof(zip_file)){
        fread(file_hdr, sizeof(struct zip_file_hdr), 1, zip_file);
        if(file_hdr->signature == 0x04034b50){
            printf("Arquivo %d ..\n",i);
            char* name_file = malloc(sizeof(char)*(file_hdr->name_length+1));
            if(!name_file){
                perror("Erro ao alocar memoria para o nome do arquivo!\n");
                exit(1);
            }
            fread(name_file,sizeof(char)*(file_hdr->name_length),1,zip_file);
            name_file[file_hdr->name_length+1] = '\0';
            printf(" --> Nome do Arquivo: %s\n",name_file);
            printf(" --> Tamanho Compactado: %d\n",file_hdr->compressed_size);
            printf(" --> Tamanho Descompactado: %d\n",file_hdr->uncompressed_size);
        }
        fseek(zip_file, file_hdr->extra_field_length + file_hdr->compressed_size, SEEK_CUR);
        i++;
    }   
}   