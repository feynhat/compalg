#ifndef RATIONAL_H
#define RATIONAL_H

#include "../compalg/types.h"
#include "../compalg/nt.h"

void QQ_set(QQ *, ZZ, ZZ);

void QQ_red(QQ *);
void QQ_inv(QQ *, const QQ *);

void QQ_add(QQ *, const QQ *, const QQ *);
void QQ_sub(QQ *, const QQ *, const QQ *);
void QQ_mul(QQ *, const QQ *, const QQ *);
void QQ_div(QQ *, const QQ *, const QQ *);

int QQ_eq(const QQ *, const QQ *);

double QQ_to_dbl(const QQ *);

int QQ_print(const QQ *);

#endif
