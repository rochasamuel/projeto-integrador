#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

void main(void)
{
    char clean_buffer[1000];
    int value = 0;
    int graph_index = 0;
    FILE *f;
    int to_push;
    f = fopen("values.txt","r");
    char sep = ',';
    char justread;
    char * buffer = clean_buffer;
    while(justread = fgetc(f) != EOF)
    {
        
        if(justread == '\n')
        {
            graph_index++;
        }
        if(justread == sep)
        {
            sscanf(buffer, &to_push);
            push_at_start(to_push, graph[graph_index]);
            buffer = clean_buffer;
        }
        strcat(buffer, &justread,1);
    }
    fclose(f);

    show_list(graph[1]);
}