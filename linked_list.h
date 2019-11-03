#include <stdlib.h>
#include <stdio.h>


//pre-typedef'ing a pointer to a node as link
typedef struct list_item *vertice;

//Defining a node
struct list_item{
    int label;
    int value;
    int weight;
    vertice next;
    vertice previous;
};


// pre-typedef'ing a pointer to a linked-list as header
typedef struct linked_list *adjacents;

// Defining a linked-list header
struct linked_list{
    int len;
    int label;
    vertice start;
    vertice end;
};


// On to the functions

adjacents create_list(void)
{
    adjacents L = malloc(sizeof(*L));
    L->len = 0;
    l->label = 0;
    L->start = NULL;
    L->end = NULL;
    return L;
}

vertice create_item(void)
{
    vertice new_item = malloc(sizeof(*new_item));
    new_item->next = NULL;
    new_item->previous = NULL;
    new_item->label = 0;
    new_item->value = 0;
    new_item->weight = 0;
    return new_item;
}

void show_adjacents(adjacents L)
{
    printf("L: -");
    vertice current = create_item();
    for(current = L->start; current != NULL; current = current->next)
    {
        printf("%d-",current->value);
    }
    printf("\n");
}

int remove_adjacent(int target_label, adjacents L)
{
    vertice current = create_item();
    // Traversing the list
    if(L->start->value == target)
    {
        // In case target value is fist on the list
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

int add_adjacent(int new_label, int new_value, int new_weight, adjacents L)
{
    int i;
    vertice new_item = create_item();
    new_item->value = new_value;
    new_item->label = new_label;
    new_item->weight = new_weight;
    new_item->next = L->start;
    new_item->previous = NULL;
    L->start = new_item;
    return 0;
}

int is_adjacent_to(int label, adjacents L)
{
    for(current = L->start; current != NULL; current = current->next)
    {
        if(current->label == label) return 1;
    }
    return 0;
}