
#include "crypto_hash.h"
#include "drygascon.h"

int crypto_hash(
    unsigned char *out,
    const unsigned char *in,
    unsigned long long inlen
){
    drygascon128_hash(out,in,inlen);
    return 0;
}
