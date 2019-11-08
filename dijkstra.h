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
    copy->number_of_elements = G->number_of_elements;
    copy->n_links = G->n_links;
    copy->adjacency_list = (ptr_cabecalho_LL*)malloc(sizeof(ptr_cabecalho_LL)*copy->number_of_elements);

    // Populando a lista de adjacência com os headers
    int i;
    for(i=0; i<copy->number_of_elements; i++) 
    {
        // Inicializa cada elemento to vetor de listas ligadas
        copy->adjacency_list[i] = criarCabecalho();  // Ponteiro para lista de adjacência
        copy->adjacency_list[i]->number_of_elements = 0;  // Comprimento zero
        copy->adjacency_list[i]->id = i;  // Label igual ao índice do vetor
    }

    // Agora é hora de DUPLICAR elemento a elemento. Não podemos copiar o ponteiro porque se não é o mesmo lugar da memória.
    // Iteramos mais uma vez sobre os indices do vetor de listas ligadas...
    for(i=0; i<copy->number_of_elements; i++)
    {
        ptr_elemento current = criarElemento();
        // E agora sobre cada elemento da lista ligada
        for(current = G->adjacency_list[i]->start; current != NULL; current = current->next)
        {
            pushElemento(current->id, current->value, current->weight, copy->adjacency_list[i]);
        }
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

