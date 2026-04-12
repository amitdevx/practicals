/* Q1) Write a program to implement various types of hash functions which are used to place
   the data in a hash table:
   a. Division Method  b. Mid Square Method  c. Digit Folding Method
   Accept n values from the user and display appropriate message in case of collision. */

#include <stdio.h>

#define TABLE_SIZE 10

int divisionMethod(int key) { return key % TABLE_SIZE; }

int midSquareMethod(int key) {
    long long squared = (long long)key * key;
    int numDigits = 0, divisor = 1, result;
    long long temp = squared;
    if (key == 0) return 0;
    while (temp > 0) { numDigits++; temp /= 10; }
    divisor = 1;
    temp = numDigits / 2;
    while (temp > 0) { divisor *= 10; temp--; }
    result = (int)((squared / divisor) % TABLE_SIZE);
    return result;
}

int digitFoldingMethod(int key) {
    int sum = 0;
    while (key > 0) { sum += key % 100; key /= 100; }
    return sum % TABLE_SIZE;
}

void testHash(int values[], int n, int (*func)(int), char *name) {
    int table[TABLE_SIZE] = {0}, collisions = 0, i, index;
    printf("\n=== %s ===\n", name);
    printf("Value\tIndex\tStatus\n");
    for (i = 0; i < n; i++) {
        index = func(values[i]);
        if (table[index] == 0) {
            table[index] = values[i];
            printf("%d\t%d\tInserted\n", values[i], index);
        } else {
            printf("%d\t%d\tCOLLISION with %d\n", values[i], index, table[index]);
            collisions++;
        }
    }
    printf("Total Collisions: %d\n", collisions);
}

int main() {
    int n, values[100], i;

    printf("Enter number of values: ");
    scanf("%d", &n);
    printf("Enter %d values:\n", n);
    for (i = 0; i < n; i++) scanf("%d", &values[i]);

    testHash(values, n, divisionMethod, "Division Method");
    testHash(values, n, midSquareMethod, "Mid Square Method");
    testHash(values, n, digitFoldingMethod, "Digit Folding Method");

    return 0;
}
