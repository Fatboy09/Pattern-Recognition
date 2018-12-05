#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lernmatrix.h"

void readFile(char* path, struct patron datos[], int tam, int lineas, int* m, int *n)
{
    char cad[15];
    char *token, *string;
    int i = 0, j = 0, k, l = -1;
    
    FILE* arch = fopen(path, "r");

    if(arch == NULL){
        perror("Error al abrir el archivo\n");
        exit(EXIT_FAILURE);
    }

    while(!feof(arch)){
        for(i = 1; i <= lineas; i++){
            fgets(cad,15,arch);
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
            if((matriz[i][j] != 1) && (matriz[i][j] != -1)){
                if(matriz[i][j] != 0)
                    printf("%3de ", matriz[i][j]);
                else
                    printf("%3d ", matriz[i][j]);
            }
            else{
                if(matriz[i][j] == 1)
                    printf("  e  ");
                else
                    printf("-e  ");
            }
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

int getMaximo(int a[], int tam)
{
    register int i;
    int max = 0;

    for(i = 0; i < tam; i++){
        if(a[i] > max)
            max = a[i];
    }

    return max;
}

void aprendizajeLnMatrix(int matriz[][m], struct patron datos[], int tam)
{
    register int i, j;
    int r;
    
    for( i = 0; i < tam; i++){
        r = getRow(datos[i].c, n);
        
        for( j = 0; j < m; j++){
            if(datos[i].p[j] == 1)
                matriz[r][j] += 1;
            else
                matriz[r][j] += -1; 
        }
    }
}

void FaseDeRecuperacion(int matriz[][m], int inputs[])
{
    register int i,j;
    int clase[n], maximo;

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
            printf("\t %de\n",clase[i]);
        else
            printf("\t%de\n",clase[i]);
    }

    maximo = getMaximo(clase,n);

    for(i = 0; i < n; i++){
        if(clase[i] != maximo)
            clase[i] = 0;
        else
            clase[i] = 1;
    }

    printf("\nClase a la que pertenece:\n");
    printf("\n");
    for(i = 0; i < n; i++)
        printf("\t %d\n",clase[i]);
}