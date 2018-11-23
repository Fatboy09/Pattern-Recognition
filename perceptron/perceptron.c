#include <stdio.h>
#include "perceptron.h"

int hardlims(double n)
{
    return (n >= 0) ? 1 : 0;
}

double calcular_e(int t, double a)
{
    return t - a;
}

void update_weights(double e, double w[], int p[] )
{
    register int i;

    for(i = 0; i < 2; i++){
        w[i] = w[i] + (e * p[i]);
    }   
}

void update_bias(double* b, double e)
{
    *b = *b + e;
}

void aprender(int inputs[][2], int target[], double* bias, double weights[])
{
    register int i,j;
    int flag = 0;
    int cont = 0;
    double n = 0.0;
    double e;

    while(!flag){
        for(i = 0; i < 4; i++){
            for(j = 0; j < 2; j++){
                n += inputs[i][j] * weights[j];
            }
            n += *bias;
            if(target[i] != hardlims(n)){
                e = calcular_e(target[i],hardlims(n));
                update_weights(e, weights, inputs[i]);
                update_bias(bias, e);
                cont = 0;
            }
            else{
                cont++;
            } 
            n = 0.0;
        }
        if(cont >= 4)
            flag = 1;
    }
    printf("\nNum de iteraciones para el aprendizaje: %d\n",  cont);
}

void output_NAND(double w[], double b, int p[])
{
    double n = 0.0;
    register int i;

    for(i = 0; i < 2; i++){
        n += p[i] * w[i];
    }
    n += b;
    printf("\nResultado %d NAND %d => %d\n", p[0], p[1], hardlims(n));
}