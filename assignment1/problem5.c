#include <stdio.h>
#include <compalg/nt.h>
#include <compalg/types.h>

int main(void)
{
    /* Problem 5:
     * Find the Bézout coefficients for 123456 and 654321.
     */
    ZZ c1, c2;

    xgcd(&c1, &c2, 123456, 654321, 0);
    printf("%ld %ld\n", c1, c2);

	return 0;
}

