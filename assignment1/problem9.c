/*
 * Problem 9: Write a function RanZMat(m, n) which constructs an m × n matrix
 * with random integer entries between 0 and 100. Write another function
 * RanFMat(m, n) which constructs an m × n matrix with random floating point
 * entries between 0 and 1.
 *
 * (a) Use a timing or benchmarking tool available in your system to measure
 * the average time it takes to solve a system Ax = b where A is a random 100 ×
 * 100 matrix and b is a random 100 × 1 vector. Compare systems generated using
 * RanZMat with systems generated using RanFMat, using the same function to
 * generate both A and b in each case.
 *
 */

#include <stdio.h>
#include <time.h>

#include "types.h"
#include "la.h"

#define TRIALS 1000
#define MAXSIZE_Z 10
#define MAXSIZE_F 100

int main(void)
{
    QQMat A[TRIALS], x[TRIALS], b[TRIALS];
    FMat  B[TRIALS], y[TRIALS], c[TRIALS];
    clock_t start, end;
    double delta;
    size_t size, i;

    printf("RanZMat, Rational matrices\n");
    printf("Size of the matrix\tTime in milliseconds\n");
    for (size = 1; size <= MAXSIZE_Z; ++size) {
        for (i = 0; i < TRIALS; ++i) {
            QQMat_init(&A[i], size, size);
            QQMat_init(&x[i], size, 1);
            QQMat_init(&b[i], size, 1);
            do {
                RanZMat(&A[i], size, size);
                RanZMat(&b[i], size, 1);
            } while (!QQMat_is_inv(&A[i]));
        }

        /* trials start */
        start = clock();
        for (i = 0; i < TRIALS; ++i) {
            QQMat_solve(&x[i], &A[i], &b[i]);
        }
        end = clock();
        /* trials end */

        delta = (double)(end - start) / CLOCKS_PER_SEC;
        printf("%9lu\t\t\t%1.7f\n", size, 1e3 * delta / TRIALS);

        for (i = 0; i < TRIALS; ++i) {
            QQMat_free(&A[i]);
            QQMat_free(&x[i]);
            QQMat_free(&b[i]);
        }
    }
    printf("\n");

    printf("RanFMat, Floating-point matrices\n");
    printf("Size of the matrix\tTime in milliseconds\n");
    for (size = 10; size <= MAXSIZE_F; size += 10) {
        for (i = 0; i < TRIALS; ++i) {
            FMat_init(&B[i], size, size);
            FMat_init(&y[i], size, 1);
            FMat_init(&c[i], size, 1);
            do {
                RanFMat(&B[i], size, size);
                RanFMat(&c[i], size, 1);
            } while (!FMat_is_inv(&B[i]));
        }

        /* trials start */ 
        start = clock();
        for (i = 0; i < TRIALS; ++i) {
            FMat_solve(&y[i], &B[i], &c[i]);
        }
        end = clock();
        /* trials end */

        delta = (double)(end - start) / CLOCKS_PER_SEC;
        printf("%9lu\t\t\t%1.7f\n", size, 1e3 * delta / TRIALS);

        for (i = 0; i < TRIALS; ++i) {
            FMat_free(&B[i]);
            FMat_free(&y[i]);
            FMat_free(&c[i]);
        }
    }

    return 0;
}

