#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "knn.h"

void readFile(char* path, int **m, int rows, int columns)
{
    char cad[10];
    char *token, *string;
    int i = 0, j = 0;
    FILE* arch = fopen(path, "r");

    if(arch == NULL){
        perror("Error al abrir el archivo\n");
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++)
            m[i][j] = 0;
    }
    i = 0;
    while(!feof(arch)){
        j = 0;
        fgets(cad,10,arch);
        string = strdup(cad);
        while((token = strsep(&string,":")) != NULL){
            m[i][j] = atoi(token);
            j++;
        }
        i++;
    }
    fclose(arch);
}

void writeFile(char* path, int x0, int x1, int clase)
{
    FILE* arch = fopen(path, "a");

    if(arch == NULL){
        perror("Error al abrir el archivo\n");
        exit(EXIT_FAILURE);
    }

    fprintf(arch,"\n%d:%d:%d",x0,x1,clase);

    fclose(arch);

}

int linesFile(char* path)
{
    int contador = 0;
    unsigned char caracter; 
    FILE* arch = fopen(path, "r");

    if(arch == NULL){
        perror("Error al abrir el archivo\n");
        exit(EXIT_FAILURE);
    }

    while(!feof(arch)){
        caracter = fgetc(arch);
        if(caracter == '\n')
            contador++;
    }

    fclose(arch);

    return contador+1;
}

void printArray(struct knn a[], int tam)
{
    register int m;
    
    for(m = 0; m < tam; m++){
        printf("%2d %2d %2d  %3.3f",a[m].B0,a[m].B1,a[m].clase, a[m].d);
        printf("\n");
    }
}

void printMatriz(int **m, int rows, int columns)
{
    register int i,j;
    
    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++)
            printf("%2d ",m[i][j]);
        printf("\n");
    }
}

double euclidiana(int A0, int A1, int B0, int B1)
{
    int d = 0;

    d = (pow((A0-B0),2)) + (pow((A1-B1),2));

    return sqrt(d);
}

void bubbleSort(struct knn a[], int tam)
{
    register int i,j;
    struct knn temp;

    for(i = 0; i < tam-1; i++){
        for(j = 0; j < (tam-i-1); j++){
            if(a[j].d > a[j+1].d){
                temp.B0 = a[j].B0;
                temp.B1 = a[j].B1;
                temp.clase = a[j].clase;
                temp.d = a[j].d;

                a[j].B0 = a[j+1].B0;
                a[j].B1 = a[j+1].B1;
                a[j].clase = a[j+1].clase;
                a[j].d = a[j+1].d;

                a[j+1].B0 = temp.B0;
                a[j+1].B1 = temp.B1;
                a[j+1].clase = temp.clase;
                a[j+1].d = temp.d;
            }
        }
    }
}

int knnR(int **m, int rows, int columns, int a[])
{
    register int i;
    int clase = -1;
    int cont[] = {0,0};

    struct knn *arr = NULL;
    arr = ( struct knn *) malloc(sizeof(struct knn)*rows);
    for(i = 0; i < rows; i++){
        arr[i].B0 = m[i][0];
        arr[i].B1 = m[i][1];
        arr[i].clase = m[i][2];    
    }

    //calculamos la distancia euclidiana
    for(i = 0; i < rows; i++)
        arr[i].d = euclidiana(a[0],a[1],arr[i].B0,arr[i].B1);
    
    printf("\nDistancias Euclidianas\n");
    printf("\nx0 x1  C   dE\n");
    printf("----------------\n");
    printArray(arr,rows);

    //ordenamos las distancias
    bubbleSort(arr,rows);
    printf("\nDistancias Euclidianas ordenadas\n");
    printf("\nx0 x1  C   dE\n");
    printf("----------------\n");
    printArray(arr,rows);

    if(arr[0].d == 0.0){
        printf("\nEl dato [%d,%d] pertenece a la clase %d\n",a[0],a[1],arr[0].clase);
        return -2;
    }

    //clasificamos al dato desconocido
    for(i = 0; i < a[3]; i++){      //a[3] = k
        if(arr[i].clase == 0)
            cont[0] += 1;           //incrementamos el contador para la clase 0
        else
            cont[1] += 1;           //incrementamos el contador para la clase 1
    }
    
    //si hay empate tomamos al de la distancia más minima, si no comparamos los valores con el valor del umbral
    if(cont[0] == cont[1])
        return arr[0].clase;

    //a[2] = umbral, comparamos el valor de los contadores de cada clase con el umbral
    if(cont[0] > a[2])
        clase = 0;
    
    else if(cont[1] > a[2])
        clase = 1;

    printf("\ncont[0] = %d\tcont[1] = %d\n",cont[0],cont[1]);

    free(arr);
    return clase;
}

int knndM(int **m, int rows, int columns, int a[])
{
    register int i;
    int clase = -1;
    int cont[] = {0,0};
    double prom[] = {0.0,0.0};

    struct knn *arr = NULL;
    arr = ( struct knn *) malloc(sizeof(struct knn)*rows);
    for(i = 0; i < rows; i++){
        arr[i].B0 = m[i][0];
        arr[i].B1 = m[i][1];
        arr[i].clase = m[i][2];    
    }

    //calculamos la distancia euclidiana
    for(i = 0; i < rows; i++)
        arr[i].d = euclidiana(a[0],a[1],arr[i].B0,arr[i].B1);
    
    printf("\nDistancias Euclidianas\n");
    printf("\nx0 x1  C   dE\n");
    printf("----------------\n");
    printArray(arr,rows);

    //ordenamos las distancias
    bubbleSort(arr,rows);
    printf("\nDistancias Euclidianas ordenadas\n");
    printf("\nx0 x1  C   dE\n");
    printf("----------------\n");
    printArray(arr,rows);

    if(arr[0].d == 0.0){
        printf("\nEl dato [%d,%d] pertenece a la clase %d\n",a[0],a[1],arr[0].clase);
        return -2;
    }

    //calculamos las distancias minimas medias de ambas clases
    for(i = 0; i < a[3]; i++){      //a[3] = k
        if(arr[i].clase == 0){
            prom[0] += arr[i].d; 
            cont[0] += 1;           //incrementamos el contador para la clase 0
        }
        else{
            prom[1] += arr[i].d;
            cont[1] += 1;           //incrementamos el contador para la clase 1
        }
    }

    if(cont[0] == 0)
        return 1;
    else if (cont[1] == 0)
        return 0;

    prom[0] /= cont[0];
    prom[1] /= cont[1];

    printf("\nDistancia media de la clase 0: %f\n",prom[0]);
    printf("\nDistancia media de la clase 1: %f\n",prom[1]);

    if(prom[0] < prom[1])
        clase = 0;
    else
        clase = 1;
    
    return clase;
}
