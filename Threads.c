#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*Estructura de datos necesaria para cada hebra persona*/
typedef struct th_people{
    int p_id;	/*Identifica el id del thread*/
    int p_fila;	/*Posicion de la persona*/
    int p_columna;	/*Posicion de la persona*/
    int p_weapon;	/*Arma de la persona*/
}people;

/*Estructura de datos necesaria para cada hebra persona*/
typedef struct th_zombie{
    int z_id;	/*Identifica el id del thread*/
    int z_fila;	/*Posicion del zombie*/
    int z_columna;	/*Posicion del zombie*/
}zombie;

/*Inicializacion del semaforo*/
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/*Definios la funcion de movimiento de los thread*/
/*Para eso se necesita la persona para obtener todos sus datos*/

void move(people *persona, char** board){
    /*Comprobamos primeros los 8 casos en orden arriba, abajo, derecha e izquieda*/
    /*Como el movimiento es aleatorio usamos un random de 0-7*/
    int i, j;
    i = persona->p_fila;
    j = persona->p_columna;
    int contador = 0;
    int mov;
    while(contador < 8){
        mov = (int) random()%8;
        if (mov == 0){
            /*Comprobamos que [i][j-1] arriba*/
            if(board[i][j-1] == 0){
                persona->p_columna = j-1;
                board[i][j-1] = 'P';
            }
            /*si esta ocupada suma al contador*/
            contador = contador + 1;
        }
        if (mov == 1){
            /*Comprobamos que [i][j+1] abajo*/
            if(board[i][j+1] == 0){
                persona->p_columna = j+1;
                board[i][j+1] = 'P';
            }
            /*si esta ocupada suma al contador*/
            contador = contador + 1;
        }
        if (mov == 2){
            /*Comprobamos que [i+1][j] derecha*/
            if(board[i+1][j] == 0){
                persona->p_fila = i+1;
                board[i+1][j] = 'P';
            }
            /*si esta ocupada suma al contador*/
            contador = contador + 1;
        }
        if (mov == 3){
            /*Comprobamos que [i-1][j] izquierda*/
            if(board[i-1][j] == 0){
                persona->p_fila = i-1;
                board[i-1][j] = 'P';
            }
            /*si esta ocupada suma al contador*/
            contador = contador + 1;
        }
        if (mov == 4){
            /*Comprobamos que [i+1][j-1] derecha arriba*/
            if(board[i+1][j-1] == 0){
                persona->p_fila = i+1;
                persona->p_columna = j-1;
                board[i+1][j-1] = 'P';
            }
            /*si esta ocupada suma al contador*/
            contador = contador + 1;
        }
        if (mov == 5){
            /*Comprobamos que [i-1][j-1] izquierda arriba*/
            if(board[i-1][j-1] == 0){
                persona->p_fila = i-1;
                persona->p_columna = j-1;
                board[i-1][j-1] = 'P';
            }
            /*si esta ocupada suma al contador*/
            contador = contador + 1;
        }
        if (mov == 6){
            /*Comprobamos que [i+1][j+1] derecha abajo*/
            if(board[i+1][j+1] == 0){
                persona->p_fila = i+1;
                persona->p_columna = j+1;
                board[i+1][j+1] = 'P';
            }
            /*si esta ocupada suma al contador*/
            contador = contador + 1;
        }
        if (mov == 7){
            /*Comprobamos que [i-1][j+1] izquierda abajo*/
            if(board[i-1][j+1] == 0){
                persona->p_fila = i-1;
                persona->p_columna = j+1;
                board[i-1][j+1] = 'P';
            }
            /*si esta ocupada suma al contador*/
            contador = contador + 1;
        }
    }
    /*Caso de que no s epueda mover, este se queda quieto*/
}

/*Resolvemos la batalla*/
/*Esta funcion sera cuando se encuentren*/
int battle(people *p, zombie *z){

}

/*Creamos las funciones para las dos hebras*/
void *create_people(void *arg){
    /*Definimos a la persona*/
    people *p = (people*) arg;
    pthread_mutex_lock(&mutex);	//Se bloquea el movimiento
    move(p);
    pthread_mutex_unlock(&mutex);	//Se desbloquea el movimiento
}

/*Funcion que crea todas las personas*/
void threads_people(int n_people){
    int i;
    /*Reservamos memoria para los thread y el arreglo*/
    pthread_t *threads_people = (pthread_t*) malloc(n_people*sizeof(pthread_t));
    people *array_p = (people*)malloc(sizeof(people)*n_people);
    /*Asignamos*/
    for(i=0; i< n_people; i++){
        array_p[i].p_id = i;
        array_p[i].p_position = (int) random()%100;
        /*Se les debe asignar una posicion random*/
        array_p[i].p_fila = 0;
        array_p[i].p_columna = 0;
        /****/
        array_p[i].p_weapon = 0;
    }
    /*Creamos los threads de las peronas*/
    for (i=0; i < n_people; i++) {
        pthread_create( &(threads_people[i]), NULL, create_people, (void*) &(array_p[i]));
    }
}

/*Funcion que crea a los zombies*/
/*Creemos todos los zombies a la vez*/
void threads_zombies(int n_zombie){
    /*Se Reservamos memoria para los threads*/
    pthread_t *threads_zombies = (pthread_t*) malloc(n_zombie*sizeof(pthread_t));
    /*Se crea el arreglo de zombies*/
    zombie *array_z = (zombie*)malloc(sizeof(zombie)*n_zombie);
    /*Asignamos los valores*/
    for(i=0; i< n_zombie; i++){
        array_z[i].z_id = i;
        array_z[i].z_fila = 0;
        array_z[i].z_columna = 0;
    }
    /*Creamos los threads de los zombies*/
    for (i=0; i < n_zombie; i++) {
        pthread_create( &(threads_zombies[i]), NULL, create_zombie, (void*) &(array_z[i]));
    }
}
