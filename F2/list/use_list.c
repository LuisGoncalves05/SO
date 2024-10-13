#include <stdio.h>
#include "list.h"

int main() {
    list *l = list_new();

    list_print(l);
    list_add_first(2, l);
    list_print(l);
    list_add_first(1, l);
    list_print(l);
    list_add_last(3, l);
    list_print(l);
    list_add_last(4, l);
    list_print(l);
    printf("First element: %i\n", list_get_first(l));
    printf("Last element: %i\n", list_get_last(l));

    list_remove_first(l);
    list_print(l);
    list_remove_last(l);

    list_print(l);
    list_free(l);

    printf("\n");

    l = list_new();
    list_print(l);
    list_add_last(1, l);
    list_print(l);
    list_remove_last(l);

    list_print(l);
    list_free(l);
}