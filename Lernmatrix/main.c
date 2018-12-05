#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include "lernmatrix.h"

void vaciar_buffer();

int m, n;

int main(int argc, char* argv[])
{
	struct patron *datos = NULL;
	int tam, lineas, k, flag = 1;
	char c[3];
	int inputs[5];

	printf("\t-------------------------\n");
	printf("\t|\tLernmatrix\t|\t\n");
	printf("\t-------------------------\n");

	if(argc < 2){
		perror("Error. Ingrese la ruta donde se encuentra el archivo \'datos.txt\'\n");
		exit(EXIT_FAILURE);
	}

	lineas = linesFile(argv[1]);
	tam = lineas - 1;

	datos = (struct patron *) malloc(sizeof(struct patron) * tam);
	readFile(argv[1],datos,tam,lineas,&m,&n);
	int matriz[n][m];
	iniMatrix(matriz);
	printf("\nDatos leidos del archivo:\n");
    printArray(datos,tam,m,n);
	printf("\nInicializando la matriz de entrenamiento:\n");
	printMatriz(matriz);

	aprendizajeLnMatrix(matriz,datos,tam);
	printf("\nMatriz resultante\n");
	printMatriz(matriz);

	do{
		for(k = 0; k < m; k++){
			printf("\nIngrese el valor para p[%d], 'q' para terminar el programa: ", k+1);
			vaciar_buffer();
			fgets(c,3,stdin);
			if(isdigit(c[0]) || c[0] == 'q'){
				if(c[0] != 'q'){
					if(atoi(c) > 1){
						printf("\nError. El valor debe de ser '0' o '1', favor de intentarlo de nuevo\n\n");
						k--;
					}else
						inputs[k] = atoi(c);
				}
				else
					k = m;
				flag = 0;
			}else{
                printf("\nError: No ingreso un valor numerico o no es un valor positivo, favor de intentarlo de nuevo\n\n");
				flag = 1;
				k--;
				c[0] = 'q';
			}
		}
		if(c[0] != 'q')
			FaseDeRecuperacion(matriz,inputs);
	}while(c[0] != 'q' || flag);

	printf("\nBye :3\n");
	free(datos);
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
