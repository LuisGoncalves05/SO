#include "list.h"
#include <stdlib.h>

node* node_new(int val, node* p) {
    node* q = (node*)malloc(sizeof(node));
    q->val = val;
    q->next = p;
    return q;
}