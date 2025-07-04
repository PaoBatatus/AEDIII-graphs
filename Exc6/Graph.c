//
// Created by liperasz on 04/07/25.
//

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include <limits.h>


Graph* createGraph(int num_vertices, int max_degree, int is_weighted) {
    Graph *graph;
    graph = (Graph*) malloc(sizeof(Graph));
    if (graph != NULL) {
        int i;
        graph->num_vertices = num_vertices;
        graph->max_degree = max_degree;
        graph->is_weighted = (is_weighted != 0) ? 1 : 0;
        graph->degree = (int*) calloc(num_vertices, sizeof(int));

        graph->edges = (int**) malloc(num_vertices * sizeof(int*));
        for (i = 0; i < num_vertices; i++) {
            graph->edges[i] = (int*) malloc(max_degree * sizeof(int));
        }

        if (graph->is_weighted) {
            graph->weights = (float**) malloc(num_vertices * sizeof(float*));
            for (i = 0; i < num_vertices; i++) {
                graph->weights[i] = (float*) malloc(max_degree * sizeof(float));
            }
        }
    }
    return graph;
}

void freeGraph(Graph* graph) {
    if (graph != NULL) {
        int i;
        for (i = 0; i < graph->num_vertices; i++) {
            free(graph->edges[i]);
        }
        free(graph->edges);

        if (graph->is_weighted) {
            for (i = 0; i < graph->num_vertices; i++) {
                free(graph->weights[i]);
            }
            free(graph->weights);
        }
        free(graph->degree);
        free(graph);
    }
}

int insertEdge(Graph* graph, int source, int destination, int is_digraph, float weight) {
    if (graph == NULL) {
        return 0;
    }
    if (source < 0 || source >= graph->num_vertices) {
        return 0;
    }
    if (destination < 0 || destination >= graph->num_vertices) {
        return 0;
    }

    graph->edges[source][graph->degree[source]] = destination;
    if (graph->is_weighted) {
        graph->weights[source][graph->degree[source]] = weight;
    }
    graph->degree[source]++;

    if (is_digraph == 0) {
        insertEdge(graph, destination, source, 1, weight);
    }
    return 1;
}

int removeEdge(Graph* graph, int source, int destination, int is_digraph) {
    if (graph == NULL) {
        return 0;
    }
    if (source < 0 || source >= graph->num_vertices) {
        return 0;
    }
    if (destination < 0 || destination >= graph->num_vertices) {
        return 0;
    }

    int i = 0;
    while (i < graph->degree[source] && graph->edges[source][i] != destination) {
        i++;
    }
    if (i == graph->degree[source]) {
        return 0;
    }
    graph->degree[source]--;
    graph->edges[source][i] = graph->edges[source][graph->degree[source]];
    if (graph->is_weighted) {
        graph->weights[source][i] = graph->weights[source][graph->degree[source]];
    }
    if (is_digraph == 0) {
        removeEdge(graph, destination, source, 1);
    }
    return 1;
}

void printGraph(Graph* graph) {
    if (graph == NULL) {
        return;
    }

    int i, j;
    for (i = 0; i < graph->num_vertices; i++) {
        printf("%d: ", i);
        for (j = 0; j < graph->degree[i]; j++) {
            if (graph->is_weighted) {
                printf("%d(%.2f), ", graph->edges[i][j], graph->weights[i][j]);
            } else {
                printf("%d, ", graph->edges[i][j]);
            }
        }
        printf("\n");
    }
}

void primMST(Graph* graph, int start_node) {
    if (graph == NULL || graph->is_weighted == 0) {
        printf("Invalid or non-weighted graph.\n");
        return;
    }

    int n = graph->num_vertices;
    int *visited = (int*) calloc(n, sizeof(int));
    int *parent = (int*) malloc(n * sizeof(int));
    float *key = (float*) malloc(n * sizeof(float));

    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        parent[i] = -1;
    }

    key[start_node] = 0;

    for (int counter = 0; counter < n - 1; counter++) {
        float min_key = INT_MAX;
        int u = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && key[i] < min_key) {
                min_key = key[i];
                u = i;
            }
        }

        if (u == -1) {
            break;
        }

        visited[u] = 1;

        for (int i = 0; i < graph->degree[u]; i++) {
            int v = graph->edges[u][i];
            float weight = graph->weights[u][i];

            if (!visited[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
            }
        }
    }

    printf("\nMinimum Spanning Tree (Prim's Algorithm):\n");
    float total_weight = 0;
    for (int i = 0; i < n; i++) {
        if (parent[i] != -1) {
            printf("%d - %d (weight %.2f)\n", parent[i], i, key[i]);
            total_weight += key[i];
        }
    }
    printf("Total MST weight: %.2f\n", total_weight);

    free(visited);
    free(parent);
    free(key);
}

int findElement(Graph* graph, int source) {

    if (graph == NULL) {
        return 0;
    }

    if (source < 0 || source >= graph->num_vertices) {
        return 0;
    }

    printf("Elemento %d encontrado!\n", source);
    for (int i = 0; i < graph->degree[source]; i++) {
        printf("Element connected to %d\n", graph->edges[source][i]);
    }
    printf("Number of connections: %d\n", graph->degree[source]);

    return 1;
}

int lowerWeight(Graph* graph) {

    if (graph == NULL || graph->is_weighted == 0) {
        printf("Invalid or non-weighted graph.\n");
        return 0;
    }

    float lower_weight = 0;
    int x = -1;
    int y = -1;
    for (int i = 0; i < graph->num_vertices; i++) {
        for (int j = 0; j < graph->degree[i]; j++) {
            if (i == 0 && j == 0) {
                lower_weight = graph->weights[i][j];
            }
            else {
                if (graph->weights[i][j] < lower_weight) {
                    lower_weight = graph->weights[i][j];
                    x = i;
                    y = graph->edges[i][j];
                }
            }
        }
    }

    printf("The edge with the lower weight is the one between %d and %d, with weigh %.2f", x, y, lower_weight);

    return 1;

}