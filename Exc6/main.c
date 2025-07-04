//
// Created by liperasz on 04/07/25.
//

#include "Graph.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    int eh_digrafo = 1;
    Graph* gr = createGraph(5, 5, 1);

    insertEdge(gr, 0, 1, eh_digrafo, 2);
    insertEdge(gr, 1, 3, eh_digrafo, 1);
    insertEdge(gr, 1, 2, eh_digrafo, 3);
    insertEdge(gr, 2, 4, eh_digrafo, 4);
    insertEdge(gr, 3, 0, eh_digrafo, 8);
    insertEdge(gr, 3, 4, eh_digrafo, 6);
    insertEdge(gr, 4, 1, eh_digrafo, 5);

    printGraph(gr);

    findElement(gr, 3);
    lowerWeight(gr);

    freeGraph(gr);

    system("pause");
    return 0;
}