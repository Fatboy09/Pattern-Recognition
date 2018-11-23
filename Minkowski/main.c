#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include "minkowski.h"

void vaciar_buffer();

int main(int argc, char* argv[])
{
	char opc;
	int *x = NULL;
	int *y = NULL;
	int numLines = 0;

	if(argc < 2){
		perror("Error. Ingrese la ruta donde se encuentra el archivo \'datos.txt\'\n");
		exit(EXIT_FAILURE);
	}
	numLines = linesFile(argv[1]);
	x = (int *) malloc (sizeof(int)*numLines);
	y = (int *) malloc (sizeof(int)*numLines);
	readFile(argv[1],x,y);
	do{
        system("clear");
        printf("\nMetricas de Minkowski:\n\n");
        printf("1. CityBlock\n");
        printf("2. Euclidiana\n");
        printf("3. Infinita\n");
        printf("4. Salir\n");
        printf("Ingrese la opcion deseada: ");
        vaciar_buffer();
        opc = getchar();
		printf("\nx = [ ");
		printArray(x,numLines);
		printf("]\n");
		printf("y = [ ");
		printArray(y,numLines);
		printf("]\n");
        switch(opc){
            case '1':
				printf("\nLa distancia cityBlock es de: %.3f\n",cityBlock(x,y,numLines));
                printf("\n\nPresione la tecla enter para continuar...");
                vaciar_buffer();
                getchar();
                opc = 0;
                break;
                
            case '2':  
				printf("\nLa distancia euclidiana es de: %.3f\n",euclidiana(x,y,numLines));
                printf("\n\nPresione la tecla enter para continuar...");
                vaciar_buffer();
                getchar();
                opc = 0;
                break;
                
            case '3':
                printf("\nLa distancia infinita es de: %.3f\n",infinita(x,y,numLines));
                printf("\n\nPresione la tecla enter para continuar...");
                vaciar_buffer();
                getchar();
                opc = 0;
                break;
            
            case '4':
                printf("\nBye!!! :3\n");
                exit(1);
                break;
            
            default:
                printf("Error. Opcion no valida, intentelo de nuevo. ");
                printf("Presione la tecla enter para continuar...");
                vaciar_buffer();
                getchar();
                opc = 0;
                break;
        }
    
    }while(opc == 0);
	free(x);
	free(y);
	return 0;
}

void vaciar_buffer()
{
    int fdflags;
    fdflags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, fdflags | O_NONBLOCK);
    while (getchar()!=EOF);
    fcntl(STDIN_FILENO, F_SETFL, fdflags);
}
