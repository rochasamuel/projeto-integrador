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
    int id, distance, antes;
};

antecessor criarAntecessor()
{
    antecessor ant = (antecessor)malloc(sizeof(*ant));
    ant->id = -1;
    ant->distance = -1;
    ant->antes = -1;
    return ant;    
}

typedef struct antecessores *ptrVetorDeAntecessores;

struct antecessores
{
    int len;
    antecessor *ants;
};

ptrVetorDeAntecessores criarVetorDeAntecessores(int n_vertices)
{
    ptrVetorDeAntecessores v = (ptrVetorDeAntecessores)malloc(sizeof(ptrVetorDeAntecessores));
    v->ants = (antecessor*)malloc(sizeof(antecessor)*n_vertices);
    v->len = n_vertices;
    int i;
    for(i = 0; i< n_vertices; i++)
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
        printf("(%d,%d,%d)\n", v->ants[i]->id,v->ants[i]->distance,v->ants[i]->antes);
    }
}


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

void test_run(graph G, int start, int finish)
{
    graph destructable = copy_graph(G);
    ptrVetorDeAntecessores v = criarVetorDeAntecessores(destructable->n_vertices);
    ptr_cabecalho_LL start_node = destructable->adjacency_list[start];
    min_queue Q = create_min_queue();
    int start_id = destructable->adjacency_list[start]->id;
    min_element M = create_min_element();

    M->antes = -1;
    M->distance = 0;
    M->label = start;
    
    min_push(M, Q);

    graph_report(destructable);
    printf("HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n");
    monstrarVetorDeAntecedentes(v);
    printf("HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n");
    min_show_queue(Q);
    printf("HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n");

    while(1)
    {
        printf("mais um while...\n");
        min_element current_min = create_min_element();
        current_min = min_pop(Q);
        min_show_element(current_min);printf("\n");
        ptr_cabecalho_LL cur_node = destructable->adjacency_list[current_min->label];
        mostrarElementos(cur_node);printf("\n");
        printf("Curnodelen: %d\n",cur_node->number_of_elements);
        if(cur_node->id == finish)
        {
            printf("ACHEI ESSE CORNO.\n");
            break;
        }
        ptr_elemento cur_adjacent = criarElemento();
        for(cur_adjacent = popFirstElemento(cur_node); cur_adjacent != NULL; 
                cur_adjacent = popFirstElemento(cur_node))
            {
                printf("(%d,%d)-",cur_adjacent->id, cur_adjacent->weight);
                printf("\n");
                int adj_id = cur_adjacent->id;
                if(v->ants[adj_id]->id == -1)  // Testa se já existe algum anterior registrado
                {
                    printf("Primeiro loop\n");
                    v->ants[adj_id]->id = adj_id;
                    v->ants[adj_id]->distance = cur_adjacent->weight;
                    v->ants[adj_id]->antes = cur_node->id;

                    min_element M = create_min_element();
                    printf("Criei o min.\n");
                    M->antes = current_min->label;
                    M->distance = cur_adjacent->weight;
                    M->label = adj_id;
                    printf("Preenchi o min\n");
                    min_show_element(M);
                    printf("\n");
                    min_show_queue(Q);
                    printf("Pushing (com -1).\n");
                    min_push(M, Q);
                    
                    //graph_report(destructable);
                    //printf("HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n");
                    printf("cur_node->id:%d\ncur_adjacent->id:%d\n",cur_node->id, cur_adjacent->id);
                    popElemento(cur_node->id, destructable->adjacency_list[cur_adjacent->id]);
                    mostrarElementos(cur_node);printf("\n");

                    monstrarVetorDeAntecedentes(v);
                    //printf("HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n");
                    min_show_queue(Q);
                    //printf("HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n");
                    //printf("Curnodelen: %d\n",cur_node->number_of_elements);
                    continue;
                }
                else
                {
                    printf("Entrei no else.\n");
                    printf("Curadj: (%d,%d)\n",cur_adjacent->id, cur_adjacent->weight);
                    int cur_anterior_dis = v->ants[cur_node->id]->distance + cur_adjacent->weight;
                    if(cur_anterior_dis < v->ants[adj_id]->distance)
                    {
                        printf("COLOCANDO EM :");
                        min_show_queue(Q);
                        printf("\n");
                        v->ants[cur_node->id]->distance = cur_anterior_dis;
                        v->ants[cur_node->id]->antes = cur_node->id;

                        min_element M = create_min_element();

                        M->antes = current_min->label;
                        M->distance = current_min->distance;
                        M->label = adj_id;
                        printf("Pushing (sem -1): ");
                        min_show_element(M);
                        printf("\n");
                        min_pop_by_id(adj_id,Q);
                        min_push(M, Q);
                        printf("cur_node->id:%d\ncur_adjacent->id:%d\n",cur_node->id, cur_adjacent->id);
                        popElemento(cur_node->id, destructable->adjacency_list[cur_adjacent->id]);
                        mostrarElementos(cur_node);printf("\n");

                        //graph_report(destructable);
                        //printf("HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n");
                        //monstrarVetorDeAntecedentes(v);
                        //printf("HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n");
                        min_show_queue(Q);
                        //printf("HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n");
                    }
                }
            } 
    }
    int prev = finish;
    int prev_id = v->ants[prev]->id;
    while(prev_id != start)
    {
        printf("Passando pelo prev_id %d...\n",prev_id);
        int cur_step = v->ants[prev_id]->antes;
        prev_id = cur_step;
    }
    printf("CHEGUEEEEI.");
}

