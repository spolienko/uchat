#include "libmx.h"

int mx_bubble_sort(char **arr, int size) {
    char* temp;
    int count = 0;

    for (int i = 0; i < size - 1; i++) {
        for (int g = 0; g < size - 1 - i; g++) {
	    if (mx_strcmp(arr[g], arr[g + 1]) > 0) {
                temp = arr[g];
                arr[g] = arr[g + 1];
                arr[g + 1] = temp;
                count++;
            }
        }
    }
    return count;
}

