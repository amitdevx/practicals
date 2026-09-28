#include <stdio.h>
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

    printf("\nEnter Allocation Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (scanf("%d", &alloc[i][j]) != 1) alloc[i][j] = 0;
            avail[j] -= alloc[i][j];
        }
    }

    printf("\nEnter Max Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (scanf("%d", &max_mat[i][j]) != 1) max_mat[i][j] = alloc[i][j];
            need[i][j] = max_mat[i][j] - alloc[i][j];
        }
    }

    printf("\n--- Need Matrix ---\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++) printf("%d ", need[i][j]);
        printf("\n");
    }

    printf("\n--- Available Vector ---\n");
    for (int j = 0; j < m; j++) printf("%d ", avail[j]);
    printf("\n");

    return 0;
}
