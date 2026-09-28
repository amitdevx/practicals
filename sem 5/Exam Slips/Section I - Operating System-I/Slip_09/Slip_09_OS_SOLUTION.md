# Slip 09 — Operating System-I Solution Guide

## Question 1: LRU Page Replacement (Counter Method) [15 Marks]

### Problem Statement
Write simulation program for demand paging and show page scheduling and total page faults using LRU (counter method). String: 3,5,7,2,5,1,2,3,1,3,5,3,1,6,2; n frames.

### Concept & Algorithm
1. LRU associates with each page frame the time of its last reference.
2. When replacement is needed, the frame with the oldest timestamp (minimum counter value) is replaced.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_09_Q1 Slip_09_Q1.c
./Slip_09_Q1
```

### Sample Output
```text
Step    Page    Frames          Status
-------------------------------------------------
1       3       [ 3 - - ]       PAGE FAULT
2       5       [ 3 5 - ]       PAGE FAULT
3       7       [ 3 5 7 ]       PAGE FAULT
4       2       [ 2 5 7 ]       PAGE FAULT
...
Total Page Faults: 9
Total Hits: 6
```

---

## Question 2: Non-preemptive Shortest Job First (SJF) CPU Scheduling [15 Marks]

### Problem Statement
Simulate Non-preemptive Shortest Job First (SJF) scheduling. Arrival time and burst time input. Output Gantt chart, TAT, WT, average TAT and WT.

### Concept & Algorithm
1. At each decision point, select the available process with the smallest CPU burst time.
2. Once scheduled, the process runs to completion (non-preemptive).

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_09_Q2 Slip_09_Q2.c
./Slip_09_Q2
```

### Sample Output
```text
--- Gantt Chart ---
 |  P1  |  P3  |  P2  |
End Time: 12

PID     AT      1st BT  Next BT CT      TAT     WT
P1      0       3       7       3       3       0
P2      2       5       4       12      10      5
P3      1       4       2       7       6       2

Average Turnaround Time: 6.33
Average Waiting Time: 2.33
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. Why is SJF optimal?
**Answer:** SJF gives the minimum average waiting time for a given set of processes.

### Q2. What is the main drawback of SJF in practical OS?
**Answer:** It is impossible to know the exact length of the next CPU burst in advance; it can only be estimated.

### Q3. What is turnaround time?
**Answer:** Turnaround Time is the total interval between process arrival and its completion: TAT = Completion Time - Arrival Time.

### Q4. What is waiting time?
**Answer:** Waiting Time is the total time spent by a process in the ready queue: WT = Turnaround Time - Burst Time.

### Q5. Explain the LRU counter method.
**Answer:** A logical clock or counter increments with every memory reference; each page frame records the counter value upon access, and the page with the lowest counter is replaced.
