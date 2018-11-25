#ifndef PERCEPTRON_H
#define PERCEPTRON_H

struct knn
{
    int B0;
    int B1;
    int clase;
    float d;
};

void readFile(char* path, int **m, int rows, int columns);
void writeFile(char* path, int x0, int x1, int clase);
int linesFile(char* path);
void printArray(struct knn a[], int tam);
void printMatriz(int **m, int rows, int columns);
double euclidiana(int A0, int A1, int B0, int B1);
void bubbleSort(struct knn a[], int tam);
int knnR(int **m, int rows, int columns, int a[]);
int knndM(int **m, int rows, int columns, int a[]);
#endif