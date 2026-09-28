#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

struct Process {
    int pid;
    int at;
    int bt;
    int rt;
    int next_bt;
    int ct;
    int tat;
    int wt;
};

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0) n = 3;

    printf("Enter Time Quantum: ");
    if (scanf("%d", &tq) != 1 || tq <= 0) tq = 2;

    struct Process p[20];
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Process P%d - Enter Arrival Time and Burst Time: ", p[i].pid);
        if (scanf("%d %d", &p[i].at, &p[i].bt) != 2) {
            p[i].at = 0;
            p[i].bt = (i + 1) * 3;
        }
        p[i].rt = p[i].bt;
        p[i].next_bt = (rand() % 10) + 1;
    }

    int current_time = 0, completed = 0;
    float total_tat = 0, total_wt = 0;

    printf("\n--- Gantt Chart ---\n ");
    while (completed < n) {
        bool done_any = false;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].rt > 0) {
                done_any = true;
                printf("| P%d ", p[i].pid);
                if (p[i].rt > tq) {
                    current_time += tq;
                    p[i].rt -= tq;
                } else {
                    current_time += p[i].rt;
                    p[i].rt = 0;
                    p[i].ct = current_time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    total_tat += p[i].tat;
                    total_wt += p[i].wt;
                    completed++;
                }
            }
        }
        if (!done_any) current_time++;
    }
    printf("|\nTotal Time: %d\n\n", current_time);

    printf("PID\tAT\t1st BT\tNext BT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].next_bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);

    return 0;
}
