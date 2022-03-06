#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

// COMANDO PARA COMPILAR PROGRAMA: gcc *.c -o read_mpeg
// COMANDO PARA EXECUTAR PROGRAMA: ./read_mpeg <nome do arquivo>
//	Aluno: Lucas de Lima Castro MAT: 21551892

int main(int argc, unsigned char **argv){

    unsigned char type;
    unsigned char byte1;
    unsigned char byte2;
    unsigned char byte3;
    unsigned char byte4;
    char* frame_rates[8] = {"23.976","24.000","25.000","29.970","30.000","50.000","59.940","60.000"};
    char* picture_types[3] = {"I","P","B"};

    FILE *mpeg_file = fopen(argv[1], "rb");
    if(!mpeg_file){
        perror("Erro ao abrir arquivo!\n");
        exit(1);
    }

    char * start_code = malloc(sizeof(char)*3);
    if(!start_code){
        perror("Erro ao alocar memória para o start_code!\n");
        exit(1);
    }
    
    while(!feof(mpeg_file)){
        fread(start_code, sizeof(char)*3, 1, mpeg_file);
        if(memcmp(start_code,"\x00\x00\x01", 3) == 0) {
            type = fgetc(mpeg_file);
            printf("--> Código: %.2x -- ",type);
            switch(type){
                case 0xba:
                    printf("Pack\n");
                    break;
                case 0xbb:
                    printf("System\n");
                    break;
                case 0xb3:
                    byte1 = fgetc(mpeg_file);
                    byte2 = fgetc(mpeg_file);
                    byte3 = fgetc(mpeg_file);
                    byte4 = fgetc(mpeg_file);
                    unsigned int largura = byte1 * 16 + (byte2 >> 4);
                    unsigned int altura = ( byte2 & 0x0F) * 256 + byte3;
                    unsigned int frame_rate = byte4 & 0x0f;
                    printf("Sequence Header -- Width = %d, Height = %d -- Frame rate = %sfps\n",largura,altura,frame_rates[frame_rate-1]);
                    break;
                case 0xb8:
                    printf("Group of Pictures\n");
                    break;
                case 0x00:
                    byte1 = fgetc(mpeg_file);
                    byte2 = fgetc(mpeg_file);
                    unsigned int picture_type = (byte2 >> 3) & 0x07;
                    printf("Picture -- Tipo = %s\n",picture_types[picture_type-1]);
                    break;
                default:
                    if(0x01 >= type && type <= 0xaf) printf("Slide\n");
                    else if(0xc0 >= type && type <= 0xdf) printf("Packet Video\n");
                    else if (0xe0 >= type && type <= 0xef) printf("Packet Audio\n");
                    else printf("Tipo de stream não implementado\n");
                    break;
            }
        }else {
            fseek(mpeg_file, -2, SEEK_CUR);
        }
    }
    free(start_code);
    fclose(mpeg_file);
    exit(0);
}