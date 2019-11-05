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
    copy->adjacency_list = (adjacents*)malloc(sizeof(adjacents)*copy->n_vertices);

    // Populando a lista de adjacência com os headers
    int i;
    for(i=0; i<copy->n_vertices; i++) 
    {
        // Inicializa cada elemento to vetor de listas ligadas
        copy->adjacency_list[i] = create_list();  // Ponteiro para lista de adjacência
        copy->adjacency_list[i]->len = 0;  // Comprimento zero
        copy->adjacency_list[i]->label = i;  // Label igual ao índice do vetor
    }

    // Agora é hora de DUPLICAR elemento a elemento. Não podemos copiar o ponteiro porque se não é o mesmo lugar da memória.
    // Iteramos mais uma vez sobre os indices do vetor de listas ligadas...
    for(i=0; i<copy->n_vertices; i++)
    {
        vertice current = create_item();
        // E agora sobre cada elemento da lista ligada
        for(current = G->adjacency_list[i]->start; current != NULL; current = current->next)
        {
            add_adjacent(current->label, current->value, current->weight, copy->adjacency_list[i]);
        }
    }
    return copy;
}