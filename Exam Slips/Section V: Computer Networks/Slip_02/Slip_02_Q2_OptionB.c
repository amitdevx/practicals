/*
 * Slip 2 - Q2 Option B: Framing using Character Count Method
 * 
 * Compile: gcc Slip_02_Q2_OptionB.c -o framing
 * Run: ./framing
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void stuff(const char *data, char *frame) {
    int len = strlen(data);
    sprintf(frame, "%d ", len);
    strcat(frame, data);
}

void destuff(const char *frame, char *data) {
    int len = atoi(frame);
    const char *start = strchr(frame, ' ') + 1;
    strncpy(data, start, len);
    data[len] = '\0';
}

int main() {
    char data[256], frame[512], result[256];
    int choice;
    
    while (1) {
        printf("\n1. Stuff Frame  2. Destuff Frame  3. Exit\nChoice: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                printf("Enter data: ");
                fgets(data, 256, stdin);
                data[strcspn(data, "\n")] = '\0';
                stuff(data, frame);
                printf("Frame: %s\n", frame);
                break;
            case 2:
                printf("Enter frame: ");
                fgets(frame, 512, stdin);
                frame[strcspn(frame, "\n")] = '\0';
                destuff(frame, result);
                printf("Data: %s\n", result);
                break;
            case 3:
                return 0;
        }
    }
}
