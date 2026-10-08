/* cpf.h */

#ifndef CPF_H
#define CPF_H

#include <stdint.h>

typedef uint8_t cpf_t[11];

_Bool cpf_compute_check_digits(cpf_t);
void random_cpf(cpf_t);

#endif
