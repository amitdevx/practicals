#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void sort(int a[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, i, key;
    int a[20];
    
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1) return 1;
    
    printf("Enter array elements: ");
    for (i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1) return 1;
    }
    
    printf("Enter element to search: ");
    if (scanf("%d", &key) != 1) return 1;
    
    sort(a, n);
    
    printf("Sorted array: ");
    for (i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    
    pid_t pid = fork();
    if (pid == 0) {
        char *args[25];
        char values[20][10];
        char key_str[10];
        
        args[0] = "./Slip_14_Q1_child";
        sprintf(key_str, "%d", key);
        args[1] = key_str;
        
        for (i = 0; i < n; i++) {
            sprintf(values[i], "%d", a[i]);
            args[i + 2] = values[i];
        }
        args[n + 2] = NULL;
        
        execve(args[0], args, NULL);
        perror("execve failed");
        exit(1);
    } else if (pid > 0) {
        wait(NULL);
        printf("Parent process completed.\n");
    } else {
        perror("fork failed");
    }
    return 0;
}
