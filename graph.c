#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>


// Creating a graph with N nodes

typedef struct G graph;

struct G{
    int n_vertices;
    int n_arestas;
    linked_list 
}



int fill_graph(linked_list *graph, int n_vertices)
{
    int i;
    for(i = 0;i<n_vertices;i++)
    {
        int j;
        for(j = 0; j < 3; j++)
        {
            push_at_start(1 + rand() % 20, graph[i]);
        }
    }
}


void main(void)
{
    int i, len = 6;
    linked_list graph[len];
    for(i=0;i<len;i++)
    {
        graph[i] = create_list();
    }
    fill_graph(graph,len);
    printf("List 4: ");
    show_list(graph[0]);
}



int fill_graph(linked_list *graph, float densidade)
{
    float max_v = (grafo->v)*(grafo->v - 1);
    densidade_atual = grafo->n_vertices/max_v;

    int i;
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