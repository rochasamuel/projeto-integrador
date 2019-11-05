#include <stdlib.h>
#include <stdio.h>
#include "dijkstra.h"


/*
    DIJKSTRA'S ALGORITHM

    Implementação do algoritmo de Dijkstras.
*/


void main(void)
{

    graph G = create_graph(4, 0.2, 0);
    graph_report(G);
    printf("=============COPY==========\n");
    graph copy = copy_graph(G);
    graph_report(copy);
    remove_adjacent(1,copy->adjacency_list[0]);
    printf("=============EDITED==========\n");
    graph_report(copy);
    printf("ORIGINAL\n");
    graph_report(G);

}