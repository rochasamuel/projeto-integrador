#include <stdlib.h>
#include <stdio.h>


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

typedef struct element_min_priority_queue *min_element;

struct element_min_priority_queue{
    int label;
    int distance;
    min_element next;
    min_element previous;
};

typedef struct min_priority_queue *min_queue;

struct min_priority_queue{
    int len;
    min_element start;
};

/*

    Definição das funções de alocação de memória.

*/

min_element create_min_element(void)
{
    min_element E = (min_element)malloc(sizeof(*E));
    E->label = -1;
    E->distance = -1;
    E->next = NULL;
    E->previous = NULL;
    return E;
};

min_queue create_min_queue(void)
{
    min_queue Q = (min_queue)malloc(sizeof(*Q));
    Q->len = 0;
    Q->start = NULL;
    return Q;
}


/*

    Agora à definição das funções usuais de uma fila: push(), pop(), is_empty(),
respeitando as peculiaridades de inserção na ordem correta.

*/

min_element min_pop(min_queue Q)
{
    // Retorna o primeiro elemento da fila.
    //se a fila estiver vazia, NULL será retornado.

    min_element popped = create_min_element();
    if(Q->len == 0)
    {
        return NULL;
    }
    else if (Q->len == 1)
    {
        
        popped = Q->start;
        Q->start = NULL;
        Q->len--;
        return popped;
    }
    popped = Q->start;
    Q->start = Q->start->next;
    Q->start->previous = NULL;
    Q->len--;
    return popped;
}

int min_push(min_element pushed, min_queue Q)
{
    int target_distance = pushed->distance;
    min_element current = create_min_element();
    min_element last_one = create_min_element();
    if(Q->len == 0)
    {
        Q->start = pushed;
        Q->len++;
        return 0;
    }
    for(current = Q->start; current != NULL; current = current->next)
    {
        if(current->distance >= target_distance)
        {
            if(Q->len == 1)
            {
                Q->start->previous = pushed;
                pushed->next = Q->start;
                Q->start = pushed;
                Q->len++;
                return 0;
            }
            pushed->previous = current->previous;
            pushed->previous->next = pushed;
            pushed->next = current;
            Q->len++;
            return 0;
        }
        last_one = current;
    }
    last_one->next = pushed;
    pushed->previous = last_one;
    Q->len++;
    return 0;
}

int is_empty(min_queue Q)
{
    if(Q->len == 0)
    {
        return 1;
    }
    return 0;
}

int min_show_element(min_element to_show)
{
    printf("(%d,%d)",to_show->label,to_show->distance);
    return 0;
}

int min_show_queue(min_queue Q)
{
    printf("Queue: \n");
    int counter = 1;
    min_element current = create_min_element();
    if(Q->len == 0)
    {
        printf("Empty queue.\n");
        return 0;
    }
    for(current = Q->start; current != NULL; current = current->next)
    {
        printf("#%d: ",counter); min_show_element(current); printf("\n");
        counter++;
    }
    return 0;
}

