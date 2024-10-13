#include "vector.h"

vector* vector_sub(vector* v1, vector* v2) {
    return vector_new(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
}