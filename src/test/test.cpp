#include <stdio.h>
#include <stdint.h>
#include <string.h>
void set_led(int state);

#include "supercop_api.h"

void println_bytes(const char*const msg,const void*const buf,unsigned int len){
    printf("%s",msg);
    const uint8_t*const buf8=(const uint8_t*const)buf;
    for(unsigned int i=0;i<len;i++){
        printf("%02x ",buf8[i]);
    }
    printf("\n");
}

#include "drygascon128k32.h"

#define DO_VALIDATION 0

#if DO_VALIDATION
    #include "drygascon128k32_validation.h"
#else
    #define DO_HASH 0
    #define DO_AEAD 1
#endif

int dummy(unsigned char *out, const unsigned char *in, const unsigned char *key, unsigned long long inlen){
    for(unsigned int i=0;i<inlen;i++){
        out[i] = in[i] ^ in[(i+3)%inlen] ^ ~in[(i+5)%inlen] ^ key[i%32];
    }
    return 0;
}

static uint8_t buf[32] = {0};
static uint8_t buf2[32] = {0};
uint8_t key[] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F};
    
static unsigned long long clen;
static int led=0;
void test(void){
    //printf("This is the bare metal blinky example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    printf("\n\n");
    #if DO_VALIDATION
        printf("validation: %u\n",drygascon128k32_validate_all(crypto_aead_encrypt,crypto_aead_decrypt,crypto_hash));
    #else
        for(unsigned int i=0;i<1000;i++){
            if(DO_HASH) crypto_hash(buf2,buf,32);
            else dummy(buf2,buf,key,32);
            memcpy(buf,buf2,32);
        }
        println_bytes("",buf2,32);
        for(unsigned int i=0;i<1000;i++){
            if(DO_AEAD) crypto_aead_encrypt(buf2,&clen,buf,16,buf,16,0,buf, key);
            else dummy(buf2,buf,key,32);
            memcpy(buf,buf2,32);
        }
        println_bytes("",buf2,32);
        dummy(buf2,buf,key,32);
        println_bytes("",buf2,32);
    #endif
    led=1-led;
    set_led(led);
}

