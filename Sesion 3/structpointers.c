#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct{
    unsigned int expediente;
    char nombre[50];
    unsigned int carrera;
    unsigned short edad;
}Alumno;

void limpiar(Alumno * puntero, int x) {
        puntero += x;
        strcpy(puntero -> nombre, " ");
        puntero -> expediente = 0;
        puntero -> carrera = 0;
        puntero -> edad = 0;

}

void eliminar(Alumno * puntero) {
        int dato;
        printf("Escriba el expediente del alumno a eliminar: ");
        scanf("%d",&dato);

        for (int i = 0; i < 20; i++) {
            if (puntero -> expediente == dato) {
                strcpy(puntero -> nombre, " ");
                puntero -> expediente = 0;
                puntero -> carrera = 0;
                puntero -> edad = 0;
            }
            puntero++;
        }

}

void registrar(Alumno * puntero){
    static int x = 0;
    unsigned int expp;
    char name[50];
    unsigned int carr;
    unsigned short age;

    puntero+=x;

    printf("\nEscriba nombre: ");
    gets(name);
    strcpy(puntero -> nombre, name);

    printf("Escriba expediente: ");
    scanf("%d", &expp);
    puntero -> expediente = expp;

    printf("Escriba Carrera (numero): ");
    scanf("%d", &carr);
    puntero -> carrera = carr;

    printf("Escriba Edad: ");
    scanf("%hd", &age);
    puntero -> edad = age;

    x++;
    getchar();

}

void imprimirDatos(Alumno * puntero){
    printf("\n\n");
    for (int k = 0; k < 20; k++) {
        if (strcmp(puntero -> nombre, " ")) {
            printf("Nombre: %s\n", puntero -> nombre);
            printf("Expediente: %d\n", puntero -> expediente);
            printf("Carrera: %d\n", puntero -> carrera);
            printf("Edad: %d\n", puntero -> edad);
            printf("\n\n");
        }
        puntero ++;
    }
}

void buscarExpediente(Alumno * puntero){
    int dato;
    printf("Expediente: ");
    scanf("%d",&dato);

    for (int i = 0; i < 20; i++) {
        if (puntero -> expediente == dato) {
            printf("Nombre: %s\n", puntero -> nombre);
            printf("Carrera: %d\n", puntero -> carrera);
            printf("Edad: %d\n", puntero -> edad);
        }
        puntero++;
    }

    printf("\n\n\n");
}

void buscarEdad(Alumno * puntero){
    int dato;
    printf("Edad: ");
    scanf("%d",&dato);
    printf("\n");

    for (int i = 0; i < 20; i++) {
        if (puntero -> edad == dato) {
            printf("Nombre: %s\n", puntero -> nombre);
            printf("Expediente: %d\n", puntero -> expediente);
            printf("Carrera: %d\n", puntero -> carrera);
            printf("Edad: %d\n", puntero -> edad);
            printf("\n\n");
        }
        puntero++;
    }

    printf("\n\n\n");
}

void buscar(Alumno * puntero) {
    int opt;
    printf("Como quieres buscar al alumno?\n1)Por Expediente\n2)Por Edad\n");
    scanf("%d",&opt);
    printf("\n\n");
    switch (opt) {
        case 1: buscarExpediente(puntero); break;
        case 2: buscarEdad(puntero); break;
        default: printf("\nError. Intente de nuevo");
    }
}



int main(void) {

    Alumno static alumnos[20];
    char nombre[50];
    int opcion;
    int condicion;
    static Alumno * palumnos = alumnos;

    for (int i = 0; i < 20; i++) {
            limpiar(palumnos, i);
    }


    while (1) {

        printf("\t\tMenu\n");
        printf("1) Registrar nuevo alumno\n");
        printf("2) Imprimir datos\n");
        printf("3) Eliminar alumno\n");
        printf("4) Buscar alumno\n\t- Por expediente\n\t- Por edad\n");
        printf("5) Salir\n");


    printf("Escriba opcion (numero):\n ");
    scanf("%d", &opcion);

    if(opcion == 5 ){
        break;
    }

    switch (opcion) {
        case 1: //Registrar
        getchar();
        registrar(palumnos);
        break;

        case 2://imprimir
        imprimirDatos(palumnos);
        break;

        case 3:
        eliminar(palumnos);
        break;

        case 4:
        buscar(palumnos);
        break;

        default: printf("Error, inserte una opcion válida\n" );

        }

    }




	return EXIT_SUCCESS;
}
