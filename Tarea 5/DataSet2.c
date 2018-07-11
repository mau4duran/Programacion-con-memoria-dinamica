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
    char  idTweetRT[19];
    Bool esRetweet;
};

typedef struct strElemento * Elemento;

void * cloneElemento(void* Persona);

int cmpElemento(void* Persona, void* Persona2 );

void  printElemento(void* Graph);

int main(){
    FILE * f = fopen("RETWEETS.csv", "r");
    Graph grafo = graph_create((CMP)cmpElemento, (Clone) cloneElemento, (Print) printElemento);
    char tweet [19];
    char retweet [19];


    struct strElemento strTweet, strRetweet;

    while (fscanf(f, "%[^,], %[^\n\r]",retweet,tweet)!=EOF) {
        fgetc(f);
        fgetc(f);
        strRetweet.esRetweet = true;
        strcpy(strRetweet.idTweetRT,  retweet);

        strTweet.esRetweet = false;
        strcpy(strTweet.idTweetRT,  tweet);
        graph_addVertex(grafo, &strTweet);
        graph_addVertex(grafo, &strRetweet);

        graph_addEdge(grafo, tweet, retweet);


    }

    if (graph_hasEdge(grafo, tweet, retweet)) {
        printf("true");
    }else{
        printf("false");
    }
    fclose(f);




    return 0;
}


void * cloneElemento(void* elemento){
    Elemento temp = malloc(sizeof(struct strElemento));
    strcpy(temp->idTweetRT, (char *)((Elemento) elemento)->idTweetRT);
    temp->esRetweet= (Bool)((Elemento) elemento)->esRetweet;
    return temp;
}

int cmpElemento(void* elemento, void* elemento2){
    if (elemento==NULL || elemento2==NULL) {
        return -1;
    }
    return strcmp((char *)((Elemento) elemento)->idTweetRT,(char *)((Elemento) elemento2)->idTweetRT);

}

void  printElemento(void* elemento){

    if ((Bool)((Elemento) elemento)->esRetweet) {
        printf("Retweet\nID: %s\n", (char *)((Elemento) elemento)->idTweetRT);
    }else{
        printf("Tweet\nID: %s\n", (char *)((Elemento) elemento)->idTweetRT);
    }
}
