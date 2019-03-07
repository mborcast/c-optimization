#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b) {
    *a = *a ^ *b;
    *b = *b ^ *a;
    *a = *a ^ *b;
}
void swapMin(int* data, int n, int i) {
    if (i >= (n-1)) {
        return;
    }
    if (data[i] < data[i+1]) {
        swap(&data[i], &data[i+1]);
    }
    swapMin(data, n, ++i);
}

void bubbleSort(int* data, int n) {
    if (n <= 1) {
        return;
    }
    swapMin(data, n, 0);
    bubbleSort(data, n - 1);
}

int compare (const void* a, const void* b) {
   return (*(int*)b - *(int*)a);
}
void quickSort(int* data, int n) {
    qsort(data, n, sizeof(int), compare);
}

int getSortingFunctionIndex(char* key) {

    if (strcmp(key, "bubble") == 0) {
        printf("Bubblesort selected.\n");
        return 0;
    }
    if (strcmp(key, "quick") == 0) {
        printf("Quicksort selected.\n");
        return 1;
    }
    return -1;
}

int main (int argc, char** argv) {
    
    if (!argv[1]) {
        printf("Error: Input file not defined\n");
        return 1;
    }
    if (!argv[2]) {
        printf("Error: Sorting algorithm not specified\n");
        return 1;
    }

    // open file
    FILE* inputFile = fopen(argv[1], "r");

    if (!inputFile) {
        printf("Error: Input path not found\n");
        return 1;
    }

    // first item in file should be total items count
    int itemsCount;
    fscanf(inputFile, "%d", &itemsCount);
    
    // initialize array
    int* data = malloc(itemsCount * sizeof(int));

    // load file contents into array
    for (unsigned int i = 0; i < itemsCount; i++) {
        fscanf(inputFile, "%d", &data[i]);
    }
    fclose(inputFile);

    void (*papus[2])(int*, int) = {&bubbleSort, &quickSort};

    int functionIdx = getSortingFunctionIndex(argv[2]);
    if (functionIdx < 0) {
        printf("Error: Invalid sorting algorithm\nOptions: bubble, quick\n");
        return 1;
    }


    clock_t start, end;
    double cpu_time_used;

    start = clock();

    (*papus[functionIdx])(data, itemsCount);

    end = clock();

    printf("%fms\n\n", ((double) (end - start)) / CLOCKS_PER_SEC);

    for (unsigned int i = 0; i < itemsCount; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    
    free(data);
    return 0;
}
