#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

void main(void)
{
    int contador_global = 2;
    int centena = 0, dezena = 0, unidade = 0;
    unidade = contador_global%10;
    dezena = (contador_global%100)/10;
    centena = (contador_global%1000)/100;

    printf("%d,%d,%d",centena,dezena,unidade);
}