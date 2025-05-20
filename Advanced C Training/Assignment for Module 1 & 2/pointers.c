#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
void rearrangeEvenOdd(int *arr, int size) {
    int *left = arr;          
    int *right = arr + size - 1; 
    int *evenPos = arr;        

    while (left <= right) {
        while (left <= right && *left % 2 == 0) {
            left++;
        }
        while (left <= right && *right % 2 != 0) {
            right--;
        }
        if (left < right) {
            swap(left, right);
        }
    }

    for (int *i = arr; i < left - 1; i++) {
        for (int *j = arr; j < left - 1; j++) {
            if (*(j + 1) < *j) {
                swap(j, j + 1);
            }
        }
    }
    for (int *i = left; i < arr + size - 1; i++) {
        for (int *j = left; j < arr + size - 1; j++) {
            if (*(j + 1) < *j) {
                swap(j, j + 1);
            }
        }
    }
}

void printArray(int *arr, int size) {
    for (int *p = arr; p < arr + size; p++) {
        printf("%d ", *p);
    }
    printf("\n");
}

int main() {
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int arr[size];
    printf("Enter %d integers:\n", size);
    for (int *p = arr; p < arr + size; p++) {
        scanf("%d", p);
    }

    printf("Original array: ");
    printArray(arr, size);

    rearrangeEvenOdd(arr, size);

    printf("Rearranged array (even before odd): ");
    printArray(arr, size);

    return 0;
}