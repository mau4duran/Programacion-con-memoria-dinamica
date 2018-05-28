#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

typedef struct{
	char nombre[15];
	float calificacion;
} Profesor;

float averageArray(Profesor * prof, char * nombre, int w); //se modificaron los parametros

void readArray(Profesor * prof, int num);

void mergeArrays(Profesor * prof1, int num, Profesor * prof2, int num2, Profesor * prof3, int num3);

void sortArray(Profesor * prof, int num);

void printArray(Profesor * prof , int num);


int main(void){
	Profesor arr1[20];  //Primer arreglo
	Profesor arr2[20];  //Segundo arreglo
	Profesor arrF[40];  //Arreglo final, con elementos fusionados y ordenados

	int n1, n2; //Longitud de los arreglos

    printf("Numero de profes: ");
    scanf("%d",&n1);

    readArray(arr1, n1); //leer el primer arreglo

    printf("Numero de profes: ");
    scanf("%d",&n2);

    readArray(arr2, n2); //leer el segundo arreglo

    mergeArrays(arr1, n1, arr2, n2, arrF, n1+n2);  //Fusionar los dos arreglos en un tercer arreglo

    sortArray(arrF, n1+n2);  //Ordenar los elementos del tercer arreglo, recuerde que pueden
    //existir profesores repetidos

    printf("\n\n\n");
    printArray(arrF, n1+n2);   //Imprimir el resultado final

    return EXIT_SUCCESS;
}

float averageArray(Profesor * prof , char * nombre, int w){
    float suma = 0;
    float elementos = 0;

    for (int i = 0; i < w; i++) {
        if (strcmp((prof+i)->nombre,nombre)==0) {
            suma+=(prof+i)->calificacion;
            elementos++;
        }
    }

    return suma/elementos;

}

void readArray(Profesor * prof, int num){
    for (int i = 0; i < num; i++) {
        char nombre[15];
        scanf("%s", &nombre);
        strcpy(prof -> nombre, nombre);

        float calif;
        scanf("%f", &calif);

        prof -> calificacion = calif;

        prof ++;
    }
}

void mergeArrays(Profesor * prof1, int num, Profesor * prof2, int num2, Profesor * profF, int num3){
    int condition = 0;

	int w = 0;

    Profesor temporal[40];
    Profesor * temp = temporal;



    for (int i = 0; i < num; i++) {
		condition = 0;
		for (int k = 0; k < i; k++) {
            if (strcmp((prof1+i)->nombre,(prof1+k)->nombre)==0) {
            	condition = 1;
            }
        }

        (temp+i)->calificacion = (prof1+i)->calificacion;
        strcpy((temp+i)->nombre,(prof1+i)->nombre);

		if (condition == 0) {
			//(profF+w)->calificacion = (prof1+i)->calificacion;
			strcpy((profF+w)->nombre,(prof1+i)->nombre);
			w++;
		}

	}

	for (int i = num; i < num+num2; i++) {
		condition = 0;
		for (int k = 0; k < i; k++) {
			if (strcmp((prof2+i-num)->nombre,(profF+k)->nombre)==0) {
				condition = 1;
			}
		}

        (temp+i)->calificacion = (prof2+i-num)->calificacion;
        strcpy((temp+i)->nombre,(prof2+i-num)->nombre);

		if (condition == 0) {
			//(profF+w)->calificacion = (prof2+i-num)->calificacion;
			strcpy((profF+w)->nombre,(prof2+i-num)->nombre);
			w++;
		}

	}

    for (int i = 0; i < w; i++) {
        (profF+i)->calificacion = averageArray(temp,(temp+i)->nombre,num+num2);
    }



}

void sortArray(Profesor * prof, int num){
    Profesor swap;
    for (int i = 0; i < num; i++) {
        for (int k = 0; k < num-1; k++) {
            if ((prof+k)->calificacion<(prof+k+1)->calificacion) {
                swap.calificacion = (prof+k)->calificacion;
                strcpy(swap.nombre, (prof+k)->nombre);

                (prof+k)->calificacion = (prof+k+1)->calificacion;
                strcpy((prof+k)->nombre, (prof+k+1)->nombre);

                (prof+k+1)->calificacion = swap.calificacion;
                strcpy((prof+k+1)->nombre, swap.nombre);

            }
        }
    }
}

void printArray(Profesor * prof, int num){
    for (int i = 0; i < num; i++) {
		if (prof->calificacion != 0.0) {
			printf("%s\t%.1f\n",prof->nombre, prof->calificacion);
		}
        prof++;
    }
}
