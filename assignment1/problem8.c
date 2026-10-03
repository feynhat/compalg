/* Problem 8 (a):
 * Write a function which computes the n-th Hilbert matrix exactly, with
 * entries in Q, and another which computes it numerically, with floating point
 * entries.
 *
 * Problem 8 (b):
 * Define b = H_{10,10}·(1, 2, . . . , 10)T using exact rational arithmetic and
 * solve the system H_{10,10}x = b exactly. Then convert both H10,10 and b to
 * floating point representations and solve the resulting system numerically.
 * State the floating point precision you used and comment on what you notice
 * about the results.
 */

#include <stdio.h>

#include "types.h"
#include "la.h"
#include "format.h"

int main(void)
{
    QQMat H0, b0, x0, sol;
    FMat  H1, b1, x1, float_sol;
    ZZ pre_sol[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    /* Part (a) */
    QQMat_init(&H0, 10, 10);
    QQMat_hilbert(&H0, 10);

    QQMat_init(&x0, 10, 1);
    QQMat_fromZZ(&x0, 10, 1, pre_sol);

    QQMat_init(&b0, 10, 1);
    QQMat_mul(&b0, &H0, &x0);

    QQMat_init(&sol, 10, 1);
    QQMat_solve(&sol, &H0, &b0);

    printf("(a) Exact solution:\n");
    QQMat_fprint(stdout, &sol, QQ_ALIGN_RIGHT, 0);

    QQMat_free(&H0);
    QQMat_free(&x0);
    QQMat_free(&b0);
    QQMat_free(&sol);

    /* Part (b) */
    FMat_init(&H1, 10, 10);
    FMat_hilbert(&H1, 10);

    FMat_init(&x1, 10, 1);
    FMat_fromZZ(&x1, 10, 1, pre_sol);

    FMat_init(&b1, 10, 1);
    FMat_mul(&b1, &H1, &x1);

    FMat_init(&float_sol, 10, 1);
    FMat_solve(&float_sol, &H1, &b1);

    printf("(b) Numerical (Floating-point) solution:\n");
    FMat_fprint(stdout, &float_sol, 17, RR_ALIGN_POINT, 0);

    FMat_free(&H1);
    FMat_free(&x1);
    FMat_free(&b1);
    FMat_free(&float_sol);

    return 0;
}
