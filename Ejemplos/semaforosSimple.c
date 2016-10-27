#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Este programa no hace nada más que sumar 1 al contador por cada hebra que se ejecuta.
   Es solo para mostrar la exlusión mutua y como un semaforo lo arregla 				*/

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;	//Semaforo utilizado
int contador=0;	//Variable global que produce problemas

void *funcionConflictiva(void *argumentos){

	pthread_mutex_lock(&mutex);	//Se bloquea el mutex
		
	//Sección critica	
	contador++;
	//Fin sección critica

	pthread_mutex_unlock(&mutex);	//Se desbloquea el mutex
	
	pthread_exit(NULL);
}

int main(int argc,char *argv[]){

	int i;	
	int cantidadHebras = atoi(argv[1]);	//Se recibe la cantidad de hebras que se quieren crear
	pthread_t *arr_thread = (pthread_t*)malloc(sizeof(pthread_t)*cantidadHebras);	//Se asigna memoria para las n hebras
	
	//Se crea cada hebra
	for(i=0;i<cantidadHebras;i++){
		pthread_create(&arr_thread[i],NULL,&funcionConflictiva,NULL);	
	}

	//Se espera a que cada hebra termine
	for(i=0;i<cantidadHebras;i++){
		pthread_join(arr_thread[i],NULL);
	}

	printf("El valor de contador es: %i\n",contador);

	return 0;

}
