//
// Created by liperasz on 04/07/25.
//

#ifndef GRAPH_H
#define GRAPH_H

typedef struct {
    int is_weighted;
    int num_vertices;
    int max_degree;
    int** edges;
    float** weights;
    int* degree;
} Graph;

Graph* createGraph(int num_vertices, int max_degree, int is_weighted);
void freeGraph(Graph* graph);
int insertEdge(Graph* graph, int source, int destination, int is_digraph, float weight);
int removeEdge(Graph* graph, int source, int destination, int is_digraph);
void printGraph(Graph* graph);
void primMST(Graph* graph, int start_node);

int findElement(Graph* graph, int source);
int lowerWeight(Graph* graph);

#endif //GRAPH_H