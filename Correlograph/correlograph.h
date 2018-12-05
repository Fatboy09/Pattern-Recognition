#ifndef CORRELOGRAPH_H
#define CORRELOGRAPH_H

extern int m, n;

struct patron
{
    int *p;
    int *c;
};

void readFile(char* path, struct patron datos[], int tam, int lineas, int* m, int *n);
int linesFile(char* path);
int getRow(int clase[], int tam);
void printArray(struct patron pt[], int tam, int m, int n);
void printMatriz(int matriz[][m]);
void iniMatrix(int matriz[][m]);
void aprendizajeLnMatrix(int matriz[][m], struct patron datos[], int tam);
void FaseDeRecuperacion(int matriz[][m], int inputs[]);
#endif