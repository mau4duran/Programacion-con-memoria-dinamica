//
//  Stack.c
//  Tarea 4 Balanceo Parentesis
//
//  Created by Mauricio Durán on 27/06/18.
//  Copyright © 2018 Mauricio Durán. All rights reserved.
//

#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>


struct strNode{
    Type data;
    struct strNode * prior;
};

typedef struct strNode * Node;

struct strStack{
    Node top;
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
    while (!isEmpty(who)) {
        pop(who);
    }
    free(who);
}

Boolean isEmpty(Stack who){
    if (who->size == 0) {
        return True;
    }
    return False;
}

Boolean push(Stack who, Type data){
    Node new = (Node) malloc(sizeof(struct strNode));
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

Type pop(Stack who){
    if (who->top == NULL){
        return NULL;
    }
    Node temp = who->top;
    Type dato = who->top->data;
    
    who->top = who->top->prior;
    who->size--;
    free(temp);
    return dato;
}

Type top(Stack who){
    if (who->top==NULL) {
        return NULL;
    }
    return who->top->data;
}
