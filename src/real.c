#include <compalg/real.h>
#include <compalg/types.h>
#include <math.h>

int F_eq(RR x, RR y)
{
    return fabs(x - y) < EPS;
}
