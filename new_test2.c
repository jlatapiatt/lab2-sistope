#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

/*Estructura de datos necesaria para cada hebra persona*/
typedef struct th_people{
    int p_id;	/*Identifica el id del thread*/
    int p_fila;	/*Posicion de la persona*/
    int p_columna;	/*Posicion de la persona*/
    int p_weapon;	/*Arma de la persona*/
}people;

/*Tablero declarado global*/
char** board;

/*Inicializacion del semaforo*/
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/*Definios la funcion de movimiento de los thread*/
/*Para eso se necesita la persona para obtener todos sus datos*/
void move_people(people *persona, char** board){
    /*Comprobamos primeros los 8 casos en orden arriba, abajo, derecha e izquieda*/
    /*Como el movimiento es aleatorio usamos un random de 0-7*/
    int i, j;
    i = persona->p_fila;
    j = persona->p_columna;
    int contador = 0;
    int mov;
    while(contador < 8){
        mov = rand()%8;
        if (mov == 0){
            /*Comprobamos que [i][j-1] arriba*/
            if(board[i][j-1] == '0'){
                persona->p_columna = j-1;
                board[i][j-1] = 'P';
                contador = 8;
            }
            /*si esta ocupada suma al contador*/
            contador = contador + 1;
        }
        if (mov == 1){
            /*Comprobamos que [i][j+1] abajo*/
            if(board[i][j+1] == '0'){
                persona->p_columna = j+1;
                board[i][j+1] = 'P';
                contador = 8;
            }
            /*si esta ocupada suma al contador*/
            contador = contador + 1;
        }
        if (mov == 2){
            /*Comprobamos que [i+1][j] derecha*/
            if(board[i+1][j] == '0'){
                persona->p_fila = i+1;
                board[i+1][j] = 'P';
                contador = 8;
            }
            /*si esta ocupada suma al contador*/
            contador = contador + 1;
        }
        if (mov == 3){
            /*Comprobamos que [i-1][j] izquierda*/
            if(board[i-1][j] == '0'){
                persona->p_fila = i-1;
                board[i-1][j] = 'P';
                contador = 8;
            }
            /*si esta ocupada suma al contador*/
            contador = contador + 1;
        }
        if (mov == 4){
            /*Comprobamos que [i+1][j-1] derecha arriba*/
            if(board[i+1][j-1] == '0'){
                persona->p_fila = i+1;
                persona->p_columna = j-1;
                board[i+1][j-1] = 'P';
                contador = 8;
            }
            /*si esta ocupada suma al contador*/
            contador = contador + 1;
        }
        if (mov == 5){
            /*Comprobamos que [i-1][j-1] izquierda arriba*/
            if(board[i-1][j-1] == '0'){
                persona->p_fila = i-1;
                persona->p_columna = j-1;
                board[i-1][j-1] = 'P';
                contador = 8;
            }
            /*si esta ocupada suma al contador*/
            contador = contador + 1;
        }
        if (mov == 6){
            /*Comprobamos que [i+1][j+1] derecha abajo*/
            if(board[i+1][j+1] == '0'){
                persona->p_fila = i+1;
                persona->p_columna = j+1;
                board[i+1][j+1] = 'P';
                contador = 8;
            }
            /*si esta ocupada suma al contador*/
            contador = contador + 1;
        }
        if (mov == 7){
            /*Comprobamos que [i-1][j+1] izquierda abajo*/
            if(board[i-1][j+1] == '0'){
                persona->p_fila = i-1;
                persona->p_columna = j+1;
                board[i-1][j+1] = 'P';
                contador = 8;
            }
            /*si esta ocupada suma al contador*/
            contador = contador + 1;
        }
    }
    /*Caso de que no s epueda mover, este se queda quieto*/
}

/*Crear personas*/
void *create_people(void *arg){
    /*Definimos a la persona*/
    people *p = (people*) arg;
    pthread_mutex_lock(&mutex);	/*Se bloquea el movimiento*/
    move_people(p, board);
    pthread_mutex_unlock(&mutex);	/*Se desbloquea el movimiento*/
}

/*Funcion que crea a las personas*/
void threads_peoples(int n_people, int N, int M){
    int i;
    /*Reservamos memoria para los thread y el arreglo*/
    pthread_t *threads_peoples = (pthread_t*) malloc(n_people*sizeof(pthread_t));
    people *array_p = (people*)malloc(sizeof(people)*n_people);
    /*Asignamos*/
    for(i=0; i< n_people; i++){
        array_p[i].p_id = i;
        int fila = rand()%N;
        int columna = rand()%M;
        array_p[i].p_fila = fila;
        array_p[i].p_columna = columna;
        array_p[i].p_weapon = 0;
    }
    /*Creamos los threads de las peronas*/
    for (i=0; i < n_people; i++) {
        pthread_create( &(threads_peoples[i]), NULL, create_people, (void*) &(array_p[i]));
    }
    for (i=0; i < n_people; i++){
        pthread_join(threads_peoples[i], NULL);
    }

}
/******************************************************************************/
/*Generar board*/
char** spaceForBoard(int n, int m){
    char *boardAux = (char*)calloc(n*m, sizeof(char));
    char **board = (char**)calloc(n*m, sizeof(char*));
    for (int i = 0; i < n; i++){
      board[i] = boardAux + i*m;
    }
    return board;
}

char** board_created(char** board, int ancho, int largo){
    int i, j;
    for(i=0; i < ancho; i++){
        for(j=0; j < largo; j++){
            board[i][j] = '0';
        }
    }
    return board;
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

/******************************************************************************/


int main (int argc, char *argv[]){
  int n,m,p;
  n = atoi(argv[1]);
  m = atoi(argv[2]);
  p = atoi(argv[3]);

  board = spaceForBoard(n,m);
  board = board_created(board, n, m);
  threads_peoples(p, n, m);
  printBoard(n, m, board);
  exit(0);
}
