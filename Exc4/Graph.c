//
// Created by liperasz on 04/07/25.
//

#include "Graph.h"
#include <stdlib.h>
#include <stdio.h>

Graph* createGraph(int numElements) {

    Graph* graph = malloc(sizeof(Graph));
    if (graph != NULL) {
        graph->numElements = numElements;
        graph->degree = calloc(numElements, sizeof(int));

        graph->edge = (int**)malloc(sizeof(int) * numElements);
        for (int i = 0; i < numElements; i++) {
            graph->edge[i] = (int*)malloc(sizeof(int));
        }
    }
    return graph;
}

int insertEdge(Graph* graph, int source, int destination, int is_digraph) {

    if(graph == NULL || source < 0 || destination < 0 || source >= graph->numElements || destination >= graph->numElements) {
        return 0;
    }

    graph->edge[source][graph->degree[source]] = destination;
    graph->degree[source]++;

    if (is_digraph == 0) {
        insertEdge(graph, destination, source, 1);
    }

    return 1;

}

int removeEdge(Graph* graph, int source, int destination, int is_digraph) {

    if(graph == NULL || source < 0 || destination < 0 || source >= graph->numElements || destination >= graph->numElements) {
        return 0;
    }

    int i = 0;
    while (i < graph->degree[source] && graph->edge[source][i] != destination) {
        i++;
    }

    if(i == graph->degree[source]) {
        return 0;
    }

    graph->degree[source]--;
    graph->edge[source][i] = graph->degree[source][graph->degree[source]];

    if(is_digraph == 0)
        removeEdge(graph, destination, source, 1);

    return 1;
}

void freeGraph(Graph* graph) {

    if (graph != NULL) {

        for(int i = 0; i <graph->numElements; i++) {
            free(graph->edge[i]);
        }

        free(graph->edge);
        free(graph->degree);
        free(graph);
    }

}