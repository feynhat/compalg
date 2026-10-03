#ifndef LA_H
#define LA_H

#include "../compalg/types.h"
#include "../compalg/rational.h"
#include "../compalg/real.h"

#include <stdlib.h>

void QQMat_init(QQMat *, size_t, size_t);
void QQMat_free(QQMat *);
void QQMat_fromZZ(QQMat *, size_t, size_t, ZZ *);
void QQMat_copy(QQMat *, const QQMat *);

void QQMat_set(QQMat *, size_t, size_t, QQ *);
void QQMat_get(QQ *, const QQMat *, size_t, size_t);

/* void QQMat_print(const QQMat *); */

void QQMat_mul(QQMat *, const QQMat *, const QQMat *);
void QQMat_gaussian(QQMat *, const QQMat *);
void QQMat_solve(QQMat *res, const QQMat *mat, const QQMat *vec);
int QQMat_is_inv(const QQMat *);
void QQMat_hilbert(QQMat *, size_t);

void RanZMat(QQMat *, size_t, size_t);

void FMat_init(FMat *, size_t, size_t);
void FMat_free(FMat *);
void FMat_fromZZ(FMat *, size_t, size_t, ZZ *);
void FMat_copy(FMat *, const FMat *);

void FMat_set(FMat *, size_t, size_t, RR);
RR FMat_get(const FMat *, size_t, size_t);

/* void FMat_print(const FMat *); */

void FMat_mul(FMat *, const FMat *, const FMat *);
void FMat_gaussian(FMat *, const FMat *);
void FMat_solve(FMat *res, const FMat *mat, const FMat *vec);
int FMat_is_inv(const FMat *);
void FMat_hilbert(FMat *, size_t);

void RanFMat(FMat *, size_t, size_t);

#endif
