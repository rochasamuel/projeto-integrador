#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>


// Creating a graph with N nodes

typedef struct graph_structure graph;

struct graph_structure{
    int n_vertices;
    int n_links;
    adjacents adjacency_list[]; 
};

int create_graph(int n_vertices, float density)
{
    int i;
    graph g = malloc(sizeof(*g));
    g->n_vertices = n_vertices;
    g->n_links = 0;
    g->adjacency_list = create_list();
    
    for(i=0; i<n_vertices; i++)
    {

    }
    // Início do grafo, condição mínima de existência
    for(i=0; i<grafo->n_vertices-1; i++)
    {
        switch(i)
        {
            case 0:
                grafo->ad_list[i].push_in_front(vertice[value=i+1])
                ligacoes++;
            case grafo->n_vertices-1:
                grafo->ad_list[i].push_in_front(vertice[value=i-1])
                ligacoes++;
            default: 
                grafo->ad_list[i].push_in_front(vertice[value=i+1])
                ligacoes++;
                grafo->ad_list[i].push_in_front(vertice[value=i-1])
                ligacoes++;
        }
    }

    if(densidade_alvo == 0)
    {
        return grafo
    }

    while(ligacoes/lig_max <= densidade_alvo)
    {
        p1 = gerar_peso();
        p2 = gerar_peso();
        v1 = v_aleatorio();
        v1->peso = p1;
        v2 = v_aleatorio();
        v2->peso = p2;
        if(graph[v1].contains(v2) || v1==v2)
        {
            continue;
        }
        
        push_at_start(v2, graph[v1])
        push_at_start(v1, graph[v2])
        ligacoes++;
    }

}