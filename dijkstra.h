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

typedef struct antecessores *ptrVetorDeAntecessores;

struct antecessores
{
    int len;
    antecessor *ants;
};

ptrVetorDeAntecessores criarVetorDeAntecessores(int nVertices)
{
    ptrVetorDeAntecessores v = (ptrVetorDeAntecessores)malloc(sizeof(ptrVetorDeAntecessores));
    v->ants = (antecessor*)malloc(sizeof(antecessor)*nVertices);
    v->len = nVertices;
    int i;
    for(i = 0; i< nVertices; i++)
    {
        v->ants[i] = criarAntecessor();
    }
    return v;
}

int monstrarVetorDeAntecedentes(ptrVetorDeAntecessores v)
{
    int i;
    for(i = 0; i<v->len;i++)
    {
        printf("(%d,%d,%d)\n", v->ants[i]->id,v->ants[i]->total_distance,v->ants[i]->elemento_de_origem);
    }
}


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

void test_run(graph G, int start, int finish)
{
    graph destructable = copy_graph(G);
    ptrVetorDeAntecessores v = criarVetorDeAntecessores(destructable->nVertices);
    ptr_cabecalho_LL start_node = destructable->listaDeAdjacencia[start];
    ptr_cabecalho_LL Q = criarCabecalho();
    int start_id = destructable->listaDeAdjacencia[start]->id;
    ptr_elemento M = criarElemento();
    ptr_elemento current_from_queue = criarElemento();
    M->elemento_de_origem = -1;
    M->total_distance = 0;
    M->id = start;
    
    pushListaMinimo(M, Q);

    do
    {
        min_show_queue(Q);
        ptr_elemento current_from_queue = criarElemento();
        current_from_queue = min_pop(Q);
        min_show_element(current_from_queue);
        ptr_cabecalho_LL cur_node = destructable->listaDeAdjacencia[current_from_queue->id];
        printf("Elementos do vertice atual.\n\t");
        mostrarElementos(cur_node);
        if(cur_node->id == finish)
        {
            break;
        }
        ptr_elemento current_neighbour = criarElemento();
        for(current_neighbour = popFirstElemento(cur_node); current_neighbour != NULL; 
                current_neighbour = popFirstElemento(cur_node))
            {
                monstrarVetorDeAntecedentes(v);
                if(v->ants[current_neighbour->id]->id == -1)  // Testa se é carne fresca no vetor
                {
                    v->ants[current_neighbour->id]->id = current_neighbour->id;
                    v->ants[current_neighbour->id]->total_distance = current_neighbour->weight;
                    v->ants[current_neighbour->id]->elemento_de_origem = cur_node->id;

                    ptr_elemento M = criarElemento();
                    M->elemento_de_origem = current_from_queue->id;
                    M->total_distance = current_neighbour->weight;
                    M->id = current_neighbour->id;
                    pushListaMinimo(M, Q);
                    printf("Just pushed:");
                    min_show_element(M);
                    printf("\n");
                    
                    popIdLista(cur_node->id, destructable->listaDeAdjacencia[current_neighbour->id]);  // Joga fora o link
                    continue;
                }
                else
                {
                    printf("Bom, tá tem {%d,%d,%d} aqui.\n",
                    v->ants[current_neighbour->id]->id,
                    v->ants[current_neighbour->id]->total_distance,
                    v->ants[current_neighbour->id]->elemento_de_origem = cur_node->id);

                    int distancia_candidata = v->ants[cur_node->id]->total_distance + current_neighbour->weight;
                    printf("\tMinha distancia candidata eh: %d\n",distancia_candidata);
                    printf("Estando no %d\n",current_neighbour->id);
                    printf("Passando por %d\n",cur_node->id);
                    if(distancia_candidata < v->ants[current_neighbour->id]->total_distance)
                    {
                        printf("\tA candidata é melhor! Troquemos.\n");
                        v->ants[cur_node->id]->total_distance = distancia_candidata;
                        v->ants[cur_node->id]->elemento_de_origem = current_neighbour->id;

                        ptr_elemento M = criarElemento();

                        M->elemento_de_origem = current_neighbour->id;
                        M->total_distance = distancia_candidata;
                        M->id = current_neighbour->id;
                        pushListaMinimo(M, Q);
                        popIdLista(cur_node->id, destructable->listaDeAdjacencia[current_neighbour->id]);  // Joga fora o link
                    }
                }
            } 
    }while(1 == 1);
    int previous = finish;
    printf("Começando com prev = %d e start = %d\n",previous,start);
    monstrarVetorDeAntecedentes(v);
    int i;
    scanf("%d",&i);
    printf("\tCaminho: ");
    while(previous != start)
    {
        printf("%d-",previous);
        previous = v->ants[previous]->elemento_de_origem;
    }
    
    printf("%d\n",start);
}

