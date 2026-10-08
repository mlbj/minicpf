#include "cpf.h"
#include "lcg.h"

#include <stdint.h>

// Computes and sets check digits of a given cpf_t.
// Returns 1 if the cpf_t digits were already correctly set.
_Bool cpf_compute_check_digits(cpf_t cpf)
{
    _Bool valid = 1;
    uint8_t digit = 0;

    // Computes first digit
    uint32_t sum = 0;

    for (uint8_t i = 0; i < 9; i++) {
        sum += cpf[i] * (10 - i);
    }

    uint32_t r = sum % 11;
    digit = (r < 2) ? 0 : 11 - r;

    if (digit != cpf[9]) {
        valid = 0;
        cpf[9] = digit;
    }

    // Computes second digit
    sum = 0;
    for (uint8_t i = 0; i < 10; i++) {
        sum += cpf[i] * (11 - i);
    }

    r = sum % 11;
    digit = (r < 2) ? 0: 11 - r;

    if (digit != cpf[10]) {
        valid = 0;
        cpf[10] = digit;
    }

    return valid;
}

void random_cpf(cpf_t cpf)
{
    for (int i = 0; i < 9; i++) {
        cpf[i] = random_digit();
    }

    cpf_compute_check_digits(cpf);
}



