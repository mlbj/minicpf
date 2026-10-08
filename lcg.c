#include "lcg.h"

static uint32_t lcg_state = 1;

#if defined(__mips__)
_Bool platform_random_u32(uint32_t *value)
{
    // In 24Kc, $9 is CP0 Register Count
    __asm__ volatile (
        "mfc0 %0, $9"
        : "=r"(*value)
    );

    return 1;
}

#elif defined(__x86_64__)
_Bool platform_random_u32(uint32_t *value)
{
    _Bool ok;

    __asm__ volatile (
        "rdrand %0\n\t"
        "setc %1"
        : "=r"(*value), "=qm"(ok)
        :
        : "cc"
    );

    return ok;
}

#endif

void random_seed(uint32_t seed)
{
    lcg_state = seed;
}

uint32_t random_u32(void)
{
    lcg_state = 1664525u * lcg_state + 1013904223u;
    return lcg_state;
}

// Returns a pseudorandom digit [0, 9] by taking the modulo 10 of the current lcg
// state. This introduces modulo bias because the number of uint32_t values
// mapping to each digit is not the same. To overcome this bias, this function
// performs rejection sampling with the highest possible multiple of 10 within
// that range, that is:  0xFFFFFFFAu = 4294967290u.
uint8_t random_digit(void)
{
    uint32_t state;

    do {
        state = random_u32();
    } while (state >= 0xFFFFFFFAu);

    return (uint8_t)(state % 10u);
}

_Bool random_init(void)
{
    uint32_t seed;

    for (int i = 0; i < LCG_MAX_SEED_TRIES; i++) {
        if (platform_random_u32(&seed)) {
            random_seed(seed);
            return 1;
        }
    }

    // Hardware-dependent platform_random_u32() failed repeatedly
    random_seed(0);
    return 0;
}
