#include "list.h"

int list_get_first(list *l) {
    return l->first->val;
}
