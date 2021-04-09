#include "polynomials.h"

#include <stdlib.h>
#include <string.h>

void plnm_init(polynomial_t *y, int order) {
	*y = realloc(*y, sizeof(coeff_t) * (order + 2));
	memset(*y, 0, sizeof(coeff_t) * (order + 2));
	
	unsigned int *polynomial_order = (unsigned int*) *y;
	*polynomial_order = order;
}

void plnm_init_linear(polynomial_t *y, coeff_t m, coeff_t c) {
	plnm_init(y, 1);
	
	(*y)[1] = m;
	(*y)[2] = c;
}

void plnm_init_quadratic(polynomial_t *y, coeff_t a, coeff_t b, coeff_t c) {
	plnm_init(y, 2);
	
	(*y)[1] = a;
	(*y)[2] = b;
	(*y)[3] = c;
}

int plnm_roots(polynomial_t *y, root_t *buffer) {
	if (plnm_order(y) == 1) {
		if (PLNM_IS_ZERO( (*y)[1] )) return -2;
		
		buffer[0] = -(*y)[2]/(*y)[1];
		return 1;
		
	} else if (plnm_order(y) == 2) {
		return plnm_roots_quadratic(y, buffer);
		
	}
	
	return -7;
}

int plnm_roots_quadratic(polynomial_t *y, root_t *buffer) {
	// not a quadratic
	if (plnm_order(y) != 2) return -3;
	
	// has a zero highest-order coefficient
	if ((*y)[1] == 0) return -2;
	
	polynomial_t p = *y;
	coeff_t discriminant = p[2]*p[2] - 4 * p[1] * p[3];
	
	if (PLNM_IS_ZERO(discriminant)) {
		buffer[0] = -p[2] / ((coeff_t) 2) / p[1];
		
		return 1;
		
	} else if (discriminant > 0) {
		buffer[0] = (-p[2] + sqrt(discriminant)) / ((coeff_t) 2) / p[1];
		buffer[1] = (-p[2] - sqrt(discriminant)) / ((coeff_t) 2) / p[1];
		
		return 2;
		
	} else if(discriminant < 0) {
		buffer[0] = (-p[2] + sqrt(-discriminant) * I) / ((coeff_t) 2) / p[1];
		buffer[1] = (-p[2] - sqrt(-discriminant) * I) / ((coeff_t) 2) / p[1];
		
		return 2;
	}
	
	return -1;
}

int plnm_order(polynomial_t *y) {
	return *((unsigned int *) *y);
}
