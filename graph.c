#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>


// Definindo struct de grafo
typedef struct graph_structure graph;

struct graph_structure{
    int n_vertices;  // Número de vértices
    int n_links;  // Número de arestas 
    adjacents adjacency_list; // Vetor de listas ligadas, de adjacência
};

float random_weight(int max_weight)
{
    // Função para retornar pesos aleatórios aos vértices do grafo.
    if(max_weight == 0) return 1;
    return 1 + (rand() % max_weight);
}

graph create_graph(int n_vertices, float density, int max_weight)
{
    // Função que retorna struct 'grafo' preenchida com n_vertices e densidade de links = 'density'
    int i;
    graph g = malloc(sizeof(*g));  // Aloca espaço na memória para struct de grafo
    g->n_vertices = n_vertices;  // Pré-determina número de vértices
    g->n_links = 0;  // Número de links é zero porque é incrementado dinamicamente
    g->adjacency_list = (adjacents*)malloc(sizeof(adjacents)*n_vertices);
    // Cria vetor com tamanho 'v_vertices' de ponteiros para listas de adjacências.
    for(i=0; i<n_vertices; i++)
    {
        // Inicializa cada elemento to vetor de listas ligadas
        g->adjacency_list[i] = create_list();  // Ponteiro para lista de adjacência
        g->adjacency_list[i]->len = 0;  // Comprimento zero
        g->adjacency_list[i]->label = i;  // Label igual ao índice do vetor
    }


    // Inicialização do grafo, condição mínima de existência
    // Fazendo uma 'fila indiana' de conexões, onde 0 está ligado a 1, 1 a 2, 2 a 3, etc.
    // Se isso não for garantido o grafo fica fatiado em vários mini-grafos não contínuos.

    for(i=0; i < grafo->n_vertices; i++)
    {
        switch(i)
        {
            case 0:  // Caso inicial, onde não há elemento anterior a adicionar
                /*
                Esse bloco de código adiciona, na lista de adjacência do vértice 0, o vértice
                1 como elemento.
                */
                next_label = i+1;
                next_value = i+1;
                next_weight = random_weight(max_weight);
                add_adjacent(next_label, next_value, next_weight, grafo->adjacency_list[i]);
                grafo->n_links++;
                break;

            case grafo->n_vertices-1:
                /*
                Esse bloco de código adiciona, na lista de adjacência do último vértice do vetor
                de listas de adjacência , o penúltimo vértice como elemento.
                */
                next_label = i+1;
                next_value = i+1;
                next_weight = random_weight(max_weight);
                add_adjacent(next_label, next_value, next_weight, grafo->adjacency_list[i]);
                grafo->n_links++;
                break;

            default: 
                /*
                Essa opção default se aplica a todos os vértices que não são o primeiro e o último.
                Ela adiciona tanto o vértice anterior como o próximo vértice na sequência como 
                elementos da lista de adjacẽncia.
                */
                next_label = i+1;
                next_value = i+1;
                next_weight = random_weight(max_weight);
                add_adjacent(next_label, next_value, next_weight, grafo->adjacency_list[i]);
                grafo->n_links++;

                prev_label = i-1;
                prev_value = i-1;
                prev_weight = random_weight(max_weight);
                add_adjacent(prev_label, prev_value, prev_weight, grafo->adjacency_list[i]);
                grafo->n_links++;
        }
    }

    if(density == 0)
    {
        // Se a densidade alvo for 0, ou seja, a menor possível, o grafo já está pronto.
        return grafo;
    }
    int max_links = (grafo->n_vertices)*(grafo->n_vertices - 1);  // Definindo valor máximo de links
    float current_density = grafo->n_links/max_links;  // Valor atual da densidade (links_atual/max)
    while(current_density <= density)
    {
        // Pegando dois elementos aleatórios do grafo, pelos labels
        vertice_1 = rand() % grafo->n_vertices;
        vertice_2 = rand() % grafo->n_vertices;

        // Testando para ver se eles já não estão ligados
        
    }

}