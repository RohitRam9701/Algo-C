/**
 * @file
 * @brief a Newton-Raphson method and square-root implementation
 * https://en.wikipedia.org/wiki/Newton%27s_method
 * @details
 * square-root implementation by using newton raphson method
 * @author [Ali Kaan UYAR](https://github.com/kaan2463)
 */


#include <stdio.h> //for printf
#include <assert.h> // for assert

// Epsilon value 0.00000001 (Delta E)
#define NR_DE               1.0e-8 
// Max iteration of nr algorithm
#define NR_MAX_ITER         55 


typedef double (*DFUNC2D) (double, double); // functional type that is used as f in newton raphson algorithm
typedef double (*DFUNC1D) (double); // functional type that is used as derivative of f

/**
 * @brief absolute difference between two double
 * @param a : number1
 * @param b : number2
 * @returns |a-b|
 */
double abs_diff(double a, double b)
{
	return a > b ? a - b : b - a;
}

/**
* @brief Newton Raphson Method (nr)
* @param a : number that is contant in f (ex: f = x^2 -a)
* @param f : function f that algortihm use
* @param df : derivative of f
* @returns point that f intersect to x-axis
*/
double nr(double a, DFUNC2D f, DFUNC1D df)
{
	// initial point is chosen 1.0, it can be any positive number
	static const double initial_point = 1.0;
	int iter = 0;
	double old_x;
	double x = initial_point;
	do
	{
		old_x = x;
		x = x - f(x, a) / df(x);
		iter++;
	} while (iter < NR_MAX_ITER && NR_DE < abs_diff(old_x, x));
	return x;
}

/**
 * @brief parabola function (x^2 - a)
 * @param x : variable x
 * @param a : constant number that shift parabola to -y direction
 * @returns x^2 - a
 */
double parabola(double x, double a)
{
	return x * x - a;
}

/**
 * @brief derivative of parabola
 * @param x : variable x
 * @returns 2*x
 */
double deriv_parabola(double x)
{
	return 2 * x;
}

/**
 * @brief square root function, f,a = parabola will give us sqrt of a in nr-algorithm
 * @param x : variable x
 * @returns sqrt(x) (x^(1/2))
 */
double square_root(double x)
{
	return nr(x, &parabola, &deriv_parabola);
}

/**
 * @brief test function
 * @returns void
 */
static void test()
{
	double numbers[] = {12, 4, 16, 3, 9, 49, 86, 34, 5467, 0.23, 0.0721}; // random numbers

	size_t sz = sizeof(numbers) / sizeof(double); // size of array above

	double root; // calculated by nr-algorithm
	double abs_error; // abs error between number and square of root ==> |a-(sqrt(a)*sqrt(a))|
	size_t i;
	for (i = 0; i < sz; i++)
	{
		root = square_root(numbers[i]);
		abs_error = abs_diff(numbers[i], root * root);
		printf("square_root(%lf) = %lf, square_abs_error = %lf \n", numbers[i], root, abs_error);
		assert(abs_error < NR_DE); // if error is under DE = 1.0e-8 it passes the test
	}
	printf("\n\n");
	printf("All tests have successfully passed!\n");
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main()
{
	test();
	return 0;
}
