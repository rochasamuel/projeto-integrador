#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


void main(void)
{
    int nodes, mw, should_print;
    float density;
    printf("Vertices: ");
    scanf("%d",&nodes);
    printf("\nDensity: ");
    scanf("%f",&density);
    printf("\nMax weight: ");
    scanf("%d",&mw);
    printf("\nShould print?: ");
    scanf("%d",&should_print);


    clock_t begin = clock();

<<<<<<< HEAD
    graph g = create_graph(nodes, density, mw, should_print);
=======
    graph g = preencherGrafo(nodes, density, mw, should_print);
>>>>>>> master
    //graph_report(g);
    clock_t end = clock();

    double delta = ((double)end-(double)begin)/CLOCKS_PER_SEC;
    printf("Total runtime: %.2f s\n",delta);
<<<<<<< HEAD
    to_txt(g);    
=======
    to_txt(g);
    int graph_r;
    printf("Report?\n");
    scanf("%d",&graph_r);
    if(graph_r == 1)
    {
        graph_report(g);   
    }    
>>>>>>> master
}