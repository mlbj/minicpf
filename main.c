#include "lcg.h"
#include "cpf.h"

#include <stdio.h>

void print_cpf(cpf_t cpf) {
    printf("%d", cpf[0]);
    printf("%d", cpf[1]);
    printf("%d.", cpf[2]);
    printf("%d", cpf[3]);
    printf("%d", cpf[4]);
    printf("%d.", cpf[5]);
    printf("%d", cpf[6]);
    printf("%d", cpf[7]);
    printf("%d-", cpf[8]);
    printf("%d", cpf[9]);
    printf("%d\n", cpf[10]);
}

int main(void)
{
    random_init();

    cpf_t cpf = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    for (int i = 0; i < 20; i++) {
        random_cpf(cpf);
        print_cpf(cpf);
    }

    return 0;
}
