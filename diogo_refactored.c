#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "graph.h"
#include "linked_list.h"

#define QtNode 10
#define INF 1000                //Valor absurdo para conexao inexistente
#define TamanhoPopulacao 10     //Quantidade de cromossomos em cada geracao
#define ORIGEM 1                //Node de origem dos cromossomos
#define DESTINO 2               //Node de destino dos cromossomos
#define TaxaMutacao 50
#define TaxaElitismo 10   //Referente a permanencia de percentual de individuos para a proxima geracao
#define QtGeracoes 10

/*
    **ANTES DE COMPILAR: Ajeitar caminho absoluto do arquivo -> graph.txt
*/
#define path "/Users/diogotelheirodonascimento/Desktop/PI/graph.txt" //Caminho ABSOLUTO do arquivo txt que contem a estrutura do grafo


/*
**Retorna 1 se o node nao possuir conexoes
**Retorna 0 se o node possuir conexoes
*/
int semConexao(ptr_cabecalho_LL Node)
{
    if(Node->len == 0)
    {
        return 1;
    }
    return 0;
}

/*
**Utiliza endereco de array de node para acrescentar conexoes com devido peso
**acrescenta o endereco do destino na proxima posicao disponivel da lista ligada da origem
*/


// A função de criar aresta está na biblioteca 'linked_list.h' (é um elemento)

// A função de inicializar um Gene está na biblioteca 'linked_list.h' (é um elemento)

// A função de inicializar um GeneNode está na biblioteca 'linked_list.h' (é um elemento)

// A função de calcular o peso do cromossomo pode ser substituída pelo atributo .sum_of_weights

ptr_cabecalho_LL caminhoAleatorio(graph G, int id_START, int id_END)
{   // Returna LL se gerou, NULL se não.
    // Primeiro uma lista ligada com todos os ids de elementos do grafo
    ptr_cabecalho_LL elementos_restantes = copiarLista(listaDeElementos(G));  // É uma lista ligada isso aqui.
    // Agora, a partir do id_START, juntar aleatoriamente vértices, até acabar com eles ou chegar ao destino.

    ptr_cabecalho_LL caminho_aleatorio = criarCabecalho();
    ptr_elemento to_add = popElemento(id_START, elementos_restantes);
    while(to_add != NULL & elementos_restantes->number_of_elements > 0)
    {
        pushElemento(to_add->id, to_add->value, to_add->weight, caminho_aleatorio);
        to_add = elementoAleatorio(G->adjacency_list[to_add->id]);
        popElemento(to_add->id, elementos_restantes);
        if(to_add->id == id_END)
        {
            pushElemento(to_add->id, to_add->value, to_add->weight, caminho_aleatorio);
            return caminho_aleatorio;
        }
    }
    return NULL;
}

int removerLoops(ptr_)