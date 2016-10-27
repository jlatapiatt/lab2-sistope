//argv[1] es n = número de procesos

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>

#define TRUE 1
#define FALSE 0
#define LARGO_BUFFER 6*sizeof(char)

int main(int argc, char *argv[]) {
	//Verificar cantidad de argumentos
	if (argc < 2) {
		printf("Cantidad de argumento inválida\n");
		return 1;
	}

	int n, p, maxDescriptor, idProceso;
	char esPadre = TRUE;
	//Verificar argumentos
	if (sscanf(argv[1], "%d", &n) <= 0) { //Aprendan a usar sscanf y sus variantes, lo preguntaré en alguno de los labs presenciales
		printf("Segundo argumento inválido, debe ser un número\n");
		return 1;
	}
	
	//Descriptores
	int *descriptores = malloc(n*2*sizeof(int));
	maxDescriptor = 0;
	printf("Mostrando descriptores de los pipes [lectura, escritura]\n");
	for (int i = 0; i < 2*n; i=i+2) {
		if (pipe(&(descriptores[i])) < 0) {
			printf("Error al crear un pipe\n");
			return 1;
		}
		//Busca el descriptor más grande, sólo los de lectura que son los i-esimos (los de escritura están en los i+1)
		if (descriptores[i] > maxDescriptor) {
			maxDescriptor = descriptores[i];
		}
		printf("[%d, %d]\n", descriptores[i], descriptores[i+1]); //muestro el N° del descriptor de lectura y de escritura
	}
	
	//Crear procesos con fork
	printf("\nSe van a crear %d procesos\n", n);
	for (int i = 0; i < n; i++) {
		p = fork();
		if (p == 0) {
			esPadre = FALSE;
			idProceso = i; //Para poder identificarlo después
			break; //El hijo sale del bucle
		}
		else if (p < 0) {
			printf("Error al crear un proceso hijo\n");
			return 1;
		}
	}
	
	//LA IDEA ES QUE TODOS LOS HIJOS LE HABLEN AL PADRE LUEGO DE UNOS SEGUNDOS
	if (esPadre == FALSE) {
		// Esto es nada más que un truquillo para que los procesos con id > 2 esperen menos que los otros procesos,
		// como para que vean que select() puede leer desde cualquiera de todos los descriptores que uno diga
		if (idProceso > 2) {
			sleep(2); //Espero 2 segundos
		}
		else {
			sleep(3); //Espero 3 segundos
		}
		
		//La variable i quedó con el último indice de la itración al crear los procesos
		int descriptorEscritura = descriptores[2*idProceso+1]; //Recordar que los pares son los de lectura y los impares son de escritura
		char *mensaje = malloc(LARGO_BUFFER);
		mensaje[0] = 'i';mensaje[1] = 'd'; mensaje[2] = ':';mensaje[3] = ' '; mensaje[4] = (char)(idProceso+48); mensaje[5] = 0;
		printf("El proceso N°%d va a escribir en el pipe con descriptor: %d\n", idProceso, descriptorEscritura);
		write(descriptorEscritura, mensaje, LARGO_BUFFER);
	}
	else { //El padre
		char *mensajeRecibido = malloc(LARGO_BUFFER);
		
		printf("El padre intentará leer\n");
		/*
		 //Descomente esto y comente lo de abajo para probar que sólo lea desde el primer proceso
		read(descriptores[0], mensajeRecibido, LARGO_BUFFER);
		printf("Ha llegado un mensaje desde el descriptor: %d\n", descriptores[0]);
		printf("El mensaje dice: '%s'\n", mensajeRecibido);
		
		*/
		
		
		
		
		
		
		fd_set setDescriptores;
		
		struct timeval timeout;
		timeout.tv_sec = 7; //Esperará máximo 7 segundos escuchando por los pipes al usar select(), CAMBIEN ESTO POR 1 PARA VER COMO SE VA A TIMEOUT, YA QUE LOS PROCESOS HIJOS SE DEMORAN MÁS DE 1 SEGUNDO EN ESCRIBIR
		timeout.tv_usec = 0; //Hay que poner esto en 0 si no van a usar microsegundos, recuerden que inicialmente puede haber cualquier basura en memoria
		
		FD_ZERO(&setDescriptores); //Pongo todos los bits del set de descriptores en 0
		printf("Padre: Se va a leer desde %d pipes a la vez\n", n);
		for (int i = 0; i < 2*n; i=i+2) {
			FD_SET(descriptores[i], &setDescriptores); //Digo que quiero leer sólo desde los descriptores que están en posiciones pares del arreglo (los de lectura)
		}
		int cantidadPipesListos = select(maxDescriptor+1, &setDescriptores, NULL, NULL, &timeout);
		if (cantidadPipesListos > 0) {
			printf("Es posible leer %d pipes\n", cantidadPipesListos);
		}
		else if (cantidadPipesListos == 0) {
			printf("No hay pipes para leer, se fue a timeout\n");
		}
		int resultadoIsset;
		for (int i = 0; i < 2*n; i=i+2) {
			//DEBIESEN PODER LEERSE CORRECTAMENTE "cantidadPipesListos" N°s de pipes. Eso es lo que devolvió select()
			resultadoIsset = FD_ISSET(descriptores[i], &setDescriptores); //Compruebo en cuales quedó seteado su bit en 1, de esta forma se de cual hacer read
			if (resultadoIsset > 0) {
				read(descriptores[i], mensajeRecibido, LARGO_BUFFER);
				printf("Ha llegado un mensaje desde el descriptor: %d\n", descriptores[i]);
				printf("El mensaje dice: '%s'\n", mensajeRecibido);
			}
		}
		
		
		 
		
		
		
		
		//Espero a que terminen todos los hijos
		for (int i = 0; i < n; i++) {
			wait();
		}
		printf("terminó el padre luego de esperar a todos los procesos hijos\n");
	}
	
	//RECUERDEN QUE PUEDEN OBTENER MÁS INFORMACIÓN EN LA CONSOLA ESCRIBIENDO: man select
	
	return 0;
}
