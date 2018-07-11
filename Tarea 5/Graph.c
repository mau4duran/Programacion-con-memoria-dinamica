////  Graph.c
////  Listas
////
////  Created by Mauricio Durán, Edgar Francisco Medina, Anahí Santana on 04/07/18.
////  Copyright © 2018 Mauricio Durán. All rights reserved.
//
//#include "Graph.h"
//#include "List.h"
//#include <stdio.h>
//#include <stdlib.h>
//
//struct strVertex{
//    int identificador;
//    Type data;
//    List sucesores;
//};
//
//typedef struct strVertex * Vertex;
//
//struct strGraph{
//    Vertex * arreglo;
//    int numVertices;
//    int numAristas;
//    CMP comparator;
//    Clone clonar;
//    Print imprimir;
//};
//
//Vertex vertex_create(Type data, int id){
//    Vertex new = (Vertex)malloc(sizeof(struct strVertex));
//    new->identificador = id;
//    new->data = data;
//    new->sucesores = list_create();
//    return new;
//}
//
//Graph graph_create(CMP comparator, Clone clone, Print print){
//    Graph new = (Graph) malloc(sizeof(struct strGraph));
//    new->arreglo = (Vertex *) malloc(sizeof(Vertex));
//    new->numAristas = 0;
//    new->numVertices = 0;
//    new->comparator = comparator;
//    new->clonar =clone;
//    new->imprimir = print;
//    return new;
//}
//
//void graph_destroy(Graph who){
//    int i;
//    if (who!=NULL) {
//        for (i=0; i<who->numVertices; i++) {
//            list_destroy((who->arreglo[i])->sucesores);
//        }
//        free(who->arreglo);
//        free(who);
//    }
//}
//
//Bool graph_addVertex(Graph who, Type data) {
//    int status;
//    for (int i=0; i<who->numVertices; i++) {
//        status = who->comparator(data, who->arreglo[i]->data);
//        if (status == 0) {
//            return false;
//        }
//    }
//    static int id = 1;
//    Vertex new = vertex_create(who->clonar(data), id);
//    who->arreglo[id-1] = new;
//    Vertex * temp = NULL;
//    id++;
//    temp = realloc(who->arreglo, sizeof(Vertex)*(id));
//    if (temp!=NULL) {
//        who->arreglo = temp;
//        who->numVertices++;
//        return true;
//    }
//    id--;
//    return false;
//}
//
//Bool graph_addEdge(Graph who, Type source, Type sink){
//    Bool hasAnEdge;
//    hasAnEdge = graph_hasEdge(who, source, sink);
//    if(!hasAnEdge){
//        int status;
//        for (int i=0; i<who->numVertices; i++) {
//                status = who->comparator(source, who->arreglo[i]->data);
//                if (status==0) {
//
//                    list_add(who->arreglo[i]->sucesores, sink);
//
//                    //printf("%p %p\n\n", sink, list_get(who->arreglo[i]->sucesores, list_size(who->arreglo[i]->sucesores)-1));
//                    //who->imprimir(list_get(who->arreglo[i]->sucesores, list_size(who->arreglo[i]->sucesores)-1));/////
//                    who->numAristas++;
//                    return true;
//                }
//        }
//    }
//    return false;
//
//}
//
//unsigned long graph_vertexCount(Graph who){
//    return who->numVertices;
//}
//
//unsigned long graph_edgeCount(Graph who){
//    return who->numAristas;
//}
//
//unsigned long graph_outDegree(Graph who, Type source){
//    int status;
//
//    for (int i = 0; i<who->numVertices;i++){
//        status = who->comparator(source, who->arreglo[i]->data);
//        if (status == 0) {
//            return list_size(who->arreglo[i]->sucesores);
//        }
//    }
//    return -1;
//}
//
//Bool graph_hasEdge(Graph who, Type source, Type sink){
//    int status;
//    int status2;
//    for (int i=0; i<who->numVertices; i++) {
//        status = who->comparator(source, who->arreglo[i]->data);
//        if (status==0) {
//            for (int k=0; k<list_size(who->arreglo[i]->sucesores); k++) {
//                status2 = who->comparator(list_get(who->arreglo[i]->sucesores, k), sink);
//
//                if (status2==0) {
//                    return true;
//                }
//            }
//            break;
//        }
//    }
//    return false;
//}
//
//void graph_print(Graph who){
//    for (int i=0; i<who->numVertices; i++) {
//        who->imprimir(who->arreglo[i]->data);
//    }
//}
//
//Type returnVertex(Graph who,Type source){
//    int status;
//    for (int i=0; i<who->numVertices; i++) {
//        status = who->comparator(source, who->arreglo[i]->data);
//        if (status==0) {
//            return who->arreglo[i]->data;
//                }
//            }
//    return NULL;
//}
//
//

//  Graph.c
//  Listas
//
//  Created by Mauricio Durán, Edgar Francisco Medina, Anahí Santana on 04/07/18.
//  Copyright © 2018 Mauricio Durán. All rights reserved.

#include "Graph.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>

struct strVertex{
    int identificador;
    Type data;
    List sucesores;
};

typedef struct strVertex * Vertex;

struct strGraph{
    Vertex * arreglo;
    int numVertices;
    int numAristas;
    CMP comparator;
    Clone clonar;
    Print imprimir;
};

Vertex vertex_create(Type data, int id){
    Vertex new = (Vertex)malloc(sizeof(struct strVertex));
    new->identificador = id;
    new->data = data;
    new->sucesores = list_create();
    return new;
}

Graph graph_create(CMP comparator, Clone clone, Print print){
    Graph new = (Graph) malloc(sizeof(struct strGraph));
    new->arreglo = (Vertex *) malloc(sizeof(Vertex));
    new->numAristas = 0;
    new->numVertices = 0;
    new->comparator = comparator;
    new->clonar =clone;
    new->imprimir = print;
    return new;
}

void graph_destroy(Graph who){
    int i;
    if (who!=NULL) {
        for (i=0; i<who->numVertices; i++) {
            list_destroy((who->arreglo[i])->sucesores);
        }
        free(who->arreglo);
        free(who);
    }
}

Bool graph_addVertex(Graph who, Type data) {
    int status;
    for (int i=0; i<who->numVertices; i++) {
        status = who->comparator(data, who->arreglo[i]->data);
        if (status == 0) {
            return false;
        }
    }
    static int id = 1;
    Vertex new = vertex_create(who->clonar(data), id);
    who->arreglo[id-1] = new;
    Vertex * temp = NULL;
    id++;
    temp = realloc(who->arreglo, sizeof(Vertex)*(id));
    if (temp!=NULL) {
        who->arreglo = temp;
        who->numVertices++;
        return true;
    }
    id--;
    return false;
}

Bool graph_addEdge(Graph who, Type source, Type sink){
    Bool hasAnEdge;
    hasAnEdge = graph_hasEdge(who, source, sink);
    if(!hasAnEdge){
        int status;
        for (int i=0; i<who->numVertices; i++) {
            status = who->comparator(source, who->arreglo[i]->data);
            if (status==0) {

                list_add(who->arreglo[i]->sucesores, who->clonar(sink));

                //printf("%p %p\n\n", sink, list_get(who->arreglo[i]->sucesores, list_size(who->arreglo[i]->sucesores)-1));
                //who->imprimir(list_get(who->arreglo[i]->sucesores, list_size(who->arreglo[i]->sucesores)-1));/////
                who->numAristas++;
                return true;
            }
        }
    }
    return false;

}

unsigned long graph_vertexCount(Graph who){
    return who->numVertices;
}

unsigned long graph_edgeCount(Graph who){
    return who->numAristas;
}

unsigned long graph_outDegree(Graph who, Type source){
    int status;

    for (int i = 0; i<who->numVertices;i++){
        status = who->comparator(source, who->arreglo[i]->data);
        if (status == 0) {
            return list_size(who->arreglo[i]->sucesores);
        }
    }
    return -1;
}

Bool graph_hasEdge(Graph who, Type source, Type sink){
    int status;
    int status2;
    for (int i=0; i<who->numVertices; i++) {
        status = who->comparator(source, who->arreglo[i]->data);
        if (status==0) {
            for (int k=0; k<list_size(who->arreglo[i]->sucesores); k++) {
                status2 = who->comparator(list_get(who->arreglo[i]->sucesores, k), sink);

                if (status2==0) {
                    return true;
                }
            }
            break;
        }
    }
    return false;
}

void graph_print(Graph who){
    for (int i=0; i<who->numVertices; i++) {
        who->imprimir(who->arreglo[i]->data);
    }
}

Type returnVertex(Graph who,Type source){
    int status;
    for (int i=0; i<who->numVertices; i++) {
        status = who->comparator(source, who->arreglo[i]->data);
        if (status==0) {
            return who->arreglo[i]->data;
        }
    }
    return NULL;
}
