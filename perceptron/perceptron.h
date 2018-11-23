#ifndef PERCEPTRON_H
#define PERCEPTRON_H
void aprender(int inputs[][2], int target[], double* bias, double weights[]);
int hardlims(double n);
double calcular_e(int t, double a);
void update_weights(double e, double w[], int p[]);
void update_bias(double* b, double e);
void output_NAND(double w[], double b, int p[]);
#endif