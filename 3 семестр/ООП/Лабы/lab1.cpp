#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
int* genRandArray(int size, int maxValue) {
    int* arr = (int*)malloc((size + 1) * sizeof(int));
    if (arr == NULL) {
        printf("Failed\n");
    }

    arr[0] = size;
    for (int i = 1; i <= size; i++) {
        arr[i] = rand() % maxValue;
    }

    return arr;
}

void print(int* arr) {
    int size = arr[0];
    printf("%d: ", size);
    for (int i = 1; i <= size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));
    int size = rand() % 10;
    int maxValue = 100;
    int* arr = genRandArray(size, maxValue);

    print(arr);
    free(arr);

    return 0;
}
*/


int** genRandMatrix(int size, int maxValue) {
    int** matrix = (int**)malloc(size * sizeof(int*));
    if (matrix == 0) {
        printf("Failed\n");
    }

    for (int i = 0; i < size; i++) {
        int rowSize = rand() % 10;
        matrix[i] = (int*)malloc((rowSize + 1) * sizeof(int));
        if (matrix[i] == NULL) {
            printf("Failed string %d\n", i);
            return NULL;
        }
        matrix[i][0] = rowSize;
        for (int j = 1; j <= rowSize; j++) {
            matrix[i][j] = rand() % maxValue;
        }
    }
    return matrix;
}

void printMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        int rowSize = matrix[i][0];
        printf("%d: ", rowSize);
        for (int j = 1; j <= rowSize; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void freeMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    srand(time(0));
    int size = rand() % 10 + 1;
    int maxValue = 100;

    int** matrix = genRandMatrix(size, maxValue);
    if (matrix == 0) {
        return -1;
    }
    printMatrix(matrix, size);
    freeMatrix(matrix, size);

    return 0;
}

