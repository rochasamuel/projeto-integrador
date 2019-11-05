#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

int main(void)
{
    int user;
    min_queue Q = create_min_queue();
    do
    {
        int label, distance;
        printf("Menu:\n\tPush - 1\n\tPop - 2\n\tIs empty - 3\n\tShow - 4\n\tBreak - 9\n");
        scanf("%d",&user);
        min_element subject = create_min_element();
        switch (user)
        {
        case 1: // Push
            printf("Digite label e distância separados por vírgula:\n");
            scanf("%d,%d",&label,&distance);
            subject->label = label;
            subject->distance = distance;
            min_push(subject,Q);
            break;
        case 2:  // Pop
            subject = min_pop(Q);
            if(subject != NULL)
            {
                min_show_element(subject);
                printf("\n");
                break;
            }
            printf("Queue empty.\n");
            break;
        case 3:  // Is empty
            if(is_empty(Q))
            {
                printf("Yes, it's empty.\n");
            }
            else
            {
                printf("Nope, has %d elements.\n",Q->len);
            }
            
            break;
        case 4:  // Show
            min_show_queue(Q);
            break;
        case 9:  // Break
            printf("Bye :)\n");
            break;
        
        default:
        printf("Opção inválida.\n");
            break;
        }
    } while(user != 9);
    
}