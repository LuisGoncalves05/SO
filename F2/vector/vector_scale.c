#include "vector.h"

vector* vector_scale(double scaler, vector* v) {
    return vector_new(scaler * v->x, scaler * v->y, scaler * v->z);
}