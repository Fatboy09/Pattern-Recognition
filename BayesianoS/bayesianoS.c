#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "lista.h"

char* reservarMem(char cad[]);
lista definirClases(int n, lista l, char cad[]);
void Cardinalidad_Clases(lista l);
int isEqual(int array[], int tam);
void imprimirArray(int [],int tam);
double calcularProbabilidad(int Pa, int PEm);
void ejecutarAprendizaje(lista l);

int EspacioM_cardin;

int main(int argc, char const *argv[])
{
	int numClases, muestra;
	char *EspacioM_name = NULL;
	char cadena[512];
	char *clases = NULL;
	lista l = NULL;
	l = empty(l);

	printf("Ingrese el nombre de su espacio muestral: ");
	scanf("%[^\n]",cadena);

	EspacioM_name = reservarMem(cadena);
	strcpy(EspacioM_name,cadena);
	
	printf("Ingrese la cardinalidad de su espacio muestral: ");
	scanf("%d",&EspacioM_cardin);

	printf("Ingrese la cantidad de clases que pertenecen a su espacio muestral: ");
	scanf("%d",&numClases);

	l = definirClases(numClases, l, cadena);
	Cardinalidad_Clases(l);
	ejecutarAprendizaje(l);

	free(EspacioM_name);
	delete(&l);
	l = NULL;

	return 0;
}

void imprimirArray(int a[], int tam)
{
    register int i;
    
    for(i = 0; i < tam; i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
}

int isEqual(int array[], int tam)
{
	register int i;
	int sum = 0;

	for (i = 0; i < tam; i++)
	{
		sum = sum + array[i];
	}

	return (sum == EspacioM_cardin) ? TRUE : FALSE;
}

char* reservarMem(char cad[])
{
	int tamanio = strlen(cad);

	char* mem = NULL;

	mem = (char *) malloc(sizeof(char)*(tamanio+1));
	return mem;
}

lista definirClases(int n, lista l, char cad[])
{
	register int i;
	int cardin, bandera = TRUE;

	printf("-----------------------------------------------");

	for ( i = 0; i < n; i++)
	{
		setbuf(stdin,NULL);
		printf("\nIngrese el nombre de la clase %d: ", i);
		scanf("%[^\n]", cad);
		insert(&l,cad);
	}

	return l;
}

double calcularProbabilidad(int Pa, int PEm)
{
	return (double) Pa/PEm;
}

void Cardinalidad_Clases(lista l)
{
	register int i;
	int *array, dato, tamanio, bandera = TRUE;
	lista auxL = l;
	tamanio = cardinalidad(l);

	array = (int*) malloc(sizeof(int)*tamanio);

	printf("-----------------------------------------------");

	while(bandera)
	{
		for (i = 0; i < tamanio; i++)
		{
			printf("\nIngrese la cardinalidad de la clase %s: ",auxL->nombre);
			scanf("%d", &dato);
			array[i] = dato;
			auxL =  auxL->sig;
		}

		if(isEqual(array,tamanio))
		{
			bandera = FALSE;
		}
		else
		{
			printf("Error. La suma de la cardinalidad de sus clases no es igual a la cardinalidad de su espacio muestral.\n");
			printf("Por favor de ingresar de nuevo los valores\n");
			auxL = l;
		}
	}

	for (i = 0; i < tamanio; i++)
		modify(&l,i,array[i],calcularProbabilidad(array[i],EspacioM_cardin));

	free(array);
}

void ejecutarAprendizaje(lista l)
{
	register int i;
	double probM = 0.0;
	int indice = 0;
	NODE* newNode = NULL;
	int tam = cardinalidad(l);
	lista auxL = l;

	for (i = 0; i < tam; i++)
	{
		if( auxL->probabilidad > probM )
		{
			probM = auxL->probabilidad;
			indice = i;
		}
		auxL = auxL->sig;
	}
	
	printf("\nEspere unos segundos, estoy en modo de aprendizaje...\n");
	sleep(5);

	newNode = getNode(l,indice);
	printf("La muestra pertenece a la clase %d: %s\n",indice,newNode->nombre);
}
