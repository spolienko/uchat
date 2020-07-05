#include "libmx.h"

t_list *mx_create_node(void *data) {
    t_list *new_node = NULL;

    new_node = (t_list*)malloc(sizeof(t_list));
    new_node->data = strdup((char *)data);
    new_node->next = NULL;
    return new_node;
}

