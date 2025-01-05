#include "vector.h"
#include <stdlib.h>

vector* vector_new(double x, double y, double z) {
    vector *result = malloc(sizeof(vector));
    result->x = x;
    result->y = y;
    result->z = z;
    return result;
}