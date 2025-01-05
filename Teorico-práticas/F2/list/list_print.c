#include "list.h"
#include <stdio.h>

void list_print(list* l) {
    printf("(");
    node* current = l->first;
    if (current) {
        while (current->next) {
            printf("%d,", current->val);
            current = current->next;
        }
        printf("%d", current->val);
    }
    printf(")\n");
}