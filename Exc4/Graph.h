//
// Created by liperasz on 04/07/25.
//

#ifndef GRAPH_H
#define GRAPH_H

typedef struct{

    int **edge;
    int *degree;
    int numElements;

} Graph;
// Com certeza o principal desafio era utilizar a estrutura basica, sem nem mesmo o *degree, mas eu nao consegui fazer
// isso, então pelo menos ela eu tive que usar.

Graph* createGraph(int numElements);
int insertEdge(Graph* graph, int source, int destination, int is_digraph);
int removeEdge(Graph* graph, int source, int destination, int is_digraph);
void freeGraph(Graph* graph);



#endif //GRAPH_H
