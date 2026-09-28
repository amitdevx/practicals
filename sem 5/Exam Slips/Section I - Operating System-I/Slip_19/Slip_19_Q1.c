#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

struct Process {
    int pid;
    int at;
    int bt;
    int rt;
    int pr;
    int next_bt;
    int ct;
    int tat;
    int wt;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0) n = 3;

    struct Process p[20];
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Process P%d - Enter Arrival Time, Burst Time, and Priority: ", p[i].pid);
        if (scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr) != 3) {
            p[i].at = i;
            p[i].bt = 5;
            p[i].pr = 3 - i;
        }
        p[i].rt = p[i].bt;
        p[i].next_bt = (rand() % 10) + 1;
    }

    int current_time = 0, completed = 0;
    int last_pid = -1;
    float total_tat = 0, total_wt = 0;

    printf("\n--- Gantt Chart ---\n ");
    while (completed < n) {
        int idx = -1;
        int highest_pr = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].rt > 0) {
                if (p[i].pr < highest_pr) {
                    highest_pr = p[i].pr;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            if (p[idx].pid != last_pid) {
                printf("| P%d ", p[idx].pid);
                last_pid = p[idx].pid;
            }
            p[idx].rt--;
            current_time++;

            if (p[idx].rt == 0) {
                p[idx].ct = current_time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                total_tat += p[idx].tat;
                total_wt += p[idx].wt;
                completed++;
            }
        } else {
            current_time++;
        }
    }
    printf("|\nTotal Time: %d\n\n", current_time);

    printf("PID\tPriority\tAT\t1st BT\tNext BT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].pr, p[i].at, p[i].bt, p[i].next_bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);

    return 0;
}
