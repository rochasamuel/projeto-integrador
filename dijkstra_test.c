#include <stdlib.h>
#include <stdio.h>
#include "dijkstra.h"


/*
    DIJKSTRA'S ALGORITHM

    Implementação do algoritmo de Dijkstras.
*/


void main(void)
{
    graph G = create_graph(18, 0.852451231, 10, 1);
    graph destructable = copy_graph(G);
    test_run(G, 0 ,10);    
}