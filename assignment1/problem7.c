/* Problem 7: Using your Chinese Remainder Algorithm implementation, find a
 * nonnegative integer less than 2310 = 2 · 3 · 5 · 7 · 11 whose remainders on
 * division by 2, 3, 5, 7 and 11 are 0, 0, 2, 6, and 9 respectively.
 */

#include <stdio.h>

#include <compalg/types.h>
#include <compalg/nt.h>

int main(void)
{
    ZZ m[] = {2, 3, 5, 7, 11}, r[] = {0, 0, 2, 6, 9}, a;

    a = crt(r, m, 5);
    printf("%ld\n", a);

    return 0;
}

