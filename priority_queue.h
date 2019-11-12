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
int min_show_element();
int min_show_queue();


typedef struct element_min_priority_queue *min_element;

struct element_min_priority_queue{
    int label;
    int distance;
    int antes;
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
    E->antes = -1;
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
    printf("popando min.\n");
    min_element popped = create_min_element();
    for(popped = Q->start; popped != NULL; popped = popped->next)
    {
        Q->start = popped->next;
        return popped;
    }
    return popped;
    /*if(Q->len == 0)
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
    return popped;*/
}

min_element min_pop_by_id(int id, min_queue Q)
{
    // Retorna o elemento com id da fila.
    //se a fila estiver vazia, NULL será retornado.
    printf("popando id: %d\n",id);
    min_element popped = create_min_element();
    int i = 0;
    printf("QSTART: %d",i);
    min_show_element(Q->start);
    if(Q->start->label == id)
    {
        popped = Q->start;
        Q->start = Q->start->next;
        Q->start->previous == NULL;
        return popped;
    }
    for(popped = Q->start; popped != NULL; popped = popped->next)
    {

        i++;
        min_show_element(popped);
        printf("loop #%d: label: %d",i,popped->label);
        if(popped->label == id)
        {
            popped->previous->next = popped->next;
            if(popped->next != NULL)
            {
                popped->next->previous = popped->previous;
            }
            Q->len--;
            return popped;
        }
    }
    return NULL;
}

int min_push(min_element pushed, min_queue Q)
{
    printf("PUSHING :");
    min_show_element(pushed);
    printf("\nInto:");
    min_show_queue(Q);
    printf("\n");
    int target_distance = pushed->distance;
    min_element current = create_min_element();
    min_element last_one = create_min_element();
    if(Q->len == 0)
    {
        Q->start = pushed;
        Q->len++;
        return 0;
    }
    printf("ok, %d not zero.\n",Q->len);
    for(current = Q->start; current != NULL; current = current->next)
    {
        printf("Begin pushing\n.");
        printf("Current: ");
        min_show_element(current);
        int cur_dis = current->distance;
        printf("\nTarget distance: %d\n",target_distance);
        printf("Current distance: %d\n",cur_dis);
        if(cur_dis >= target_distance)
        {
            printf("Q->len: %d",Q->len);
            if(Q->len == 1)
            {
                printf("Q com len 1.\n");
                Q->start->previous = pushed;
                pushed->next = Q->start;
                Q->start = pushed;
                Q->len++;
                return 0;
            }
            printf("Current:");
            min_show_element(current);
            printf("Pushed: ");
            min_show_element(pushed);
            pushed->previous = current->previous;
            if(current->previous != NULL)
            {
                pushed->previous->next = pushed;
            }
            else
            {
                Q->start = pushed;
            }
            
            pushed->next = current;
            Q->len++;
            return 0;
        }
        printf("Trying last one: ");
        min_show_element(last_one);
        printf("\n");
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
    if(to_show != NULL)
    {
        printf("(%d,%d,%d)",to_show->label,to_show->distance, to_show->antes);
        return 0;
    }
    printf("Nothing here.\n");
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

