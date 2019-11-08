#include <stdlib.h>
#include <stdio.h>
#include "dijkstra.h"


/*
    DIJKSTRA'S ALGORITHM

    Implementação do algoritmo de Dijkstras.
*/


void main(void)
{

    graph G = create_graph(10, 0.8, 0);
    graph_report(G);
    printf("=============COPY==========\n");
    graph copy = copy_graph(G);
    graph_report(copy);
    remove_link(4,5,copy);
    printf("=============MINUS 4<->5==========\n");
    graph_report(copy);
    printf("==========MINUS 1=========\n");
    remove_node_from_graph(1,copy);
    graph_report(copy);
    printf("==========ORIGINAL==========\n");
    graph_report(G);

}