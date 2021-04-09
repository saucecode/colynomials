#include "polynomials.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void test_printing();
void print_polynomial(polynomial_t *y);

int main() {
	
	// Creating a quadratic polynomial:
	polynomial_t quad = NULL;
	plnm_init_quadratic(&quad, 3, -8, 5); // y = 3x^2 - 8x + 5
	
	// Printing it out
	printf("y = ");
	print_polynomial(&quad);
	printf("\n\n");
	
	// gets the order of a polynomial
	int order = plnm_order(&quad);
	
	// Finding some roots
	root_t roots[2];
	int root_count = plnm_roots(&quad, roots);
	
	printf("This polynomial of order %d has %d solutions:\n", order, root_count);
	
	// printing the full complex number form, which isn't always necessary.
	// using creal and cimag *is* necessary, since we're using C99's <complex.h>.
	for(int solution = 0; solution < root_count; solution += 1) {
		printf("y = %f%+fi\n", creal(roots[solution]), cimag(roots[solution]));
		/* alternatively:
		printf("y = %f\n", creal(roots[solution]));
		*/
	}
	printf("\n");
	
	
	// Creating a cubic
	polynomial_t cub = NULL;
	plnm_init_cubic(&cub, 25, 0, 15, 0);
	
	printf("y = ");
	print_polynomial(&cub);
	printf("\n\n");
	
	// Scaling the cubic by a constant
	printf("Scaled down by a factor of 1/5:\n");
	plnm_scale(&cub, 1/5.0);
	printf("y/5 = ");
	print_polynomial(&cub);
	
	printf("\n");
	
	return 0;
}

void test_printing() {
	// Creates a sixth order polynomial and fills it with some numbers
	// then prints it out.
	polynomial_t foo = NULL;
	plnm_init(&foo, 6);
	
	coeff_t coeffs[] = {1., -2., 3., -4., -5., 6., 7.};
	memcpy(foo+1, coeffs, sizeof(coeffs));
	
	print_polynomial(&foo);
	printf("\n");
	
	if(foo) free(foo);
}

void print_polynomial(polynomial_t *y) {
	int order = plnm_order(y);
	for(int i = 0; i < order; i += 1) {
		if(i == 0)
			printf("%f x", (*y)[i+1]);
		else
			printf("%f x", fabs((*y)[i+1]));
		
		if (i != order - 1)
			printf("^%d", order - i);
		
		printf(((*y)[i+2] < 0) ? " - " : " + ");
	}
	printf("%f", fabs((*y)[order+1]));
}