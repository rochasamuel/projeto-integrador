#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

/*
    DIJKSTRA'S ALGORITHM

    Implementação do algoritmo de Dijkstras.
*/

/*

    Vamos começar com a implementação de uma fila de prioridade ao mínimo, ou seja:
ao fazer fila.pop() o elemento que sai é sempre o menor elemento da fila.

    A implementação vai ser feita em uma lista ligada que será sempre ordenada,
mantendo a ordenação a cada novo elemento inserido. O menor elemento será o 
primeiro elemento da fila, e será o removido assim que foi feito um .pop()

*/

/*
typedef struct element_min_priority_queue *ptr_elemento;

struct element_min_priority_queue{
    int label;
    int distance;
    int anterior;
    ptr_elemento next;
    ptr_elemento previous;
};

typedef struct min_priority_queue *ptr_cabecalho_LL;

struct min_priority_queue{
    int len;
    ptr_elemento start;
};
*/


/*

    Definição das funções de alocação de memória.

*/

/*
ptr_elemento create_ptr_elemento(void)
{
    ptr_elemento E = (ptr_elemento)malloc(sizeof(*E));
    E->id = -1;
    E->weight = -1;
    E->elemento_de_origem = -1;
    E->next = NULL;
    E->previous = NULL;
    return E;
};

ptr_cabecalho_LL criarCabecalho(void)
{
    ptr_cabecalho_LL Q = (ptr_cabecalho_LL)malloc(sizeof(*Q));
    Q->len = 0;
    Q->start = NULL;
    return Q;
}
*/

/*

    Agora à definição das funções usuais de uma fila: push(), pop(), is_empty(),
respeitando as peculiaridades de inserção na ordem correta.

*/

/*
ptr_elemento min_pop(ptr_cabecalho_LL Q)
{
    // Retorna o primeiro elemento da fila.
    //se a fila estiver vazia, NULL será retornado.
    printf("popando min.\n");
    ptr_elemento popped = create_ptr_elemento();
    if(Q->start == NULL)
    {
        return NULL;
    }
    popped = Q->start;
    Q->start = Q->start->next;
    if(Q->start == NULL)
    {
        return popped;
    }
    Q->start->previous = NULL;
    return popped;
    if(Q->len == 0)
    {
        printf("QLEN ZERO!\n");
        return NULL;
    }
    else if (Q->len == 1)
    {
        printf("QLEN UM!\n");
        popped = Q->start;
        Q->start = NULL;
        Q->len--;
        return popped;
    }
    printf("QLEN->%d",Q->len);
    popped = Q->start;
    printf("Popped:");
    min_show_element(popped); printf("\n");
    Q->start = Q->start->next;
    Q->start->previous = NULL;
    Q->len--;
    return popped;
}
*/

/*
ptr_elemento min_pop_by_id(int id, ptr_cabecalho_LL Q)
{
    // Retorna o elemento com id da fila.
    //se a fila estiver vazia, NULL será retornado.
    printf("popando id: %d\n",id);
    ptr_elemento to_pop = create_ptr_elemento();
    /*int i = 0;
    printf("QSTART: %d",i);
    min_show_element(Q->start);
    if(Q->start->id == id)
    {
        to_pop = Q->start;
        Q->start = Q->start->next;
        Q->start->previous == NULL;
        return to_pop;
    }* /
    for(to_pop = Q->start; to_pop != NULL; to_pop = to_pop->next)
    {
        if(to_pop->id == id)
        {
            to_pop->previous->next = to_pop->next;
            if(to_pop->next != NULL)
            {
                to_pop->next->previous = to_pop->previous;
            }
            Q->len--;
            return to_pop;
        }
    }
    return NULL;
}
*/

int pushListaMinimo(ptr_elemento newcomer, ptr_cabecalho_LL minQ)
{
    if(newcomer->id == newcomer->elemento_de_origem)
    {
        printf("\t\tMINQ_ELEMENT SAME SOURCE AND ID.\n");
        return 0;
    }
    ptr_elemento doppleganger = popIdLista(newcomer->id,minQ);
    if(doppleganger != NULL)  // Se realmente existir item com ID igual
    {
        if(newcomer->weight > doppleganger->weight)
        {
            newcomer = doppleganger;
            pushListaMinimo(newcomer, minQ);
            return 1;
        }
    }

    ptr_elemento current = NULL;
    ptr_elemento previous = NULL;
    for(current = minQ->start; current != NULL; current = current->next)
    {
        previous = current;  // Ele vai carregar o current pra fora do loop
        // Condição de saída diferente. Testa se o PRÓXIMO é nulo, ou seja,
        // se current é o último elemento da lista
        if(current->weight >= newcomer->weight)
        {
            if(current->previous == NULL)
            {
                minQ->start = newcomer;  // Caso em que ele é o primeiro da lista
            }else
            {
                current->previous->next = newcomer;
            }
            newcomer->previous = current->previous;
            current->previous = newcomer;
            newcomer->next = current;
            minQ->number_of_elements++;
            minQ->sum_of_weights += newcomer->weight;
            return 1;
        }
    }
    if(current == NULL && previous == NULL) // Fila vazia
    {
        minQ->start = newcomer;
        newcomer->previous = NULL;
        newcomer->next = NULL;
        minQ->number_of_elements++;
        minQ->sum_of_weights += newcomer->weight;
        return 1;
    }
    if(current == NULL && previous->previous == NULL)  // Current é o primeiro da fila
    {
        if(previous->weight >= newcomer->weight)
        {
            minQ->start = newcomer;
            newcomer->previous = NULL;
            newcomer->next = previous;
            previous->previous = newcomer;
            minQ->number_of_elements++;
            minQ->sum_of_weights += newcomer->weight;
            return 1;
        }
    }
    // Caso no qual current é o último da fila, ou seja, saiu do loop acima.
    if(current->weight >= newcomer->weight)
    {
        if(previous == NULL)
        {
            // Se previous for NULL, 
        }
    }
    newcomer->previous = previous;
    previous->next = newcomer;
    newcomer->next = NULL;
    if(newcomer->previous == NULL)
    {
        minQ->start = newcomer;  // Caso em que ele é o primeiro da lista
    }
    minQ->number_of_elements++;
    minQ->sum_of_weights += newcomer->weight;
    return 1;
    /*if(Q->start == NULL)
    {
        Q->start = newcomer;
        Q->len++;
        return 0;
    }*/
    
    
    /*
    printf("Inserting: {%d,%d,%d}\n",newcomer->id,newcomer->weight,newcomer->an);
    if(minQ->start == NULL)
    {
        printf("Q estava vazia.\n");
        minQ->start = newcomer;
        newcomer->previous = NULL;
        newcomer->next = NULL;

            min_show_queue(minQ);
        return 0;
    }
    ptr_elemento temp = create_ptr_elemento();
    int i=0;
    for(current = Q->start; current != NULL; current = current->next)
    {
        i++;
        printf("\tComparando com #%d: {%d,%d,%d}\n",i,current->id,current->weight,current->elemento_de_origem);
        temp = current;
        printf("\t\t %d >= %d ?\n",current->weight, newcomer->weight);
        if(current->weight >= newcomer->weight)
        {
            if(current->previous == NULL) //Caso no qual o current é o primeiro da fila
            {
                newcomer->next = current;
                current->previous = newcomer;
                Q->start = newcomer;
                newcomer->previous = NULL;
                printf("Era o primeiro.\n");
                min_show_queue(Q);
                return 0;
            }
            if(current->next == NULL)
            {
                current->previous->next = newcomer;
                newcomer->previous = current->previous;
                printf("\tO anterior do que entra agora é: %d\n",newcomer->previous->id);
                newcomer->next = current;
                
                min_show_queue(Q);
                return 0;
            }

            printf("\t\t\tSim!\n");
            newcomer->next = current;
            current->previous->next = newcomer;
            printf("Agora o proximo do %d é o %d.\n",newcomer->id, newcomer->next->id);
            newcomer->previous = newcomer;
            min_show_queue(Q);
            return 0;
        }
    }
    newcomer->previous = temp->previous;
    temp->previous = newcomer;
    newcomer->next = temp;
    min_show_queue(Q);
    return 0;
    */
}