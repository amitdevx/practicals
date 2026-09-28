# CPU and Disk Scheduling Templates in C

def get_cpu_fcfs_c():
    return '''#include <stdio.h>
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

    printf("\\n--- Gantt Chart ---\\n ");
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
    printf("|\\n0");
    current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < p[i].at) current_time = p[i].at;
        current_time += p[i].bt;
        printf("      %d", current_time);
    }
    printf("\\n\\nProcess Details:\\n");
    printf("PID\\tAT\\t1st BT\\tNext BT\\tCT\\tTAT\\tWT\\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\\t%d\\t%d\\t%d\\t%d\\t%d\\t%d\\n",
               p[i].pid, p[i].at, p[i].bt, p[i].next_bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\\nAverage Waiting Time: %.2f\\n", total_wt / n);

    return 0;
}
'''

def get_cpu_sjf_np_c():
    return '''#include <stdio.h>
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

    printf("\\n--- Gantt Chart ---\\n ");
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
    printf("|\\nEnd Time: %d\\n\\n", current_time);

    printf("PID\\tAT\\t1st BT\\tNext BT\\tCT\\tTAT\\tWT\\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\\t%d\\t%d\\t%d\\t%d\\t%d\\t%d\\n",
               p[i].pid, p[i].at, p[i].bt, p[i].next_bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\\nAverage Waiting Time: %.2f\\n", total_wt / n);

    return 0;
}
'''

def get_cpu_sjf_p_c():
    return '''#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

struct Process {
    int pid;
    int at;
    int bt;
    int rt;      // Remaining Time
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
        printf("Process P%d - Enter Arrival Time and Burst Time: ", p[i].pid);
        if (scanf("%d %d", &p[i].at, &p[i].bt) != 2) {
            p[i].at = i;
            p[i].bt = 6 - i;
        }
        p[i].rt = p[i].bt;
        p[i].next_bt = (rand() % 10) + 1;
    }

    int current_time = 0, completed = 0;
    int last_pid = -1;
    float total_tat = 0, total_wt = 0;

    printf("\\n--- Gantt Chart ---\\n ");
    while (completed < n) {
        int idx = -1;
        int min_rt = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].rt > 0) {
                if (p[i].rt < min_rt) {
                    min_rt = p[i].rt;
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
    printf("|\\nTotal Time: %d\\n\\n", current_time);

    printf("PID\\tAT\\t1st BT\\tNext BT\\tCT\\tTAT\\tWT\\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\\t%d\\t%d\\t%d\\t%d\\t%d\\t%d\\n",
               p[i].pid, p[i].at, p[i].bt, p[i].next_bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\\nAverage Waiting Time: %.2f\\n", total_wt / n);

    return 0;
}
'''

def get_cpu_priority_np_c():
    return '''#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

struct Process {
    int pid;
    int at;
    int bt;
    int pr;      // Priority (smaller value = higher priority)
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
        printf("Process P%d - Enter Arrival Time, Burst Time, and Priority: ", p[i].pid);
        if (scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr) != 3) {
            p[i].at = i;
            p[i].bt = 4;
            p[i].pr = i + 1;
        }
        p[i].next_bt = (rand() % 10) + 1;
        p[i].completed = false;
    }

    int current_time = 0, completed_count = 0;
    float total_tat = 0, total_wt = 0;

    printf("\\n--- Gantt Chart ---\\n ");
    while (completed_count < n) {
        int idx = -1;
        int highest_pr = 1e9;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= current_time) {
                if (p[i].pr < highest_pr) {
                    highest_pr = p[i].pr;
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
    printf("|\\nTotal Time: %d\\n\\n", current_time);

    printf("PID\\tPriority\\tAT\\t1st BT\\tNext BT\\tCT\\tTAT\\tWT\\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\\t%d\\t\\t%d\\t%d\\t%d\\t%d\\t%d\\t%d\\n",
               p[i].pid, p[i].pr, p[i].at, p[i].bt, p[i].next_bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\\nAverage Waiting Time: %.2f\\n", total_wt / n);

    return 0;
}
'''

def get_cpu_priority_p_c():
    return '''#include <stdio.h>
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

    printf("\\n--- Gantt Chart ---\\n ");
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
    printf("|\\nTotal Time: %d\\n\\n", current_time);

    printf("PID\\tPriority\\tAT\\t1st BT\\tNext BT\\tCT\\tTAT\\tWT\\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\\t%d\\t\\t%d\\t%d\\t%d\\t%d\\t%d\\t%d\\n",
               p[i].pid, p[i].pr, p[i].at, p[i].bt, p[i].next_bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\\nAverage Waiting Time: %.2f\\n", total_wt / n);

    return 0;
}
'''

def get_cpu_round_robin_c():
    return '''#include <stdio.h>
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

    printf("\\n--- Gantt Chart ---\\n ");
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
    printf("|\\nTotal Time: %d\\n\\n", current_time);

    printf("PID\\tAT\\t1st BT\\tNext BT\\tCT\\tTAT\\tWT\\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\\t%d\\t%d\\t%d\\t%d\\t%d\\t%d\\n",
               p[i].pid, p[i].at, p[i].bt, p[i].next_bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\\nAverage Waiting Time: %.2f\\n", total_wt / n);

    return 0;
}
'''

def get_disk_fcfs_c(req_str="55, 58, 39, 18, 90, 160, 150, 38, 184", head=50):
    return f'''#include <stdio.h>
#include <stdlib.h>

int main() {{
    int default_req[] = {{{req_str}}};
    int n = sizeof(default_req) / sizeof(default_req[0]);
    int head = {head};
    int total_blocks = 200;

    printf("FCFS Disk Scheduling Simulation\\n");
    printf("Total Disk Blocks: %d\\n", total_blocks);
    printf("Starting Head Position: %d\\n", head);

    int total_head_movements = 0;
    int current_head = head;

    printf("\\nOrder of Request Service:\\n%d", head);
    for (int i = 0; i < n; i++) {{
        int movement = abs(default_req[i] - current_head);
        total_head_movements += movement;
        current_head = default_req[i];
        printf(" -> %d", current_head);
    }}

    printf("\\n\\nTotal Head Movements: %d cylinders\\n", total_head_movements);
    return 0;
}}
'''

def get_disk_sstf_c(req_str="30, 10, 60, 95, 120, 150, 175", head=50):
    return f'''#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {{
    int req[] = {{{req_str}}};
    int n = sizeof(req) / sizeof(req[0]);
    bool visited[50] = {{false}};
    int head = {head};

    printf("SSTF Disk Scheduling Simulation\\n");
    printf("Starting Head Position: %d\\n", head);

    int total_head_movements = 0;
    int current_head = head;

    printf("\\nOrder of Request Service:\\n%d", head);
    for (int count = 0; count < n; count++) {{
        int min_dist = 1e9;
        int next_idx = -1;

        for (int i = 0; i < n; i++) {{
            if (!visited[i]) {{
                int dist = abs(req[i] - current_head);
                if (dist < min_dist) {{
                    min_dist = dist;
                    next_idx = i;
                }}
            }}
        }}

        visited[next_idx] = true;
        total_head_movements += min_dist;
        current_head = req[next_idx];
        printf(" -> %d", current_head);
    }}

    printf("\\n\\nTotal Head Movements: %d cylinders\\n", total_head_movements);
    return 0;
}}
'''

def get_disk_scan_c(req_str="82, 170, 43, 140, 24, 16, 190, 65", head=50, direction="Left"):
    return f'''#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {{
    return (*(int*)a - *(int*)b);
}}

int main() {{
    int req[] = {{{req_str}}};
    int n = sizeof(req) / sizeof(req[0]);
    int head = {head};
    int total_blocks = 200;

    // Sort requests
    qsort(req, n, sizeof(int), compare);

    printf("SCAN Disk Scheduling Simulation (Direction: {direction})\\n");
    printf("Total Disk Blocks: %d\\n", total_blocks);
    printf("Starting Head Position: %d\\n", head);

    int total_head_movements = 0;
    int current_head = head;

    printf("\\nOrder of Request Service:\\n%d", head);

    // Direction: Left means service downwards towards 0, then reverse
    int idx = 0;
    while (idx < n && req[idx] < head) idx++;

    for (int i = idx - 1; i >= 0; i--) {{
        total_head_movements += abs(req[i] - current_head);
        current_head = req[i];
        printf(" -> %d", current_head);
    }}
    // Head reaches cylinder 0
    total_head_movements += abs(0 - current_head);
    current_head = 0;
    printf(" -> 0");

    // Reverse direction to the right
    for (int i = idx; i < n; i++) {{
        total_head_movements += abs(req[i] - current_head);
        current_head = req[i];
        printf(" -> %d", current_head);
    }}

    printf("\\n\\nTotal Head Movements: %d cylinders\\n", total_head_movements);
    return 0;
}}
'''

def get_disk_cscan_c(req_str="82, 170, 43, 140, 24, 16, 190, 65", head=50, direction="Left"):
    return f'''#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {{
    return (*(int*)a - *(int*)b);
}}

int main() {{
    int req[] = {{{req_str}}};
    int n = sizeof(req) / sizeof(req[0]);
    int head = {head};
    int total_blocks = 200;

    qsort(req, n, sizeof(int), compare);

    printf("C-SCAN Disk Scheduling Simulation (Direction: {direction})\\n");
    printf("Total Disk Blocks: %d\\n", total_blocks);
    printf("Starting Head Position: %d\\n", head);

    int total_head_movements = 0;
    int current_head = head;

    printf("\\nOrder of Request Service:\\n%d", head);

    int idx = 0;
    while (idx < n && req[idx] < head) idx++;

    // Service requests towards 0
    for (int i = idx - 1; i >= 0; i--) {{
        total_head_movements += abs(req[i] - current_head);
        current_head = req[i];
        printf(" -> %d", current_head);
    }}

    // Reach 0, jump to max (total_blocks - 1)
    total_head_movements += abs(0 - current_head);
    printf(" -> 0 -> %d", total_blocks - 1);
    total_head_movements += (total_blocks - 1); // Circular jump
    current_head = total_blocks - 1;

    for (int i = n - 1; i >= idx; i--) {{
        total_head_movements += abs(req[i] - current_head);
        current_head = req[i];
        printf(" -> %d", current_head);
    }}

    printf("\\n\\nTotal Head Movements: %d cylinders\\n", total_head_movements);
    return 0;
}}
'''

def get_disk_look_c(req_str="86, 147, 91, 177, 45, 12, 130", head=60, direction="Right"):
    return f'''#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {{
    return (*(int*)a - *(int*)b);
}}

int main() {{
    int req[] = {{{req_str}}};
    int n = sizeof(req) / sizeof(req[0]);
    int head = {head};

    qsort(req, n, sizeof(int), compare);

    printf("LOOK Disk Scheduling Simulation (Direction: {direction})\\n");
    printf("Starting Head Position: %d\\n", head);

    int total_head_movements = 0;
    int current_head = head;

    printf("\\nOrder of Request Service:\\n%d", head);

    int idx = 0;
    while (idx < n && req[idx] < head) idx++;

    // Service to the right first
    for (int i = idx; i < n; i++) {{
        total_head_movements += abs(req[i] - current_head);
        current_head = req[i];
        printf(" -> %d", current_head);
    }}

    // Then reverse to the left (without going to edge 0)
    for (int i = idx - 1; i >= 0; i--) {{
        total_head_movements += abs(req[i] - current_head);
        current_head = req[i];
        printf(" -> %d", current_head);
    }}

    printf("\\n\\nTotal Head Movements: %d cylinders\\n", total_head_movements);
    return 0;
}}
'''
