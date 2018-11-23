#ifndef PERCEPTRON_H
#define PERCEPTRON_H
void readFile(char* path, int x[], int y[]);
int linesFile(char* path);
void printArray(int a[], int tam);
double cityBlock(int x[], int y[], int tam);
double euclidiana(int x[], int y[], int tam);
double infinita(int x[], int y[], int tam);
#endif