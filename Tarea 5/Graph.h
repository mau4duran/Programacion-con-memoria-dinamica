//
//  Graph.h
//  Listas
//
//  Created by Mauricio Durán on 04/07/18.
//  Copyright © 2018 Mauricio Durán. All rights reserved.
//

#ifndef Graph_h
#define Graph_h

#include "List.h"

typedef struct strGraph * Graph;

typedef int (*CMP)(void *, void *);
typedef Type (*Clone) (Type);
typedef void (* Print)(Type);

Graph graph_create(CMP comparator, Clone clone, Print print);

void graph_destroy(Graph who);

Bool graph_addVertex(Graph who, Type data);

Bool graph_addEdge(Graph g, Type source, Type sink);

unsigned long graph_vertexCount(Graph who);

unsigned long graph_edgeCount(Graph who);

unsigned long graph_outDegree(Graph who, Type source);

Bool graph_hasEdge(Graph who, Type source, Type sink);

void graph_print(Graph who);

Type returnVertex(Graph who,Type source);

#endif /* Graph_h */
