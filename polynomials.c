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
	
	(*y)[2] = m;
	(*y)[1] = c;
}

void plnm_init_quadratic(polynomial_t *y, coeff_t a, coeff_t b, coeff_t c) {
	plnm_init(y, 2);
	
	(*y)[3] = a;
	(*y)[2] = b;
	(*y)[1] = c;
}

void plnm_init_cubic(polynomial_t *y, coeff_t a, coeff_t b, coeff_t c, coeff_t d) {
	plnm_init(y, 3);
	
	(*y)[4] = a;
	(*y)[3] = b;
	(*y)[2] = c;
	(*y)[1] = d;
}

int plnm_roots(polynomial_t *y, root_t *buffer) {
	if (plnm_order(y) == 1) {
		if (PLNM_IS_ZERO( (*y)[1] )) return -2;
		
		buffer[0] = -(*y)[1]/(*y)[2];
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
	if (PLNM_IS_ZERO((*y)[3])) return -2;
	
	polynomial_t p = *y;
	coeff_t discriminant = p[2]*p[2] - 4 * p[3] * p[1];
	
	if (PLNM_IS_ZERO(discriminant)) {
		buffer[0] = -p[2] / ((coeff_t) 2) / p[3];
		
		return 1;
		
	} else if (discriminant > 0) {
		buffer[0] = (-p[2] + sqrt(discriminant)) / ((coeff_t) 2) / p[3];
		buffer[1] = (-p[2] - sqrt(discriminant)) / ((coeff_t) 2) / p[3];
		
		return 2;
		
	} else if(discriminant < 0) {
		buffer[0] = (-p[2] + sqrt(-discriminant) * I) / ((coeff_t) 2) / p[3];
		buffer[1] = (-p[2] - sqrt(-discriminant) * I) / ((coeff_t) 2) / p[3];
		
		return 2;
	}
	
	return -1;
}

int plnm_product(polynomial_t *left, polynomial_t *right, polynomial_t *result) {
	int order_left = plnm_order(left);
	int order_right = plnm_order(right);
	int order_result = order_left + order_right;
	
	plnm_init(result, order_result);
	for(int i = 1; i <= order_left + 1; i += 1) {
		int left_exp = order_left - i + 1;
		
		for(int j = 1; j <= order_right + 1; j += 1) {
			int right_exp = order_right - j + 1;
			
			int exponent = left_exp + right_exp;
			(*result)[order_result - exponent + 1] += (*left)[i] * (*right)[j];
		}
	}
	
	return order_result;
}

int plnm_order(polynomial_t *y) {
	return *((unsigned int *) *y);
}

void plnm_scale(polynomial_t *y, coeff_t x)
{
	for (int i = 0; i <= plnm_order(y); i++)
		(*y)[i + 1] *= x;
}

void plnm_copy(polynomial_t *copy, polynomial_t *source) {
	if (!source) return;
	
	if (*copy == NULL || plnm_order(copy) == plnm_order(source))
		plnm_init(copy, plnm_order(source));
	
	memcpy(*copy, *source, plnm_sizeof(source));
}

coeff_t plnm_at(polynomial_t *y, size_t pos)
{
	if (pos == 0 || plnm_order(y) + 1 < pos)
		return 0;
	return (*y)[pos];
}
