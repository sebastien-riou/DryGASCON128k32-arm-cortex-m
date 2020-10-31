#include <stdio.h>
#include <stdint.h>
void set_led(int state);

extern "C" {
    #include "crypto_hash.h"
    #include "crypto_aead.h"
    void println_bytes(const char*const msg,const void*const buf,unsigned int len){
        printf("%s",msg);
        const uint8_t*const buf8=(const uint8_t*const)buf;
        for(unsigned int i=0;i<len;i++){
            printf("%02x ",buf8[i]);
        }
        printf("\n");
    }
}

#include "drygascon.h"

#define DO_VALIDATION 0

#if DO_VALIDATION
    #include "drygascon128k32_validation.h"
    #define DO_HASH 1
    #define DO_AEAD 1
#else
    #define DO_HASH 0
    #define DO_AEAD 1
#endif

#define DO_DUMMY !(DO_HASH || DO_AEAD)

int dummy(unsigned char *out, const unsigned char *in, unsigned long long inlen){
    for(unsigned int i=0;i<inlen;i++){
        out[i] = in[i] ^ in[(i+3)%inlen] ^ ~in[(i+5)%inlen];
    }
    return 0;
}

static uint8_t buf[32] = {0};
static unsigned long long clen;
static int led=0;
void test(void){
    //printf("This is the bare metal blinky example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    printf("\n\n");
    #if DO_VALIDATION
        printf("validation: %u\n",drygascon128k32_validate_all(crypto_aead_encrypt,crypto_aead_decrypt,crypto_hash));
    #else
        for(unsigned int i=0;i<1000;i++){
            if(DO_HASH) crypto_hash(buf,buf,32);
            if(DO_AEAD) crypto_aead_encrypt(buf,&clen,buf,16,buf,16,0,buf, buf);
            if(DO_DUMMY) dummy(buf,buf,32);
        }
        println_bytes("",buf,32);
    #endif
    led=1-led;
    set_led(led);
}

