#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include "knn.h"

void vaciar_buffer();
void printDataFile(int **m, int rows, int columns);

int main(int argc, char* argv[])
{
	char opc, c[3];
	int **datos;
	int numLines = 0, flag = 1, clase;
    int inputs[4];
    register int i;

	if(argc < 2){
		perror("Error. Ingrese la ruta donde se encuentra el archivo \'datos.txt\'\n");
		exit(EXIT_FAILURE);
	}
	
	do{
        c[0] = ' ';
        c[3] = ' ';
        
        system("clear");
        printf("\nClasificador K-nn:\n\n");
        printf("1. K-nn con rechazo\n");
        printf("2. K-nn con distancia media\n");
        printf("3. Salir\n");
        printf("Ingrese la opcion deseada: ");
        vaciar_buffer();
        opc = getchar();

        switch(opc){
            case '1':
                flag = 1;
				while(flag)
                {
                    printf("\nIngrese el valor de k: ");
                    vaciar_buffer();
                    fgets(c,3,stdin);

                    if(isdigit(c[0])){
                        inputs[3] = atoi(c);
                        flag = 0;
                    }
                    else
                        printf("\nError: No ingreso un valor numerico, favor de intentarlo de nuevo\n\n");
                }
                flag = 1;
                while(flag || (c[0] != 'q')){
                    numLines = linesFile(argv[1]);
                    datos = (int **) malloc(sizeof(int *) * numLines);
                    for(i = 0; i < numLines; i++){
                        datos[i] = (int *) malloc(sizeof(int)*3);
                    }
                    readFile(argv[1],datos,numLines,3);
                    printDataFile(datos,numLines,3);

                    for(i = 0; i < 3; i++){
                        if( i != 2)
                            printf("Ingrese el valor de A%d, \'q\' para regresar al menu principal: ",i);
                        else
                            printf("Ingrese el valor del umbral, \'q\' para regresar al menu principal: ");
                        vaciar_buffer();
                        fgets(c,3,stdin);

                        if(isdigit(c[0]) || (c[0] == 'q') || (isdigit(c[1]))){
                            if(c[0] != 'q')
                                inputs[i] = atoi(c);
                            else
                                i = 3;      //para salirse del ciclo for
                            flag = 0;
                        }else{
                            printf("\nError: No ingreso un valor numerico, favor de intentarlo de nuevo\n\n");
				            flag = 1;
                            i = 3;          //para salirse del ciclo for
                            c[0] = 'q';
                        }
                    }
                    if(c[0] != 'q'){
                        clase = knnR(datos,numLines,3,inputs);
                        if(clase >= 0){
                            printf("\nEl dato [%d,%d] pertenece a la clase %d\n",inputs[0],inputs[1],clase);
                            writeFile(argv[1],inputs[0],inputs[1],clase);
                        }else{
                            if(clase == -1)
                                printf("\nSin clasificación\n");
                        }
                    }
                    printf("\n");
                    for(i = 0; i < numLines; i++)
                        free(datos[i]);
        
                    free(datos);
                }
                printf("\nPresione la tecla enter para continuar...");
                vaciar_buffer();
                getchar();
                opc = 0;
                break;
                
            case '2':  
				flag = 1;
				while(flag)
                {
                    printf("\nIngrese el valor de k: ");
                    vaciar_buffer();
                    fgets(c,3,stdin);

                    if(isdigit(c[0])){
                        inputs[3] = atoi(c);
                        flag = 0;
                    }
                    else
                        printf("\nError: No ingreso un valor numerico, favor de intentarlo de nuevo\n\n");
                }
                flag = 1;
                while(flag || (c[0] != 'q')){
                    numLines = linesFile(argv[1]);
                    datos = (int **) malloc(sizeof(int *) * numLines);
                    for(i = 0; i < numLines; i++){
                        datos[i] = (int *) malloc(sizeof(int)*3);
                    }
                    readFile(argv[1],datos,numLines,3);
                    printDataFile(datos,numLines,3);

                    for(i = 0; i < 2; i++){
                        printf("Ingrese el valor de A%d, \'q\' para regresar al menu principal: ",i);
                        vaciar_buffer();
                        fgets(c,3,stdin);

                        if(isdigit(c[0]) || (c[0] == 'q') || (isdigit(c[1]))){
                            if(c[0] != 'q')
                                inputs[i] = atoi(c);
                            else
                                i = 3;      //para salirse del ciclo for
                            flag = 0;
                        }else{
                            printf("\nError: No ingreso un valor numerico, favor de intentarlo de nuevo\n\n");
				            flag = 1;
                            i = 3;          //para salirse del ciclo for
                            c[0] = 'q';
                        }
                    }
                    inputs[2] = 0;               //umbral = 0
                    if(c[0] != 'q'){
                        clase = knndM(datos,numLines,3,inputs);
                        if(clase >= 0){
                            printf("\nEl dato [%d,%d] pertenece a la clase %d\n",inputs[0],inputs[1],clase);
                            writeFile(argv[1],inputs[0],inputs[1],clase);
                        }else{
                            if(clase == -1)
                                printf("\nSin clasificación\n");
                        }
                    }
                    printf("\n");
                    for(i = 0; i < numLines; i++)
                        free(datos[i]);
        
                    free(datos);
                }
                printf("\nPresione la tecla enter para continuar...");
                vaciar_buffer();
                getchar();
                opc = 0;
                break;
            
            case '3':
                printf("\nBye!!! :3\n");
                exit(1);
                break;
            
            default:
                printf("Error. Opcion no valida, intentelo de nuevo. ");
                printf("Presione la tecla enter para continuar...");
                vaciar_buffer();
                getchar();
                opc = 0;
                break;
        }
    }while(opc == 0);
	
	return 0;
}

void vaciar_buffer()
{
    int fdflags;
    fdflags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, fdflags | O_NONBLOCK);
    while (getchar()!=EOF);
    fcntl(STDIN_FILENO, F_SETFL, fdflags);
}

void printDataFile(int **m, int rows, int columns)
{
    printf("\ndatos leidos del archivo:\n");
    printf("\nx0 x1  C\n");
    printf("---------\n");
    printMatriz(m,rows,columns);
    printf("\n");
}
