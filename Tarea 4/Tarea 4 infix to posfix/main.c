//
//  main.c
//  Tarea 4 infix to posfix
//
//  Created by Mauricio Durán on 28/06/18.
//  Copyright © 2018 Mauricio Durán. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Contenedores.h"

char * infixToPosfix(char * exp);
int valueOfOperator(char * operator);
Boolean hasHigherPrecedence(char* top, char *operator);

int main(int argc, const char * argv[]) {
    // insert code here...
    char * string = infixToPosfix("(A + B) * C + D / (E + F * G) - H");
    printf("%s\n", string);
    return 0;
}

char * infixToPosfix(char * exp){
    int n = 1;
    int condition = 0;
    char * new = (char *) malloc(sizeof(char)*n);
    char * temp = NULL;
    char * tope = NULL;
    char * Checarespacio = NULL;
    char * espacio = (char *) malloc(sizeof(char));
    * espacio = ' ';
    
    Stack pila = createStack();
    Queue resultante = createQueue();
    Queue intermedia = createQueue() ;
    
    int i = 0;
    while (exp[i]!='\0') {
        temp = (char *) malloc(sizeof(char));
        *temp = *(exp+i);
        offerQueue(intermedia, temp);
        
        i++;
    }
    
    temp = (char *) malloc(sizeof(char));
    
    while (!isEmptyQueue(intermedia)) {
        condition = 0;
        temp = pullQueue(intermedia);
        
        if (*temp == ' '){
            continue;
        }
        if (*temp != '+' && *temp != '-' && *temp != '*' && *temp != '/' && *temp != '(' && *temp != ')') {
            offerQueue(resultante, temp);
            Checarespacio = peekQueue(intermedia);
            if (Checarespacio!= NULL && (*Checarespacio < 48 || *Checarespacio > 57) && (*Checarespacio < 65 || *Checarespacio > 90) && (*Checarespacio < 97 || *Checarespacio > 122) ) {
                offerQueue(resultante, espacio);
                condition = 1;
            }
        } else if (*temp=='('){
            pushStack(pila, temp);
        }else if( *temp == '+' || *temp == '-' || *temp == '*' || *temp == '/'){
            tope = topStack(pila);
            while (!isEmptyStack(pila) && *tope!='(') {
                if (hasHigherPrecedence(tope, temp)) {
                    tope = popStack(pila);
                    offerQueue(resultante, tope);
                    tope = topStack(pila);
                }else{
                    break;
                }
            }
            pushStack(pila, temp);
        }else {
            //Caso en el que es )
            tope = topStack(pila);
            while (!isEmptyStack(pila)&&* tope !='(') {
                tope = popStack(pila);
                offerQueue(resultante, tope);
                tope = topStack(pila);
            }
            if (!isEmptyStack(pila)&&* tope =='(') {
                popStack(pila);
            }
        }
    }
    
    temp = peekQueue(resultante);
    
    if (condition==1 || (*temp>=65 && *temp<=90) || (*temp>=97 && *temp<=122) || (*temp>=48 && *temp<=57)) {
        offerQueue(resultante, espacio);
    }
    while (!isEmptyStack(pila)) {
        tope = popStack(pila);
        offerQueue(resultante, tope);
    }
    
    
    while (!isEmptyStack(pila)) {
        tope = popStack(pila);
        offerQueue(resultante, tope);
    }
    
    char * concatenador = NULL;
    
    while (!isEmptyQueue(resultante)) {
        concatenador = pullQueue(resultante);
        if (n!=1) {
            n++;
            temp = realloc(new, sizeof(char)*n);
            if (temp!=NULL) {
                new = temp;
                
            }
            
        }

        n++;
        temp = realloc(new, sizeof(char)*n);
        if (temp!=NULL) {
            new = temp;
            strcat(new,  concatenador);
            if (*concatenador == '+' || *concatenador == '-' || *concatenador == '*' || *concatenador == '/') {
                strcat(new,  " ");
            }
        }
        
    }
    
    return new;
}

Boolean hasHigherPrecedence(char* top, char *operator){

    return valueOfOperator(operator)<=valueOfOperator(top);
}

int valueOfOperator(char * operator){
    if (*operator == '/' || * operator == '*') {
        return 2;
    }
    return 1;
}
