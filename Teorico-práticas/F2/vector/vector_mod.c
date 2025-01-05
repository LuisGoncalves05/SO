#include "vector.h"
#include <math.h>

double vector_mod(vector* v1) {
    return sqrt(pow(v1->x, 2) + pow(v1->y, 2) + pow(v1->z, 2));
}