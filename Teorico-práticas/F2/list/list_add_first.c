#include "list.h"
#include <stdlib.h>

void list_add_first(int val, list *l) {
    if (l->size == 0) {
        node *first = malloc(sizeof(node));
        first->next = NULL;
        first->val = val;
        l->size++;
        l->first = first;
    } else {
        node *node = malloc(sizeof(node));
        node->next = l->first;
        l->first = node;
        node->val = val;
        l->size++;
    }
}