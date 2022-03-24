#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <netinet/in.h>

// COMANDO PARA COMPILAR PROGRAMA: gcc *.c -o read_tcp_ip
// COMANDO PARA EXECUTAR PROGRAMA: ./read_tcp_ip <nome do arquivo>
//	Aluno: Lucas de Lima Castro MAT: 21551892

typedef struct{
  uint8_t daddr[6];
  uint8_t saddr[6];
  uint16_t protocol;
} ethernet_hdr_t;

typedef struct{
  uint8_t hdr_len : 4, version : 4;
  uint8_t tos;
  uint16_t tot_len;
  uint16_t id;
  uint16_t frag_off;
  uint8_t ttl;
  uint8_t protocol;
  uint16_t check;
  uint8_t saddr[4];
  uint8_t daddr[4];
} ip_hdr_t;

typedef struct {
  uint16_t sport;
  uint16_t dport;
  uint32_t seq;
  uint32_t ack_seq;
  uint8_t reservado:4, hdr_len:4;
  uint8_t flags;
  uint16_t window;
  uint16_t check;
  uint16_t urg_ptr;
} tcp_hdr_t;

void printMAC(char* label, uint8_t* mac){
  printf("%s",label);
  for(int i=0; i< 6; i++){
    printf("%.2x",mac[i]);
    if(i < 5) printf(":");
  }
  printf("\n");
}

void printIP(char* label, uint8_t* ip){
  printf("%s",label);
  for(int i=0; i< 4; i++){
    printf("%d",ip[i]);
    if(i < 3) printf(".");
  }
  printf("\n");
}

int main(int argc, unsigned char **argv){
  FILE* tcp_ip_file = fopen(argv[1],"r");
  if(!tcp_ip_file){
    perror("Arquivo não encontrado!");
    exit(1);
  }
  
  printf("Lendo Ethernet ..\n");
  ethernet_hdr_t* ethernet_data = malloc(sizeof(ethernet_hdr_t));
  if(!ethernet_data){
    perror("Erro ao alocar dados ethernet!");
    exit(1);
  }
  fread(ethernet_data, sizeof(ethernet_hdr_t),1, tcp_ip_file);
  printMAC("\t--> Mac de origem: ",ethernet_data->saddr);
  printMAC("\t--> Mac de destino: ",ethernet_data->daddr);

  printf("Lendo IP ..\n");
  ip_hdr_t* ip_data = malloc(sizeof(ip_hdr_t));
  if(!ip_data){
    perror("Erro ao alocar dados IP!");
    exit(1);
  }
  fread(ip_data, sizeof(ip_hdr_t),1, tcp_ip_file);
  printf("\t--> Versão do IP: %d\n",ip_data->version);
  printf("\t--> Tamanho do cabeçalho: %d bytes\n",ip_data->hdr_len*4);
  printf("\t--> Tamanho do Pacote: %d bytes\n",ntohs(ip_data->tot_len));
  printIP("\t--> Endereço IP de Origem: ",ip_data->saddr);
  printIP("\t--> Endereço IP de Destino: ",ip_data->daddr);
  fseek(tcp_ip_file,ip_data->hdr_len*4 - sizeof(ip_hdr_t),SEEK_CUR);

  printf("Lendo TCP ..\n");
  tcp_hdr_t* tcp_data = malloc(sizeof(tcp_hdr_t));
  if(!tcp_data){
    perror("Erro ao alocar dados TCP!");
    exit(1);
  }
  fread(tcp_data, sizeof(tcp_hdr_t),1, tcp_ip_file);
  printf("\t--> Porta de Origem: %d\n",ntohs(tcp_data->sport));
  printf("\t--> Porta de Destino: %d\n",ntohs(tcp_data->dport));
  printf("\t--> Tamanho do cabeçalho: %d bytes\n",tcp_data->hdr_len*4);
  fseek(tcp_ip_file,tcp_data->hdr_len*4 - sizeof(tcp_hdr_t),SEEK_CUR);

  printf("Lendo Dados (HTTP) ..\n");
  int tam_dados = ntohs(ip_data->tot_len) - (ip_data->hdr_len*4) - (tcp_data->hdr_len*4);
  char* HTML_data =  malloc(sizeof(char)*tam_dados);
  if(!HTML_data){
    perror("Erro ao alocar dados HTTP!");
    exit(1);
  }
  fread(HTML_data, sizeof(char),tam_dados, tcp_ip_file);
  printf("\t--> Tamanho dos dados: %d bytes\n",tam_dados);
  printf("\t--> Dados:\n%s",HTML_data);

  free(ethernet_data);
  free(ip_data);
  free(tcp_data);
  free(HTML_data);
  fclose(tcp_ip_file);
  exit(0);

}