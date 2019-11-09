#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"
#include "graph.h"


/*

DIJKSTRA'S ALGORITHM

*/


/*

Primeiro, definir uma função que copia um grafo.
Isso é necessário porque o algoritmo precisa saber por quais vértices já passou, de
forma destrutiva, então não podemos usar o grafo original para não inutilizá-lo.

*/

graph copy_graph(graph G)
{
    graph copy = (graph)malloc(sizeof(*copy));
    copy->n_vertices = G->n_vertices;
    copy->n_links = G->n_links;
    copy->adjacency_list = (ptr_cabecalho_LL*)malloc(sizeof(ptr_cabecalho_LL)*copy->n_vertices);

    // Populando a lista de adjacência com os headers
    int i;
    for(i = 0; i < G->n_vertices; i++)
    {
        copy->adjacency_list[i] = copiarLista(G->adjacency_list[i]);
    }
    return copy;
}

int remove_node_from_graph(int id, graph G)
{
    // Será necessário pra remover nódulos do grafo copiado
    ptr_elemento current = criarElemento();
    for(current = G->adjacency_list[id]->start; current != NULL; current = current->next)
    {
        remove_link(id, current->id, G);
        G->n_links = G->n_links - 2;
    }
    return 0;
}

