#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_BLOCKS 100
#define MAX_FILES 20

struct FileNode {
    char name[30];
    int start_block;
    int length;
    int blocks[MAX_BLOCKS];
};

int bit_vector[MAX_BLOCKS];
struct FileNode directory[MAX_FILES];
int file_count = 0;
int total_blocks = 50;

void init_disk() {
    srand(time(NULL));
    for (int i = 0; i < total_blocks; i++) {
        // Randomly allocate ~20% blocks initially
        bit_vector[i] = (rand() % 5 == 0) ? 1 : 0;
    }
}

void show_bit_vector() {
    printf("\nBit Vector (0 = Free, 1 = Allocated):\n");
    for (int i = 0; i < total_blocks; i++) {
        printf("%d ", bit_vector[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }
    printf("\n");
}

void create_file() {
    if (file_count >= MAX_FILES) {
        printf("Directory full!\n");
        return;
    }
    char fname[30];
    int length;
    printf("Enter file name: ");
    scanf("%s", fname);
    printf("Enter number of blocks required: ");
    scanf("%d", &length);

    // Count free blocks
    int free_count = 0;
    for (int i = 0; i < total_blocks; i++) {
        if (bit_vector[i] == 0) free_count++;
    }

    if (free_count < length) {
        printf("[-] Not enough free blocks available! (Free: %d, Required: %d)\n", free_count, length);
        return;
    }

    strcpy(directory[file_count].name, fname);
    directory[file_count].length = length;

    int allocated = 0;
    for (int i = 0; i < total_blocks && allocated < length; i++) {
        if (bit_vector[i] == 0) {
            bit_vector[i] = 1;
            directory[file_count].blocks[allocated] = i;
            if (allocated == 0) {
                directory[file_count].start_block = i;
            }
            allocated++;
        }
    }
    file_count++;
    printf("[+] File '%s' created successfully using Linked Allocation.\n", fname);
}

void show_directory() {
    printf("\n--- File Directory (Linked Allocation) ---\n");
    printf("File Name\tStart Block\tLength\tLinked Blocks\n");
    printf("-----------------------------------------------------------------\n");
    for (int i = 0; i < file_count; i++) {
        printf("%s\t\t%d\t\t%d\t", directory[i].name, directory[i].start_block, directory[i].length);
        for (int j = 0; j < directory[i].length; j++) {
            printf("%d", directory[i].blocks[j]);
            if (j < directory[i].length - 1) printf(" -> ");
        }
        printf("\n");
    }
    printf("-----------------------------------------------------------------\n");
}

int main() {
    printf("Enter total number of disk blocks: ");
    if (scanf("%d", &total_blocks) != 1 || total_blocks <= 0) total_blocks = 50;

    init_disk();
    int choice;
    do {
        printf("\n=== LINKED FILE ALLOCATION MENU ===\n");
        printf("1. Show Bit Vector\n");
        printf("2. Create New File\n");
        printf("3. Show Directory\n");
        printf("4. Exit\n");
        printf("Enter your choice (1-4): ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1: show_bit_vector(); break;
            case 2: create_file(); break;
            case 3: show_directory(); break;
            case 4: printf("Exiting.\n"); break;
            default: printf("Invalid choice! Enter 1-4.\n");
        }
    } while (choice != 4);

    return 0;
}
