#include "libmx.h"

int mx_list_size(t_list *list) {
    t_list *current = list;
    int count = 0;

    while (current != NULL) {
        current = current->next;
        count++;
    }
    return count;
}

