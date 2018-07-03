//
//  Contenedores.h
//  Tarea 4 infix to posfix
//
//  Created by Mauricio Durán on 28/06/18.
//  Copyright © 2018 Mauricio Durán. All rights reserved.
//

#ifndef Contenedores_h
#define Contenedores_h

typedef void * Type;

typedef enum {False, True} Boolean;

/**********************************
              STACK
 **********************************/

typedef struct strStack * Stack;

Stack createStack(void);

void destroyStack(Stack who);

Boolean isEmptyStack(Stack who);

Boolean pushStack(Stack who, Type data);

Type popStack(Stack who);

Type topStack(Stack who);


/**********************************
            Queue
 **********************************/

typedef struct strQueue * Queue;

Queue createQueue(void);

Boolean isEmptyQueue(Queue who);

int sizeQueue(Queue who);

Type peekQueue(Queue who);

void offerQueue(Queue who, Type data);

Type pullQueue(Queue who);

void destroyQueue(Queue who);


#endif /* Contenedores_h */
