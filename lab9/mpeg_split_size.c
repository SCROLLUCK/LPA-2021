#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEGA_BYTE_IN_BYTES 1048576

// COMANDO PARA COMPILAR PROGRAMA: gcc *.c -o mpeg_split_size
// COMANDO PARA EXECUTAR PROGRAMA: ./mpeg_split_size <nome do arquivo> <numero de bytes desejado>
//	Aluno: Lucas de Lima Castro MAT: 21551892

int main(int argc, unsigned char **argv){

    int video_part = 1;
    FILE* mpeg_file = fopen(argv[1], "rb");
    if(!mpeg_file){
        perror("Erro ao abrir arquivo!\n");
        exit(1);
    }

    char* code_prefix = malloc(sizeof(char)*4);
    if(!code_prefix){
        perror("Erro ao alocar memória para o code_prefix!\n");
        exit(1);
    }

    int buffer_size = atoi(argv[2])*MEGA_BYTE_IN_BYTES;
    unsigned char* buffer_sequence = calloc(buffer_size+1,sizeof(char));

    char name_file[50] = {0};
    sprintf(name_file,"video_parte_%d.mpg", video_part);
    FILE *video_part_file = fopen(name_file, "wb");

    size_t buffer_ocupation = 0, file_size = 0;

    printf("Criando arquivo video_part_%d.pmg ..\n",video_part);
    
    while(fread(code_prefix, sizeof(char), 4, mpeg_file) >= 4){
        
        if(!(memcmp(code_prefix,"\x00\x00\x01\xb3", 4) == 0)){

            buffer_sequence[buffer_ocupation++] = code_prefix[0];
            fseek(mpeg_file, -3, SEEK_CUR);
        
        }else{

            memcpy(&buffer_sequence[buffer_ocupation], code_prefix, 4);
            buffer_ocupation += 4;
            
            if((file_size + buffer_ocupation) > buffer_size){

                fclose(video_part_file);
                sprintf(name_file,"video_parte_%d.mpg", ++video_part);
                video_part_file = fopen(name_file,"wb");
                fwrite(buffer_sequence, sizeof(char), buffer_ocupation, video_part_file);
                file_size = buffer_ocupation;
                buffer_ocupation = 0;
                printf("Criando arquivo video_part_%d.pmg ..\n",video_part);

            }else{
                
                fwrite(buffer_sequence, sizeof(char), buffer_ocupation, video_part_file);
                file_size += buffer_ocupation; 
                buffer_ocupation = 0;
                
            }
        }
    }

    free(code_prefix);
    fclose(mpeg_file);
    system("ls -lh");
    exit(0);

}