#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


//Nomeando o ponteiro para a struct como 'ptr_elemento'
typedef struct list_item *ptr_elemento;

//Definindo um item da lista de adjacência
struct list_item{
    int id;  // Nome do vértice
    //int value;  // Valor do vértice
    int weight;  // Peso da conexão ao vértice
    int elemento_de_origem; // Atributo específico para uso pela priority_queue
    int total_distance; // Atributo específico para uso pela priority_queue
    ptr_elemento next; // Ponteiro pro próximo vértice na lista
    ptr_elemento previous;  // Ponteiro pro vértice anterior na lista
};


// Chamando a struct com a 'cabeça' da lista de adjacência de 'ptr_cabecalho_LL'
typedef struct linked_list *ptr_cabecalho_LL;

// Definindo a cabeça da lista de adjacência
struct linked_list{
    int number_of_elements;  // Tamanho da lista
    int sum_of_weights; // Soma de todos os pesos no Grafo
    int id;  // Nome do vértice a que a lista se refere
    ptr_elemento start;  // Vértice inicial da lista
    ptr_elemento end;  // Vértice final da lista
};


// Vamos àsfunções

ptr_cabecalho_LL criarCabecalho(void)
{
    // Essa função retorna um ponteiro para uma lista ligada de adjacência
    ptr_cabecalho_LL L = (ptr_cabecalho_LL)malloc(sizeof(*L));  // Alocação de memória
    L->number_of_elements = 0;  // Tamanho da lista
    L->sum_of_weights = 0;  // Soma de todos os pesos
    L->id = -1;  // Nome do vértice a que a lista se refere
    L->start = NULL; // Endereço do primeiro vértice da lista de adjacência
    L->end = NULL;  // Endereço do último vértice da lista de adjacência
    return L;
}

ptr_elemento criarElemento(void)
{
    // Cria um vértice para lista de adjacẽncia
    ptr_elemento new_item = (ptr_elemento)malloc(sizeof(*new_item));  // Alocação de memória
    new_item->next = NULL; // Ponteiro para o próximo vértice na lista de adjacẽnca
    new_item->previous = NULL;  // Ponteiro para o vértice anterior na lista de adjacência
    new_item->id = -1;  // Nome do vértice
    new_item->elemento_de_origem = -1;  // Atributo exclusivo para priority_queue;
    //new_item->value = 0;  // Valor do vértice
    new_item->weight = -1;  // Peso para conexão a este vértice nessa lista
    return new_item;
}

int mostrarElemento(ptr_elemento elemento)
{
    printf("\t[i:%d,w:%d,td:%d,o:%d]\n",elemento->id, 
                                        elemento->weight, 
                                        elemento->total_distance,
                                        elemento->elemento_de_origem);
    return 1;
}

void mostrarLista(ptr_cabecalho_LL L)
{
    // Cabeçalho da lista
    printf("{i:%d,l:%d,w:%d}:\n",L->id,L->number_of_elements,L->sum_of_weights);
    // Mostra os elementos da lista de adjacência
    ptr_elemento current = criarElemento();  // Cria um vértice local para receber os valores
    for(current = L->start; current != NULL; current = current->next)
    // For loop que itera sobre a lista toda
    // esse loop é usado diversas vezes.
    {
        // Printa 3-upla para cada item, com id, value e weight
        mostrarElemento(current);
    }
    printf("[]\n");
}

ptr_elemento popIdLista(int target_id, ptr_cabecalho_LL L)
{
    /*if(L->number_of_elements == 0)
    {
        return NULL;
    }*/

    // Remove o item de id 'target_id' da lista de adjacência

    ptr_elemento current = criarElemento();
    
    // Testando para o caso no qual o primeiro ptr_elemento da lista já é nosso alvo
    
    /*if(L->start->value == target_id)
    {
        L->sum_of_weights -= L->start->weight;
        ptr_elemento temp = criarElemento();
        temp = L->start;
        L->start = temp->next;
        L->number_of_elements--;  // Diminui o comprimento da lista em 1
        return temp;
    }*/

    // Itera sobre a lista para buscar item a ser removido
    for(current = L->start; current != NULL; current = current->next)
    {
        if(current->id == target_id)  // Se encontra o item com o ID alvo
        {
            L->sum_of_weights -= current->weight;  //Remove o peso do item removido do total
            if(current->previous != NULL)  // Testa se o current não é o primeiro da fila
            {                              // porque se for não tem um 'previous'
                current->previous->next = current->next; // Se pula com o 'next'
            }
            if(current->next != NULL)  // Testa se não é o último da fila
            {                          // porque o último não tem 'next'
                current->next->previous = current->previous;
            }
            L->number_of_elements--;  // Tira 1 do número de elementos da lista;
            return current;
        }
    }
    return NULL; // Caso não encontre o ID
}

ptr_elemento popPrimeiroLista(ptr_cabecalho_LL L)
{
    ptr_elemento primeiro_da_lista = criarElemento();
    primeiro_da_lista = L->start;  // Já coloca o primeiro no dummy
    if(primeiro_da_lista != NULL)  // Se não for lista vazia
    {
        L->start = primeiro_da_lista->next;
        if(L->start != NULL)  // Testa se a lista agora é vazia
        {
            L->start->previous = NULL;  // Se fosse único não teria 'previous'
        }
    }
    return primeiro_da_lista;
}


int pushLista(int new_id, int new_weight, ptr_cabecalho_LL L)
{
    // Adiciona vértice à lista de adjacência
    int i;
    ptr_elemento new_item = criarElemento();  // Cria novo vértice....
    new_item->id = new_id;
    new_item->weight = new_weight;  // ... e preenche os valores informados

    // Começa a operar sobre a lista
    new_item->next = L->start;  // Coloca o new_item pra apontar pro primeiro da lista
    new_item->previous = NULL;  //Previous NULL pois é o primeiro da lista
    if(new_item->next != NULL) // Só precisa reescrever o 'anterior' do primeiro item se houver um primeiro item
    {
        new_item->next->previous = new_item;  // Se existir next, liga ao atual via 'previous'
    }
    L->start = new_item;
    L->sum_of_weights += new_item->weight;  // Atualiza o total do peso da lista
    L->number_of_elements++;  // Adiciona mais um ao número de elementos da lista
    return 1;
}

/*
ptr_elemento elementoAleatorio(ptr_cabecalho_LL L)
{
    // Retorna membro aleatório da lista ligada, ou NULL se não houver.
    if(L->number_of_elements == 0)
    {
        return NULL;
    }
    int iterations = rand() % L->number_of_elements;
    ptr_elemento current = criarElemento();
    int counter;
    for(counter=0; counter < L->number_of_elements; counter++)
    {
        current = current->next;  // Vai até o iterations-ésimo elemento e o retorna.
    }
    return current;
}
*/

int pertenceLista(int id, ptr_cabecalho_LL L)
{
    // Testa se 'id' é pertencente a essa lista de adjacência e retorna o elemento, se não NULL.
    ptr_elemento current = criarElemento();
    for(current = L->start; current != NULL;current = current->next)
    {
        if(current->id == id)
        {
            return 1;
        }
    }
    return 0;
}

ptr_cabecalho_LL copiarLista(ptr_cabecalho_LL L)
{
    ptr_cabecalho_LL copia = criarCabecalho();
    copia->id = L->id;  // Copia o id da Lista de origem
    ptr_elemento current = criarElemento();
    for(current = L->start; current != NULL; current = current->next)
    {
        // A cada elemento não-NULL copia o ID e o peso;
        pushLista(current->id, current->weight, copia);
    }
    return copia;
}

/*
int removerLoops(ptr_cabecalho_LL L)
{
    // Vou usar os atributos da lista ligada já definida de uma forma um pouco diferente.

    ptr_cabecalho_LL arvore = criarCabecalho(); // por hora a definição é normal
    int iterations = L->number_of_elements;
    printf("Vou fazer %d iteracoes.\n",iterations);
    ptr_elemento current;
    int loops_found = 0;
    for(current = L->start; current != NULL; current = current->next)
    {
        printf("Vendo se %d esta na lista acima...\n",current->id);
        ptr_elemento antecessor = pertenceLista(current->id, arvore); //currentID está na árvore?
        if(antecessor != NULL) // Se não é NULL, está!
        {
            loops_found++;
            printf("Achei um loop!\n");
            printf("%d <-----> %d\n",antecessor->id, current->id);
            antecessor->next = current->next;
            if(antecessor->next != NULL)
            {
                antecessor->next->previous = antecessor;
            }
        }
        else
        {
            pushLista(current->id,current->value, current->weight, arvore);
            printf("Minha arvore atual.\n");
            mostrarElementos(arvore);
        }
    }
    return 1;
}
*/