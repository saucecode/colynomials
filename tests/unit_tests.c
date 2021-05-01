#include "../polynomials.h"
#include <criterion/criterion.h>

#include <string.h>
#include <stdio.h>

Test(plnm_scale, quadraticValue1)
{
	polynomial_t quad = NULL;

	plnm_init_quadratic(&quad, 2, 3, 5);
	plnm_scale(&quad, 2);
	cr_expect(quad[1] == 10);
	cr_expect(quad[2] == 6);
	cr_expect(quad[3] == 4);
	free(quad);
}

Test(plnm_copy, big_copy)
{
	polynomial_t big = NULL;
	plnm_init(&big, 24);
	// random coefficients
	coeff_t coeffs[] = {
		5.80, 6.94, 6.03, 6.03, 1.19, 2.69,
		3.93, 5.05, 0.11, 9.74, 3.78, 6.45,
		7.57, 9.01, 4.27, 8.40, 0.36, 3.23,
		3.12, 5.34, 0.18, 0.21, 7.41, 6.54
	};
	memcpy(&big[1], coeffs, sizeof(coeffs));
	
	polynomial_t copy = NULL;
	plnm_copy(&copy, &big);
	
	cr_expect(memcmp(copy, big, plnm_sizeof(&big)) == 0);
	
	free(big);
	free(copy);
}

Test(plnm_roots, quadratic_one_root)
{
	// The polynomial 2(x - 4)^2, expanded to 2x^2 - 16x + 32
	// has exactly one root at x = 4.
	polynomial_t quad = NULL;

	plnm_init_quadratic(&quad, 2, -16, 32);
	
	root_t roots[2];
	int root_count = plnm_roots(&quad, roots);
	
	cr_assert(root_count == 1);
	cr_assert(PLNM_IS_CLOSE(roots[0], 4));
	
	free(quad);
}

Test(plnm_roots, quadratic_two_real_roots)
{
	// The polynomial (x + 17)^2 - 18^2, expanded to x^2 + 34x - 35
	// has exactly two real roots at x = -35 and x = 1.
	polynomial_t quad = NULL;

	plnm_init_quadratic(&quad, 1, 34, -35);
	
	root_t roots[2];
	int root_count = plnm_roots(&quad, roots);
	
	cr_assert(root_count == 2);
	cr_assert(PLNM_IS_CLOSE(creal(roots[0]), 1));
	cr_assert(PLNM_IS_CLOSE(creal(roots[1]), -35));
	
	free(quad);
}

Test(plnm_product, big_product)
{
	// Multiplication of two polynomials, one of order 23 and another of order 17
	// to yield a result of order 40. PLNM_IS_CLOSE() macro is used for the
	// comparison
	coeff_t coeffs_left[] = {
		0.62,-0.80, 0.72, -0.52, 0.76, -0.60,
		0.22, 0.13, -0.74, -0.20, 0.73, 0.90,
		-0.35, -0.69, -0.25, 0.13, 0.56, 0.83,
		0.62, -0.77, -0.49, 0.32, -0.48, 0.48
	};
	coeff_t coeffs_right[] = {
		0.94, -0.33, 0.10, -0.75, -0.22, 0.86,
		0.63, 0.04, 0.10, -0.34, 0.52, -0.73,
		-0.23, 0.63, 0.78, -0.03, -0.88, -0.73
	};
	coeff_t coeffs_solution[] = {
		0.58280, -0.95660, 1.00280, -1.27140, 1.42160, -0.69760,
		0.41500, -0.32600, -0.39730, 0.10020, 1.14070, -0.21230,
		1.05480, -2.03210, -0.69610, -0.32560, 2.25070, 1.82250,
		-0.66400, -2.12980, -0.62640, -0.07570, -0.35290, 2.09580,
		1.58770, 0.93310, -1.51620, -2.64140, -0.51770, 0.76230,
		1.70660, 2.00170, -1.14780, -1.54070, -1.54900, 0.07650,
		0.91170, 0.46490, 0.17440, -0.07200, -0.35040
	};
	polynomial_t left = NULL;
	plnm_init(&left, 23);
	// random coefficients
	memcpy(&left[1], coeffs_left, sizeof(coeffs_left));
	
	polynomial_t right = NULL;
	plnm_init(&right, 17);
	memcpy(&right[1], coeffs_right, sizeof(coeffs_right));
	
	cr_assert(plnm_order(&left) == 23);
	cr_assert(plnm_order(&right) == 17);
	
	polynomial_t result = NULL;
	plnm_product(&left, &right, &result);
	cr_assert(plnm_order(&result) == 40);
	
	for(int i = 1; i < plnm_order(&result) + 2; i++) {
		// printf("%d\t%f\t%f\n", i, result[i], coeffs_solution[i-1]);
		cr_assert(PLNM_IS_CLOSE(result[i], coeffs_solution[i-1]));
	}
	
	free(left);
	free(right);
	free(result);
}
