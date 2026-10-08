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
    printf("\nDirectory (Sequential Allocation)\n");
    printf("File Name\tStart Block\tLength\tBlocks Occupied\n");

    for (int i = 0; i < file_count; i++) {
        printf("%s\t\t%d\t\t%d\t%d to %d\n",
               directory[i].name, directory[i].start_block, directory[i].length,
               directory[i].start_block, directory[i].start_block + directory[i].length - 1);
    }

}

void delete_file() {
    char fname[30];
    printf("Enter file name to delete: ");
    scanf("%s", fname);

    int idx = -1;
    for (int i = 0; i < file_count; i++) {
        if (strcmp(directory[i].name, fname) == 0) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("[-] File '%s' not found!\n", fname);
        return;
    }

    for (int i = 0; i < directory[idx].length; i++) {
        bit_vector[directory[idx].start_block + i] = 0;
    }

    for (int i = idx; i < file_count - 1; i++) {
        directory[i] = directory[i + 1];
    }
    file_count--;

    printf("[+] File '%s' deleted successfully.\n", fname);
}

int main() {
    printf("Enter total number of disk blocks: ");
    if (scanf("%d", &total_blocks) != 1 || total_blocks <= 0 || total_blocks > MAX_BLOCKS) {
        printf("Invalid input or exceeds MAX_BLOCKS (%d). Setting to default 50.\n", MAX_BLOCKS);
        total_blocks = 50;
    }

    init_disk();
    int choice;
    do {
        printf("\nSEQUENTIAL (CONTIGUOUS) FILE ALLOCATION MENU\n");
        printf("1. Show Bit Vector\n");
        printf("2. Create New File\n");
        printf("3. Show Directory\n");
        printf("4. Delete File\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1: show_bit_vector(); break;
            case 2: create_file(); break;
            case 3: show_directory(); break;
            case 4: delete_file(); break;
            case 5: printf("Exiting.\n"); break;
            default: printf("Invalid choice! Enter 1-5.\n");
        }
    } while (choice != 5);

    return 0;
}
