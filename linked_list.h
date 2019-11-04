#include <stdlib.h>
#include <stdio.h>


//Nomeando o ponteiro para a struct como 'vertice'
typedef struct list_item *vertice;

//Definindo um item da lista de adjacência
struct list_item{
    int label;  // Nome do vértice
    int value;  // Valor do vértice
    int weight;  // Peso da conexão ao vértice
    vertice next; // Ponteiro pro próximo vértice na lista
    vertice previous;  // Ponteiro pro vértice anterior na lista
};


// Chamando a struct com a 'cabeça' da lista de adjacência de 'adjacents'
typedef struct linked_list *adjacents;

// Definindo a cabeça da lista de adjacência
struct linked_list{
    int len;  // Tamanho da lista
    int label;  // Nome do vértice a que a lista se refere
    vertice start;  // Vértice inicial da lista
    vertice end;  // Vértice final da lista
};


// Vamos àsfunções

adjacents create_list(void)
{
    // Essa função retorna um ponteiro para uma lista ligada de adjacência
    adjacents L = malloc(sizeof(*L));  // Alocação de memória
    L->len = 0;  // Tamanho da lista
    L->label = 0;  // Nome do vértice a que a lista se refere
    L->start = NULL; // Endereço do primeiro vértice da lista de adjacência
    L->end = NULL;  // Endereço do último vértice da lista de adjacência
    return L;
}

vertice create_item(void)
{
    // Cria um vértice para lista de adjacẽncia
    vertice new_item = malloc(sizeof(*new_item));  // Alocação de memória
    new_item->next = NULL; // Ponteiro para o próximo vértice na lista de adjacẽnca
    new_item->previous = NULL;  // Ponteiro para o vértice anterior na lista de adjacência
    new_item->label = 0;  // Nome do vértice
    new_item->value = 0;  // Valor do vértice
    new_item->weight = 0;  // Peso para conexão a este vértice nessa lista
    return new_item;
}

void show_adjacents(adjacents L)
{
    // Mostra os elementos da lista de adjacência
    printf("L: -");
    vertice current = create_item();  // Cria um vértice local para receber os valores
    for(current = L->start; current != NULL; current = current->next)
    // For loop que itera sobre a lista toda
    // esse loop é usado diversas vezes.
    {
        // Printa 3-upla para cada item, com label, value e weight
        printf("(%d,%d,%d)-",current->label, current->value, current->weight);
    }
    printf("\n");
}

int remove_adjacent(int target_label, adjacents L)
{
    // Remove o item de label 'target_label' da lista de adjacência
    vertice current = create_item();
    // Testando para o caso no qual o primeiro elemento da lista já é nosso alvo
    if(L->start->value == target_label)
    {
        vertice temp = create_item();
        temp = L->start;
        L->start = temp->next;
        L->len--;  // Diminui o comprimento da lista em 1
        free(temp);  // Libera espaço de temp na memória
        return 0;
    }
    // Itera sobre a lista para buscar item a ser removido
    for(current = L->start; current != NULL; current = current->next)
    {
        if(current->next->value == target_label)
        {
            vertice temp = create_item();
            temp = current->next;
            current->next = current->next->next;
            L->len--;
            free(temp);
            return 0;
        }
    }
    printf("Item not on list");
    return 0;
}

int add_adjacent(int new_label, int new_value, int new_weight, adjacents L)
{
    // Adiciona vértice à lista de adjacência
    int i;
    vertice new_item = create_item();  // Cria novo vértice....
    new_item->value = new_value;
    new_item->label = new_label;
    new_item->weight = new_weight;  // ... e preenche os valores informados
    new_item->next = L->start;
    new_item->previous = NULL;
    printf("\t\tVejamos o tamanho da lista de adjacentes: %d\n",L->len);
    if(L->len > 0) // Só precisa reescrever o 'anterior' do primeiro item se houver um primeiro item
    {
        L->start->previous = new_item;
    }
    L->start = new_item;  // E adiciona ele ao início da fila
    return 0;
}

int is_adjacent_to(int label, adjacents L)
{
    // Testa se 'label' é pertencente a essa lista de adjacência
    vertice current = create_item();
    for(current = L->start; current != NULL; current = current->next)
    {
        if(current->label == label) return 1;
    }
    return 0;
}