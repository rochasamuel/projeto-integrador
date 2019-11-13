#pragma once

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
    int nVertices;  // Número de vértices
    int nLinks;  // Número de arestas 
    ptr_cabecalho_LL *listaDeAdjacencia; // Vetor de listas ligadas, de adjacência
};

float rndWeight(int maxWeight)
{
    // Função para retornar pesos aleatórios aos vértices do grafo.
    if(maxWeight == 0) return 1;
    return 1 + (rand() % maxWeight);
}

graph esqueletoGrafo(int nVertices)
{
    // Inicialização do grafo, condição mínima de existência
    // Fazendo uma 'fila indiana' de conexões, onde 0 está ligado a 1, 1 a 2, 2 a 3, etc.
    // Se isso não for garantido o grafo fica fatiado em vários mini-grafos não contínuos.
    graph G = (graph)malloc(sizeof(*G));  // Aloca espaço na memória para struct de grafo
    G->nVertices = nVertices;  // Pré-determina número de vértices]
    G->nLinks = 0;  // Número de links é zero porque é incrementado dinamicamente
    G->listaDeAdjacencia = (ptr_cabecalho_LL*)malloc(sizeof(ptr_cabecalho_LL)*nVertices);
    // Cria vetor com tamanho 'v_vertices' de ponteiros para listas de adjacências.
    int i;
    for(i=0; i<nVertices; i++) 
    {
        // Inicializa cada elemento to vetor de listas ligadas
        G->listaDeAdjacencia[i] = criarCabecalho();  // Ponteiro para lista de adjacência
        G->listaDeAdjacencia[i]->number_of_elements = 0;  // Comprimento zero
        G->listaDeAdjacencia[i]->id = i;  // Label igual ao índice do vetor
    }
    return G;
}


graph preencherGrafo(graph G, float density, int maxWeight, int should_print)
{
    clock_t creation_start = clock();
    // Função que retorna struct 'grafo' preenchida com nVertices e densidade de links = 'density'
    clock_t init_start = clock();
    int i;
    for(i=0; i < G->nVertices; i++)
    {
        // Caso inicial, onde não há elemento anterior a adicionar
        /*
        Esse bloco de código adiciona, na lista de adjacência do vértice 0, o vértice
        1 como elemento.
        */
        if(i == 0)
        {
            int next_id = i+1;
            //int next_value = i+1;
            int next_weight = rndWeight(maxWeight);
            pushLista(next_id, next_weight, G->listaDeAdjacencia[i]);
            G->nLinks++;
        }

        /*
        Esse bloco de código adiciona, na lista de adjacência do último vértice do vetor
        de listas de adjacência , o penúltimo vértice como elemento.
        */
        else if(i == G->nVertices-1)
        {
            int next_id = i-1;
            //int next_value = i-1;
            int next_weight = rndWeight(maxWeight);
            pushLista(next_id, next_weight, G->listaDeAdjacencia[i]);
            G->nLinks++;
        }
        /*
        Essa opção default se aplica a todos os vértices que não são o primeiro e o último.
        Ela adiciona tanto o vértice anterior como o próximo vértice na sequência como 
        elementos da lista de adjacẽncia.
        */

        else        
        {
            int next_id = i+1;
            //int next_value = i+1;
            int next_weight = rndWeight(maxWeight);
            pushLista(next_id, next_weight, G->listaDeAdjacencia[i]);
            G->nLinks++;

            int prev_id = i-1;
            //int prev_value = i-1;
            int prev_weight = rndWeight(maxWeight);
            pushLista(prev_id, prev_weight, G->listaDeAdjacencia[i]);
            G->nLinks++;
        }
    }
    clock_t init_end = clock();
    double delta_init = ((double)init_end-(double)init_start)/CLOCKS_PER_SEC;
    

    if(density == 0)
    {
        // Se a densidade alvo for 0, ou seja, a menor possível, o grafo já está pronto.
        return G;
    }
    double max_links = (double)(((long)(G->nVertices)*(long)(G->nVertices - 1))/2.0)*0.95;  // Definindo valor máximo de links
                                                            //Coloquei um multiplicador de 0.95 porque 1 tava dando pau
    double current_density = ((double)G->nLinks/(double)(max_links))/2.0;  // Valor atual da densidade (links_atual/max)
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
        int vertice_1 = rand() % G->nVertices;
        int vertice_2;
        do
        {
            vertice_2 = rand() % G->nVertices;
        } while(vertice_1 == vertice_2);  // Para garantir que eles não são iguais
        clock_t different_end = clock();
        delta_different += delta_clock(different_start,different_end);
        

        // Testando para ver se eles já não estão ligados
        ptr_elemento cur = criarElemento();
        clock_t contem_start = clock();
        if(pertenceLista(vertice_1, G->listaDeAdjacencia[vertice_2]) != NULL)
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
        pushLista(vertice_1, rndWeight(maxWeight), G->listaDeAdjacencia[vertice_2]);
        G->nLinks++;
        // E adicionando o 2 como adjacente do 1
        pushLista(vertice_2, rndWeight(maxWeight), G->listaDeAdjacencia[vertice_1]);
        G->nLinks++;
        // Atualizando o numero de links
        clock_t push_end = clock();
        delta_push += delta_clock(push_start, push_end);
        current_density = ((double)G->nLinks/(double)(max_links))/2.0;
        clock_t loop_end = clock();
        delta_loop += delta_clock(loop_start,loop_end);
        if(clock_counter%100000 == 0 & should_print)
        {
            printf("nLinks: %.1f\n",(double)G->nLinks);
            printf("maxLinks: %.1f\n",(double)(max_links));
            clock_t elapsed_end = clock();
            double elapsed = delta_clock(init_start, elapsed_end);
            float wasted = 1.0-((float)valid_counter/(float)clock_counter);
            printf("Elapsed: %.2fs\tDen: %.6f\tWasted: %.7f\tDifTest: %.6fs\tdLoop: %.6fs\tdContem: %.6f\tdPush: %.6f\n",
            elapsed, current_density,wasted ,delta_different,delta_loop,delta_contem,delta_push);
            delta_casca = 0.0; delta_loop = 0.0; delta_different = 0.0; delta_contem = 0.0; delta_push = 0.0;
        }
        
    }
    printf("Total iterations: %d\n",clock_counter);
    printf("Total links: %d\n",G->nLinks);
    printf("Total initialization runtime: %.2f s\n",delta_init);
    return G;
}

int removerConexao(int id_A, int id_B, graph G)
{
    popIdLista(id_A, G->listaDeAdjacencia[id_B]);
    G->nLinks--;
    popIdLista(id_B, G->listaDeAdjacencia[id_A]);
    G->nLinks--;
    return 0;
}

int adicionarConexao(int id_A, int id_B, int maxWeight, graph G)
{
    if(pertenceLista(id_B, G->listaDeAdjacencia[id_A]) != NULL)
    {
        return 0;
    }
    pushLista(id_A, rndWeight(maxWeight),G->listaDeAdjacencia[id_B]);
    G->nLinks++;
    pushLista(id_B, rndWeight(maxWeight),G->listaDeAdjacencia[id_A]);
    G->nLinks++;
    return 1;
}

void graph_report(graph G)
{
    printf("Graph Report\n");
    printf("\tGraph Metadata\n");
    printf("\t Vertices: %d\n",G->nVertices);
    printf("\t Links reais: %d\n",G->nLinks/2);
    printf("Adjacency list\n");
    int i;
    for(i = 0; i < G->nVertices; i++)
    {
        printf("\tNode %d:\n",G->listaDeAdjacencia[i]->id);
        ptr_elemento current = criarElemento();
        int k = 0;
        for(current = G->listaDeAdjacencia[i]->start; current != NULL; current = current->next)
        {
            printf("\t\t#%d: (%d,%d)\n",k+1,current->id, current->weight);
            k++;
        }
    }
}

/*
ptr_cabecalho_LL listaDeElementos(graph G)
{
    ptr_cabecalho_LL elementos_restanterior = criarCabecalho();
    int i;

    for(i = 0; i < G->nVertices; i++)
    {
        pushLista(G->listaDeAdjacencia[i]->id, 0, 0, elementos_restanterior);
    }
    return elementos_restanterior;
}
*/

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
    for(i=0; i < G->nVertices; i++)
    {
        if(i == 0)
        {
            fprintf(f, "%d\n",G->nVertices);
            continue;
        }
        int origem = G->listaDeAdjacencia[i]->id;
        ptr_elemento current = criarElemento();
        for(current = G->listaDeAdjacencia[i]->start;
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


graph from_text(void)
{
    int line;
    FILE *f = fopen("./grafos_em_txt/300_grafo.txt","r");
    //FILE *f = fopen(path,"r");
    if(f == NULL)
    {
        printf("Deu ruim.\n");
    }
    graph G = NULL;
    for(line = 0; !feof(f); line++)
    {
        if(line == 0)
        {
            int nVertices;
            fscanf(f,"%d",&nVertices);
            G = esqueletoGrafo(nVertices);
            continue;
        }
        int node, adj, weight;
        fscanf(f,"%d,%d,%d",&node,&adj,&weight);
        pushLista(adj, weight, G->listaDeAdjacencia[node]);
        G->nLinks++;
    }
    return G;
}