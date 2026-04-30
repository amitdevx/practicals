/*
 * Assignment 5 - Set A - Question 1
 * 
 * Write a program to implement various types of hash functions which are used to place the
 * data in a hash table:
 * a. Division Method
 * b. Mid Square Method
 * c. Digit Folding Method
 * Accept n values from the user and display appropriate message in case of collision for each of
 * the above functions.
 */

#include <stdio.h>
#include <math.h>

#define TABLE_SIZE 10

int divisionMethod(int key) {
    return key % TABLE_SIZE;
}

int midSquareMethod(int key) {
    if (key == 0) {
        return 0;
    }
    long long squared = (long long)key * key;
    int numDigits = 0;
    long long temp = squared;
    
    while (temp > 0) {
        numDigits++;
        temp /= 10;
    }
    
    int mid = numDigits / 2;
    int divisor = pow(10, mid);
    int result = (squared / divisor) % TABLE_SIZE;
    
    return result;
}

int digitFoldingMethod(int key) {
    int sum = 0;
    
    while (key > 0) {
        sum += key % 100;
        key /= 100;
    }
    
    return sum % TABLE_SIZE;
}

void testHashFunction(int values[], int n, int (*hashFunc)(int), char *methodName) {
    int hashTable[TABLE_SIZE] = {0};
    int collisions = 0;
    
    printf("\n=== %s ===\n", methodName);
    printf("Value\tHash Index\tStatus\n");
    printf("-----\t----------\t------\n");
    
    for (int i = 0; i < n; i++) {
        int index = hashFunc(values[i]);
        
        if (hashTable[index] == 0) {
            hashTable[index] = values[i];
            printf("%d\t%d\t\tInserted\n", values[i], index);
        } else {
            printf("%d\t%d\t\tCOLLISION with %d\n", values[i], index, hashTable[index]);
            collisions++;
        }
    }
    
    printf("Total Collisions: %d\n", collisions);
}

int main() {
    int n, values[100];
    
    printf("Enter number of values: ");
    scanf("%d", &n);
    
    printf("Enter %d values:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &values[i]);
    }
    
    testHashFunction(values, n, divisionMethod, "Division Method");
    testHashFunction(values, n, midSquareMethod, "Mid Square Method");
    testHashFunction(values, n, digitFoldingMethod, "Digit Folding Method");
    
    return 0;
}
