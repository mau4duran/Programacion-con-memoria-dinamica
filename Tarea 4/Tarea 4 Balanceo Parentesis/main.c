//
//  main.c
//  Tarea 4 Balanceo Parentesis
//
//  Created by Mauricio Durán on 27/06/18.
//  Copyright © 2018 Mauricio Durán. All rights reserved.
//
#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>

Boolean balancedBrackets(char *exp);

int main()
{
    char string[20];
    printf("Inserta cadena\n");
    scanf("%s", string);
    if (balancedBrackets(string)) {
        printf("correcto\n");
    }else{
        printf("incorrecto\n");
    }
    return EXIT_SUCCESS;
}

Boolean balancedBrackets(char *exp){
    Stack stack = createStack();
    char * temporal = NULL;
    int i = 0;
    while (exp[i]!='\0') {
        if (exp[i]=='(' || exp[i]=='[' || exp[i]=='{') {
            push(stack, &exp[i]);
        }
        if (exp[i]==')' || exp[i]==']'|| exp[i]=='}') {
            if (isEmpty(stack)) {
                return False;
            }
            temporal = (char *) top(stack);
            if ((exp[i]==')' && *temporal != '(') || (exp[i]==']' && *temporal != '[') || (exp[i]=='}' && *temporal != '{') ) {
                return False;
            }
            
            pop(stack);
        }
        i++;
    }
    return True;
}
