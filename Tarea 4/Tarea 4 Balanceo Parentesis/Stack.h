//
//  Stack.h
//  Tarea 4 Balanceo Parentesis
//
//  Created by Mauricio Durán on 27/06/18.
//  Copyright © 2018 Mauricio Durán. All rights reserved.
//

#ifndef Stack_h
#define Stack_h

typedef void * Type;

typedef enum {False, True} Boolean;

/**********************************
            STACK
**********************************/

typedef struct strStack * Stack;

Stack createStack(void);

void destroyStack(Stack who);

Boolean isEmpty(Stack who);

Boolean push(Stack who, Type data);

Type pop(Stack who);

Type top(Stack who);

#endif /* Stack_h */
