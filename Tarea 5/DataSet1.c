/*
 * useList.c
 *
 *  Created on: 12/11/2017
 *      Author: administrador
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

struct strElemento{
    char  NombreOTitulo[100];
    char  year[5];
    char  categoriaEdadOTagline[300];
    Bool esPersona;
};

typedef struct strElemento * Elemento;



//struct strMovie{
//    char titulo[100];
//    char estreno[5];
//    char tagline[100];
//    Bool esPersona;
//};

void * clonePersona(void* Persona);

int cmpPersona(void* Persona, void* Persona2 );

void  printPersona(void* Graph);

int main(){
    FILE * f = fopen("vertex_person.csv", "r");
    Graph grafo = graph_create((CMP)cmpPersona, (Clone) clonePersona, (Print) printPersona);
    char nombre [100];
    char pelicula [100];
    char year [5];
    char categoriaEdad [300];

    //int w = 0;

    while (fscanf(f, "%[^,],%[^,],%[^,\n\r]",nombre,year,categoriaEdad )!=EOF) {
        fgetc(f);
            fgetc(f);

        struct strElemento entrada;
        entrada.esPersona = true;
        strcpy(entrada.NombreOTitulo, nombre);
        strcpy(entrada.year, year);
        strcpy(entrada.categoriaEdadOTagline, categoriaEdad);
        graph_addVertex(grafo, &entrada);
    }

    fclose(f);

    //Peliculas

    f = fopen("vertex_movies.csv", "r");

    while (fscanf(f, "%[^,],%[^,],%[^,\n\r]",nombre,year,categoriaEdad )!=EOF) {
        fgetc(f);
        fgetc(f);
        struct strElemento entrada;
        entrada.esPersona = false;
        strcpy(entrada.NombreOTitulo, nombre);
        strcpy(entrada.year, year);
        strcpy(entrada.categoriaEdadOTagline, categoriaEdad);
        graph_addVertex(grafo, &entrada);
    }

    //graph_print(grafo);

    fclose(f);

    f=fopen("edges_PersonMovies.csv", "r");


    Elemento actor, movie;
    while (fscanf(f, "%[^,], %[^\n\r]",nombre,pelicula)!=EOF) {
        fgetc(f);
        fgetc(f);
        Elemento acto = malloc(sizeof(struct strElemento));
        strcpy(acto->NombreOTitulo, nombre);

        Elemento peli = malloc(sizeof(struct strElemento));
        strcpy(peli->NombreOTitulo, nombre);

        actor = returnVertex(grafo, nombre);
        movie = returnVertex(grafo, pelicula);

        graph_addEdge(grafo, actor, movie);



    }

    actor = returnVertex(grafo, "Aaron Sorkin");
    movie = returnVertex(grafo, "A Few Good Men");



    //printf("%lu",graph_edgeCount(grafo));
    //printf("\n\n%lu", graph_edgeCount(grafo));



    return 0;
}


void * clonePersona(void* Persona){
    Elemento temp = malloc(sizeof(struct strElemento));
    strcpy(temp->NombreOTitulo, (char *)((Elemento) Persona)->NombreOTitulo);
    strcpy(temp->year,(char *)((Elemento) Persona)->year);
    strcpy(temp->categoriaEdadOTagline, (char *)((Elemento) Persona)->categoriaEdadOTagline);
    temp->esPersona = (Bool)((Elemento) Persona)->esPersona;
    return temp;
}

int cmpPersona(void* Persona, void* Persona2){
    if (Persona==NULL || Persona2==NULL) {
        return -1;
    }
    return strcmp((char *)((Elemento) Persona)->NombreOTitulo,(char *)((Elemento) Persona2)->NombreOTitulo);

}

void  printPersona(void* Graph){
    if (Graph!=NULL) {
        static int status = 1;
        if ((Bool)((Elemento) Graph)->esPersona) {

            if (status == 1 && (Bool)((Elemento) Graph)->esPersona){
                printf("--------------------\n");
                printf("|      Actores      |\n");
                printf("--------------------\n\n");
                status = 0;
            }

            printf("Nombre: %s\nFecha de Nacimiento: %s\nCategoria de Edad: %s\n\n", (char *)((Elemento) Graph)->NombreOTitulo,(char *)((Elemento) Graph)->year,(char *)((Elemento) Graph)->categoriaEdadOTagline);
        }else{
            if (status == 0 && !(Bool)((Elemento) Graph)->esPersona) {
                printf("\n\n\n\n-----------------------\n");
                printf("|      Peliculas      |\n");
                printf("-----------------------\n\n");
                status = 1;
            }
            printf("Titulo: %s\nEstreno: %s\nTagline: %s\n\n", (char *)((Elemento) Graph)->NombreOTitulo,(char *)((Elemento) Graph)->year,(char *)((Elemento) Graph)->categoriaEdadOTagline);
        }
    }


}
