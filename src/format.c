#include <stdio.h>
#include <stdlib.h>
#include "format.h"

int ZZ_sprint(char *buf, ZZ a)
{
    return sprintf(buf, "%ld", a);
}

int QQ_sprint(char *buf, const QQ *q)
{
    int len;

    len = ZZ_sprint(buf, q->numer);
    if (q->denom != 1) {
        buf[len++] = '/';
        len += ZZ_sprint(buf + len, q->denom);
    }
    return len;
}

void QQMat_fprint(FILE *fp, const QQMat *mat, enum QQ_align align, size_t bar)
{
    size_t i, j;
    int len, last, *nw, *dw;
    char buf[QQ_STR_MAX];
    QQ q;

    /*
     * nw[j]: width of the widest entry in column j (QQ_ALIGN_RIGHT),
     *        or of the widest numerator (QQ_ALIGN_SLASH)
     * dw[j]: width of the widest denominator, 0 if all entries are integers
     */
    nw = (int *)calloc(2 * mat->ncols, sizeof *nw);
    dw = nw + mat->ncols;

    for (i = 0; i < mat->nrows; ++i) {
        for (j = 0; j < mat->ncols; ++j) {
            QQMat_get(&q, mat, i, j);
            if (align == QQ_ALIGN_RIGHT) {
                len = QQ_sprint(buf, &q);
                if (len > nw[j])
                    nw[j] = len;
            } else {
                len = ZZ_sprint(buf, q.numer);
                if (len > nw[j])
                    nw[j] = len;
                if (q.denom != 1) {
                    len = ZZ_sprint(buf, q.denom);
                    if (len > dw[j])
                        dw[j] = len;
                }
            }
        }
    }

    for (i = 0; i < mat->nrows; ++i) {
        for (j = 0; j < mat->ncols; ++j) {
            /* no padding after the last column, so lines have no trailing spaces */
            last = (j + 1 == mat->ncols);
            if (bar && j == bar)
                fputs("  |", fp);
            QQMat_get(&q, mat, i, j);
            if (align == QQ_ALIGN_RIGHT) {
                QQ_sprint(buf, &q);
                fprintf(fp, "  %*s", nw[j], buf);
            } else {
                ZZ_sprint(buf, q.numer);
                fprintf(fp, "  %*s", nw[j], buf);
                if (q.denom != 1) {
                    ZZ_sprint(buf, q.denom);
                    fprintf(fp, "/%-*s", last ? 0 : dw[j], buf);
                } else if (dw[j] && !last) {
                    fprintf(fp, "%*s", dw[j] + 1, "");
                }
            }
        }
        putc('\n', fp);
    }

    free(nw);
}
