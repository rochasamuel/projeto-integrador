#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


void main(void)
{
    int nodes, mw;
    float density;
    printf("Vertices: ");
    scanf("%d",&nodes);
    printf("\nDensity: ");
    scanf("%f",&density);
    printf("\nMax weight: ");
    scanf("%d",&mw);

    clock_t begin = clock();

    graph g = create_graph(nodes, density, mw);
    //graph_report(g);
    clock_t end = clock();

    double delta = ((double)end-(double)begin)/CLOCKS_PER_SEC;
    to_txt(3,0,0,g);
    printf("Total runtime: %.2f s\n",delta);
}