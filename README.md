# colynomials

Polynomial math library in C, and with one of those annoying names that has to have the host language in it. Only supports __real polynomials__, so real (floating point) coefficients and complex roots.

Read `polynomials.h` for the functions currently implemented.

## Development

This project is written in C99, and follows the [openage `tabs_n_spaces.md` style](https://github.com/SFTtech/openage/blob/master/doc/code_style/tabs_n_spaces.md) for indentation.

This project has no dependencies. Tests are written using [criterion](https://criterion.readthedocs.io/en/master/intro.html) and code coverage using [gcovr](https://gcovr.com/en/stable/).

### Internal Structure

`polynomial_t` is a `double*` under the hood, but the first element is an `unsigned int` specifying the *order* of the polynomial. Therefore, `polynomial_t` can be treated as an array starting at 1. To access the order, use `plnm_order()` or simply declare a pointer to your polynomial (`*((unsigned int *) polynomial)`).

Coefficients are stored in descending order of order, i.e `2x^2 + 10x - 5` is stored as `[2, 10, -5]`. This does mean if a polynomal is decleared in other formats (eg. 10x + 5x^2 + 2), if you want the 10x, you either:
* Remember that the polynomial is x^2, and therefor 10x is the third element (Discoraged, for several reasons including readablilty)
* Or, if you want your code to either be more readable, or just rely less on your memory: Assuming you know what element you want (eg. 10x), use plnm_order() to access the order, then just access the coefficent; eg:
 
 ```unsigned int poly_order = plnm_order(&myPolynomial); // using the example polynomial above```
 
 ```double coefficent_x = myPolynomial[(poly_order - 1)]; /so: we know the plnm_order for this polynomail is going to be 3, and if we want the second one, we subtract one from that to get the second element.```
 
 , and then you can use it for whatever you want.
