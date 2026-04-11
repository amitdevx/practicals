/*
 * Slip 1 - Q2 Option A: Data Link Layer Framing
 * Character Stuffing and Bit Stuffing Implementation
 * 
 * Compile: gcc Slip_01_Q2_OptionA.c -o framing
 * Run: ./framing
 */

#include <stdio.h>
#include <string.h>

#define MAX_SIZE 256

void characterStuffing(char data[], char stuffed[]) {
    int i, j = 0;
    strcpy(stuffed, "DLE STX ");
    j = 8;
    
    for (i = 0; data[i] != '\0'; i++) {
        if (data[i] == 'D' && data[i+1] == 'L' && data[i+2] == 'E') {
            strcpy(stuffed + j, "DLE DLE ");
            j += 8;
            i += 2;
        } else {
            stuffed[j++] = data[i];
            stuffed[j++] = ' ';
        }
    }
    strcpy(stuffed + j - 1, "DLE ETX");
}

void characterDestuffing(char stuffed[], char destuffed[]) {
    int j = 0;
    char *start = strstr(stuffed, "DLE STX") + 7;
    char *end = strstr(stuffed, "DLE ETX");
    
    for (char *p = start; p < end; p++) {
        if (strncmp(p, "DLE DLE", 7) == 0) {
            destuffed[j++] = 'D';
            destuffed[j++] = 'L';
            destuffed[j++] = 'E';
            p += 7;
        } else if (*p != ' ') {
            destuffed[j++] = *p;
        }
    }
    destuffed[j] = '\0';
}

void bitStuffing(char data[], char stuffed[]) {
    int i, j = 0, ones = 0;
    strcpy(stuffed, "01111110");
    j = 8;
    
    for (i = 0; data[i] != '\0'; i++) {
        if (data[i] == '1') {
            stuffed[j++] = '1';
            ones++;
            if (ones == 5) {
                stuffed[j++] = '0';
                ones = 0;
            }
        } else if (data[i] == '0') {
            stuffed[j++] = '0';
            ones = 0;
        }
    }
    strcpy(stuffed + j, "01111110");
}

void bitDestuffing(char stuffed[], char destuffed[]) {
    int i, j = 0, ones = 0, len = strlen(stuffed);
    
    for (i = 8; i < len - 8; i++) {
        if (stuffed[i] == '1') {
            destuffed[j++] = '1';
            ones++;
            if (ones == 5) {
                i++;
                ones = 0;
            }
        } else {
            destuffed[j++] = '0';
            ones = 0;
        }
    }
    destuffed[j] = '\0';
}

int main() {
    char data[MAX_SIZE], stuffed[MAX_SIZE * 2], result[MAX_SIZE];
    int choice;
    
    while (1) {
        printf("\n1. Character Stuffing  2. Bit Stuffing  3. Exit\nChoice: ");
        scanf("%d", &choice);
        getchar();
        
        if (choice == 3) break;
        
        if (choice == 1) {
            printf("Enter data: ");
            fgets(data, MAX_SIZE, stdin);
            data[strcspn(data, "\n")] = '\0';
            characterStuffing(data, stuffed);
            printf("Stuffed: %s\n", stuffed);
            characterDestuffing(stuffed, result);
            printf("Destuffed: %s\n", result);
        } else if (choice == 2) {
            printf("Enter binary (0s and 1s): ");
            fgets(data, MAX_SIZE, stdin);
            data[strcspn(data, "\n")] = '\0';
            bitStuffing(data, stuffed);
            printf("Stuffed: %s\n", stuffed);
            bitDestuffing(stuffed, result);
            printf("Destuffed: %s\n", result);
        }
    }
    
    return 0;
}
