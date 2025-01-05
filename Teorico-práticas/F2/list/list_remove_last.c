#include "list.h"
#include <stdlib.h>

void list_remove_last(list *l) {
    node* current = l->first;
    node* before = NULL;
    while (current->next) {
        before = current;
        current = current->next;
    }
    l->size--;
    if (before) {
        before->next = NULL;
    } else {
        l->first = NULL;
    }
    free(current);
}