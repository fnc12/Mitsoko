
#pragma once

#include <string.h>
#include <stdio.h>
#include <string>

#ifndef uint8
#define uint8  unsigned char
#endif

#ifndef uint32
#define uint32 unsigned long int
#endif

#define GET_UINT32(n,b,i)                       \
{                                               \
(n) = ( (uint32) (b)[(i)    ] << 24 )       \
| ( (uint32) (b)[(i) + 1] << 16 )       \
| ( (uint32) (b)[(i) + 2] <<  8 )       \
| ( (uint32) (b)[(i) + 3]       );      \
}

#define PUT_UINT32(n,b,i)                       \
{                                               \
(b)[(i)    ] = (uint8) ( (n) >> 24 );       \
(b)[(i) + 1] = (uint8) ( (n) >> 16 );       \
(b)[(i) + 2] = (uint8) ( (n) >>  8 );       \
(b)[(i) + 3] = (uint8) ( (n)       );       \
}

typedef struct
{
    uint32 total[2];
    uint32 state[8];
    uint8 buffer[64];
}sha256_context;

typedef unsigned char sha256_t[32];

void sha256_starts( sha256_context *ctx );

void sha256_process( sha256_context *ctx, uint8 data[64] );

void sha256_update( sha256_context *ctx, uint8 *input, uint32 length );

static uint8 sha256_padding[64] =
{
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void sha256_finish( sha256_context *ctx, uint8 digest[32] );

//void sha256_print(unsigned char digest[32]);
void sha256_print(unsigned char *digest,size_t len=32);

void sha256(unsigned char *data,size_t len,unsigned char output[32]);

/*std::string shaString(const std::string &str){
    sha256_t res;
    ::sha256((unsigned char*)str.c_str(), str.length(), res);
    return {(const char*)res,sizeof(res)};
}*/

int sha256_file(const char *filename,uint8 digest[32]);
