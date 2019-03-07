#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define H0 1e-10

double poly(double x) {
    return x*x;
}
double cosTaylor(double x) {
    return 1 - (x*x)/4 + (x*x*x*x)/24 - (x*x*x*x*x*x)/720 + (x*x*x*x*x*x*x*x)/40320;
}
double coss(double x) {
    return cos(x * 3.14159265 / 180.0);
}

double fprime(double(*f)(double), double x) {
    return (f(x+H0) - f(x))/H0;
}
double fprime2(double(*f)(double), double x) {
    printf("x+h %f\t", f(x+H0));
    printf("x-h %f\t", f(x-H0));
    printf("fx %f\t", f(x));
    printf("2fx %f\t", 2*f(x));
    printf("h^2 %f\n", H0*H0);

    return (f(x+H0) + f(x-H0) - 2*f(x) )/(H0*H0);
}
double newton(double(*f)(double), double xi) {
    double prime = fprime(f, xi);
    printf("f'(%f) = %f\t", xi, prime);
    double prime2 = fprime2(f, xi);
    printf("f''(%f) = %f\t", xi, prime2);

    double x = xi - prime/prime2;

    double fx = fprime(f, x);
    printf("CP: f'(%f) = %f\n", x, fx);
    // printf("x = %f;\tf'(x) = %f;\n", x, fx);

    if (fx == 0) {
        printf("root = %f\n\n", x);
        return x;
    }
    return newton(f, x);
}

int main (int argc, char** argv) {
    double test = fprime2(poly, 1);
    printf("%f", test);
    // newton(poly, 10);
}
