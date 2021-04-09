#include "../polynomials.h"
#include <criterion/criterion.h>

Test(plnm_scale, quadraticValue1)
{
    polynomial_t quad;
    plnm_init_quadratic(&quad, 2, 3, 5);
    plnm_scale(&quad, 2);
    cr_expect(quad[1] == 4);
    free(quad);
}

Test(plnm_scale, quadraticValue2)
{
    polynomial_t quad;
    plnm_init_quadratic(&quad, 2, 3, 5);
    plnm_scale(&quad, 2);
    cr_expect(quad[2] == 6);
    free(quad);
}

Test(plnm_scale, quadraticValue3)
{
    polynomial_t quad;
    plnm_init_quadratic(&quad, 2, 3, 5);
    plnm_scale(&quad, 2);
    cr_expect(quad[3] == 10);
    free(quad);
}
