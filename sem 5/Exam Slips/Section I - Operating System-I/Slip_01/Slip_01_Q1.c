/*
 * Lab Course: CS-305-MJ-P (Operating System-I)
 * Slip No: 01 - Question 1
 * 
 * Q.1) Write a C Menu driven Program to implement following functionality:
 *      a) Accept Available
 *      b) Display Allocation, Max
 *      c) Display the contents of need matrix
 *      d) Display Available
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_P 10
#define MAX_R 10

int num_p = 5;
int num_r = 3;

// Allocation Matrix
int alloc[MAX_P][MAX_R] = {
    {2, 3, 2},
    {4, 0, 0},
    {5, 0, 4},
    {4, 3, 3},
    {2, 2, 4}
};

// Max Matrix
int max_m[MAX_P][MAX_R] = {
    {9, 7, 5},
    {5, 2, 2},
    {1, 0, 4},
    {4, 4, 4},
    {6, 5, 5}
};

// Available Vector
int avail[MAX_R] = {3, 3, 2};

// Need Matrix
int need[MAX_P][MAX_R];

// Function to calculate Need matrix: Need = Max - Allocation
void calculate_need() {
    for (int i = 0; i < num_p; i++) {
        for (int j = 0; j < num_r; j++) {
            need[i][j] = max_m[i][j] - alloc[i][j];
        }
    }
}

// Function a): Accept Available
void accept_available() {
    printf("\nEnter Available resources (%d resource types: A, B, C...):\n", num_r);
    for (int j = 0; j < num_r; j++) {
        printf("Available for Resource %c: ", 'A' + j);
        if (scanf("%d", &avail[j]) != 1) {
            printf("Invalid input!\n");
            return;
        }
    }
    printf("Available resources updated successfully.\n");
}

// Function b): Display Allocation, Max
void display_alloc_max() {
    printf("\n%-10s | %-16s | %-16s\n", "Process", "Allocation", "Max");
    printf("           | ");
    for (int j = 0; j < num_r; j++) printf("%-4c", 'A' + j);
    printf("     | ");
    for (int j = 0; j < num_r; j++) printf("%-4c", 'A' + j);

    for (int i = 0; i < num_p; i++) {
        printf("P%-9d | ", i);
        for (int j = 0; j < num_r; j++) {
            printf("%-4d", alloc[i][j]);
        }
        printf("     | ");
        for (int j = 0; j < num_r; j++) {
            printf("%-4d", max_m[i][j]);
        }
        printf("\n");
    }
}

// Function c): Display the contents of need matrix
void display_need() {
    calculate_need();
    printf("\nNeed Matrix (Need = Max - Allocation):\n");
    printf("%-10s | ", "Process");
    for (int j = 0; j < num_r; j++) printf("%-4c", 'A' + j);

    for (int i = 0; i < num_p; i++) {
        printf("P%-9d | ", i);
        for (int j = 0; j < num_r; j++) {
            printf("%-4d", need[i][j]);
        }
        printf("\n");
    }
}

// Function d): Display Available
void display_available() {
    printf("\nAvailable Resources Vector:\n");
    for (int j = 0; j < num_r; j++) {
        printf("Resource %c: %d\n", 'A' + j, avail[j]);
    }
}

int main() {
    int choice;
    calculate_need();

    while (1) {

        printf("   BANKER'S ALGORITHM - MENU DRIVEN PROGRAM\n");

        printf("1. Accept Available\n");
        printf("2. Display Allocation and Max\n");
        printf("3. Display Contents of Need Matrix\n");
        printf("4. Display Available\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");

        if (scanf("%d", &choice) != 1) {
            break;
        }

        switch (choice) {
            case 1:
                accept_available();
                break;
            case 2:
                display_alloc_max();
                break;
            case 3:
                display_need();
                break;
            case 4:
                display_available();
                break;
            case 5:
                printf("\nExiting program. Goodbye!\n");
                exit(0);
            default:
                printf("\nInvalid choice! Please choose between 1 and 5.\n");
        }
    }
    return 0;
}
