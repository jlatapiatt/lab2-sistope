/*#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>*/
#ifndef THREADS_H_
#define THREADS_H_


/*Estructura de datos necesaria para cada hebra persona*/
typedef struct people{
    int p_id;	/*Identifica el id del thread*/
    int p_fila;	/*Posicion de la persona*/
    int p_columna;	/*Posicion de la persona*/
    int p_weapon;	/*Arma de la persona*/
    int p_bitten;
}people;

/*Estructura de datos necesaria para cada hebra persona*/
typedef struct zombie{
    int z_id;	/*Identifica el id del thread*/
    int z_fila;	/*Posicion del zombie*/
    int z_columna;	/*Posicion del zombie*/
}zombie;

/* Variable global */
int N_spawned = 0;
people *array_p;
//ARRAY DE HUMANOS

/*Inicializacion del semaforo*/
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/*Definios la funcion de movimiento de los thread*/
/*Para eso se necesita la persona para obtener todos sus datos*/

void movePerson(people *persona){
  /*Comprobamos primeros los 8 casos en orden arriba, abajo, derecha e izquieda*/
  /*Como el movimiento es aleatorio usamos un random de 0-7*/
  int i, j;
  i = persona->p_fila;
  j = persona->p_columna;
  int contador = 0;
  int mov = rand()%8;
  while(contador < 8){
      if (mov == 0){
          /*Comprobamos que [i][j-1] arriba*/
          if(j > 0) {
            if (board[i][j-1] == '0'){
                persona->p_columna = j-1;
                board[i][j-1] = 'P';
                board[i][j] = '0';
                contador = 8;
            } else if (board[i][j-1] == 'G'){
                persona->p_columna = j-1;
                board[i][j-1] = 'P';
                board[i][j] = '0';
                persona->p_weapon = B;
                contador = 8;
            }
          }
          /*si esta ocupada suma al contador*/
          contador = contador + 1;
      }
      if (mov == 1){
          /*Comprobamos que [i][j+1] abajo*/
          if(j < M-1){
            if(board[i][j+1] == '0'){
              persona->p_columna = j+1;
              board[i][j+1] = 'P';
              board[i][j] = '0';
              contador = 8;
            } else if (board[i][j+1] == 'G'){
              persona->p_columna = j+1;
              board[i][j+1] = 'P';
              board[i][j] = '0';
              persona->p_weapon = B;
              contador = 8;
          }
        }
          /*si esta ocupada suma al contador*/
          contador = contador + 1;
      }
      if (mov == 2){
          /*Comprobamos que [i+1][j] derecha*/
          if(i < N-1) {
            if (board[i+1][j] == '0'){
              persona->p_fila = i+1;
              board[i+1][j] = 'P';
              board[i][j] = '0';
              contador = 8;
            } else if (board[i+1][j] == 'G'){
              persona->p_fila = i+1;
              board[i+1][j] = 'P';
              board[i][j] = '0';
              persona->p_weapon = B;
              contador = 8;
            }
          }
          /*si esta ocupada suma al contador*/
          contador = contador + 1;
      }
      if (mov == 3){
          /*Comprobamos que [i-1][j] izquierda*/
          if(i > 0) {
            if (board[i-1][j] == '0'){
              persona->p_fila = i-1;
              board[i-1][j] = 'P';
              board[i][j] = '0';
              contador = 8;
            } else if (board[i-1][j] == 'G'){
              persona->p_fila = i-1;
              board[i-1][j] = 'P';
              board[i][j] = '0';
              persona->p_weapon = B;
              contador = 8;
          }
        }
          /*si esta ocupada suma al contador*/
          contador = contador + 1;
      }
      if (mov == 4){
          /*Comprobamos que [i+1][j-1] derecha arriba*/
          if(i < N-1 && j > 0) {
            if (board[i+1][j-1] == '0'){
              persona->p_fila = i+1;
              persona->p_columna = j-1;
              board[i+1][j-1] = 'P';
              board[i][j] = '0';
              contador = 8;
            } else if (board[i+1][j-1] == 'g'){
              persona->p_fila = i+1;
              persona->p_columna = j-1;
              board[i+1][j-1] = 'P';
              board[i][j] = '0';
              persona->p_weapon = B;
              contador = 8;
          }
        }
          /*si esta ocupada suma al contador*/
          contador = contador + 1;
      }
      if (mov == 5){
          /*Comprobamos que [i-1][j-1] izquierda arriba*/
          if(i > 0 && j > 0) {
            if (board[i-1][j-1] == '0'){
              persona->p_fila = i-1;
              persona->p_columna = j-1;
              board[i-1][j-1] = 'P';
              board[i][j] = '0';
              contador = 8;
            } else if (board[i-1][j-1] == 'G'){
              persona->p_fila = i-1;
              persona->p_columna = j-1;
              board[i-1][j-1] = 'P';
              board[i][j] = '0';
              persona->p_weapon = B;
              contador = 8;
            }
          }
          /*si esta ocupada suma al contador*/
          contador = contador + 1;
      }
      if (mov == 6){
          /*Comprobamos que [i+1][j+1] derecha abajo*/
          if(i < N-1 && j < M-1) {
            if (board[i+1][j+1] == '0'){
              persona->p_fila = i+1;
              persona->p_columna = j+1;
              board[i+1][j+1] = 'P';
              board[i][j] = '0';
              contador = 8;
            } else if (board[i+1][j+1] == 'G'){
              persona->p_fila = i+1;
              persona->p_columna = j+1;
              board[i+1][j+1] = 'P';
              board[i][j] = '0';
              persona->p_weapon = B;
              contador = 8;
            }
          }
          /*si esta ocupada suma al contador*/
          contador = contador + 1;
      }
      if (mov == 7){
          /*Comprobamos que [i-1][j+1] izquierda abajo*/
          if(i > 0 && j < M-1) {
            if (board[i-1][j+1] == '0'){
              persona->p_fila = i-1;
              persona->p_columna = j+1;
              board[i-1][j+1] = 'P';
              board[i][j] = '0';
              contador = 8;
            } else if (board[i-1][j+1] == 'G'){
              persona->p_fila = i-1;
              persona->p_columna = j+1;
              board[i-1][j+1] = 'P';
              board[i][j] = '0';
              persona->p_weapon = B;
              contador = 8;
            }
          }
          /*si esta ocupada suma al contador*/
          contador = contador + 1;
      }
      mov = (mov+1)%8;
  }
  /*Caso de que no s epueda mover, este se queda quieto*/
}

void moveZombie(zombie *zomb){
  /*Comprobamos primeros los 8 casos en orden arriba, abajo, derecha e izquieda*/
  /*Como el movimiento es aleatorio usamos un random de 0-7*/
  int i, j;
  i = zomb->z_fila;
  j = zomb->z_columna;
  int contador = 0;
  int mov = rand()%8;
  while(contador < 8){
      if (mov == 0){
          /*Comprobamos que [i][j-1] arriba*/
          if(j > 0) {
            if (board[i][j-1] == '0' || board[i][j-1] == 'G'){
                zomb->z_columna = j-1;
                board[i][j-1] = 'Z';
                board[i][j] = '0';
                contador = 8;
            }
          }
          /*si esta ocupada suma al contador*/
          contador = contador + 1;
      }
      if (mov == 1){
          /*Comprobamos que [i][j+1] abajo*/
          if(j < M-1){
            if(board[i][j+1] == '0' || board[i][j+1] == 'G'){
              zomb->z_columna = j+1;
              board[i][j+1] = 'Z';
              board[i][j] = '0';
              contador = 8;
            }
        }
          /*si esta ocupada suma al contador*/
          contador = contador + 1;
      }
      if (mov == 2){
          /*Comprobamos que [i+1][j] derecha*/
          if(i < N-1) {
            if (board[i+1][j] == '0' || board[i+1][j] == 'G'){
              zomb->z_fila = i+1;
              board[i+1][j] = 'Z';
              board[i][j] = '0';
              contador = 8;
            }
          }
          /*si esta ocupada suma al contador*/
          contador = contador + 1;
      }
      if (mov == 3){
          /*Comprobamos que [i-1][j] izquierda*/
          if(i > 0) {
            if (board[i-1][j] == '0' || board[i-1][j] == 'G'){
              zomb->z_fila = i-1;
              board[i-1][j] = 'Z';
              board[i][j] = '0';
              contador = 8;
            }
        }
          /*si esta ocupada suma al contador*/
          contador = contador + 1;
      }
      if (mov == 4){
          /*Comprobamos que [i+1][j-1] derecha arriba*/
          if(i < N-1 && j > 0) {
            if (board[i+1][j-1] == '0' || board[i+1][j-1] == 'G'){
              zomb->z_fila = i+1;
              zomb->z_columna = j-1;
              board[i+1][j-1] = 'Z';
              board[i][j] = '0';
              contador = 8;
            }
        }
          /*si esta ocupada suma al contador*/
          contador = contador + 1;
      }
      if (mov == 5){
          /*Comprobamos que [i-1][j-1] izquierda arriba*/
          if(i > 0 && j > 0) {
            if (board[i-1][j-1] == '0' || board[i-1][j-1] == 'G'){
              zomb->z_fila = i-1;
              zomb->z_columna = j-1;
              board[i-1][j-1] = 'Z';
              board[i][j] = '0';
              contador = 8;
            }
          }
          /*si esta ocupada suma al contador*/
          contador = contador + 1;
      }
      if (mov == 6){
          /*Comprobamos que [i+1][j+1] derecha abajo*/
          if(i < N-1 && j < M-1) {
            if (board[i+1][j+1] == '0' || board[i+1][j+1] == 'G'){
              zomb->z_fila = i+1;
              zomb->z_columna = j+1;
              board[i+1][j+1] = 'Z';
              board[i][j] = '0';
              contador = 8;
            }
          }
          /*si esta ocupada suma al contador*/
          contador = contador + 1;
      }
      if (mov == 7){
          /*Comprobamos que [i-1][j+1] izquierda abajo*/
          if(i > 0 && j < M-1) {
            if (board[i-1][j+1] == '0' || board[i-1][j+1] == 'G'){
              zomb->z_fila = i-1;
              zomb->z_columna = j+1;
              board[i-1][j+1] = 'Z';
              board[i][j] = '0';
              contador = 8;
            }
          }
          /*si esta ocupada suma al contador*/
          contador = contador + 1;
      }
      mov = (mov+1)%8;
  }
  /*Caso de que no s epueda mover, este se queda quieto*/
}
/*Entradas Zombie*/
void startZombie(zombie *zomb){
    int i, j;
    for(i=0; i < N; i++){
        for(j=0; j < M; j++){
            if(board[i][j] == 'E'){
                zomb->z_fila = i;
                zomb->z_columna = j;
                board[i][j] = 'Z';
                break;
            }
        }
    }
}

/*Resolvemos la batalla*/
/*Esta funcion sera cuando se encuentren*/
int battle(people *p, zombie *z){
  return 0;
}

int amIDead(people* person){
  int i = person->p_fila;
  int j = person->p_columna;
  if (person->p_bitten == 0){
    //CREAR UN ZOMBIE
    P_alive--;
    pthread_exit(NULL);
  } else if (person->p_bitten > 0){
    person->p_bitten = person->p_bitten - 1;
  } else if (person->p_weapon == 0){
    if (j > 0){
      if (board[i][j-1] == 'Z'){
        //MATATE en 3 segundos;
        person->p_bitten = 3;
        return 1;
      } else if (i < N-1 && board[i+1][j-1] == 'Z'){
        //MATATE en 3 segundos;
        person->p_bitten = 3;
        return 1;
      }else if (i > 0 && board[i-1][j-1] == 'Z'){
        //MATATE en 3 segundos;
        person->p_bitten = 3;
        return 1;
      }
    }
    if (j < M-1){
      if (board[i][j+1] == 'Z'){
        //MATATE en 3 segundos;
        person->p_bitten = 3;
        return 1;
      } else if (i < N-1 && board[i+1][j+1] == 'Z'){
        //MATATE en 3 segundos;
        person->p_bitten = 3;
        return 1;
      }else if (i > 0 && board[i-1][j+1] == 'Z'){
        //MATATE en 3 segundos;
        person->p_bitten = 3;
        return 1;
      }
      if (i > 0 && board[i-1][j] == 'Z'){
        //MATATE en 3 segundos;
        person->p_bitten = 3;
        return 1;
      }
      if (i < N-1 && board[i+1][j] == 'Z'){
        //MATATE en 3 segundos;
        person->p_bitten = 3;
        return 1;
      }
    }

  }
  return 0;
}

int didIDiededed(zombie* zomb){
  int i = zomb->z_fila;
  int j = zomb->z_columna;
  int w,v;
  for (int k = 0; k < P; k++){
    if (array_p[k].p_bitten == -1 && array_p[k].p_weapon > 0){
      w = array_p[k].p_fila;
      v = array_p[k].p_columna;
      if (i-1 == w && j == k){
        array_p[k].p_weapon = array_p[k].p_weapon - 1;
        return 1;
      } else if (i+1 == w && j == k){
        array_p[k].p_weapon = array_p[k].p_weapon - 1;
        return 1;
      } else if (i-1 == w && j == k-1){
        array_p[k].p_weapon = array_p[k].p_weapon - 1;
        return 1;
      } else if (i-1 == w && j == k+1){
        array_p[k].p_weapon = array_p[k].p_weapon - 1;
        return 1;
      } else if (i+1 == w && j == k-1){
        array_p[k].p_weapon = array_p[k].p_weapon - 1;
        return 1;
      } else if (i+1 == w && j == k+1){
        array_p[k].p_weapon = array_p[k].p_weapon - 1;
        return 1;
      }
      else if (i == w && j == k-1){
        array_p[k].p_weapon = array_p[k].p_weapon - 1;
        return 1;
      }
      else if (i == w && j == k+1){
        array_p[k].p_weapon = array_p[k].p_weapon - 1;
        return 1;
      }
    }
  }
  return 0;
}

/*Creamos las funciones para las dos hebras*/
void *create_people(void *arg){
    /*Definimos a la persona*/
    people *p = (people*) arg;
    while (1) {
      pthread_mutex_lock(&mutex);	//Se bloquea el movimiento
      if (p->p_bitten == -1){
        movePerson(p);
      }
      pthread_mutex_unlock(&mutex);	//Se desbloquea el movimiento
      //printBoard(N,M,board);
      //BARRERAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA 1
      id_barrier1 = pthread_barrier_init(&barrier, NULL, E);
      /*Si no han llegado todos descansa 3 segundos*/
      if(id_barrier1 == 0){ //NO DEBERIA SER WHILE?
          sleep(1);
      }
      amIDead(p);
      //Comprobacion de muerte
      //BARRERAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA 2
    }
}

void *create_zombie(void *arg){
    /*Definimos a la persona*/
    zombie *z = (zombie*) arg;
    while (1) {
        startZombie(z);
        pthread_mutex_lock(&mutex);	//Se bloquea el movimiento
        moveZombie(z);
        pthread_mutex_unlock(&mutex);	//Se desbloquea el movimiento
        if (didIDiededed(z) == 1){
          Z_alive--;
          pthread_exit(NULL);
        }
        //getch();
        //printBoard(N,M,board);
    }
      //BARRERAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA 1
      //Comprobacion de muerte
      //BARRERAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA 2
}

/*Funcion que crea todas las personas*/
void threads_people(int n_people){
    int i;
    /*Reservamos memoria para los thread y el arreglo*/
    pthread_t *threads_people = (pthread_t*) malloc(n_people*sizeof(pthread_t));
    array_p = (people*)malloc(sizeof(people)*n_people);
    /*Asignamos*/
    for(i=0; i< n_people; i++){
      array_p[i].p_id = i;
      int fila = rand()%N;
      int columna = rand()%M;
      array_p[i].p_fila = fila;
      array_p[i].p_columna = columna;
      array_p[i].p_weapon = 0;
      array_p[i].p_bitten = -1;
    }
    /*Creamos los threads de las peronas*/
    for (i=0; i < n_people; i++) {
        pthread_create(&(threads_people[i]), NULL, create_people, (void*) &(array_p[i]));
    }
    /*
    for (i=0; i < n_people; i++){
        pthread_join(threads_people[i], NULL);
    }*/
}

/*Funcion que crea a los zombies*/
/*Creemos todos los zombies a la vez*/
void threads_zombies(int n_zombie){
    int i;
    /*Se Reservamos memoria para los threads*/
    pthread_t *threads_zombies = (pthread_t*) malloc(n_zombie*sizeof(pthread_t));
    /*Se crea el arreglo de zombies*/
    zombie *array_z = (zombie*)malloc(sizeof(zombie)*n_zombie);
    /*Asignamos los valores*/
    for(int i = 0; i < n_zombie; i++){
        array_z[i].z_id = i;
        array_z[i].z_fila = 0;
        array_z[i].z_columna = 0;
    }
    /*Creamos los threads de los zombies*/
    for (i=0; i < n_zombie; i++) {
        pthread_create( &(threads_zombies[i]), NULL, create_zombie, (void*) &(array_z[i]));
    }

    /*for (i=0; i < n_zombie; i++){
        pthread_join(threads_zombies[i], NULL);
    }*/
}

#endif
