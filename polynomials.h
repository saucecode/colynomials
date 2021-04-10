#ifndef _saucecodes_polynomials_h
#define _saucecodes_polynomials_h

#include <tgmath.h>

#define coeff_t double
#define root_t coeff_t complex
typedef coeff_t* polynomial_t; // typedef because its a pointer type

#define PLNM_A_VERY_SMALL_NUMBER 0.00001

#define PLNM_IS_CLOSE(x, t) (fabs((x) - (t)) < PLNM_A_VERY_SMALL_NUMBER)
#define PLNM_IS_ZERO(x) (fabs(x) < PLNM_A_VERY_SMALL_NUMBER)

#define plnm_sizeof(p) ((2+plnm_order(p))*sizeof(coeff_t))


/*
	Initializes a polynomial structure.
	This will call realloc() on the polynomial_t.
*/
void plnm_init(polynomial_t *y, int order);

// Returns the polynomial's order.
int plnm_order(polynomial_t *y);

/*
	Calculates all roots of the polynomial and stores them
	in buffer (this must be pre-allocated).
	
	This function calls other plnm_roots_* functions. A polynomial
	of any order may be passed into this function.
	
	Returns the number of roots found.
	Returns -1 if a mysterious error occured.
	Returns -2 if a division by zero would occur.
	Returns -7 if polynomials of the given order are unsupported.
*/
int plnm_roots(polynomial_t *y, root_t *buffer);

/*
	Multiplies two polynomials and inserts them into the result.
	result will have plnm_init() called on it.
	
	Returns the order of the resultant polynomial.
*/
int plnm_product(polynomial_t *left, polynomial_t *right, polynomial_t *result);

/*
	Copies the content of the source polynomial into the other.
	This will call plnm_init() on the copy if they are not already
	the same order. i.e plnm_order(copy) == plnm_order(source).
*/
void plnm_copy(polynomial_t *copy, polynomial_t *source);

// Initializes a linear polynomial following y = mx + c
void plnm_init_linear(polynomial_t *y, coeff_t m, coeff_t c);

// Initializes a quadratic polynomial following y = ax^2 + bx + c
void plnm_init_quadratic(polynomial_t *y, coeff_t a, coeff_t b, coeff_t c);

// Initializes a cubic polynomial following y = ax^3 + bx^2 + cx + d
void plnm_init_cubic(polynomial_t *y, coeff_t a, coeff_t b, coeff_t c, coeff_t d);

/*
	Solves a quadratic using the quadratic formula, to return either
	one or two roots.
	
	See plnm_roots.
*/
int plnm_roots_quadratic(polynomial_t *y, root_t *buffer);

// Scales a polynomial in place by coeff x
void plnm_scale(polynomial_t *y, coeff_t x);

#endif
