#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "dijkstra.h"


/*
    DIJKSTRA'S ALGORITHM

    Implementação do algoritmo de Dijkstras.
*/


void main(void)
{
    int nVertices;    
    int seed = time(0);
    srand(seed);
    int centena = 0, dezena = 0, unidade = 0;
    //FILE *report = fopen("./grafos_em_txt/A report.txt","w");
    //const char *colunas = "grafo,vertices,densidade,maxweight,segundos,distancia_total,caminho\n";
    //fclose(report);
    //fprintf(report,"%s",colunas);
    int contador_global = 444;
    int maxWeight;
    float density;
    graph G;
    int fromFile = 1, start = 1, finish = 486;
    for(nVertices = 487; nVertices <=487; nVertices+= 500)
    {//graph_report(G);
        for(maxWeight=500;maxWeight<=500;maxWeight+=500)
        {
            for(density=0.35;density < 0.36;density+=0.3)
            {
                
                contador_global++;
                unidade = contador_global%10;
                dezena = (contador_global%100)/10;
                centena = (contador_global%1000)/100;
                if(fromFile == 0)
                {
                    
                    G = esqueletoGrafo(nVertices);
                    preencherGrafo(G, density, maxWeight, 1);
                    printf("Gonna write now.\n");
                    to_txt(G,centena,dezena,unidade);
                    //graph_report(G);
                    FILE *report = fopen("./grafos_em_txt/A report.txt","a");
                    fprintf(report, "%d,%d,%f,%d,",contador_global,nVertices,density,maxWeight);
                    graph destructable = copy_graph(G);
                    test_run(destructable, start,finish,report);
                    fclose(report);printf("V:%d\tD:%.2f\tW:%d\t\n",nVertices,density,maxWeight);
                }
                else
                {
                    G = from_text();
                    density = G->nLinks/(G->nVertices*(G->nVertices-1));
                    FILE *report = fopen("./grafos_em_txt/A report.txt","a");
                    fprintf(report, "%d,%d,%f,%d,",contador_global,nVertices,density,maxWeight);
                    graph destructable = copy_graph(G);
                    test_run(destructable, start,finish,report);
                    fclose(report);printf("V:%d\tD:%.2f\tW:%d\t\n",nVertices,density,maxWeight);
                    return;
                }
            }
        }
    }
    //fclose(report);
        

   /*
    graph G = from_text();
    //graph_report(H);
    graph destructable2 = copy_graph(G);
    int start = 1;
    int finish = 5;
    printf("de %d a %d\n",start,finish);
    test_run(destructable2, start,finish);

    G = from_text();
    //graph_report(H);
    destructable2 = copy_graph(G);
    start = 15;
    finish = 953;
    printf("de %d a %d\n",start,finish);
    test_run(destructable2, start,finish);

    G = from_text();
    //graph_report(H);
    destructable2 = copy_graph(G);
    start = 547;
    finish = 879;
    printf("de %d a %d\n",start,finish);
    test_run(destructable2, start,finish);

    G = from_text();
    //graph_report(H);
    destructable2 = copy_graph(G);
    start = 999;
    finish = 1;
    printf("de %d a %d\n",start,finish);
    test_run(destructable2, start,finish);

    G = from_text();
    //graph_report(H);
    destructable2 = copy_graph(G);
    start = 958;
    finish = 98;
    printf("de %d a %d\n",start,finish);
    test_run(destructable2, start,finish);
   */
}