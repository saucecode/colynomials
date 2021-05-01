# colynomials

Polynomial math library in C, and with one of those annoying names that has to have the host language in it. Only supports __real polynomials__, so real (floating point) coefficients and complex roots.

Read `polynomials.h` for the functions currently implemented.

## Development

This project is written in C99, and follows the [openage `tabs_n_spaces.md` style](https://github.com/SFTtech/openage/blob/master/doc/code_style/tabs_n_spaces.md) for indentation.

This project has no dependencies. Tests are written using [criterion](https://criterion.readthedocs.io/en/master/intro.html) and code coverage using [gcovr](https://gcovr.com/en/stable/).

### Internal Structure

`polynomial_t` is a `double*` under the hood, but the first element is an `unsigned int` specifying the *order* of the polynomial. Therefore, `polynomial_t` can be treated as an array starting at 1. To access the order, use `plnm_order()` or simply `*((unsigned int *) polynomial)`.

Coefficients are stored in **ascending order** of order, i.e `2x^2 + 10x - 5` is stored as `[-5, 10, 2]`.