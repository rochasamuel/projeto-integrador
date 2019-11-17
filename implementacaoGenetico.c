#include "genetico.h"


int TamanhoPopulacao;
int ORIGEM = 1;
int DESTINO = 486;
int TaxaMutacao;
int TaxaElitismo;
int TaxaMutagenicos;

void main(void)
{
    int i;
    scanf("%d,%d,%d,%d",&TamanhoPopulacao, &TaxaMutacao, &TaxaElitismo, &TaxaMutagenicos);
    for(i=0;i<10;i++)
    {
        algoritmoGenetico(487,TamanhoPopulacao,ORIGEM,DESTINO,TaxaMutacao,TaxaElitismo,TaxaMutagenicos);
    }
}