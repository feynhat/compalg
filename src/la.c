#include "../compalg/la.h"
#include "../compalg/types.h"
#include "../compalg/rational.h"

#include <stdlib.h>
#include <stdio.h>

/****************************************************************************/
/* Rational Matrices                                                        */
/****************************************************************************/

void QQMat_init(QQMat *mat, size_t nrows, size_t ncols)
{
    mat->nrows = nrows;
    mat->ncols = ncols;

    mat->entries = (QQ *)malloc(sizeof(QQ)*nrows*ncols);
}

void QQMat_fromZZ(QQMat *mat, size_t nrows, size_t ncols, ZZ* entries)
{
    size_t i, j;
    QQ q;

    for (i = 0; i < nrows; ++i) {
        for (j = 0; j < ncols; ++j) {
            QQ_set(&q, entries[i*ncols + j], 1);
            QQMat_set(mat, i, j, &q);
        }
    }
}

void QQMat_free(QQMat *mat)
{
    mat->nrows = 0;
    mat->ncols = 0;

    free(mat->entries);
}

/*void QQMat_augment(QQMat *res, const QQMat *A, const QQMat *B)
{
    //TODO
}*/

void QQMat_copy(QQMat *res, const QQMat *mat)
{
    QQ q;
    size_t i, j;

    for (i = 0; i < mat->nrows; ++i) {
        for (j = 0; j < mat->ncols ; ++j) {
            QQMat_get(&q, mat, i, j);
            QQMat_set(res, i, j, &q);
        }
    }
}

void QQMat_set(QQMat *mat, size_t i, size_t j, QQ *val)
{
    QQ_set(mat->entries + i*mat->ncols + j, val->numer, val->denom);
}

void QQMat_get(QQ *q, const QQMat *mat, size_t i, size_t j)
{
    QQ p;

    p = mat->entries[i * (mat->ncols) + j];
    QQ_set(q, p.numer, p.denom);
}

void QQMat_hilbert(QQMat *mat, size_t n)
{
    size_t i, j;
    QQ q;

    /* QQMat_init(mat, n, n); */
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            QQ_set(&q, 1, i + j + 1);
            QQMat_set(mat, i, j, &q);
        }
    }
}

void QQMat_print(const QQMat *mat)
{
    size_t i, j;
    QQ q;

    for (i = 0; i < mat->nrows; ++i) {
        for (j = 0; j < mat->ncols; ++j) {
            QQMat_get(&q, mat, i, j);
            putchar(' ');
            QQ_print(&q);
        }
        putchar('\n');
    }
}

void QQMat_gaussian(QQMat *res, const QQMat *mat)
{
    size_t i, j, i_0, k;
    QQ q, r, s, t, u, v, w;

    /* QQMat_init(res, mat->nrows, mat->ncols); */
    QQMat_copy(res, mat);
    i = 0;
    j = 0;
    while (i < res->nrows && j < res->ncols) {
        for (i_0 = i; i_0 < res->nrows; ++i_0) {
            QQMat_get(&q, res, i_0, j);
            if (q.numer)
                break;
        }
        if (i_0 < res->nrows) {
            for (k = 0; k < res->ncols; ++k) {
                QQMat_get(&q, res, i, k);
                QQMat_get(&r, res, i_0, k);
                QQMat_set(res, i, k, &r);
                QQMat_set(res, i_0, k, &q);
            }
        } else {
            ++j;
            continue;
        }
        if (j >= res->ncols) {
            return;
        }
        i_0 = i + 1;
        while (i_0 < res->nrows) {
            QQMat_get(&q, res, i_0, j);
            if (q.numer) {
                QQMat_get(&r, res, i, j);
                QQ_div(&s, &q, &r);
                for (k = 0; k < res->ncols; ++k) {
                    QQMat_get(&t, res, i_0, k);
                    QQMat_get(&u, res, i, k);
                    QQ_mul(&v, &s, &u);
                    QQ_sub(&w, &t, &v);
                    QQMat_set(res, i_0, k, &w);
                }
            }
            ++i_0;
        }
        ++i;
        ++j;
    }
}

void QQMat_solve(QQMat *res, const QQMat *mat, const QQMat *vec)
{
    QQMat aug, rref;
    QQ q, a, x, ax, b;
    size_t i, j, n;

    n = mat->nrows;
    QQMat_init(&aug, n, n + 1);
    QQMat_copy(&aug, mat);
    for (i = 0; i < n; ++i) {
        QQMat_get(&q, vec, i, 0);
        QQMat_set(&aug, i, n, &q);
    }
    QQMat_init(&rref, n, n + 1);
    QQMat_gaussian(&rref, &aug);
    i = n;
    while (i > 0) {
        --i;
        QQMat_get(&b, &rref, i, n);
        for (j = n-1; j > i; --j) {
            QQMat_get(&a, &rref, i, j);
            QQMat_get(&x, res, j, 0);
            QQ_mul(&ax, &a, &x);
            QQ_sub(&b, &b, &ax);
        }
        QQMat_get(&a, &rref, i, i);
        QQ_div(&b, &b, &a);
        QQMat_set(res, i, 0, &b);
    }
    QQMat_free(&aug);
    QQMat_free(&rref);
}

void RanZMat(QQMat *res, size_t m, size_t n)
{
    size_t i, j;
    QQ q;

    /* srand(42); */

    for (i = 0; i < m; ++i) {
        for (j = 0; j < n; ++j) {
            QQ_set(&q, rand() % 10, 1);
            QQMat_set(res, i, j, &q);
        }
    }
}

void QQMat_mul(QQMat *res, const QQMat *A, const QQMat *B)
{
    size_t i, j, k;
    QQ p, a, b, ab;

    if (A->ncols != B->nrows) {
        /* error */
    }
    for (i = 0; i < A->nrows; ++i) {
        for (j = 0; j < B->ncols; ++j) {
            QQ_set(&p, 0, 1);
            for (k = 0; k < A->ncols; ++k) {
                QQMat_get(&a, A, i, k);
                QQMat_get(&b, B, k, j);
                QQ_mul(&ab, &a, &b);
                QQ_add(&p, &p, &ab);
            }
            QQMat_set(res, i, j, &p);
        }
    }
}

int QQMat_is_inv(const QQMat *mat)
{
    QQMat ref;
    QQ q;
    size_t i;
    int ok = 1;

    QQMat_init(&ref, mat->nrows, mat->ncols);
    QQMat_gaussian(&ref, mat);
    for (i = 0; i < mat->nrows && ok; ++i) {
        QQMat_get(&q, &ref, i, i);
        ok = (q.numer != 0);
    }
    QQMat_free(&ref);
    return ok;
}

/****************************************************************************/
/* Real Matrices                                                            */
/****************************************************************************/

void FMat_init(FMat *mat, size_t nrows, size_t ncols)
{
    mat->nrows = nrows;
    mat->ncols = ncols;

    mat->entries = (RR *)malloc(sizeof(RR)*nrows*ncols);
}

void FMat_fromZZ(FMat *mat, size_t nrows, size_t ncols, ZZ* entries)
{
    size_t i, j;
    RR q;

    for (i = 0; i < nrows; ++i) {
        for (j = 0; j < ncols; ++j) {
            q = entries[i*ncols + j];
            FMat_set(mat, i, j, q);
        }
    }
}

void FMat_free(FMat *mat)
{
    mat->nrows = 0;
    mat->ncols = 0;

    free(mat->entries);
}

/*void FMat_augment(FMat *res, const FMat *A, const FMat *B)
{
    //TODO
}*/

void FMat_copy(FMat *res, const FMat *mat)
{
    RR q;
    size_t i, j;

    for (i = 0; i < mat->nrows; ++i) {
        for (j = 0; j < mat->ncols ; ++j) {
            q = FMat_get(mat, i, j);
            FMat_set(res, i, j, q);
        }
    }
}

void FMat_set(FMat *mat, size_t i, size_t j, RR val)
{
    mat->entries[i*mat->ncols + j] = val;
}

RR FMat_get(const FMat *mat, size_t i, size_t j)
{
    return mat->entries[i * (mat->ncols) + j];
}

void FMat_hilbert(FMat *mat, size_t n)
{
    size_t i, j;
    RR q;

    /* FMat_init(mat, n, n); */
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            q = 1.0 / (i + j + 1);
            FMat_set(mat, i, j, q);
        }
    }
}

void FMat_print(const FMat *mat)
{
    size_t i, j;
    RR q;

    for (i = 0; i < mat->nrows; ++i) {
        for (j = 0; j < mat->ncols; ++j) {
            q = FMat_get(mat, i, j);
            putchar(' ');
            printf("%g", q);
        }
        putchar('\n');
    }
}

void FMat_gaussian(FMat *res, const FMat *mat)
{
    size_t i, j, i_0, k;
    RR q, r, s, t, u, w;

    /* FMat_init(res, mat->nrows, mat->ncols); */
    FMat_copy(res, mat);
    i = 0;
    j = 0;
    while (i < res->nrows && j < res->ncols) {
        for (i_0 = i; i_0 < res->nrows; ++i_0) {
            q = FMat_get(res, i_0, j);
            if (!F_eq(q, 0))
                break;
        }
        if (i_0 < res->nrows) {
            for (k = 0; k < res->ncols; ++k) {
                q = FMat_get(res, i, k);
                r = FMat_get(res, i_0, k);
                FMat_set(res, i, k, r);
                FMat_set(res, i_0, k, q);
            }
        } else {
            ++j;
            continue;
        }
        if (j >= res->ncols) {
            return;
        }
        i_0 = i + 1;
        while (i_0 < res->nrows) {
            q = FMat_get(res, i_0, j);
            if (!F_eq(q, 0)) {
                r = FMat_get(res, i, j);
                s = q / r;
                for (k = 0; k < res->ncols; ++k) {
                    t = FMat_get(res, i_0, k);
                    u = FMat_get(res, i, k);
                    w = t - s * u;
                    FMat_set(res, i_0, k, w);
                }
            }
            ++i_0;
        }
        ++i;
        ++j;
    }
}

void FMat_solve(FMat *res, const FMat *mat, const FMat *vec)
{
    FMat aug, rref;
    RR q, a, x, b;
    size_t i, j, n;

    n = mat->nrows;
    FMat_init(&aug, n, n + 1);
    FMat_copy(&aug, mat);
    for (i = 0; i < n; ++i) {
        q = FMat_get(vec, i, 0);
        FMat_set(&aug, i, n, q);
    }
    FMat_init(&rref, n, n + 1);
    FMat_gaussian(&rref, &aug);
    i = n;
    while (i > 0) {
        --i;
        b = FMat_get(&rref, i, n);
        for (j = n-1; j > i; --j) {
            a = FMat_get(&rref, i, j);
            x = FMat_get(res, j, 0);
            b -= a * x;
        }
        a = FMat_get(&rref, i, i);
        b /= a;
        FMat_set(res, i, 0, b);
    }
    FMat_free(&aug);
    FMat_free(&rref);
}

void RanFMat(FMat *res, size_t m, size_t n)
{
    size_t i, j;
    RR q;

    /* srand(42); */

    for (i = 0; i < m; ++i) {
        for (j = 0; j < n; ++j) {
            q = ((double)rand()) / RAND_MAX;
            FMat_set(res, i, j, q);
        }
    }
}

void FMat_mul(FMat *res, const FMat *A, const FMat *B)
{
    size_t i, j, k;
    RR p;

    if (A->ncols != B->nrows) {
        /* error */
    }
    for (i = 0; i < A->nrows; ++i) {
        for (j = 0; j < B->ncols; ++j) {
            p = 0;
            for (k = 0; k < A->ncols; ++k) {
                p += FMat_get(A, i, k) * FMat_get(B, k, j);
            }
            FMat_set(res, i, j, p);
        }
    }
}

int FMat_is_inv(const FMat *mat)
{
    FMat ref;
    size_t i;
    int ok = 1;

    FMat_init(&ref, mat->nrows, mat->ncols);
    FMat_gaussian(&ref, mat);
    for (i = 0; i < mat->nrows && ok; ++i) {
        ok = !F_eq(FMat_get(&ref, i, i), 0.0);
    }
    FMat_free(&ref);
    return ok;
}
