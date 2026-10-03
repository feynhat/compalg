#ifndef TYPES_H

#define TYPES_H

#include <stdlib.h>

typedef long ZZ;
typedef double RR;

typedef struct {
    ZZ numer, denom;
} QQ;

typedef unsigned char byte;

typedef struct {
    size_t nrows;
    size_t ncols;
    QQ *entries;
} QQMat;

typedef struct {
    size_t nrows;
    size_t ncols;
    RR *entries;
} FMat;

#endif
