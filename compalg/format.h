#ifndef FORMAT_H
#define FORMAT_H

#include <stdio.h>
#include <limits.h>
#include "nt.h"
#include "rational.h"
#include "la.h"

/* buffer sizes, '\0' included: a B-bit integer has at most B/3 + 1 digits */
#define ZZ_STR_MAX (sizeof(ZZ) * CHAR_BIT / 3 + 3)
#define QQ_STR_MAX (2 * ZZ_STR_MAX)

/* how QQMat_fprint lines up the entries of a column */
enum QQ_align {
    QQ_ALIGN_RIGHT,     /* right-align each entry */
    QQ_ALIGN_SLASH      /* line up the '/' of fractions */
};

/* write a, or q as "n" or "n/d", into buf; return the number of chars written */
int ZZ_sprint(char *, ZZ);
int QQ_sprint(char *, const QQ *);

/* print mat with aligned columns; a '|' goes before column bar, none if bar is 0 */
void QQMat_fprint(FILE *, const QQMat *, enum QQ_align, size_t bar);

#endif
