#include "list.h"
#include <stdlib.h>

int list_get_last(list *l) {
    node *current = l->first->next;
    while (current->next != NULL) {
        current = current->next;
    }
    return current->val;
}
