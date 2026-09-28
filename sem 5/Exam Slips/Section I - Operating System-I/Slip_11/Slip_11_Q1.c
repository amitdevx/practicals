#include <stdio.h>
#include <stdbool.h>

#define P 5
#define R 3

int alloc[P][R] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
int max_mat[P][R] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
int avail[R] = {3, 3, 2};
int need[P][R];

void calculateNeed() {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max_mat[i][j] - alloc[i][j];
        }
    }
}

void displayMatrices() {
    printf("\nProcess\tAllocation\tMax\t\tNeed\n");
    for (int i = 0; i < P; i++) {
        printf("P%d\t", i);
        for (int j = 0; j < R; j++) printf("%d ", alloc[i][j]);
        printf("\t\t");
        for (int j = 0; j < R; j++) printf("%d ", max_mat[i][j]);
        printf("\t\t");
        for (int j = 0; j < R; j++) printf("%d ", need[i][j]);
        printf("\n");
    }
    printf("\nAvailable Resources: ");
    for (int j = 0; j < R; j++) printf("%d ", avail[j]);
    printf("\n");
}

bool isSafe(int safe_seq[]) {
    int work[R];
    bool finish[P] = {false};
    for (int i = 0; i < R; i++) work[i] = avail[i];

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                bool can_allocate = true;
                for (int j = 0; j < R; j++) {
                    if (need[p][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    for (int k = 0; k < R; k++) work[k] += alloc[p][k];
                    safe_seq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) return false;
    }
    return true;
}

int main() {
    calculateNeed();
    displayMatrices();

    int safe_seq[P];
    if (isSafe(safe_seq)) {
        printf("\n[+] The system is currently in a SAFE state.\nSafe Sequence: ");
        for (int i = 0; i < P; i++) {
            printf("P%d", safe_seq[i]);
            if (i < P - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        printf("\n[-] The system is in an UNSAFE state (Deadlock possible).\n");
    }

    // Check request
    int req_p = 1;
    int req[] = {1, 0, 2};
    printf("\nChecking Request from P%d: ( ", req_p);
    for (int j = 0; j < R; j++) printf("%d ", req[j]);
    printf(")\n");

    bool can_grant = true;
    for (int j = 0; j < R; j++) {
        if (req[j] > need[req_p][j]) {
            printf("[-] Error: Process exceeded maximum claim.\n");
            can_grant = false;
            break;
        }
        if (req[j] > avail[j]) {
            printf("[-] Resources not currently available; Process must wait.\n");
            can_grant = false;
            break;
        }
    }

    if (can_grant) {
        for (int j = 0; j < R; j++) {
            avail[j] -= req[j];
            alloc[req_p][j] += req[j];
            need[req_p][j] -= req[j];
        }
        if (isSafe(safe_seq)) {
            printf("[+] Request can be granted immediately! System remains safe.\n");
            printf("New Safe Sequence: ");
            for (int i = 0; i < P; i++) {
                printf("P%d", safe_seq[i]);
                if (i < P - 1) printf(" -> ");
            }
            printf("\n");
        } else {
            printf("[-] Request CANNOT be granted as it leads to an unsafe state.\n");
        }
    }

    return 0;
}
