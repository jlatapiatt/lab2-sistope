#ifndef RBOARD_H_
#define RBOARD_H_

#include <ncurses.h>

#define BUFFER_SIZE 255

/* Variables Globales del Tablero */
char** board;
int N;
int M;
int E = 0;

int readFirstLineAux(FILE* file, int* n, int* m, int* z, int* p, int* b){
  if (file == NULL){
    return 0;
  }

  int firstLineFlag = 0;
  char c;
  int i = 0;
  char* buffer = (char*)malloc(sizeof(char)*BUFFER_SIZE);

  while ((c = fgetc(file)) != EOF){
    if (c == ' ' || c == '\n'){
      if (firstLineFlag == 0){
        *n = strtol(buffer, NULL, 10);
      } else if (firstLineFlag == 1){
        *m = strtol(buffer, NULL, 10);
      } else if (firstLineFlag == 2){
        *z = strtol(buffer, NULL, 10);
      } else if (firstLineFlag == 3){
        *p = strtol(buffer, NULL, 10);
      } else if (firstLineFlag == 4){
        *b = strtol(buffer, NULL, 10);
      }
      i = 0;
      buffer[i] = '\0';
      firstLineFlag++;
      if (c == '\n'){
        if (firstLineFlag == 5){
          N = *n;
          M = *m;
          return 1;
        } else {
          return 0;
        }
      }
    } else {
      buffer[i] = c;
      buffer[i+1] = '\0';
      i++;
    }
  }
  return 0;
}

int readFirstLine(FILE* file, int* n, int* m, int* z, int* p, int* b){
  if (readFirstLineAux(file, n, m, z, p, b) == 0){
    printf("Error, la primera linea del archivo de entrada no es correcta\n");
    printf("La forma correcta de correr el programa es: N M Z P B\n");
    printf("N: Ancho del plano\n");
    printf("M: Largo del plano\n");
    printf("Z: Cantidad de zombies que atacaran\n");
    printf("P: Cantidad de personas que defenderan sus vidas\n");
    printf("B: Cuantos zombies puede matar un arma\n");
    return 0;
  }
  return 1;
}

int readRestOfFile(FILE* file, char** board, int n, int m){
  char c;
  int i = 0, j = 0;

  while ((c = fgetc(file)) != EOF){
    if (c == 'X' || c == 'E' || c == '0' || c == 'P' || c == 'G' || c == 'Z'){
      if (c == 'E'){
        E++;
      }
      board[i][j] = c;
      i++;
      if (i == n){
        if (j == m-1){
          return 1;
        }
        i = 0;
        j++;
      }

    } else if (c != ' ' && c != '\n'){
      return 0;
    }
  }
  return 0;
}

int inputErrors(int argc, char *argv[]){
  if (argc < 2) {
    printf("Error, no ingreso un archivo de entrada\n");
    printf("La forma correcta de correr el programa es: ./simulador ARCHIVO_ENTRADA\n");
    return 0;
  } else if (argc == 2){
    return 1;
  } else {
    printf("Error, ha ingresado un exceso de argumentos\n");
    printf("La forma correcta de correr el programa es: ./simulador ARCHIVO_ENTRADA\n");
    return 0;
  }
}

void printBoard(int n, int m, char** board){
  for(int j = 0; j < m; j++){
    printf("\n");
    for(int i = 0; i < n; i++){
      printf("%c",board[i][j]);
    }
  }
  printf("\n\n");
}

void printBoardCurses(int n, int m, char** board){
  for(int j = 0; j < m; j++){
    printw("\n");
    for(int i = 0; i < n; i++){
      printw("%c",board[i][j]);
    }
  }
  printw("\n\n");
}

char** spaceForBoard(int n, int m){
  char *boardAux = (char*)calloc(n*m, sizeof(char));
  char **board = (char**)calloc(n*m, sizeof(char*));
  for (int i = 0; i < n; i++){
    board[i] = boardAux + i*m;
  }
  return board;
}

#endif
