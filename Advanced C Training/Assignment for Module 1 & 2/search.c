#include <stdio.h>

int searchInMatrix(int matrix[][100], int n, int key) {

    int row = 0;
    int col = n - 1;

    while (row < n && col >= 0) {
        if (matrix[row][col] == key) {
            printf("Key %d found at position (%d, %d)\n", key, row, col);
            return 1; 
        }
        else if (matrix[row][col] > key) {
            col--; 
        }
        else {
            row++;
        }
    }

    printf("Key %d not found in the matrix\n", key);
    return 0; 
}

int main() {
    int n;
    printf("Enter the size of the matrix (n): ");
    scanf("%d", &n);

    int matrix[100][100]; 
    printf("Enter the elements of the %d x %d matrix (row-wise, sorted):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int key;
    printf("Enter the key to search for: ");
    scanf("%d", &key);

    searchInMatrix(matrix, n, key);

    return 0;
}