#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define H0 1e-10

double poly(double x) {
    return x*x - 9;
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
double newton(double(*f)(double), double xi) {
    double x = xi - f(xi)/fprime(f, xi);

    double fx = f(x);
    printf("x = %f;\tf(x) = %f;\n", x, fx);

    if (f(x) == 0) {
        printf("root = %f\n\n", x);
        return x;
    }
    return newton(f, x);
}

int main (int argc, char** argv) {
    newton(poly, 10);
}
