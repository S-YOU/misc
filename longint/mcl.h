#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// pStr [in] hex string such as 0x94...
int mcl_init(const char *pStr);

typedef void (*void3u)(uint64_t *z, const uint64_t *x, const uint64_t *y);
// n = 9 or 11
// z[n*2] = x[n] * y[n]
extern void3u mcl_mulPre;
// z[n] = Montgomery-mul(x[n], y[n]);
extern void3u mcl_mont;

// z[n] = (x[n] + y[n]) mod p[n]
extern void3u mcl_add;
// z[n] = (x[n] - y[n]) mod p[n]
extern void3u mcl_sub;

typedef void (*void2u)(uint64_t *y, const uint64_t *x);
// y[n] = Montgomery-mod(x[n * 2]);
extern void2u mcl_mod;
// y[n] = (-x[n]) mod p[n]
extern void2u mcl_neg;

#ifdef __cplusplus
}
#endif
