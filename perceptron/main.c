#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include "perceptron.h"

void vaciar_buffer();

int main(int argc, char* argv[])
{
	int inputs[][2] = {{0,0},
					  {0,1},
					  {1,0},
					  {1,1}};	//vector de entradas

	int target[] = {1,1,1,0};	//targets de la compuerta NAND
	double bias = 0.5;			// bias inicial
	double weights[] = {2.0,2.0};	//vector de pesos iniciales
	register int i;
	char c[3];
	int p[2], flag = 1;

	printf("\n+--------------------------+\n");
	printf("|Perceptron: Compuerta NAND|");
	printf("\n+--------------------------+\n\n");

	printf("Pesos iniciales: [");
	for(i = 0; i < 2; i++)
		printf("%.1f ", weights[i]);
	printf("]\nBias inicial: %.1f\n", bias);

	//comenzamos aprendizaje
	aprender(inputs,target,&bias,weights);
	printf("\nAprendizaje terminado.\n\n");

	printf("Pesos finales: [");
	for(i = 0; i < 2; i++)
		printf("%.1f ", weights[i]);
	printf("]\nBias final: %.1f\n\n", bias);

	//pruebas
	while(flag || (c[0] != 'q'))
	{
		for(i = 0; i < 2; i++){
			printf("Ingrese un valor para la entrada p%d, \'q\' para terminar el programa: ",i+1);
			vaciar_buffer();		//limpia el buffer de entrada
			fgets(c,3,stdin);
			
			if(isdigit(c[0]) || (c[0] == 'q') || (isdigit(c[1]))){
				if(c[0] != 'q')
					p[i] = atoi(c);
				else
					i = 3;			//para salirse del ciclo for
				flag = 0;
			}else{
				printf("Error: No ingreso un valor numerico, favor de intentarlo de nuevo\n");
				flag = 1;
				i = 3;				//para salirse del ciclo for
				c[0] = 'q';
			}
		}
		if(c[0] != 'q')
			output_NAND(weights,bias,p);
		printf("\n----------------------------------------------------------------------\n");
	}
	printf("\t\t\t\tBye :3\n");
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
