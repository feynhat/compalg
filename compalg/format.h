#ifndef FORMAT_H
#define FORMAT_H

#include <stdio.h>
#include <limits.h>
#include <compalg/types.h>
#include <compalg/nt.h>
#include <compalg/rational.h>
#include <compalg/la.h>

/* buffer sizes, '\0' included: a B-bit integer has at most B/3 + 1 digits */
#define ZZ_STR_MAX (sizeof(ZZ) * CHAR_BIT / 3 + 3)
#define QQ_STR_MAX (2 * ZZ_STR_MAX)

/* largest precision RR_sprint uses: 17 significant digits pin down any double */
#define RR_PREC_MAX 17
/* longest is "-d.dd...de-ddd": sign, RR_PREC_MAX digits, '.', "e-", 3 exponent digits */
#define RR_STR_MAX (RR_PREC_MAX + 8)

/* how QQMat_fprint lines up the entries of a column */
enum QQ_align {
    QQ_ALIGN_RIGHT,     /* right-align each entry */
    QQ_ALIGN_SLASH      /* line up the '/' of fractions */
};

/* how FMat_fprint lines up the entries of a column */
enum RR_align {
    RR_ALIGN_RIGHT,     /* right-align each entry */
    RR_ALIGN_POINT      /* line up the decimal points, or the 'e' if there is none */
};

/* write a, or q as "n" or "n/d", into buf; return the number of chars written */
int ZZ_sprint(char *, ZZ);
int QQ_sprint(char *, const QQ *);

/* write x into buf as "%.*g" with prec (at most RR_PREC_MAX); return the number of chars written */
int RR_sprint(char *, RR, int prec);

/* print mat with aligned columns; a '|' goes before column bar, none if bar is 0 */
void QQMat_fprint(FILE *, const QQMat *, enum QQ_align, size_t bar);
void FMat_fprint(FILE *, const FMat *, int prec, enum RR_align, size_t bar);

#endif
