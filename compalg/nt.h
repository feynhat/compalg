#ifndef NT_H
#define NT_H

#include "../compalg/types.h"
#include "../compalg/rational.h"

#include <stdlib.h>

ZZ gcd(ZZ, ZZ);
ZZ xgcd(ZZ *, ZZ *, ZZ, ZZ, int);
ZZ mod_inv(ZZ, ZZ);

ZZ crt(const ZZ *, const ZZ *, size_t);

size_t QQ_cont_frac(ZZ *, const QQ *);

size_t bin_rep(byte *, unsigned);

#endif
