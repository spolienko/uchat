#include "libmx.h"

void mx_push_back(t_list **list, void *data) {
    t_list *last = mx_create_node(data);
    t_list *current = *list;

    if (*list == NULL)
        *list = last;
    else {
        while (current->next != NULL)
            current = current->next;
        current->next = last;
    }
}

