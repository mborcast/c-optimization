#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct {
   void* data;
   int size;
} Papu;

void printSolution(Papu* x) {
    for (unsigned int i = 0; i < x->size; i++) {
        printf("%f\n", ((double*)x->data)[i]);
    }
}

int getRandomBetween(int a, int b) {
    return rand() % (b - a + 1) + a;
}

double getRandom() {
    return (double)rand() / ((double)RAND_MAX + 1) ;
}

// f(x^) = 10 + sum_i(10 * cos(2π * x_i));
double z(Papu* x) {
    double result = 10;
    double x_i;

    for (unsigned int i = 0; i < x->size; i++) {
        x_i = ((double*)(x->data))[i];
        result += pow(x_i, 2) - 10 * cos(2 * M_PI * x_i); 
    }
    return result;
}

Papu operator(Papu* a) {
    Papu b;
    b.size = a->size;
    b.data = malloc(b.size * sizeof(double));

    double integer;
    double decimalExpansion;
    int direction = (getRandomBetween(0,1) > 0) ? 1 : -1;

    for (unsigned int i = 0; i < b.size; i++) {
        integer = (double)getRandomBetween(0, 5);
        decimalExpansion = (double)(getRandomBetween(0,12) / 100);
        ((double*)b.data)[i] = ((double*)a->data)[i] + ((integer + decimalExpansion) * direction);
    }
    return b;
}

Papu simulatedAnnealing(double(*f)(Papu*), Papu(*fOp)(Papu*), Papu* x, Papu* s_0) {
    // initial temperature
    double t0 = 100;
    
    // number of repetitions allowed at each temperature level
    int N = 1000;
    
    // scaling factor
    double scalingFactor = 0.9;

    // current temperature
    double t = t0;

    // current solution
    Papu s = *s_0;

    // the best solution
    Papu s_star = *s_0;

    // repetition counter
    int n;

    double delta;
    double p;
    
    Papu s_n;

    while (t > 1) {
        printf("T: %f\n", t);
        n = 0;

        while (n < N) {
            // generate solution s_n in the neighbourhood of s_0
            s_n = fOp(s_0);

            delta = f(&s_n) - f(&s);

            if (delta >= 0) {
                s = s_n;
            }
            else {
                // generate random between 0 - 1
                double r = getRandom();

                // probability of accepting Sn when it is not better than s 
                p = exp(delta/t);

                if (r <= p) {
                    s = s_n;

                    printf("\nT: %f => %d/%d\n", t, n, N);
                    printSolution(&s);
                    n++;
                }
            }
            if (f(&s_n) > f(&s_star)) {
                s_star = s_n;
            }
            free(s_n.data);
        }
        t *= scalingFactor;
    }
    return s_star;
}


int main() {

    Papu x;
    x.size = 10;
    x.data = malloc(x.size * sizeof(double));

    for (unsigned int i = 0; i < x.size; i++) {
        ((double*)x.data)[i] = i+1;
    }

    Papu s_0;
    s_0.size = 10;
    s_0.data = malloc(s_0.size * sizeof(double));

    for (unsigned int i = 0; i < s_0.size; i++) {
        ((double*)s_0.data)[i] = 0;
    }

    srand(time(NULL));
    
    Papu x_star = simulatedAnnealing(z, operator, &x, &s_0);
    printf("\n\ns*\n");
    printSolution(&x_star);

    printf("f(s*): %f\n", z(&x_star));

    free(x.data);
    free(s_0.data);
    return 0;
}