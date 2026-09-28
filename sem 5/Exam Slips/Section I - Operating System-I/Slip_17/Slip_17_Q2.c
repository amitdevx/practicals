#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BLOCKS 100
#define MAX_FILES 20

struct FileNode {
    char name[30];
    int start_block;
    int length;
};

int bit_vector[MAX_BLOCKS];
struct FileNode directory[MAX_FILES];
int file_count = 0;
int total_blocks = 50;

void init_disk() {
    srand(time(NULL));
    for (int i = 0; i < total_blocks; i++) {
        bit_vector[i] = (rand() % 6 == 0) ? 1 : 0;
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
    printf("Enter number of contiguous blocks required: ");
    scanf("%d", &length);

    int start = -1;
    for (int i = 0; i <= total_blocks - length; i++) {
        int contiguous_free = 0;
        for (int j = 0; j < length; j++) {
            if (bit_vector[i + j] == 0) contiguous_free++;
            else break;
        }
        if (contiguous_free == length) {
            start = i;
            break;
        }
    }

    if (start == -1) {
        printf("[-] Continuous free blocks of size %d not found!\n", length);
        return;
    }

    for (int i = 0; i < length; i++) {
        bit_vector[start + i] = 1;
    }

    strcpy(directory[file_count].name, fname);
    directory[file_count].start_block = start;
    directory[file_count].length = length;
    file_count++;

    printf("[+] File '%s' allocated sequentially from block %d to %d.\n",
           fname, start, start + length - 1);
}

void show_directory() {
    printf("\n--- Directory (Sequential Allocation) ---\n");
    printf("File Name\tStart Block\tLength\tBlocks Occupied\n");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < file_count; i++) {
        printf("%s\t\t%d\t\t%d\t%d to %d\n",
               directory[i].name, directory[i].start_block, directory[i].length,
               directory[i].start_block, directory[i].start_block + directory[i].length - 1);
    }
    printf("----------------------------------------------------------\n");
}

int main() {
    printf("Enter total number of disk blocks: ");
    if (scanf("%d", &total_blocks) != 1 || total_blocks <= 0) total_blocks = 50;

    init_disk();
    int choice;
    do {
        printf("\n=== SEQUENTIAL (CONTIGUOUS) FILE ALLOCATION MENU ===\n");
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
