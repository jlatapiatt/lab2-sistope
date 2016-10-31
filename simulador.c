#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "rboard.h"
#include "Threads.h"

#define BUFFER_SIZE 255


int main (int argc, char *argv[]){
  int n,m,z,p,b;
  if (inputErrors(argc, argv) == 0){
    return 1;
  }
  FILE * file = fopen(argv[1], "r");
  if (readFirstLine(file, &n, &m, &z, &p, &b) == 0){
    return 1;
  }

  board = spaceForBoard(n,m);

  if (readRestOfFile(file, board, n, m) == 0){
    printf("Error, el tablero esta mal disenado\n");
    return 1;
  }
  //printBoard(n,m,board);

  initscr(); // inicia la pantalla de ncurses
  threads_people(p);
  threads_zombies(z);
  printBoardCurses(n,m,board); // imprime todo el board en un espacio imaginario
  refresh(); // actualiza la pantalla de ncurses
  int boardClock = 0;
  while (1) {
    //podria haber un mutex...
    erase();
    printBoardCurses(N,M,board);
    printw("\n\n");
    printw("\tTiempo: %d:%d\n", boardClock/60, boardClock%60);
    printw("\tPersonas: %d\n", P_alive);
    printw("\tZombies: %d\n", Z_alive);
    refresh();
    boardClock++;
    if (P_alive == 0 || (Z_alive > 0 && P_alive == 0)){
      getch(); // espera una accion del usuario
      endwin();
    }
    id_barrier1 = pthread_barrier_init(&barrier, NULL, E);
    /*Si no han llegado todos descansa 3 segundos*/
    if(id_barrier1 == 0){
        sleep(2);
    }
  }


  return 0;
}
