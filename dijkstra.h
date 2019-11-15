#pragma once

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

/*
typedef struct previous *antecessor;

struct previous
{
    int id, total_distance, elemento_de_origem;
};

antecessor criarAntecessor()
{
    antecessor ant = (antecessor)malloc(sizeof(*ant));
    ant->id = -1;
    ant->total_distance = -1;
    ant->elemento_de_origem = -1;
    return ant;    
}
*/
/*
typedef struct antecessores *ptrVetorDeAntecessores;

struct antecessores
{
    int len;
    antecessor *ants;
};
*/

graph criarVetorDeAntecessores(int nVertices)
{
    graph v = esqueletoGrafo(nVertices);
    int i;
    for(i = 0; i< nVertices; i++)
    {
        ptr_elemento current = criarElemento();
        current->id = -1;
        current->total_distance = 0;
        current->elemento_de_origem = -1;
        v->listaDeAdjacencia[i]->start = current;
    }
    return v;
}

int mostrarAntecessores(graph v)
{
    int i;
    printf("\tADJs.\n");
    for(i=0; i< v->nVertices; i++)
    {
        mostrarElemento(v->listaDeAdjacencia[i]->start);
    }
}

/*


int mostrarLista(ptrVetorDeAntecessores v)
{
    int i;
    for(i = 0; i<v->len;i++)
    {
        printf("(%d,%d,%d)\n", v->ants[i]->id,v->ants[i]->total_distance,v->ants[i]->elemento_de_origem);
    }
}
*/


graph copy_graph(graph G)
{
    graph copy = (graph)malloc(sizeof(*copy));
    copy->nVertices = G->nVertices;
    copy->nLinks = G->nLinks;
    copy->listaDeAdjacencia = (ptr_cabecalho_LL*)malloc(sizeof(ptr_cabecalho_LL)*copy->nVertices);

    // Populando a lista de adjacência com os headers
    int i;
    for(i = 0; i < G->nVertices; i++)
    {
        copy->listaDeAdjacencia[i] = copiarLista(G->listaDeAdjacencia[i]);
    }
    return copy;
}

/*
int removerDoGrafo(int id, graph G)
{
    // Será necessário pra remover nódulos do grafo copiado
    ptr_elemento current = criarElemento();
    for(current = G->listaDeAdjacencia[id]->start; current != NULL; current = current->next)
    {
        removerConexao(id, current->id, G);
        G->nLinks = G->nLinks - 2;
    }
    return 0;
}
*/

void test_run(graph G, int start, int finish, FILE *f)
{
    clock_t test_start = clock();
    graph destructable = copy_graph(G);
    graph v = criarVetorDeAntecessores(destructable->nVertices);
    ptr_cabecalho_LL start_node = destructable->listaDeAdjacencia[start];
    ptr_cabecalho_LL minQ = criarCabecalho();
    int start_id = destructable->listaDeAdjacencia[start]->id;
    ptr_elemento minElemento = criarElemento();
    ptr_elemento current_from_queue = criarElemento();
    minElemento->elemento_de_origem = -1;
    minElemento->total_distance = 0;
    minElemento->id = start;
    
    pushListaMinimo(minElemento, minQ);
    int global_counter = 0;
    do
    {
        //mostrarLista(minQ);
        ptr_elemento current_from_queue = criarElemento();
        current_from_queue = popPrimeiroLista(minQ);
        //printf("CurFromQ: ");
        //mostrarElemento(current_from_queue); printf("\n");
        ptr_cabecalho_LL cur_node = destructable->listaDeAdjacencia[current_from_queue->id];
        //printf("\nElementos do vertice atual:\n\t");
        //mostrarLista(cur_node);
        if(cur_node->id == finish)
        {
            break;
        }
        ptr_elemento current_neighbour = criarElemento();
        for(current_neighbour = popPrimeiroLista(cur_node); current_neighbour != NULL; 
                current_neighbour = popPrimeiroLista(cur_node))
            {
                //mostrarAntecessores(v);
                if(v->listaDeAdjacencia[current_neighbour->id]->start->id == -1)  // Testa se é carne fresca no vetor
                {
                    v->listaDeAdjacencia[current_neighbour->id]->id = current_neighbour->id;
                    v->listaDeAdjacencia[current_neighbour->id]->start->id = current_neighbour->id;
                    int total_distance = current_neighbour->weight + v->listaDeAdjacencia[cur_node->id]->start->total_distance;
                    v->listaDeAdjacencia[current_neighbour->id]->start->total_distance = total_distance;
                    v->listaDeAdjacencia[current_neighbour->id]->start->elemento_de_origem = cur_node->id;

                    // Pra colocar na minQ, já que não existia antes.
                    ptr_elemento minElemento = criarElemento();
                    minElemento->elemento_de_origem = current_from_queue->id;
                    minElemento->total_distance = current_neighbour->weight;
                    minElemento->id = current_neighbour->id;
                    pushListaMinimo(minElemento, minQ);
                    //printf("Just pushed:");
                    //mostrarElemento(minElemento);
                    //printf("\n");
                    
                    removerConexao(cur_node->id, current_neighbour->id,destructable);  // Joga fora o link
                    continue;
                }
                else
                {
                    int distancia_candidata = v->listaDeAdjacencia[cur_node->id]->start->total_distance + current_neighbour->weight;
                    /*printf("\tMinha distancia candidata eh: %d\n",distancia_candidata);
                    printf("Cheguei no %d\n",current_neighbour->id);
                    printf("Passando por %d\n",cur_node->id);*/
                    if(distancia_candidata < v->listaDeAdjacencia[current_neighbour->id]->start->total_distance)
                    {
                        //printf("\tA candidata é melhor! Troquemos.\n");
                        v->listaDeAdjacencia[current_neighbour->id]->start->total_distance = distancia_candidata;
                        v->listaDeAdjacencia[current_neighbour->id]->start->elemento_de_origem = cur_node->id;

                        ptr_elemento minElemento = criarElemento();

                        minElemento->elemento_de_origem = cur_node->id;
                        minElemento->total_distance = distancia_candidata;
                        minElemento->id = current_neighbour->id;
                        pushListaMinimo(minElemento, minQ);
                        removerConexao(cur_node->id, current_neighbour->id,destructable);  // Joga fora o link
                    }
                }
            } 
    }while(1 == 1);
    clock_t test_finish = clock();
    int previous = finish;
    //printf("Começando com prev = %d e start = %d\n",previous,start);
    int i;
    //mostrarAntecessores(v);
    double d = delta_clock(test_start,test_finish);
    printf("Time to solve: %fs\n",d);
    printf("Distancia total: %d\n",v->listaDeAdjacencia[finish]->start->total_distance);
    fprintf(f, "%f,%d,",d,v->listaDeAdjacencia[finish]->start->total_distance);
    while(previous != start)
    {
        printf("%d|",previous);
        fprintf(f,"%d|",previous);
        previous = v->listaDeAdjacencia[previous]->start->elemento_de_origem;
    }
    fprintf(f,"%d\n",start);    
    printf("%d\n",start);
    
} //segundos,distancia_total,caminho

