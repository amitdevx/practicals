#include <stdio.h>
#include <stdlib.h>

#define P 5
#define R 3

int alloc[P][R] = {{0, 1, 0}, {4, 0, 0}, {5, 0, 4}, {4, 3, 3}, {2, 2, 4}};
int max_mat[P][R] = {{0, 0, 0}, {5, 2, 2}, {1, 0, 4}, {4, 4, 4}, {6, 5, 5}};
int avail[R] = {7, 2, 6};
int need[P][R];

void calculateNeed() {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max_mat[i][j] - alloc[i][j];
        }
    }
}

void acceptAvailable() {
    printf("Enter Available instances for %d resources: ", R);
    for (int j = 0; j < R; j++) {
        if (scanf("%d", &avail[j]) != 1) avail[j] = 0;
    }
    printf("Available resources updated successfully.\n");
}

void displayAllocMax() {
    printf("\nProcess\tAllocation\tMax\n");
    for (int i = 0; i < P; i++) {
        printf("P%d\t", i);
        for (int j = 0; j < R; j++) printf("%d ", alloc[i][j]);
        printf("\t\t");
        for (int j = 0; j < R; j++) printf("%d ", max_mat[i][j]);
        printf("\n");
    }
}

void displayNeed() {
    calculateNeed();
    printf("\nNeed Matrix (Need = Max - Allocation):\n");
    printf("Process\tNeed (A B C)\n");
    for (int i = 0; i < P; i++) {
        printf("P%d\t", i);
        for (int j = 0; j < R; j++) printf("%d ", need[i][j]);
        printf("\n");
    }
}

void displayAvailable() {
    printf("\nAvailable Resources Vector:\n");
    for (int j = 0; j < R; j++) {
        printf("Resource %c: %d\n", 'A' + j, avail[j]);
    }
}

int main() {
    calculateNeed();
    int choice;
    do {
        printf("\n=============================================\n");
        printf("   BANKER'S ALGORITHM - MENU DRIVEN PROGRAM\n");
        printf("=============================================\n");
        printf("1. Accept Available\n");
        printf("2. Display Allocation and Max\n");
        printf("3. Display Contents of Need Matrix\n");
        printf("4. Display Available\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1: acceptAvailable(); break;
            case 2: displayAllocMax(); break;
            case 3: displayNeed(); break;
            case 4: displayAvailable(); break;
            case 5: printf("Exiting program.\n"); break;
            default: printf("Invalid choice! Enter 1-5.\n");
        }
    } while (choice != 5);

    return 0;
}
