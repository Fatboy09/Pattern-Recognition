#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "minkowski.h"

void readFile(char* path, int x[], int y[])
{
    char cad[10];
    char *token, *string;
    int i = 0, contador = 0;
    FILE* arch = fopen(path, "r");

    if(arch == NULL){
        perror("Error al abrir el archivo\n");
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < 4; i++){
        x[i] = 0;
        y[i] = 0;
    }
    i=0;
    while(!feof(arch)){
        fgets(cad,10,arch);
        //printf("%s",cad);
        string = strdup(cad);
        while((token = strsep(&string,":")) != NULL){
            if(contador % 2 == 0)
                x[i] = atoi(token);
            else{
                y[i] = atoi(token);
                i++;
            }
            contador++;
        }
    }
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

void printArray(int a[], int tam)
{
    register int m;
    
    for(m = 0; m < tam; m++){
        printf("%d ",a[m]);
    }
}

double cityBlock(int x[], int y[], int tam)
{
    register int i;
    int d = 0;

    for(i = 0; i < tam; i++){
        d += abs(x[i] - y[i]);
    }
    return d;
}

double euclidiana(int x[], int y[], int tam)
{
    register int i;
    int d = 0;

    for(i = 0; i < tam; i++){
        d += pow(abs(x[i] - y[i]),2);
    }
    return sqrt(d);
}

double infinita(int x[], int y[], int tam)
{
    register int i;
    int d = 0;

    for(i = 0; i < tam; i++){
        if(abs(x[i] - y[i] > d))
            d = abs(x[i] - y[i]);
    }
    return d;
}
