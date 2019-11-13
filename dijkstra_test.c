#include <stdlib.h>
#include <stdio.h>
#include "dijkstra.h"


/*
    DIJKSTRA'S ALGORITHM

    Implementação do algoritmo de Dijkstras.
*/


void main(void)
{
    graph G = create_graph(6, 0.7, 100, 1);
    graph_report(G);
    graph destructable = copy_graph(G);
    test_run(G, 0,6);
}