#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Definindo struct de grafo
typedef struct graph_structure *graph;

struct graph_structure{
    int n_vertices;  // Número de vértices
    int n_links;  // Número de arestas 
    adjacents *adjacency_list; // Vetor de listas ligadas, de adjacência
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
    graph g = (graph)malloc(sizeof(*g));  // Aloca espaço na memória para struct de grafo
    g->n_vertices = n_vertices;  // Pré-determina número de vértices]
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
    clock_t init_start = clock();
    for(i=0; i < g->n_vertices; i++)
    {
        // Caso inicial, onde não há elemento anterior a adicionar
        /*
        Esse bloco de código adiciona, na lista de adjacência do vértice 0, o vértice
        1 como elemento.
        */
        if(i == 0)
        {
            int next_label = i+1;
            int next_value = i+1;
            int next_weight = random_weight(max_weight);
            add_adjacent(next_label, next_value, next_weight, g->adjacency_list[i]);
            g->n_links++;
        }

        /*
        Esse bloco de código adiciona, na lista de adjacência do último vértice do vetor
        de listas de adjacência , o penúltimo vértice como elemento.
        */
        else if(i == g->n_vertices-1)
        {
            int next_label = i-1;
            int next_value = i-1;
            int next_weight = random_weight(max_weight);
            add_adjacent(next_label, next_value, next_weight, g->adjacency_list[i]);
            g->n_links++;
        }
        /*
        Essa opção default se aplica a todos os vértices que não são o primeiro e o último.
        Ela adiciona tanto o vértice anterior como o próximo vértice na sequência como 
        elementos da lista de adjacẽncia.
        */

        else        
        {
            int next_label = i+1;
            int next_value = i+1;
            int next_weight = random_weight(max_weight);
            add_adjacent(next_label, next_value, next_weight, g->adjacency_list[i]);
            g->n_links++;

            int prev_label = i-1;
            int prev_value = i-1;
            int prev_weight = random_weight(max_weight);
            add_adjacent(prev_label, prev_value, prev_weight, g->adjacency_list[i]);
            g->n_links++;
        }
    }
    clock_t init_end = clock();
    double delta = ((double)init_end-(double)init_start)/CLOCKS_PER_SEC;
    printf("Total initialization runtime: %.2f s\n",delta);

    if(density == 0)
    {
        // Se a densidade alvo for 0, ou seja, a menor possível, o grafo já está pronto.
        return g;
    }
    float max_links = ((g->n_vertices)*(g->n_vertices - 1))/2.0;  // Definindo valor máximo de links
    float current_density = ((float)g->n_links/(float)(max_links))/2.0;  // Valor atual da densidade (links_atual/max)
                                                       // A multiplicação por 2 é porque os links estão contados duas vezes

    int clock_counter = 0;
    clock_t partial_start = clock();
    while(current_density <= density)
    /*
    Esse While tem um problema: como ele aleatoriamente gera pares para tentar inserir, à medida que o grafo vai ficando
    mais denso a chance de conseguir gerar um novo par que funcione diminui. Então quanto mais perto de densidade 1 o grafo
    for, mais tempo ele vai ficar preso aqui tentando encontrar pares certos.
    */
    {
        clock_counter++;
        // Pegando dois elementos aleatórios do grafo, pelos labels
        int vertice_1 = rand() % g->n_vertices, vertice_2;
        do
        {
            vertice_2 = rand() % g->n_vertices;
        } while(vertice_1 == vertice_2);
        
        

        // Testando para ver se eles já não estão ligados
        vertice cur = create_item();
        if(is_adjacent_to(vertice_1, g->adjacency_list[vertice_2]))
        {
            continue;  // Se um é adjacente do outro, o outro é adjacente do um, então pegamos um novo par de valores.
        }
        
        // Adicionando o vertice 1 como adjacente do 2
        add_adjacent(vertice_1, vertice_1, random_weight(max_weight), g->adjacency_list[vertice_2]);
        g->n_links++;
        // E adicionando o 2 como adjacente do 1
        add_adjacent(vertice_2, vertice_2, random_weight(max_weight), g->adjacency_list[vertice_1]);
        g->n_links++;
        // Atualizando o numero de links
        current_density = ((float)g->n_links/(float)(max_links))/2.0;
    }
    printf("Total iterations: %d\n",clock_counter);
    return g;
}

int remove_link(int label_A, int label_B, graph G)
{
    remove_adjacent(label_A, G->adjacency_list[label_B]);
    G->n_links--;
    remove_adjacent(label_B, G->adjacency_list[label_A]);
    G->n_links--; 
}

void graph_report(graph g)
{
    printf("Graph Report\n");
    printf("\tGraph Metadata\n");
    printf("\t Vertices: %d\n",g->n_vertices);
    printf("\t Links: %d\n",g->n_links);
    printf("Adjacency list\n");
    int i;
    for(i = 0; i < g->n_vertices; i++)
    {
        printf("\tNode %d:\n",g->adjacency_list[i]->label);
        vertice current = create_item();
        int k = 0;
        for(current = g->adjacency_list[i]->start; current != NULL; current = current->next)
        {
            printf("\t\t#%d: (%d,%d,%d)\n",k+1,current->label, current->value, current->weight);
            k++;
        }
    }
}

