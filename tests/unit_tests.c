#include "../polynomials.h"
#include <criterion/criterion.h>

#include <string.h>

Test(plnm_scale, quadraticValue1)
{
    polynomial_t quad = NULL;

    plnm_init_quadratic(&quad, 2, 3, 5);
    plnm_scale(&quad, 2);
    cr_expect(quad[1] == 4);
    free(quad);
}

Test(plnm_scale, quadraticValue2)
{
    polynomial_t quad = NULL;

    plnm_init_quadratic(&quad, 2, 3, 5);
    plnm_scale(&quad, 2);
    cr_expect(quad[2] == 6);
    free(quad);
}

Test(plnm_scale, quadraticValue3)
{
    polynomial_t quad = NULL;

    plnm_init_quadratic(&quad, 2, 3, 5);
    plnm_scale(&quad, 2);
    cr_expect(quad[3] == 10);
    free(quad);
}

Test(plnm_copy, big_copy)
{
    polynomial_t big = NULL;
	plnm_init(&big, 24);
	coeff_t coeffs[] = {5.80, 6.94, 6.03, 6.03, 1.19, 2.69, 3.93, 5.05, 0.11, 9.74, 3.78, 6.45, 7.57, 9.01, 4.27, 8.40, 0.36, 3.23, 3.12, 5.34, 0.18, 0.21, 7.41, 6.54};
	memcpy(&big[1], coeffs, sizeof(coeffs));
	
	polynomial_t copy = NULL;
	plnm_copy(&copy, &big);
    
    cr_expect(memcmp(copy, big, plnm_sizeof(&big)) == 0);
    
    free(big);
}
