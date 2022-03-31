#include <stdio.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <time.h>
#include <stdlib.h>

// COMANDO PARA COMPILAR PROGRAMA: gcc *.c -o segmentos -lm -lGL -lGLU -lglut
// COMANDO PARA EXECUTAR PROGRAMA: ./segmentos <largura da janela> <altura da janela> <numero de segmentos>
// Aluno: Lucas de Lima Castro MAT: 21551892

typedef struct ponto {
  int x;
  int y;
} ponto_t;

typedef struct segmento {
  ponto_t inicio;
  ponto_t fim;
} segmento_t;


int numeroSegmentos, largura, altura, ocupacao=0;
segmento_t** segmentos;

int ccw(ponto_t A, ponto_t B, ponto_t C){
  return ((C.y-A.y)*(B.x-A.x)) > ((B.y-A.y)*(C.x-A.x));
}

int intersect(ponto_t A, ponto_t B, ponto_t C, ponto_t D){
  int result = (ccw(A,C,D) != ccw(B,C,D)) && (ccw(A,B,C) != ccw(A,B,D));
  return result;
}

void pintaSegmentos(segmento_t* segmento){
  glColor3f(0.0, 0.0, 0.0); // Seta a cor do seg. (Red, Green, Blue, entre 0.0 e 1.0)
  glBegin(GL_LINES); // Indica que um segmento será iniciado
  glVertex2f(segmento->inicio.x, segmento->inicio.y); // Seta a posição inicial do segmento (inteiros)
  glVertex2f(segmento->fim.x, segmento->fim.y); // Seta a posição final do segmento (inteiros)
  glEnd(); // Finaliza a criação do segmento
}

int validaSegmento(segmento_t* novoSegmento){
  int result = 0;
  if(ocupacao > 0 && novoSegmento){
    for(int i=0; i< ocupacao && !result; i++){
      segmento_t* segmento_atual = segmentos[i];
      if(intersect(segmento_atual->inicio,segmento_atual->fim,novoSegmento->inicio,novoSegmento->fim) == 1){
        result = 1;
        free(novoSegmento);
      }
    }
  }
  if(result == 0){
    segmentos[ocupacao] = novoSegmento;
    ocupacao+=1;
    pintaSegmentos(novoSegmento);
  }
  return result;
}

segmento_t* geraSegmento(){
  segmento_t* novoSeguimento = malloc(sizeof(segmento_t*));
  if(novoSeguimento){
    novoSeguimento->inicio.x = rand() % largura;
    novoSeguimento->inicio.y = rand() % altura;
    novoSeguimento->fim.x = rand() % largura;
    novoSeguimento->fim.y = rand() % altura;
  }
  // printf("[%d,%d,%d,%d]\n",novoSeguimento->inicio.x,novoSeguimento->inicio.y,novoSeguimento->fim.x,novoSeguimento->fim.y);
  return novoSeguimento;
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  while(ocupacao < numeroSegmentos){
    segmento_t* novoSegmento = geraSegmento();
    validaSegmento(novoSegmento);
  }

  glFlush();
}

int main(int argc, char **argv){

  srand(time(NULL));

  largura = atoi(argv[1]);
  altura = atoi(argv[2]);
  numeroSegmentos = atoi(argv[3]);

  segmentos = malloc(sizeof(segmento_t)*numeroSegmentos);
  if(!segmentos){
    perror("Erro ao criar vetor de segmentos");
    exit(1);
  }

  glutInit(&argc, argv);
  glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  // Cria uma janela de tamanho “largura” x “altura”
  glutInitWindowSize(largura, altura);
  glutCreateWindow ("Segmentos Aleatorios");
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, largura, 0.0, altura, -1.0, 1.0);
  // Seta a cor do fundo da janela
  glClearColor(1.0, 1.0, 1.0, 1.0);
  // Seta a função “display” como sendo a função que irá pintar a janela (infinitamente)
  glutDisplayFunc(display);
  glutMainLoop();


  free(segmentos);
  exit(0);
}