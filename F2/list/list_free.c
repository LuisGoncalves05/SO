#include "list.h"
#include <stdlib.h>

void list_free(list *l) {
    if (l->first) {
        node *current = l->first->next;
        node *next = current->next;
        while (next) {
            free(current);
            current = next;
            next = next->next;
        }
    }
    free(l);
}