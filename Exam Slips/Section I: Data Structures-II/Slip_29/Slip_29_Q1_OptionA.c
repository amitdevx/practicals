/* Q1) Write a program to sort n randomly generated elements using Heapsort method. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void heapify(int arr[], int n, int i) {
    int largest = i, left = 2 * i + 1, right = 2 * i + 2, temp;
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest != i) {
        temp = arr[i]; arr[i] = arr[largest]; arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    int i, temp;
    for (i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (i = n - 1; i > 0; i--) {
        temp = arr[0]; arr[0] = arr[i]; arr[i] = temp;
        heapify(arr, i, 0);
    }
}

int main() {
    int n, i;
    int arr[100];

    printf("Enter number of elements: ");
    scanf("%d", &n);

    srand(time(NULL));
    printf("Randomly generated array: ");
    for (i = 0; i < n; i++) {
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }
    printf("\n");

    heapSort(arr, n);

    printf("Sorted array using Heapsort: ");
    for (i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
