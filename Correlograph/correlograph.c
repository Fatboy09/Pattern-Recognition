#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "correlograph.h"

void readFile(char* path, struct patron datos[], int tam, int lineas, int* m, int *n)
{
    char cad[20];
    char *token, *string;
    int i = 0, j = 0, k, l = -1;
    
    FILE* arch = fopen(path, "r");

    if(arch == NULL){
        perror("Error al abrir el archivo\n");
        exit(EXIT_FAILURE);
    }

    while(!feof(arch)){
        for(i = 1; i <= lineas; i++){
            fgets(cad,20,arch);
            string = strdup(cad);
            while((token = strsep(&string,":")) != NULL){
                if(i == 1){
                    if(j % 2 == 0)
                        *m = *token - 48;
                    else
                        *n = *token - 48;
                    
                    for(k = 0; k < tam; k++){
                        datos[k].p = (int *) malloc(sizeof(int)* (*m));
                        datos[k].c = (int *) malloc(sizeof(int)* (*n));
                    }
                }
                else{
                    if(j % 2 == 0){
                        for(k = 0; k < (*m); k++){
                            datos[l].p[k] = token[k] - 48;
                        } 
                    }else{
                        for(k = 0; k < (*n); k++){
                            datos[l].c[k] = token[k] - 48;
                        }
                    }
                }
                j++;
            }
            l++;
        }
    }
    printf("m=%d\tn=%d",*m,*n);
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

void printArray(struct patron pt[], int tam, int m, int n)
{
    register int k,i;
    
    for(k = 0; k < tam; k++){
        printf("\npatron %d: ",k+1);
        for(i = 0; i < m; i++){
            printf("%d",pt[k].p[i]);
        }
        printf("\n");
        printf("clase: ");
        for(i = 0; i < n; i++){
            printf("%d",pt[k].c[i]);
        }
        printf("\n");
    }
}

void iniMatrix(int matriz[][m])
{
    register int i,j;

    for( i = 0; i < n; i++)
        for( j = 0; j < m; j++)
            matriz[i][j] = 0;
}

void printMatriz(int matriz[][m])
{
    register int i,j;

    printf("\n");

    for( i = 0; i < n; i++){
        for( j = 0; j < m; j++){
            printf("%3d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int getRow(int clase[], int tam)
{
    register int i;
    int row = 0;

    for( i = 0; i < tam; i++)
    {
        if(clase[i] == 1)
            i = tam;
        else
            row++;
    }
    
    return row;
}

void aprendizajeLnMatrix(int matriz[][m], struct patron datos[], int tam)
{
    register int i, j, k;
    
    for( i = 0; i < tam; i++){
        for( j = 0; j < n; j++){
            if(datos[i].c[j] == 1){
                for(k = 0; k < m; k++){
                    if(datos[i].p[k] == 1)
                        matriz[j][k] = 1;
                }
            }
        }
    }
}

void FaseDeRecuperacion(int matriz[][m], int inputs[])
{
    register int i,j;
    int clase[n];
    int umbral = (int) log2(m);

    for(i = 0; i < n; i++)
        clase[i] = 0;
    
    for(i = 0; i < n; i++){
        for(j = 0; j < m; j++){
            clase[i] += matriz[i][j] * inputs[j];
        }
    }

    printf("\n");
    printf("Resultado del producto entre la matriz de entrenamiento con el patron de entrada:\n");
    for(i = 0; i < n; i++){
        if(clase[i] >= 0)
            printf("\t %d\n",clase[i]);
        else
            printf("\t%d\n",clase[i]);
    }

    for(i = 0; i < n; i++){
        if(clase[i] >= umbral)
            clase[i] = 1;
        else
            clase[i] = 0;
    }

    printf("\nClase a la que pertenece:\n");
    printf("\n");
    for(i = 0; i < n; i++)
        printf("\t %d\n",clase[i]);
}