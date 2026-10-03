/* Problem 6:
* Use your Extended Euclidean Algorithm implementation to write 1234/4321 as a
* continued fraction.
*/

#include <stdio.h>

#include "types.h"
#include "nt.h"

int main(void)
{
    QQ q;
    ZZ cont_frac[10];
    size_t i, len;

    QQ_set(&q, 1234, 4321);
    len = QQ_cont_frac(cont_frac, &q);
    printf("[");
    for (i = 0; i < len; ++i) {
        if (i) printf(", ");
        printf("%ld", cont_frac[i]);
    }
    printf("]\n");

	return 0;
}

