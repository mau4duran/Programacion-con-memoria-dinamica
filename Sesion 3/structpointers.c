#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct{
    unsigned int expediente;
    char* nombre;
    unsigned int carrera;
    unsigned short edad;
}Alumno;

void registrar(Alumno * puntero){
    static int x = 0;
    unsigned int expp;
    char* name;
    unsigned int carr;
    unsigned short age;

    puntero+=x;

    printf("\nEscriba nombre: ");
    gets(name);
    //8puntero -> nombre = name;

    printf("Escriba expediente: ");
    scanf("%d", &expp);
    puntero -> expediente = expp;

    printf("\nEscriba Carrera (numero): ");
    scanf("%d", &carr);
    puntero -> carrera = carr;

    printf("\nEscriba Edad: ");
    scanf("%hd", &age);
    puntero -> edad = age;

    x++;

}

void imprimirDatos(){
    //for (size_t i = 0; i < count; i++) {
        /* code */
    //}

}


void eliminar(){

}

void buscarExpediente(){

}

void buscarEdad(){


}


int main(void) {
    Alumno static alumnos[20];

    static Alumno * palumnos = alumnos;
    //while (1) {
        printf("\t\tMenu\n");
        printf("1) Registrar nuevo alumno\n");
        printf("2) Imprimir datos\n");
        printf("3) Eliminar alumno\n");
        printf("4) Buscar alumno\n\t- Por expediente\n\t- Por edad\n");
        printf("5) Salir\n");
    //}


    registrar(palumnos);
    registrar(palumnos);
    registrar(palumnos);

    printf("%d\n%d\n%d", alumnos[0].expediente,alumnos[1].expediente, alumnos[2].expediente);


	return EXIT_SUCCESS;
}
