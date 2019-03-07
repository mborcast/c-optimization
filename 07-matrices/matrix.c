#include <stdio.h>
#include <stdlib.h>

struct Matrix {
    double rows;
    double columns;
    double size;
    double* data;
};

double getValue(struct Matrix* a, double i, double j) {
    return a->data[(int)(a->rows * i + j)];
}
void setValue(double value, struct Matrix* a, double i, double j) {
    a->data[(int)(a->rows * i + j)] = value;
}

double getGilbert(double i, double j) {
    return 1/(i+j-1);
}

struct Matrix addMatrix(struct Matrix* a, struct Matrix* b) {

    struct Matrix c;
    c.rows = a->rows;
    c.columns = a->columns;
    c.size = c.rows * c.columns;
    c.data = malloc(c.size * sizeof(double));

    for (unsigned int i = 0; i < c.size; i++) {
        c.data[i] = a->data[i] + b->data[i];
    }
    return c;
}

struct Matrix scaleMatrix(struct Matrix* a, double scalar) {

    struct Matrix b;
    b.rows = a->rows;
    b.columns = a->columns;
    b.size = b.rows * b.columns;
    b.data = malloc(b.size * sizeof(double));

    for (unsigned int i = 0; i < b.size; i++) {
        b.data[i] = a->data[i] * scalar;
    }
    return b;
}

struct Matrix multiplyMatrix(struct Matrix* a, struct Matrix* b) {

    struct Matrix c;
    c.rows = a->rows;
    c.columns = b->columns;
    c.size = c.rows * c.columns;
    c.data = malloc(c.size * sizeof(double));

    for (unsigned int i = 0; i < a.size; i++) {
        for (unsigned int j = 0; j < b.size; j++) {
            c.data[0] = a->data[]
        }
    }
    return c;
}

int main() {


    struct Matrix gilbert;
    gilbert.rows = 3;
    gilbert.columns = 3;
    gilbert.size = gilbert.rows * gilbert.columns;
    gilbert.data = malloc(gilbert.size * sizeof(double));

    for (unsigned int i = 0; i < gilbert.rows; i++) {
        for (unsigned int j = 0; j < gilbert.columns; j++) {
            setValue(getGilbert(i+1,j+1), &gilbert, i, j);
        }
    }
    free(gilbert.data);


    struct Matrix a;
    a.rows = 3;
    a.columns = 3;
    a.size = a.rows * a.columns;
    a.data = malloc(a.size * sizeof(double));
    for (unsigned int i = 0; i < a.size; i++) {
        a.data[i] = 1;
    }
    printf("A\n");
    for (unsigned int i = 0; i < a.rows; i++) {
        for (unsigned int j = 0; j < a.columns; j++) {
            printf("%d,%d = %f\n", i, j, getValue(&a, i, j));
        }
    }

    struct Matrix b;
    b.rows = 3;
    b.columns = 3;
    b.size = b.rows * b.columns;
    b.data = malloc(b.size * sizeof(double));
    for (unsigned int i = 0; i < b.size; i++) {
        b.data[i] = 9;
    }
    printf("\nB\n");
    for (unsigned int i = 0; i < b.rows; i++) {
        for (unsigned int j = 0; j < b.columns; j++) {
            printf("%d,%d = %f\n", i, j, getValue(&b, i, j));
        }
    }

    struct Matrix aPlusB = addMatrix(&a, &b);

    printf("\nA + B\n");
    for (unsigned int i = 0; i < aPlusB.rows; i++) {
        for (unsigned int j = 0; j < aPlusB.columns; j++) {
            printf("%d,%d = %f\n", i, j, getValue(&aPlusB, i, j));
        }
    }


    struct Matrix aPlusBScaled = scaleMatrix(&aPlusB, 10);

    printf("\n10 * (A + B)\n");
    for (unsigned int i = 0; i < aPlusBScaled.rows; i++) {
        for (unsigned int j = 0; j < aPlusBScaled.columns; j++) {
            printf("%d,%d = %f\n", i, j, getValue(&aPlusBScaled, i, j));
        }
    }


    // struct Matrix aProductB = multiplyMatrix(&a, &b);

    // for (unsigned int i = 0; i < aPlusBScaled.rows; i++) {
    //     for (unsigned int j = 0; j < aPlusBScaled.columns; j++) {
    //         printf("%d,%d = %f\n", i, j, getValue(&aPlusBScaled, i, j));
    //     }
    // }


    free(a.data);
    free(b.data);
    free(aPlusB.data);
    free(aPlusBScaled.data);
    return 0;
}