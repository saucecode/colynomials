# colynomials

Polynomial math library in C, and with one of those annoying names that has to have the host language in it. Only supports __real polynomials__, so real (floating point) coefficients and complex roots.

Read `polynomials.h` for the functions currently implemented.

## Internal Structure

`polynomial_t` is a `double*` under the hood, but the first element is an `unsigned int` specifying the *order* of the polynomial. Therefore, `polynomial_t` can be treated as an array starting at 1. To access the order, use `plnm_order()` or simply `*((unsigned int *) polynomial)`.

Coefficients are stored in descending order of order, i.e `2x^2 + 10x - 5` is stored as `[2, 10, -5]`.