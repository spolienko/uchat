#include "libmx.h"

void *mx_realloc(void *ptr, size_t size) {
    void *new_ptr = NULL;
    size_t len_ptr;

    if (!ptr && size)
        return (void *)mx_strnew(size);
    if (size == 0 && ptr) {
        free(ptr);
        return NULL;
    }
    len_ptr = mx_strlen(ptr);
    if (len_ptr > size)
        new_ptr = (void *)mx_strnew(len_ptr);
    else
        new_ptr = (void *)mx_strnew(size);
    if (!new_ptr)
        return NULL;
    mx_memcpy(new_ptr, ptr, size);
    free(ptr);
    return (void *)new_ptr;
}

