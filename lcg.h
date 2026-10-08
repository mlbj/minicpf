/* lcg.h */

#ifndef LCG_H
#define LCG_H

#include <stdint.h>

#define LCG_MAX_SEED_TRIES 10

_Bool platform_random_u32(uint32_t *);
void random_seed(uint32_t seed);
uint32_t random_u32(void);
uint8_t random_digit(void);
_Bool random_init(void);

#endif
