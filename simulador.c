#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "rboard.h"
//#include <ncurses.h>

#define BUFFER_SIZE 255

int main (int argc, char *argv[]){
  int n,m,z,p,b;
  if (inputErrors(argc, argv) == 0){
    return 0;
  }
  FILE * file = fopen(argv[1], "r");
  if (readFirstLine(file, &n, &m, &z, &p, &b) == 0){
    return 0;
  }
  char **board = spaceForBoard(n,m);

  if (readRestOfFile(file, board, n, m) == 0){
    printf("Error, el tablero esta mal disenado\n");
    return 0;
  }
  printBoard(n,m,board);
  return 1;
}
