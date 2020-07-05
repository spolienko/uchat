#include "libmx.h"

void mx_push_front(t_list **list, void *data) {
    t_list *first = mx_create_node(data);
    first->next = (*list);
    (*list) = first;
}

