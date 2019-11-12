#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função acessória pra calcular distância entre 2 clocks
double delta_clock(clock_t start, clock_t finish)
{
    double answer = ((double)finish-(double)start)/CLOCKS_PER_SEC;
    return answer;
}

// Definindo struct de grafo
typedef struct graph_structure *graph;

struct graph_structure{
    int n_vertices;  // Número de vértices
    int n_links;  // Número de arestas 
    ptr_cabecalho_LL *adjacency_list; // Vetor de listas ligadas, de adjacência
};

float random_weight(int max_weight)
{
    // Função para retornar pesos aleatórios aos vértices do grafo.
    if(max_weight == 0) return 1;
    return 1 + (rand() % max_weight);
}

graph create_graph(int n_vertices, float density, int max_weight, int should_print)
{
    clock_t creation_start = clock();
    // Função que retorna struct 'grafo' preenchida com n_vertices e densidade de links = 'density'
    int i;
    graph g = (graph)malloc(sizeof(*g));  // Aloca espaço na memória para struct de grafo
    g->n_vertices = n_vertices;  // Pré-determina número de vértices]
    g->n_links = 0;  // Número de links é zero porque é incrementado dinamicamente
    g->adjacency_list = (ptr_cabecalho_LL*)malloc(sizeof(ptr_cabecalho_LL)*n_vertices);
    // Cria vetor com tamanho 'v_vertices' de ponteiros para listas de adjacências.
    for(i=0; i<n_vertices; i++) 
    {
        // Inicializa cada elemento to vetor de listas ligadas
        g->adjacency_list[i] = criarCabecalho();  // Ponteiro para lista de adjacência
        g->adjacency_list[i]->number_of_elements = 0;  // Comprimento zero
        g->adjacency_list[i]->id = i;  // Label igual ao índice do vetor
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
            int next_id = i+1;
            int next_value = i+1;
            int next_weight = random_weight(max_weight);
            pushElemento(next_id, next_value, next_weight, g->adjacency_list[i]);
            g->n_links++;
        }

        /*
        Esse bloco de código adiciona, na lista de adjacência do último vértice do vetor
        de listas de adjacência , o penúltimo vértice como elemento.
        */
        else if(i == g->n_vertices-1)
        {
            int next_id = i-1;
            int next_value = i-1;
            int next_weight = random_weight(max_weight);
            pushElemento(next_id, next_value, next_weight, g->adjacency_list[i]);
            g->n_links++;
        }
        /*
        Essa opção default se aplica a todos os vértices que não são o primeiro e o último.
        Ela adiciona tanto o vértice anterior como o próximo vértice na sequência como 
        elementos da lista de adjacẽncia.
        */

        else        
        {
            int next_id = i+1;
            int next_value = i+1;
            int next_weight = random_weight(max_weight);
            pushElemento(next_id, next_value, next_weight, g->adjacency_list[i]);
            g->n_links++;

            int prev_id = i-1;
            int prev_value = i-1;
            int prev_weight = random_weight(max_weight);
            pushElemento(prev_id, prev_value, prev_weight, g->adjacency_list[i]);
            g->n_links++;
        }
    }
    clock_t init_end = clock();
    double delta_init = ((double)init_end-(double)init_start)/CLOCKS_PER_SEC;
    

    if(density == 0)
    {
        // Se a densidade alvo for 0, ou seja, a menor possível, o grafo já está pronto.
        return g;
    }
    float max_links = ((g->n_vertices)*(g->n_vertices - 1))/2.0;  // Definindo valor máximo de links
    float current_density = ((float)g->n_links/(float)(max_links))/2.0;  // Valor atual da densidade (links_atual/max)
                                                       // A multiplicação por 2 é porque os links estão contados duas vezes

    int clock_counter = 0;
    int valid_counter = 0;
    clock_t partial_start = clock(), contem_start = clock(), push_start = clock(); 
    double delta_casca = 0.0, delta_loop = 0.0, delta_different = 0.0, delta_contem = 0.0, delta_push = 0.0;
    while(current_density <= density)
    /*
    Esse While tem um problema: como ele aleatoriamente gera pares para tentar inserir, à medida que o grafo vai ficando
    mais denso a chance de conseguir gerar um novo par que funcione diminui. Então quanto mais perto de densidade 1 o grafo
    for, mais tempo ele vai ficar preso aqui tentando encontrar pares certos.
    */
    {
        clock_t loop_start = clock();
        clock_counter++;
        // Pegando dois elementos aleatórios do grafo, pelos ids
        clock_t different_start = clock();
        int vertice_1 = rand() % g->n_vertices, vertice_2;
        do
        {
            vertice_2 = rand() % g->n_vertices;
        } while(vertice_1 == vertice_2);
        clock_t different_end = clock();
        delta_different += delta_clock(different_start,different_end);
        

        // Testando para ver se eles já não estão ligados
        ptr_elemento cur = criarElemento();
        clock_t contem_start = clock();
        if(listaContem(vertice_1, g->adjacency_list[vertice_2]) != NULL)
        {
            clock_t contem_end = clock();
            delta_contem += delta_clock(contem_start,contem_end);
            continue;  // Se um é adjacente do outro, o outro é adjacente do um, então pegamos um novo par de valores.
        }
        valid_counter++;
        clock_t contem_end = clock();
        delta_contem += delta_clock(contem_start,contem_end);
        
        clock_t push_start = clock();
        // Adicionando o ptr_elemento 1 como adjacente do 2
        pushElemento(vertice_1, vertice_1, random_weight(max_weight), g->adjacency_list[vertice_2]);
        g->n_links++;
        // E adicionando o 2 como adjacente do 1
        pushElemento(vertice_2, vertice_2, random_weight(max_weight), g->adjacency_list[vertice_1]);
        g->n_links++;
        // Atualizando o numero de links
        clock_t push_end = clock();
        delta_push += delta_clock(push_start, push_end);
        current_density = ((float)g->n_links/(float)(max_links))/2.0;
        clock_t loop_end = clock();
        delta_loop += delta_clock(loop_start,loop_end);
        if(clock_counter%100000 == 0 & should_print)
        {
            clock_t elapsed_end = clock();
            double elapsed = delta_clock(init_start, elapsed_end);
            float wasted = 1.0-((float)valid_counter/(float)clock_counter);
            printf("Elapsed: %.2fs\tDen: %.6f\tWasted: %.7f\tDifTest: %.6fs\tdLoop: %.6fs\tdContem: %.6f\tdPush: %.6f\n",
            elapsed, current_density,wasted ,delta_different,delta_loop,delta_contem,delta_push);
            delta_casca = 0.0; delta_loop = 0.0; delta_different = 0.0; delta_contem = 0.0; delta_push = 0.0;
        }
        
    }
    printf("Total iterations: %d\n",clock_counter);
    printf("Total links: %d\n",g->n_links);
    printf("Total initialization runtime: %.2f s\n",delta_init);
    return g;
}

int remove_link(int id_A, int id_B, graph G)
{
    popElemento(id_A, G->adjacency_list[id_B]);
    G->n_links--;
    popElemento(id_B, G->adjacency_list[id_A]);
    G->n_links--;
    return 0;
}

int add_link(int id_A, int value_A, int max_weight_A, 
                int id_B, int value_B, int max_weight_B,  graph G)
{
    if(listaContem(id_B, G->adjacency_list[id_A]) != NULL)
    {
        return 0;
    }
    pushElemento(id_A, value_A, random_weight(max_weight_A),G->adjacency_list[id_B]);
    G->n_links++;
    pushElemento(id_B, value_B, random_weight(max_weight_B),G->adjacency_list[id_A]);
    G->n_links++;
    return 1;
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
        printf("\tNode %d:\n",g->adjacency_list[i]->id);
        ptr_elemento current = criarElemento();
        int k = 0;
        for(current = g->adjacency_list[i]->start; current != NULL; current = current->next)
        {
            printf("\t\t#%d: (%d,%d)\n",k+1,current->id, current->weight);
            k++;
        }
    }
}

ptr_cabecalho_LL listaDeElementos(graph G)
{
    ptr_cabecalho_LL elementos_restantes = criarCabecalho();
    int i;

    for(i = 0; i < G->n_vertices; i++)
    {
        pushElemento(G->adjacency_list[i]->id, 0, 0, elementos_restantes);
    }
    return elementos_restantes;
}

int to_txt(graph G)
{
    int n1,n2,n3;
    printf("3 dnmeros separados por vírgulas");
    scanf("%d,%d,%d",&n1,&n2,&n3);
    char file_name[] = "./grafos_em_txt/xxx_grafo.txt";
    int c_index = 16, d_index = 17, u_index = 18;
    file_name[c_index] = n1+'0';
    file_name[d_index] = n2+'0';
    file_name[u_index] = n3+'0';
    printf("%s",file_name);
    FILE *f = fopen(file_name,"w");
    if(f ==NULL)
    {
        printf("Deu ruim!\n");
        return 0;
    }

    int i;
    for(i=0; i < G->n_vertices; i++)
    {
        int origem = G->adjacency_list[i]->id;
        ptr_elemento current = criarElemento();
        for(current = G->adjacency_list[i]->start;
            current != NULL; 
            current = current ->next)
            {
                int destino = current->id;
                int peso = current->weight;
                fprintf(f, "%d,%d,%d\n",origem,destino,peso);
            }
    }
    fclose(f);
    return 0;
}