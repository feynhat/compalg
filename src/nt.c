#include "nt.h"
#include "types.h"
#include "rational.h"
#include <stdio.h>
#include <math.h>

ZZ gcd(ZZ a, ZZ b)
{
    ZZ r;

    while (a % b) {
        r = a%b;
        a = b;
        b = r;
    }
    return b;
}

ZZ xgcd(ZZ *u, ZZ *v, ZZ a, ZZ b, int print)
{
    ZZ q = 0,
        r_0 = a,
        r_1 = b,
        s_0 = 1,
        t_0 = 0,
        s_1 = 0,
        t_1 = 1,
        r = r_1,
        s = s_1,
        t = t_1;
    int i = 0;

    if (print) {
        printf("i = %d\tr_i = %ld\t\tq_i = %ld\t\ts_i = %ld\t\tt_i = %ld\n",
                i++, r_0, q, s_0, t_0);
    }
    while (r) {
        q = r_0 / r_1;
        if (print) {
            printf("i = %d\tr_i = %ld\t\tq_i = %ld\t\ts_i = %ld\t\tt_i = %ld\n",
                    i++, r_1, q, s_1, t_1);
        }
        r = r_0 % r_1;
        s = s_0  - q*s_1;
        t = t_0  - q*t_1;
        r_0 = r_1;
        r_1 = r;
        s_0 = s_1;
        s_1 = s;
        t_0 = t_1;
        t_1 = t;
    }
    if (print) {
        printf("i = %d\tr_i = %ld\t\t\t\t\ts_i = %ld\t\tt_i = %ld\n",
                i, r_1, s_1, t_1);
    }
    *u = s_0;
    *v = t_0;

    return r_0;
}

ZZ mod_inv(ZZ a, ZZ m)
{
    ZZ g, u, v;

    g = xgcd(&u, &v, a, m, 0);
    if (g != 1) {
        /*error: a is not invertible mod m*/
    }
    return (m + u)%m;
}

size_t bin_rep(byte *res, unsigned n)
{
    size_t i, j, len = 0;
    ZZ tmp;

    while (n) {
        res[len++] = n & 1;
        n >>= 1;
    }

    i = 0;
    j = len-1;
    while (i < j) {
        tmp = res[i];
        res[i] = res[j];
        res[j] = tmp;
        ++i;
        --j;
    }

    return len;
}

ZZ crt(const ZZ *rems, const ZZ *moduli, size_t n)
{
    ZZ res=0, M = 1;
    size_t i;

    for (i = 0; i < n; ++i) {
        M *= moduli[i];
    }

    for (i = 0; i < n; ++i) {
        res += rems[i] * mod_inv(M/moduli[i], moduli[i]) * M/moduli[i];
    }

    return res % M;
}

size_t QQ_cont_frac(ZZ *out, const QQ *q)
{
    size_t len = 0;
    ZZ u0, u1, t;

    u0 = q->numer;
    u1 = q->denom;
    while (u1) {
        out[len++] = u0/u1;
        t = u0 % u1;
        u0 = u1;
        u1 = t;
    }
    return len;
}
