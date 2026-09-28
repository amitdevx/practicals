#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

struct Process {
    int pid;
    int at;
    int bt;
    int next_bt;
    int ct;
    int tat;
    int wt;
    bool completed;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0) n = 3;

    struct Process p[20];
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Process P%d - Enter Arrival Time and Burst Time: ", p[i].pid);
        if (scanf("%d %d", &p[i].at, &p[i].bt) != 2) {
            p[i].at = i;
            p[i].bt = 5 - i;
        }
        p[i].next_bt = (rand() % 10) + 1;
        p[i].completed = false;
    }

    int current_time = 0, completed_count = 0;
    float total_tat = 0, total_wt = 0;

    printf("\n--- Gantt Chart ---\n ");
    while (completed_count < n) {
        int idx = -1;
        int min_bt = 1e9;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= current_time) {
                if (p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            printf("|  P%d  ", p[idx].pid);
            current_time += p[idx].bt;
            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            total_tat += p[idx].tat;
            total_wt += p[idx].wt;
            p[idx].completed = true;
            completed_count++;
        } else {
            current_time++;
        }
    }
    printf("|\nEnd Time: %d\n\n", current_time);

    printf("PID\tAT\t1st BT\tNext BT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].next_bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);

    return 0;
}
