#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"


void main(void)
{
    ptr_cabecalho_LL minQ = criarCabecalho();
    minQ->id = 2;
    ptr_elemento N1 = criarElemento();
    N1->id = 3;
    N1->weight = 3;
    N1->elemento_de_origem = 2;
    pushListaMinimo(N1,minQ);
    mostrarLista(minQ);
    ptr_elemento N2 = criarElemento();
    N2->id = 2;
    N2->weight = 5;
    N2->elemento_de_origem = 4;
    pushListaMinimo(N2,minQ);
    mostrarLista(minQ);
    ptr_elemento N3 = criarElemento();
    N3->id = 2;
    N3->weight = 2;
    N3->elemento_de_origem = 5;
    pushListaMinimo(N3,minQ);
    mostrarLista(minQ);
    ptr_elemento N4 = criarElemento();
    N4->id = 6;
    N4->weight = 1;
    N4->elemento_de_origem = 6;
    pushListaMinimo(N4,minQ);
    mostrarLista(minQ);
    ptr_elemento N = criarElemento();
    N->id = 4;
    N->weight = 6;
    N->elemento_de_origem = 5;
    pushListaMinimo(N,minQ);
    mostrarLista(minQ);
    ptr_elemento K = criarElemento();
    K->id = 4;
    K->weight = 1;
    K->elemento_de_origem = 5;
    pushListaMinimo(K,minQ);
    mostrarLista(minQ);
}