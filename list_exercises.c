#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

void main(void)
{
    linked_list L = create_list();
    push_at_start(4,L);
    push_at_start(2,L);
    push_at_start(3,L);
}