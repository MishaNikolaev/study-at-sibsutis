#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


void fillMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 100;
        }
    }
}

void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void fillByRightDiagonals(int** matrix, int n, int* D, int& index) {
    for (int col = n - 1; col >= 0; col--) {
        int j = col, i = 0;
        while (j < n) {
            D[index++] = matrix[i][j];
            i++;
            j++;
        }
    }

    for (int row = 1; row < n; row++) {
        int j = 0, i = row;
        while (i < n) {
            D[index++] = matrix[i][j];
            i++;
            j++;
        }
    }
}

void fillByLeftDiagonals(int** matrix, int n, int* D, int& index) {
    for (int col = 0; col < n; ++col) {
        int j = col, i = 0;
        while (j >= 0) {
            D[index++] = matrix[i][j];
            i++;
            j--;
        }
    }

    for (int row = 1; row < n; ++row) {
        int j = n - 1, i = row;
        while (i < n) {
            D[index++] = matrix[i][j];
            i++;
            j--;
        }
    }
}

void fillBySpiralFromCenter(int** matrix, int n, int* D, int& index) {
    int startRow = n / 2, startCol = n / 2;
    int layers = (n + 1) / 2;

    for (int layer = 0; layer < layers; layer++) {
        int r = startRow - layer;
        int c = startCol - layer;
        int size = layer * 2 + 1;

        for (int i = 0; i < size; ++i) D[index++] = matrix[r][c + i];         // top
        for (int i = 1; i < size; ++i) D[index++] = matrix[r + i][c + size - 1]; // right
        for (int i = size - 1; i >= 0 && size > 1; --i) D[index++] = matrix[r + size - 1][c + i]; // bottom
        for (int i = size - 2; i >= 1 && size > 1; --i) D[index++] = matrix[r + i][c]; // left
    }
}

void fillBySpiralFromTopLeft(int** matrix, int n, int* D, int& index) {
    int top = 0, bottom = n - 1, left = 0, right = n - 1;

    while (top <= bottom && left <= right) {
        for (int i = left; i <= right; ++i) D[index++] = matrix[top][i];
        top++;
        for (int i = top; i <= bottom; ++i) D[index++] = matrix[i][right];
        right--;
        if (top <= bottom) {
            for (int i = right; i >= left; --i) D[index++] = matrix[bottom][i];
            bottom--;
        }
        if (left <= right) {
            for (int i = bottom; i >= top; --i) D[index++] = matrix[i][left];
            left++;
        }
    }
}


int main() {
    srand((time(0)));

    int n;
    cout << "Input matrix NxN: ";
    cin >> n;

    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }

    fillMatrix(matrix, n);
    cout << "Initial matrix:\n";
    printMatrix(matrix, n);
    cout << endl;

    int* D = (int*)malloc(n * n * sizeof(int));
    int index = 0;

    fillByRightDiagonals(matrix, n, D, index);
    cout << "Elements by right diagonals:\n";
    for (int i = 0; i < index; ++i) cout << D[i] << " ";
    cout << endl;

    index = 0;

    fillByLeftDiagonals(matrix, n, D, index);
    cout << "Elements by left diagonals:\n";
    for (int i = 0; i < index; ++i) cout << D[i] << " ";
    cout << "\n";

    index = 0;

    fillBySpiralFromCenter(matrix, n, D, index);
    cout << "Elements by spiral from center:\n";

    for (int i = 0; i < index; ++i) cout << D[i] << " ";
    cout << "\n";

    index = 0;

    fillBySpiralFromTopLeft(matrix, n, D, index);
    cout << "Elements by spiral from top left:\n";
    for (int i = 0; i < index; ++i){
        cout << D[i] << " ";
    }

    free(D);
    for (int i = 0; i < n; ++i) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}



/*
int main() {
    int rows;

    printf("Enter count of rows: ");
    scanf("%d", &rows);

    int **array = (int **)malloc(rows * sizeof(int *));
    if (array == NULL) {
        printf("Exception of memory\n");
    }

    int *rowSizes = (int *)malloc(rows * sizeof(int));
    if (rowSizes == NULL) {
        printf("Exception of memory\n");
    }

    for (int i = 0; i < rows; i++) {
        printf("Input count elements of row %d: ", i + 1);
        scanf("%d", &rowSizes[i]);

        array[i] = (int *)malloc(rowSizes[i] * sizeof(int));
        if (array[i] == NULL) {
            printf("Exception of memory\n");
        }

        printf("Enter %d elements for row %d: ", rowSizes[i], i + 1);
        for (int j = 0; j < rowSizes[i]; j++) {
            scanf("%d", &array[i][j]);
        }
    }

    printf("\nOur dynamic array:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rowSizes[i]; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
        free(array[i]);
    }

    free(array);
    free(rowSizes);

    return 0;
}
*/