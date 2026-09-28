# File Allocation, Custom Shell, and Process Control Templates in C

def get_file_alloc_linked_c():
    return '''#include <stdio.h>
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
    printf("\\nBit Vector (0 = Free, 1 = Allocated):\\n");
    for (int i = 0; i < total_blocks; i++) {
        printf("%d ", bit_vector[i]);
        if ((i + 1) % 10 == 0) printf("\\n");
    }
    printf("\\n");
}

void create_file() {
    if (file_count >= MAX_FILES) {
        printf("Directory full!\\n");
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
        printf("[-] Not enough free blocks available! (Free: %d, Required: %d)\\n", free_count, length);
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
    printf("[+] File '%s' created successfully using Linked Allocation.\\n", fname);
}

void show_directory() {
    printf("\\n--- File Directory (Linked Allocation) ---\\n");
    printf("File Name\\tStart Block\\tLength\\tLinked Blocks\\n");
    printf("-----------------------------------------------------------------\\n");
    for (int i = 0; i < file_count; i++) {
        printf("%s\\t\\t%d\\t\\t%d\\t", directory[i].name, directory[i].start_block, directory[i].length);
        for (int j = 0; j < directory[i].length; j++) {
            printf("%d", directory[i].blocks[j]);
            if (j < directory[i].length - 1) printf(" -> ");
        }
        printf("\\n");
    }
    printf("-----------------------------------------------------------------\\n");
}

int main() {
    printf("Enter total number of disk blocks: ");
    if (scanf("%d", &total_blocks) != 1 || total_blocks <= 0) total_blocks = 50;

    init_disk();
    int choice;
    do {
        printf("\\n=== LINKED FILE ALLOCATION MENU ===\\n");
        printf("1. Show Bit Vector\\n");
        printf("2. Create New File\\n");
        printf("3. Show Directory\\n");
        printf("4. Exit\\n");
        printf("Enter your choice (1-4): ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1: show_bit_vector(); break;
            case 2: create_file(); break;
            case 3: show_directory(); break;
            case 4: printf("Exiting.\\n"); break;
            default: printf("Invalid choice! Enter 1-4.\\n");
        }
    } while (choice != 4);

    return 0;
}
'''

def get_file_alloc_seq_c():
    return '''#include <stdio.h>
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
    printf("\\nBit Vector (0 = Free, 1 = Allocated):\\n");
    for (int i = 0; i < total_blocks; i++) {
        printf("%d ", bit_vector[i]);
        if ((i + 1) % 10 == 0) printf("\\n");
    }
    printf("\\n");
}

void create_file() {
    if (file_count >= MAX_FILES) {
        printf("Directory full!\\n");
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
        printf("[-] Continuous free blocks of size %d not found!\\n", length);
        return;
    }

    for (int i = 0; i < length; i++) {
        bit_vector[start + i] = 1;
    }

    strcpy(directory[file_count].name, fname);
    directory[file_count].start_block = start;
    directory[file_count].length = length;
    file_count++;

    printf("[+] File '%s' allocated sequentially from block %d to %d.\\n",
           fname, start, start + length - 1);
}

void show_directory() {
    printf("\\n--- Directory (Sequential Allocation) ---\\n");
    printf("File Name\\tStart Block\\tLength\\tBlocks Occupied\\n");
    printf("----------------------------------------------------------\\n");
    for (int i = 0; i < file_count; i++) {
        printf("%s\\t\\t%d\\t\\t%d\\t%d to %d\\n",
               directory[i].name, directory[i].start_block, directory[i].length,
               directory[i].start_block, directory[i].start_block + directory[i].length - 1);
    }
    printf("----------------------------------------------------------\\n");
}

int main() {
    printf("Enter total number of disk blocks: ");
    if (scanf("%d", &total_blocks) != 1 || total_blocks <= 0) total_blocks = 50;

    init_disk();
    int choice;
    do {
        printf("\\n=== SEQUENTIAL (CONTIGUOUS) FILE ALLOCATION MENU ===\\n");
        printf("1. Show Bit Vector\\n");
        printf("2. Create New File\\n");
        printf("3. Show Directory\\n");
        printf("4. Exit\\n");
        printf("Enter your choice (1-4): ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1: show_bit_vector(); break;
            case 2: create_file(); break;
            case 3: show_directory(); break;
            case 4: printf("Exiting.\\n"); break;
            default: printf("Invalid choice! Enter 1-4.\\n");
        }
    } while (choice != 4);

    return 0;
}
'''

def get_file_alloc_indexed_c():
    return '''#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BLOCKS 100
#define MAX_FILES 20

struct FileNode {
    char name[30];
    int index_block;
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
        bit_vector[i] = (rand() % 5 == 0) ? 1 : 0;
    }
}

void show_bit_vector() {
    printf("\\nBit Vector (0 = Free, 1 = Allocated):\\n");
    for (int i = 0; i < total_blocks; i++) {
        printf("%d ", bit_vector[i]);
        if ((i + 1) % 10 == 0) printf("\\n");
    }
    printf("\\n");
}

void create_file() {
    if (file_count >= MAX_FILES) {
        printf("Directory full!\\n");
        return;
    }
    char fname[30];
    int length;
    printf("Enter file name: ");
    scanf("%s", fname);
    printf("Enter number of data blocks required: ");
    scanf("%d", &length);

    int free_count = 0;
    for (int i = 0; i < total_blocks; i++) {
        if (bit_vector[i] == 0) free_count++;
    }

    if (free_count < length + 1) { // 1 index block + data blocks
        printf("[-] Not enough free blocks! Need %d (1 index + %d data).\\n", length + 1, length);
        return;
    }

    int idx_block = -1;
    for (int i = 0; i < total_blocks; i++) {
        if (bit_vector[i] == 0) {
            idx_block = i;
            bit_vector[i] = 1;
            break;
        }
    }

    strcpy(directory[file_count].name, fname);
    directory[file_count].index_block = idx_block;
    directory[file_count].length = length;

    int allocated = 0;
    for (int i = 0; i < total_blocks && allocated < length; i++) {
        if (bit_vector[i] == 0) {
            bit_vector[i] = 1;
            directory[file_count].blocks[allocated++] = i;
        }
    }
    file_count++;

    printf("[+] File '%s' allocated with Index Block at %d.\\n", fname, idx_block);
}

void show_directory() {
    printf("\\n--- Directory (Indexed File Allocation) ---\\n");
    printf("File Name\\tIndex Block\\tLength\\tData Blocks\\n");
    printf("----------------------------------------------------------\\n");
    for (int i = 0; i < file_count; i++) {
        printf("%s\\t\\t%d\\t\\t%d\\t", directory[i].name, directory[i].index_block, directory[i].length);
        for (int j = 0; j < directory[i].length; j++) {
            printf("%d ", directory[i].blocks[j]);
        }
        printf("\\n");
    }
    printf("----------------------------------------------------------\\n");
}

int main() {
    printf("Enter total number of disk blocks: ");
    if (scanf("%d", &total_blocks) != 1 || total_blocks <= 0) total_blocks = 50;

    init_disk();
    int choice;
    do {
        printf("\\n=== INDEXED FILE ALLOCATION MENU ===\\n");
        printf("1. Show Bit Vector\\n");
        printf("2. Create New File\\n");
        printf("3. Show Directory\\n");
        printf("4. Exit\\n");
        printf("Enter your choice (1-4): ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1: show_bit_vector(); break;
            case 2: create_file(); break;
            case 3: show_directory(); break;
            case 4: printf("Exiting.\\n"); break;
            default: printf("Invalid choice! Enter 1-4.\\n");
        }
    } while (choice != 4);

    return 0;
}
'''

def get_orphan_process_c():
    return '''#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("[Child] PID: %d, Initial Parent PID: %d\\n", getpid(), getppid());
        printf("[Child] Sleeping for 4 seconds to become orphan...\\n");
        sleep(4);
        printf("[Child] Woke up! Current Parent PID: %d (Adopted by systemd/init)\\n", getppid());
        printf("[Child] Exiting normally.\\n");
    } else {
        // Parent process
        printf("[Parent] PID: %d, Child PID: %d\\n", getpid(), pid);
        printf("[Parent] Terminating immediately without waiting for child.\\n");
        exit(0);
    }

    return 0;
}
'''

def get_nice_process_c():
    return '''#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        int old_nice = getpriority(PRIO_PROCESS, 0);
        printf("[Child] Initial Nice Value: %d\\n", old_nice);

        // Assign nice value: lower priority (+5) or higher priority
        int new_nice = nice(5);
        printf("[Child] After nice(5), Updated Nice Value: %d\\n", new_nice);

        printf("[Child] Doing task and finishing...\\n");
        exit(0);
    } else {
        // Parent process
        int p_nice = getpriority(PRIO_PROCESS, 0);
        printf("[Parent] Parent Nice Value: %d\\n", p_nice);
        wait(NULL);
        printf("[Parent] Child execution complete.\\n");
    }

    return 0;
}
'''

def get_sort_fork_c():
    return '''#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int n;
    printf("Enter number of integers: ");
    if (scanf("%d", &n) != 1 || n <= 0) n = 5;

    int arr[50];
    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) arr[i] = (i + 1) * 3;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child sorts using Insertion Sort
        printf("\\n[Child PID: %d] Sorting using Insertion Sort...\\n", getpid());
        insertion_sort(arr, n);
        printf("[Child] Sorted Array: ");
        for (int i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("\\n");
        exit(0);
    } else {
        // Parent sorts using Bubble Sort and waits
        wait(NULL);
        printf("\\n[Parent PID: %d] Child finished. Sorting using Bubble Sort...\\n", getpid());
        bubble_sort(arr, n);
        printf("[Parent] Sorted Array: ");
        for (int i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("\\n");
    }

    return 0;
}
'''

def get_execve_search_c():
    return '''#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void sort_array(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n = 5;
    int arr[] = {45, 12, 89, 23, 7};

    printf("[Parent] Original Array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\\n");

    sort_array(arr, n);
    printf("[Parent] Sorted Array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\\n");

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process performs binary search
        int target = 23;
        int low = 0, high = n - 1, found = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] == target) {
                found = mid;
                break;
            } else if (arr[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        printf("[Child PID: %d] Binary Searching for %d in sorted array...\\n", getpid(), target);
        if (found != -1) {
            printf("[Child] Element %d found at index %d!\\n", target, found);
        } else {
            printf("[Child] Element %d not found.\\n", target);
        }
        exit(0);
    } else {
        wait(NULL);
        printf("[Parent] Child search operation completed.\\n");
    }

    return 0;
}
'''

def get_shell_search_c():
    return '''#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void search_file(char mode, char* pattern, char* filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    char line[512];
    int line_num = 1;
    int occurrence_count = 0;
    int first_found = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, pattern)) {
            occurrence_count++;
            if (mode == 'f' && !first_found) {
                printf("First occurrence at Line %d: %s", line_num, line);
                first_found = 1;
                break;
            } else if (mode == 'a') {
                printf("Line %d: %s", line_num, line);
            }
        }
        line_num++;
    }

    if (mode == 'c') {
        printf("Total occurrences of '%s' in '%s': %d\\n", pattern, filename, occurrence_count);
    } else if (mode == 'f' && !first_found) {
        printf("Pattern '%s' not found in file '%s'.\\n", pattern, filename);
    }
    fclose(fp);
}

int main() {
    char input[256];
    char *args[20];

    while (1) {
        printf("$ ");
        fflush(stdout);

        if (!fgets(input, sizeof(input), stdin)) break;
        input[strcspn(input, "\\n")] = 0;

        int argc = 0;
        char *token = strtok(input, " ");
        while (token != NULL) {
            args[argc++] = token;
            token = strtok(NULL, " ");
        }
        args[argc] = NULL;

        if (argc == 0) continue;

        if (strcmp(args[0], "exit") == 0 || strcmp(args[0], "quit") == 0) {
            printf("Exiting shell.\\n");
            break;
        }

        // Handle custom command: search <f|c|a> <pattern> <filename>
        if (strcmp(args[0], "search") == 0) {
            if (argc < 4) {
                printf("Usage: search <f|c|a> <pattern> <filename>\\n");
            } else {
                search_file(args[1][0], args[2], args[3]);
            }
            continue;
        }

        // External system commands
        pid_t pid = fork();
        if (pid == 0) {
            if (execvp(args[0], args) < 0) {
                perror("Command execution failed");
                exit(1);
            }
        } else if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
        } else {
            perror("fork failed");
        }
    }
    return 0;
}
'''
