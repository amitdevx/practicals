#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

struct Process {
    int pid;
    int at;
    int bt1;
    int rem_bt1;
    int io_time;
    int bt2;
    int rem_bt2;
    int ct;
    int state; // 0: Not arrived, 1: CPU1 ready/running, 2: IO, 3: CPU2 ready/running, 4: Terminated
};

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0) n = 3;

    printf("Enter Time Quantum: ");
    if (scanf("%d", &tq) != 1 || tq <= 0) tq = 2;

    struct Process p[n];
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Process P%d - Enter Arrival Time and 1st Burst Time: ", p[i].pid);
        if (scanf("%d %d", &p[i].at, &p[i].bt1) != 2) {
            p[i].at = 0;
            p[i].bt1 = 3;
        }
        p[i].rem_bt1 = p[i].bt1;
        p[i].io_time = 0;
        p[i].bt2 = (rand() % 10) + 1;
        p[i].rem_bt2 = p[i].bt2;
        p[i].state = 0;
        p[i].ct = 0;
    }

    int current_time = 0;
    int completed = 0;
    
    int ready_queue[1000];
    int front = 0, rear = 0;
    
    // Sort by arrival time initially to handle simultaneous arrivals properly (optional, but good practice)
    
    // Enqueue processes arriving at time 0
    for(int i=0; i<n; i++) {
        if(p[i].at == 0) {
            p[i].state = 1;
            ready_queue[rear++] = i;
        }
    }

    printf("\nGantt Chart\n");
    while (completed < n) {
        // Handle I/O completion
        for (int i = 0; i < n; i++) {
            if (p[i].state == 2 && p[i].io_time <= current_time) {
                p[i].state = 3;
                ready_queue[rear++] = i;
            }
        }
        
        if (front < rear) {
            int idx = ready_queue[front++];
            int exec_time = 0;
            printf("| P%d ", p[idx].pid);
            
            if (p[idx].state == 1) {
                exec_time = (p[idx].rem_bt1 > tq) ? tq : p[idx].rem_bt1;
                p[idx].rem_bt1 -= exec_time;
            } else if (p[idx].state == 3) {
                exec_time = (p[idx].rem_bt2 > tq) ? tq : p[idx].rem_bt2;
                p[idx].rem_bt2 -= exec_time;
            }
            
            // Advance time
            for (int t = 1; t <= exec_time; t++) {
                current_time++;
                // Check arrivals during execution
                for (int i = 0; i < n; i++) {
                    if (p[i].state == 0 && p[i].at == current_time) {
                        p[i].state = 1;
                        ready_queue[rear++] = i;
                    }
                }
                // Check IO completions during execution
                for (int i = 0; i < n; i++) {
                    if (p[i].state == 2 && p[i].io_time == current_time) {
                        p[i].state = 3;
                        ready_queue[rear++] = i;
                    }
                }
            }
            
            // After execution
            if (p[idx].state == 1) {
                if (p[idx].rem_bt1 == 0) {
                    p[idx].state = 2;
                    p[idx].io_time = current_time + 2; // Fixed IO time = 2
                } else {
                    ready_queue[rear++] = idx;
                }
            } else if (p[idx].state == 3) {
                if (p[idx].rem_bt2 == 0) {
                    p[idx].state = 4;
                    p[idx].ct = current_time;
                    completed++;
                } else {
                    ready_queue[rear++] = idx;
                }
            }
            
        } else {
            // Idle CPU
            current_time++;
            for (int i = 0; i < n; i++) {
                if (p[i].state == 0 && p[i].at == current_time) {
                    p[i].state = 1;
                    ready_queue[rear++] = i;
                }
            }
            for (int i = 0; i < n; i++) {
                if (p[i].state == 2 && p[i].io_time == current_time) {
                    p[i].state = 3;
                    ready_queue[rear++] = i;
                }
            }
        }
    }
    printf("|\nTotal Time: %d\n\n", current_time);

    float total_tat = 0, total_wt = 0;
    printf("PID\tAT\t1st BT\tNext BT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        int tat = p[i].ct - p[i].at;
        int wt = tat - p[i].bt1 - p[i].bt2 - 2; // Wait time excludes BT1, BT2, and IO time
        total_tat += tat;
        total_wt += wt;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt1, p[i].bt2, p[i].ct, tat, wt);
    }

    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);

    return 0;
}
