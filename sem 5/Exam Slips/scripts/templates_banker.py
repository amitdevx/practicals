# Banker's Deadlock Avoidance Algorithm in C

def get_banker_safety_c(alloc_data, max_data, avail_data, p_count=5, r_count=3, req_pid=1, req_vec="1, 0, 2"):
    alloc_str = ", ".join([f"{{{', '.join(map(str, row))}}}" for row in alloc_data])
    max_str = ", ".join([f"{{{', '.join(map(str, row))}}}" for row in max_data])
    avail_str = ", ".join(map(str, avail_data))

    return f'''#include <stdio.h>
#include <stdbool.h>

#define P {p_count}
#define R {r_count}

int alloc[P][R] = {{{alloc_str}}};
int max_mat[P][R] = {{{max_str}}};
int avail[R] = {{{avail_str}}};
int need[P][R];

void calculateNeed() {{
    for (int i = 0; i < P; i++) {{
        for (int j = 0; j < R; j++) {{
            need[i][j] = max_mat[i][j] - alloc[i][j];
        }}
    }}
}}

void displayMatrices() {{
    printf("\\nProcess\\tAllocation\\tMax\\t\\tNeed\\n");
    for (int i = 0; i < P; i++) {{
        printf("P%d\\t", i);
        for (int j = 0; j < R; j++) printf("%d ", alloc[i][j]);
        printf("\\t\\t");
        for (int j = 0; j < R; j++) printf("%d ", max_mat[i][j]);
        printf("\\t\\t");
        for (int j = 0; j < R; j++) printf("%d ", need[i][j]);
        printf("\\n");
    }}
    printf("\\nAvailable Resources: ");
    for (int j = 0; j < R; j++) printf("%d ", avail[j]);
    printf("\\n");
}}

bool isSafe(int safe_seq[]) {{
    int work[R];
    bool finish[P] = {{false}};
    for (int i = 0; i < R; i++) work[i] = avail[i];

    int count = 0;
    while (count < P) {{
        bool found = false;
        for (int p = 0; p < P; p++) {{
            if (!finish[p]) {{
                bool can_allocate = true;
                for (int j = 0; j < R; j++) {{
                    if (need[p][j] > work[j]) {{
                        can_allocate = false;
                        break;
                    }}
                }}
                if (can_allocate) {{
                    for (int k = 0; k < R; k++) work[k] += alloc[p][k];
                    safe_seq[count++] = p;
                    finish[p] = true;
                    found = true;
                }}
            }}
        }}
        if (!found) return false;
    }}
    return true;
}}

int main() {{
    calculateNeed();
    displayMatrices();

    int safe_seq[P];
    if (isSafe(safe_seq)) {{
        printf("\\n[+] The system is currently in a SAFE state.\\nSafe Sequence: ");
        for (int i = 0; i < P; i++) {{
            printf("P%d", safe_seq[i]);
            if (i < P - 1) printf(" -> ");
        }}
        printf("\\n");
    }} else {{
        printf("\\n[-] The system is in an UNSAFE state (Deadlock possible).\\n");
    }}

    // Check request
    int req_p = {req_pid};
    int req[] = {{{req_vec}}};
    printf("\\nChecking Request from P%d: ( ", req_p);
    for (int j = 0; j < R; j++) printf("%d ", req[j]);
    printf(")\\n");

    bool can_grant = true;
    for (int j = 0; j < R; j++) {{
        if (req[j] > need[req_p][j]) {{
            printf("[-] Error: Process exceeded maximum claim.\\n");
            can_grant = false;
            break;
        }}
        if (req[j] > avail[j]) {{
            printf("[-] Resources not currently available; Process must wait.\\n");
            can_grant = false;
            break;
        }}
    }}

    if (can_grant) {{
        for (int j = 0; j < R; j++) {{
            avail[j] -= req[j];
            alloc[req_p][j] += req[j];
            need[req_p][j] -= req[j];
        }}
        if (isSafe(safe_seq)) {{
            printf("[+] Request can be granted immediately! System remains safe.\\n");
            printf("New Safe Sequence: ");
            for (int i = 0; i < P; i++) {{
                printf("P%d", safe_seq[i]);
                if (i < P - 1) printf(" -> ");
            }}
            printf("\\n");
        }} else {{
            printf("[-] Request CANNOT be granted as it leads to an unsafe state.\\n");
        }}
    }}

    return 0;
}}
'''

def get_banker_menu_c(alloc_data, max_data, avail_data, p_count=5, r_count=3):
    alloc_str = ", ".join([f"{{{', '.join(map(str, row))}}}" for row in alloc_data])
    max_str = ", ".join([f"{{{', '.join(map(str, row))}}}" for row in max_data])
    avail_str = ", ".join(map(str, avail_data))

    return f'''#include <stdio.h>
#include <stdlib.h>

#define P {p_count}
#define R {r_count}

int alloc[P][R] = {{{alloc_str}}};
int max_mat[P][R] = {{{max_str}}};
int avail[R] = {{{avail_str}}};
int need[P][R];

void calculateNeed() {{
    for (int i = 0; i < P; i++) {{
        for (int j = 0; j < R; j++) {{
            need[i][j] = max_mat[i][j] - alloc[i][j];
        }}
    }}
}}

void acceptAvailable() {{
    printf("Enter Available instances for %d resources: ", R);
    for (int j = 0; j < R; j++) {{
        if (scanf("%d", &avail[j]) != 1) avail[j] = 0;
    }}
    printf("Available resources updated successfully.\\n");
}}

void displayAllocMax() {{
    printf("\\nProcess\\tAllocation\\tMax\\n");
    for (int i = 0; i < P; i++) {{
        printf("P%d\\t", i);
        for (int j = 0; j < R; j++) printf("%d ", alloc[i][j]);
        printf("\\t\\t");
        for (int j = 0; j < R; j++) printf("%d ", max_mat[i][j]);
        printf("\\n");
    }}
}}

void displayNeed() {{
    calculateNeed();
    printf("\\nNeed Matrix (Need = Max - Allocation):\\n");
    printf("Process\\tNeed (A B C)\\n");
    for (int i = 0; i < P; i++) {{
        printf("P%d\\t", i);
        for (int j = 0; j < R; j++) printf("%d ", need[i][j]);
        printf("\\n");
    }}
}}

void displayAvailable() {{
    printf("\\nAvailable Resources Vector:\\n");
    for (int j = 0; j < R; j++) {{
        printf("Resource %c: %d\\n", 'A' + j, avail[j]);
    }}
}}

int main() {{
    calculateNeed();
    int choice;
    do {{
        printf("\\n=============================================\\n");
        printf("   BANKER'S ALGORITHM - MENU DRIVEN PROGRAM\\n");
        printf("=============================================\\n");
        printf("1. Accept Available\\n");
        printf("2. Display Allocation and Max\\n");
        printf("3. Display Contents of Need Matrix\\n");
        printf("4. Display Available\\n");
        printf("5. Exit\\n");
        printf("Enter your choice (1-5): ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {{
            case 1: acceptAvailable(); break;
            case 2: displayAllocMax(); break;
            case 3: displayNeed(); break;
            case 4: displayAvailable(); break;
            case 5: printf("Exiting program.\\n"); break;
            default: printf("Invalid choice! Enter 1-5.\\n");
        }}
    }} while (choice != 5);

    return 0;
}}
'''

def get_banker_general_c():
    return '''#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0) n = 3;
    printf("Enter number of resource types: ");
    if (scanf("%d", &m) != 1 || m <= 0) m = 3;

    int total[10], avail[10], alloc[10][10], max_mat[10][10], need[10][10];

    printf("Enter total instances for each of the %d resources: ", m);
    for (int j = 0; j < m; j++) {
        if (scanf("%d", &total[j]) != 1) total[j] = 10;
        avail[j] = total[j];
    }

    printf("\\nEnter Allocation Matrix (%d x %d):\\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (scanf("%d", &alloc[i][j]) != 1) alloc[i][j] = 0;
            avail[j] -= alloc[i][j];
        }
    }

    printf("\\nEnter Max Matrix (%d x %d):\\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (scanf("%d", &max_mat[i][j]) != 1) max_mat[i][j] = alloc[i][j];
            need[i][j] = max_mat[i][j] - alloc[i][j];
        }
    }

    printf("\\n--- Need Matrix ---\\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++) printf("%d ", need[i][j]);
        printf("\\n");
    }

    printf("\\n--- Available Vector ---\\n");
    for (int j = 0; j < m; j++) printf("%d ", avail[j]);
    printf("\\n");

    return 0;
}
'''
