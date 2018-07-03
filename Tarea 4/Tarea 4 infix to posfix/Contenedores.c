//
//  Contenedores.c
//  Tarea 4 infix to posfix
//
//  Created by Mauricio Durán on 28/06/18.
//  Copyright © 2018 Mauricio Durán. All rights reserved.
//

#include "Contenedores.h"
#include <stdio.h>
#include <stdlib.h>

/**********************************
               Stack
 **********************************/

struct strNodeStack{
    Type data;
    struct strNodeStack * prior;
};

typedef struct strNodeStack * NodeStack;

struct strStack{
    NodeStack top;
    int size;
};

Stack createStack(){
    Stack new = (Stack) malloc(sizeof(struct strStack));
    if (new == NULL) {
        return NULL;
    }
    
    new->size=0;
    new->top=NULL;
    return new;
}

void destroyStack(Stack who){
    while (!isEmptyStack(who)) {
        popStack(who);
    }
    free(who);
}

Boolean isEmptyStack(Stack who){
    if (who->size == 0) {
        return True;
    }
    return False;
}

Boolean pushStack(Stack who, Type data){
    NodeStack new = (NodeStack) malloc(sizeof(struct strNodeStack));
    Type datoT;
    datoT = data;
    
    if (new == NULL) {
        return False;
    }
    new->data = datoT;
    new->prior = who->top;
    who->top = new;
    who->size ++;
    return True;
    
};

Type popStack(Stack who){
    if (who->top == NULL){
        return NULL;
    }
    NodeStack temp = who->top;
    Type dato = who->top->data;
    
    who->top = who->top->prior;
    who->size--;
    free(temp);
    return dato;
}

Type topStack(Stack who){
    if (who->top==NULL) {
        return NULL;
    }
    return who->top->data;
}

/**********************************
              Queue
 **********************************/
struct strNodeQueue{
    struct strNodeQueue * next;
    Type data;
};

typedef struct strNodeQueue * NodeQueue;

struct strQueue{
    int size;
    NodeQueue first;
    NodeQueue last;
};

Queue createQueue(){
    Queue new = (Queue) malloc(sizeof(struct strQueue));
    new->size = 0;
    new->first = NULL;
    new->last = NULL;
    return new;
}

Boolean isEmptyQueue(Queue who){
    if (who->size == 0) {
        return True;
    }
    return False;
}

int sizeQueue(Queue who){
        return who->size;
}

Type peekQueue(Queue who){
    if (!isEmptyQueue(who)) {
        return who->first->data;
    }
    return NULL;
}

void offerQueue(Queue who, Type data){
    NodeQueue new = (NodeQueue)malloc(sizeof(struct strQueue));
    new->data = data;
    new->next=NULL;
    if (isEmptyQueue(who)) {
        who->first = new;
        who->last = new;
    }else{
        who->last->next = new;
        who->last = new;
    }
    who->size++;
}

Type pullQueue(Queue who){
    if (isEmptyQueue(who)) {
        return NULL;
    }
    NodeQueue temp = who->first;
    Type tempData = who->first->data;
    who->first = who->first->next;
    if (isEmptyQueue(who)) {
        who->last = NULL;
    }
    free(temp);
    who->size--;
    return tempData;
}

void destroyQueue(Queue who){
    while (!isEmptyQueue(who)) {
        pullQueue(who);
    }
    free(who);
}



