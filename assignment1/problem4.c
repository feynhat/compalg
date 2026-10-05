/* Problem 4:
 *
 * Write 3264 in its binary representation.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include <compalg/types.h>
#include <compalg/nt.h>

int main(void)
{
    size_t i, len;
    byte s[20];

    len = bin_rep(s, 3264); /* and all that! */
    for (i = 0; i < len; ++i) {
        printf("%d", s[i]);
    }

	return 0;
}
