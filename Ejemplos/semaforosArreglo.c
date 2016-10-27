#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Este programa tiene como finalidad mostrar un id generado por el programador
   para cada hebra, de forma progresiva 										*/

pthread_mutex_t *mutex;
int canHebras;

void *listarHebras (void *args){

	int *i = (int *) args;
	
	//Se bloquea el mutex de la hebra que se está usando
	pthread_mutex_lock(&mutex[*i]);
	
	//Sección Critica
	printf("Soy una hebra y mi tid es: %d\n",*i);
	//Fin sección critica	

	//Cuando termina la sección critica, se da paso a la siguiente hebra
	pthread_mutex_unlock(&mutex[*i+1]);
	
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){

	int i;
	canHebras = atoi(argv[1]);	//Se recibe la cantidad de hebras como argumento de entrada
	pthread_t *arrThread = (pthread_t*)malloc(sizeof(pthread_t)*canHebras);	//Se genera espacio para las hebras

	mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)*canHebras);

	//Se genera el vector de mutex y se cierran todos
	for(i=0;i<canHebras;i++){
		pthread_mutex_init(&mutex[i],NULL);
		pthread_mutex_lock(&mutex[i]);
	}
	
	//Se libera el primer mutex
	pthread_mutex_unlock(&mutex[0]);


	//Se genera un arreglo de numeros para darlos como argumentos
	//Si no se hace así y se le entrega directamente la dirección de memoria de i se cae en un problema de inanición,
	//ya que dos hebras pueden intentar entrar con el mismo i, y si pasa eso, la segunda se encontrará con que su semaforo está bloqueado
	//y por tanto nunca se podrá ejecutar, al igual que el resto de las hebras
	int *numeros = (int*)malloc(sizeof(int)*canHebras);

	for(i=0;i<canHebras;i++){
		numeros[i] = i;
	}
	
	//Se crean las hebras
	for(i=0;i<canHebras;i++){
		pthread_create(&arrThread[i],NULL,&listarHebras, &numeros[i]);
	}		

	//Se espera a que cada hebra termine
	for(i=0;i<canHebras;i++){
		pthread_join(arrThread[i],NULL);
	}

	return 0;

}
