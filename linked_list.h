#include <stdlib.h>
#include <stdio.h>


//pre-typedef'ing a pointer to a node as link
typedef struct node *vertice;

//Defining a node
struct node{
    int label;
    int value;
    int weight;
    vertice next;
    vertice previous;
};


// pre-typedef'ing a pointer to a linked-list as header
typedef struct header *linked_list;

// Defining a linked-list header
struct header{
    int len;
    vertice start;
    vertice end;
};


// On to the functions

linked_list create_list(void)
{
    linked_list L = malloc(sizeof(*L));
    L->len = 0;
    L->start = NULL;
    L->end = NULL;
    return L;
}

vertice create_item(void)
{
    vertice new_item = malloc(sizeof(*new_item));
    new_item->next = NULL;
    new_item->previous = NULL;
    return new_item;
}

void show_list(linked_list L)
{
    printf("L: -");
    vertice current = create_item();
    for(current = L->start; current != NULL; current = current->next)
    {
        printf("%d-",current->value);
    }
    printf("\n");
}

int delete_from_list(int target, linked_list L)
{
    vertice current = create_item();
    // Traversing the list
    if(L->start->value == target)
    {
        vertice temp = create_item();
        temp = L->start;
        L->start = temp->next;
        L->len--;
        free(temp);
        show_list(L);
        return 0;
    }
    for(current = L->start; current != NULL; current = current->next)
    {
        if(current->next->value == target)
        {
            vertice temp = create_item();
            temp = current->next;
            current->next = current->next->next;
            L->len--;
            free(temp);
            show_list(L);
            return 0;
        }
    }
    printf("Item not on list");
    return 0;
}

int push_at(int new_value, int at, linked_list L)
{
    if(at > L->len)
    {
        printf("List ain't that long");
        return 0;
    }
    int i;
    vertice new_item = create_item();
    new_item->value = new_value;
    vertice target_item = L->start;
    for(i = 0; i < at; i++)
    {
        target_item = target_item->next;
    }
    new_item->next = target_item->next->next;
    target_item->next = new_item;
    L->len++;
    show_list(L);
    return 0;
}

int push_at_start(int new_value, linked_list L)
{
    int i;
    vertice new_item = create_item();
    new_item->value = new_value;
    new_item->next = L->start;
    L->start = new_item;
    show_list(L);
    return 0;
}

int contains(int x, linked_list L)
{
    for(current = L->start; current != NULL; current = current->next)
    {
        if(current->value == x) return 1;
    }
    return 0;
}