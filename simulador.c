#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "rboard.h"
#include <ncurses.h>

#define BUFFER_SIZE 255

void printBoardCurses(int n, int m, char** board){
  for(int j = 0; j < m; j++){
    printw("\n");
    for(int i = 0; i < n; i++){
      printw("%c",board[i][j]);
    }
  }
  printw("\n\n");
}

int main (int argc, char *argv[]){
  int n,m,z,p,b;
  if (inputErrors(argc, argv) == 0){
    return 1;
  }
  FILE * file = fopen(argv[1], "r");
  if (readFirstLine(file, &n, &m, &z, &p, &b) == 0){
    return 1;
  }
  char **board = spaceForBoard(n,m);

  if (readRestOfFile(file, board, n, m) == 0){
    printf("Error, el tablero esta mal disenado\n");
    return 1;
  }
  //printBoard(n,m,board);

  initscr(); // inicia la pantalla de ncurses
  printBoardCurses(n,m,board); // imprime todo el board en un espacio imaginario
  refresh(); // actualiza la pantalla de ncurses
  getch(); // espera una accion del usuario
  endwin(); // termina el modo ncurses

  return 0;
}
