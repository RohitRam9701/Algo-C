/**
 * @file
 * @brief Trigonometric Functions
 * implemented by using Taylor Series
 * https://en.wikipedia.org/wiki/Taylor_series
 * @details
 * Trigonometric functions that are implemented by using Taylor Series
 * They give us efficient result for 0 < x < pi/2.
 * And for reverse func. they give us efficient result for 0 < x < pi/4.
 * Values other than this interval can easily implemented by trigonometric conversions.
 * @author [Ali Kaan UYAR](https://github.com/kaan2463)
 */

#include <stdio.h> // for printf
#include <math.h> // for std trigonometric functions to compare
#include <assert.h> // for assert

// Max depth in Taylor series
#define TRIG_MAX_ITER   70
// PI constant
#define TRIG_PI         3.14159265358979323846 

/**
 * @brief sinus function
 * @param x : variable
 * @returns sin(x)
 */
double trig_sin(double x)
{
    double pow_x = 1.0;
    double fac = 1.0;
    double result = 0.0;
    double sign;
    for (size_t i = 0; i < TRIG_MAX_ITER - 1; i++)
    {
        if (i % 2 == 1)
        {
            sign = ((i - 1) / 2) % 2 == 0 ? 1.0 : -1.0;
            result += sign * pow_x / fac;
        }
        fac *= (double)(i + 1);
        pow_x = pow_x * x;
    }
    return result;
}

/**
 * @brief cosinus function
 * @param x : variable
 * @returns cos(x)
 */
double trig_cos(double x)
{
    double pow_x = 1.0;
    double fac = 1.0;
    double result = 0.0;
    double sign;
    for (size_t i = 0; i < TRIG_MAX_ITER; i++)
    {
        if (i % 2 == 0)
        {
            sign = (i / 2) % 2 == 0 ? 1.0 : -1.0;
            result += sign * pow_x / fac;
        }
        fac *= (double)(i + 1);
        pow_x = pow_x * x;
    }
    return result;
}

/**
 * @brief tangent function
 * not efficient
 * @param x : variable
 * @returns tan(x)
 */
double trig_tan(double x)
{
    double pow_x = 1.0;
    double fac = 1.0;
    double result_sin = 0.0;
    double result_cos = 0.0;
    double sign_sin;
    double sign_cos;
    for (size_t i = 0; i < TRIG_MAX_ITER; i++)
    {
        if (i % 2 == 1)
        {
            sign_sin = ((i - 1) / 2) % 2 == 0 ? 1.0 : -1.0;
            result_sin += sign_sin * pow_x / fac;
        }

        if (i % 2 == 0)
        {
            sign_cos = (i / 2) % 2 == 0 ? 1.0 : -1.0;
            result_cos += sign_cos * pow_x / fac;
        }
        fac *= (double)(i + 1);
        pow_x = pow_x * x;
    }
    return result_sin / result_cos;
}

/**
 * @brief reverse sinus function
 * not efficient
 * @param x : variable
 * @returns arcsin(x)
 */
double trig_arcsin(double x)
{
    double pow_x = 1.0;
    double pow4 = 1.0;
    double fac = 1.0;
    double fac2n = 1.0;
    double result = 0.0;
    for (size_t i = 0; i < TRIG_MAX_ITER + 1; i++)
    {
        if (i > 1)
        {
            fac2n *= (double)(i - 1);
        }
        if (i % 2 == 1)
        {
            if (i > 1)
            {
                fac *= ((double)(i - 1)) / 2.0;
            }
            fac = fac == 0 ? 1.0 : fac;
            result += (fac2n * pow_x) / (pow4 * (fac * fac) * ((double)i));
            pow4 *= 4;
        }
        pow_x = pow_x * x;
    }
    return result;
}

/**
 * @brief reverse tangent function
 * not efficient
 * @param x : variable
 * @returns arctan(x)
 */
double trig_arctan(double x)
{
    double pow_x = 1.0;
    double result = 0.0;
    double sign;
    for (size_t i = 0; i < TRIG_MAX_ITER - 1; i++)
    {
        if (i % 2 == 1)
        {
            sign = ((i - 1) / 2) % 2 == 0 ? 1.0 : -1.0;

            result += sign * pow_x / ((double)i);
        }
        pow_x = pow_x * x;
    }
    return result;
}

//TEST

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
 
typedef double (*trig_f)(double); //trigonometric function type
 
// help to arrange test params
#define test_param(x) &trig_ ## x, &x, #x
// Epsilon value 0.000001
#define TEST_DE 1.0e-6 

/**
 * @brief test helper function for sin, cos, tan
 * @param rad : radian
 * @param f : functional (trig_sin, trig_cos, trig_tan)(implemented func.)
 * @param sf : std functional (sin, cos, tan)
 * @param f_str : name of function
 * @return void
 */
 void test_func(double rad, trig_f f, trig_f sf, char* f_str)
 {
     double trig_result = f(rad); // trigonometric function result 
     double std_result = sf(rad); // std trigonometric function result
     double abs_error; // difference between implemeted func. and std func.

     abs_error = abs_diff(trig_result, std_result);
     printf("trig_%s(%lf) = %lf, std_%s(%lf) = %lf, abs_error = %lf \n",
         f_str, rad, trig_result,
         f_str, rad, std_result,
         abs_error);
     assert(abs_error < TEST_DE);
 }

 /**
 * @brief test : compare implemented functions and std function
 * @return void
 */
 void test()
 {
     // 0 < rad < pi/2
     double radians[] = {0.33, 0.47, 0.44, 0.25, 0.12, 0.2};
 
     size_t sz = sizeof(radians) / sizeof(double);
 
     double rad;
     size_t i;
     for (i = 0; i < sz; i++)
     {
         rad = radians[i] * TRIG_PI;
         test_func(rad, test_param(sin));
     }
 
     for (i = 0; i < sz; i++)
     {
         rad = radians[i] * TRIG_PI;
         test_func(rad, test_param(cos));
     }
 
     for (i = 0; i < sz; i++)
     {
         rad = radians[i] * TRIG_PI;
         test_func(rad, test_param(tan));
     }

     // 0 < rad < pi/2
     double radians2[] = {0.1, 0.229, 0.22, 0.019, 0.123};

     size_t sz2 = sizeof(radians2) / sizeof(double);

     double abs_error; // abs error func between actual value and reverse trigonometric functions
     double result;
     for (i = 0; i < sz2; i++)
     {
         rad = radians2[i] * TRIG_PI;
         result = trig_arcsin(trig_sin(rad));
         abs_error = abs_diff(rad, result);
         printf("arcsin(sin(%lf)) = %lf, abs_error = %lf\n", rad, result, abs_error);
         assert(abs_error <TEST_DE);
     }

     for (i = 0; i < sz2; i++)
     {
         rad = radians2[i] * TRIG_PI;
         result = trig_arctan(trig_tan(rad));
         abs_error = abs_diff(rad, result);
         printf("arctan(tan(%lf)) = %lf, abs_error = %lf\n", rad, result, abs_error);
         assert(abs_error < TEST_DE);
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

