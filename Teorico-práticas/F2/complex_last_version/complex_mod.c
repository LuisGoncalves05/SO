#include <math.h>
#include "complex.h"

double complex_mod(complex z){
    return sqrt(z.x * z.x + z.y * z.y);
}