#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*Estructura de datos necesaria para cada hebra persona*/
typedef struct th_people{
    int p_id;	/*Identifica el id del thread*/
    int p_estado;
    int p_position;	/*Posicion d la persona*/
    int p_weapon;	/*Arma de la persona*/
}people;

/*Estructura de datos necesaria para cada hebra persona*/
typedef struct th_zombie{
    int z_id;	/*Identifica el id del thread*/
    int z_estado;
    int z_position;	/*Posicion d la persona*/
}zombie;

/*Declaramos las funciones void que requieren los thread para ser creados*/
/*Segun la documentacion todas las funciones del thread deben ser dadas por su
funcion, por lo que el movimiento deberia ser realziado aqui*/
void *create_people(void *arg){
    people *p = (people*) arg;
    int num = p->p_id;
    while(1){
        printf("Soy la persona con id %i\n", num);
    }
}
/*Lo mismo para el Zombie*/
void *create_zombie(void *arg){
    zombie *z = (zombie*) arg;
    int num = z->z_id;
    while(1){
        printf("Soy el zombie con id %i\n", num);
    }
}

/*Variables para las pruebas*/
int n_people;   /*Cantidad de personas*/
int n_zombie;   /*Cantidad de zombies*/
int weapon;		 /*Usos del arma*/
int id_people, id_zombie;   /*Ides*/
int position_people, position_zombie;   /*Posiciones*/
int i;
int tablero[100];

int main(int argc, char *argv[]){
    /*Variables de entrada*/
    n_people = atoi(argv[1]);
    n_zombie = atoi(argv[2]);
    weapon = atoi(argv[3]);

    /*Creamos los dos arreglos para los threads de persona y zombies*/
    pthread_t *threads_peoples = (pthread_t*) malloc(n_people*sizeof(pthread_t));
    pthread_t *threads_zombies = (pthread_t*) malloc(n_zombie*sizeof(pthread_t));

    /*Creamos el vector para los datos de ambos threads de personas y zombies*/
    people *array_p = (people*)malloc(sizeof(people)*n_people);
    zombie *array_z = (zombie*)malloc(sizeof(zombie)*n_zombie);

    /*Llenamos los datos de las personas*/
    for(i=0; i< n_people; i++){
        array_p[i].p_id = i;
        array_p[i].p_position = (int) random()%100;
        array_p[i].p_estado = 1;
        array_p[i].p_weapon = weapon;
    }

    /*Llenamos los datos de los zombie*/
    for(i=0; i< n_zombie; i++){
        array_z[i].z_id = i;
        array_z[i].z_estado = 1;
        array_z[i].z_position = (int) random()%100;
    }

    //Se crean las hebras necesarias para personas
    for (i=0; i < n_people; i++) {
        pthread_create( &(threads_peoples[i]), NULL, create_people, (void*) &(array_p[i]));
    }

    printf("esperando a las hebras personas\n");
    //Se espera que todas las hebras finalicen
    for (i=0; i <= n_people; i++){
        pthread_join(threads_peoples[i], NULL);		//Mediante join me aseguro que las hebras finalizan
    }


    //Se crean las hebras necesarias para zombies
    for (i=0; i < n_zombie; i++) {
        pthread_create( &(threads_zombies[i]), NULL, create_zombie, (void*) &(array_z[i]));
    }

    printf("esperando a las hebraszombies\n");
    //Se espera que todas las hebras finalicen
    for (i=0; i <= n_zombie; i++){
        pthread_join(threads_zombies[i], NULL);		//Mediante join me aseguro que las hebras finalizan
    }

    for(i=0; i < n_people; i++){
        pthread_attr_t(&(threads_peoples[i]));
    }

    exit(0);
}
