#include "rational.h"
#include "nt.h"
#include <stdio.h>

void QQ_set(QQ *q, ZZ a, ZZ b)
{
    if (!b) {
        /* error: 0 denominator */
    }
    q->numer = a;
    q->denom = b;
    QQ_red(q);
}

void QQ_red(QQ *q)
{
    ZZ g;

    g = gcd(q->numer, q->denom);
    q->numer /= g;
    q->denom /= g;
    if (q -> denom < 0) {
        q->numer = - q->numer;
        q->denom = - q->denom;
    }
}

void QQ_inv(QQ *q, const QQ *p)
{
    if (!p->numer) {
        /* error: can't invert 0 */
    }
    q->numer = p->denom;
    q->numer = p->denom;
}

void QQ_add(QQ *res, const QQ *p, const QQ *q)
{
    ZZ g, pd, qd;

    g = gcd(p->denom, q->denom);
    pd = p->denom / g;
    qd = q->denom / g;

    QQ_set(res, p->numer * qd + q->numer * pd, p->denom * qd);
}

void QQ_sub(QQ *res, const QQ *p, const QQ *q)
{
    ZZ g, pd, qd;

    g = gcd(p->denom, q->denom);
    pd = p->denom / g;
    qd = q->denom / g;

    QQ_set(res, p->numer * qd - q->numer * pd, p->denom * qd);
}

void QQ_mul(QQ *res, const QQ *p, const QQ *q)
{
    ZZ g1, g2;

    g1 = gcd(p->numer, q->denom);
    g2 = gcd(q->numer, p->denom);

    QQ_set(res, (p->numer / g1) * (q->numer / g2),
            (p->denom / g2) * (q->denom / g1));
}

void QQ_div(QQ *res, const QQ *p, const QQ *q)
{
    ZZ g1, g2;

    if (!q->numer) {
        /* error: division by 0 */
    }
    
    g1 = gcd(p->numer, q->numer);
    g2 = gcd(p->denom, q->denom);

    QQ_set(res, (p->numer / g1) * (q->denom / g2),
            (p->denom / g2) * (q->numer / g1));
}

int QQ_eq(const QQ *p, const QQ *q)
{
    return (p->numer * q->denom == p->denom * q->numer);
}

double QQ_to_dbl(const QQ *q)
{
    double a, b;

    a = q->numer;
    b = q->denom;

    return a/b;
}

int QQ_print(const QQ *q)
{
    if (q->denom == 1) {
        return printf("%ld", q->numer);
    } else {
        return printf("%ld/%ld", q->numer, q->denom);
    }
}
