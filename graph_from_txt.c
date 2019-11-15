#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

void main()
{
    graph G = from_text();
    graph_report(G);    
}