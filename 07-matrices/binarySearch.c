#include <stdio.h>
#include <stdlib.h>

int binarySearch(int* data, int value, int min, int high) {
    if (high < min) {
        return -1;
    }
    int mid = (int)((high-min) * 0.5) + min;

    if (data[mid] == value) {
        return mid;
    }
    if (value < data[mid]) {
        return binarySearch(data, value, min, mid-1);
    }
    return binarySearch(data, value, mid+1, high);
}

int compare (const void* a, const void* b) {
   return (*(int*)a - *(int*)b);
}

int main (int argc, char** argv) {
    
    if (!argv[1]) {
        printf("Error: Input file not defined\n");
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

    // prompt user
    int searchValue;
    printf("Enter search value: ");
    scanf("%d", &searchValue);

    // sort data before search
    qsort(data, itemsCount, sizeof(int), compare);

    int result = binarySearch(data, searchValue, 0, itemsCount);
    if (result > 0) {
        printf(">>> Value found at index %d\n\n", result);
    }
    else {
        printf(">>> Value not found\n");
    }
    
    free(data);
    return 0;
}
