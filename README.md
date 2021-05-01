# colynomials

Polynomial math library in C, and with one of those annoying names that has to have the host language in it. Only supports __real polynomials__, so real (floating point) coefficients and complex roots.

Read `polynomials.h` for the functions currently implemented.

## Development

This project is written in C99, and follows the [openage `tabs_n_spaces.md` style](https://github.com/SFTtech/openage/blob/master/doc/code_style/tabs_n_spaces.md) for indentation.

This project has no dependencies. Tests are written using [criterion](https://criterion.readthedocs.io/en/master/intro.html) and code coverage using [gcovr](https://gcovr.com/en/stable/).

### Internal Structure

`polynomial_t` is a `double*` under the hood, but the first element is an `unsigned int` specifying the *order* of the polynomial. Therefore, `polynomial_t` can be treated as an array starting at 1. To access the order, use `plnm_order()` or simply declare a pointer to your polynomial (`*((unsigned int *) polynomial)`).

Coefficients are stored in accending order, i.e `2x^2 + 10x - 5` is stored as `[-5, 10, 2]`. If you want to access the coefficent of `x`, for example, you can simply, without knowing anything about the polynomial:
* Get the polynomial order:
* ```my_polynomial_order = plnm_order(&my_polynomial)```
* and then, because we know that the order will be 2, as x^2 is the highest power, and we want the coefficent of `x`, which is the same as `x^1`, so we skip `x^0`, and knowing that the zeroth value of a `polynomial_t` array is the order, we can deduce that we want to access the 2nd element of the array.
*  (Remember, the coefficents start at the first element of the array, and we want the second coefficent, so we want the second element.)
* Because of this, we can simply add one to the power of pronumeral related to the coefficent we want.
* Simply access it like this:
* ```double coefficent = my_polynomial[ (desired coefficent's power's pronumeral) + 1]```
* , and then you can use it for whatever you want.
