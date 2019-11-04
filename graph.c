#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>


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
    printf("Me pediram um grafo com %d vertices, densidade de %f, e peso maximo de %d\n",n_vertices,density, max_weight);
    graph g = malloc(sizeof(*g));  // Aloca espaço na memória para struct de grafo
    printf("Aloquei o espaço de memória do grafo G\n");
    g->n_vertices = n_vertices;  // Pré-determina número de vértices]
    printf("Meu grafo agora sabe que tem %d vertices.\n",g->n_vertices);
    g->n_links = 0;  // Número de links é zero porque é incrementado dinamicamente
    printf("Por hora, o numero de links é %d\n",g->n_links);
    g->adjacency_list = malloc(sizeof(adjacents)*n_vertices);
    printf("Aloquei o espaço de memória pro array de listas de adjacência, no tamanho de %ld bits\n", sizeof(g->adjacency_list));
    // Cria vetor com tamanho 'v_vertices' de ponteiros para listas de adjacências.
    printf("Vou começar a iterar sobre os vertices para criá-los\n");
    for(i=0; i<n_vertices; i++) 
    {
        printf("Criando a lista do vertice #%d\n",i);
        // Inicializa cada elemento to vetor de listas ligadas
        g->adjacency_list[i] = create_list();  // Ponteiro para lista de adjacência
        printf("Criei a lista\n");
        g->adjacency_list[i]->len = 0;  // Comprimento zero
        printf("Coloquei o tamanho dela como %d.\n",g->adjacency_list[i]->len);
        g->adjacency_list[i]->label = i;  // Label igual ao índice do vetor
        printf("E o label dela eh: %d\n",g->adjacency_list[i]->label);
    }


    // Inicialização do grafo, condição mínima de existência
    // Fazendo uma 'fila indiana' de conexões, onde 0 está ligado a 1, 1 a 2, 2 a 3, etc.
    // Se isso não for garantido o grafo fica fatiado em vários mini-grafos não contínuos.

    printf("AGORA vou iterar sobre os %d vertices do grafo.\n",g->n_vertices);
    for(i=0; i < g->n_vertices; i++)
    {
        printf("Estou no i = %d\n",i);
        // Caso inicial, onde não há elemento anterior a adicionar
        /*
        Esse bloco de código adiciona, na lista de adjacência do vértice 0, o vértice
        1 como elemento.
        */
        if(i == 0)
        {
            printf("\tEstou no primeiro vertice, então vou adicionar só o da frente.\n");
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
            printf("\tEstou no ultimo vertice, então vou adicionar só o de tras.\n");
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
            printf("\tEstou num vertice do meio, então vou adicionar o da frente e o de tras.\n");
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

    if(density == 0)
    {
        // Se a densidade alvo for 0, ou seja, a menor possível, o grafo já está pronto.
        return g;
    }
    int max_links = (g->n_vertices)*(g->n_vertices - 1);  // Definindo valor máximo de links
    printf("\t\tMax links: %d",max_links);
    printf("\t\tNumero atual de links: %d",g->n_links);
    float current_density = (float)g->n_links/(float)(2*max_links);  // Valor atual da densidade (links_atual/max)
                                                       // A multiplicação por 2 é porque os links estão contados duas vezes

    while(current_density <= density)
    /*
    Esse While tem um problema: como ele aleatoriamente gera pares para tentar inserir, à medida que o grafo vai ficando
    mais denso a chance de conseguir gerar um novo par que funcione diminui. Então quanto mais perto de densidade 1 o grafo
    for, mais tempo ele vai ficar preso aqui tentando encontrar pares certos.
    */
    {
        // Pegando dois elementos aleatórios do grafo, pelos labels
        int vertice_1 = rand() % g->n_vertices;
        int vertice_2 = rand() % g->n_vertices;

        // Testando para ver se eles já não estão ligados
        printf("Testando se %d.....\n",vertice_1);
        vertice cur = create_item();
        printf("Is in here: ");
        for(cur = g->adjacency_list[vertice_2]->start; cur != NULL; cur = cur->next)
        {
            printf("%d, ",cur->label);
        }
        if(is_adjacent_to(vertice_1, g->adjacency_list[vertice_2]))
        {
            printf("\t Já é!\n");
            continue;  // Se um é adjacente do outro, o outro é adjacente do um, então pegamos um novo par de valores.
        }
        printf("\t Não é!\n");

        // Adicionando o vertice 1 como adjacente do 2
        add_adjacent(vertice_1, vertice_1, random_weight(max_weight), g->adjacency_list[vertice_2]);
        g->n_links++;
        // E adicionando o 2 como adjacente do 1
        add_adjacent(vertice_2, vertice_2, random_weight(max_weight), g->adjacency_list[vertice_1]);
        g->n_links++;
        // Atualizando o numero de links
        current_density = (float)g->n_links/(float)(2*max_links);
        printf("Densidade atual ----> %f\n",current_density);
        int x;
        printf("\t\tNumero atual de links: %d",g->n_links);
        scanf("%d",&x);
    }

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
            k++;
            printf("\t\t#%d: (%d,%d,%d)\n",k+1,current->label, current->value, current->weight);
        }
    }
}

void main(void)
{
    graph g = create_graph(5, 0.3, 0);
    printf("AAAANTES: Vertices -> %d",g->n_vertices);
    graph_report(g);

}