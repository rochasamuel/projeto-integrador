#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

void main(void)
{
    ptr_cabecalho_LL L = criarCabecalho();
    pushElemento(1,0,0,L);
    pushElemento(2,0,0,L);
    pushElemento(3,0,0,L);
    pushElemento(4,0,0,L);
    pushElemento(2,0,0,L);
    pushElemento(6,0,0,L);
    pushElemento(7,0,0,L);
    mostrarElementos(L);
    removerLoops(L);
    mostrarElementos(L);
}