#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Process {
    int pid;
    int at;      // Arrival Time
    int bt;      // First CPU Burst
    int next_bt; // Next CPU Burst (randomly generated)
    int ct;      // Completion Time
    int tat;     // Turnaround Time
    int wt;      // Waiting Time
};

int main() {
    int n;
    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0) n = 3;

    struct Process p[20];
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Process P%d - Enter Arrival Time and First Burst Time: ", p[i].pid);
        if (scanf("%d %d", &p[i].at, &p[i].bt) != 2) {
            p[i].at = i;
            p[i].bt = (i + 1) * 2;
        }
        p[i].next_bt = (rand() % 10) + 1; // randomly generated next burst
    }

    // Sort by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int current_time = 0;
    float total_tat = 0, total_wt = 0;

    printf("\n--- Gantt Chart ---\n ");
    for (int i = 0; i < n; i++) {
        if (current_time < p[i].at) {
            current_time = p[i].at;
        }
        printf("|  P%d  ", p[i].pid);
        current_time += p[i].bt;
        p[i].ct = current_time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }
    printf("|\n0");
    current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < p[i].at) current_time = p[i].at;
        current_time += p[i].bt;
        printf("      %d", current_time);
    }
    printf("\n\nProcess Details:\n");
    printf("PID\tAT\t1st BT\tNext BT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].next_bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);

    return 0;
}
