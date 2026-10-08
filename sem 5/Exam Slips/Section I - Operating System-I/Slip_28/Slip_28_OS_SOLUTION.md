# Slip 28 — Operating System-I Solution Guide

## Question 1: SCAN Disk Scheduling Simulation [15 Marks]

### Problem Statement
Write simulation program for disk scheduling using SCAN algorithm. Request: 10, 25, 75, 90, 130, 145, 180, 55; Start Head: 80; Direction: Left.

### Concept & Algorithm
1. Head moves leftwards to 0, then reverses to service higher requests.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_28_Q1 Slip_28_Q1.c
./Slip_28_Q1
```

### Sample Output
```text
Enter total number of disk blocks: 200
Enter number of requests: 8
Enter disk request string: 10 25 75 90 130 145 180 55
Enter current head position: 80
SCAN Disk Scheduling Simulation (Direction: Left)

Order of Request Service:
80 -> 75 -> 55 -> 25 -> 10 -> 0 -> 90 -> 130 -> 145 -> 180

Total Head Movements: 260 cylinders
```

---

## Question 2: MFU (Most Frequently Used) Page Replacement [15 Marks]

### Problem Statement
Write simulation program for demand paging using MFU page replacement algorithm. String: 8, 5, 7, 8, 5, 7, 2, 3, 7, 3, 5, 9, 4, 6, 2; n frames.

### Concept & Algorithm
1. MFU assumes that the page with the highest reference frequency has already been used and should be replaced in favor of newer pages with low counts.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_28_Q2 Slip_28_Q2.c
./Slip_28_Q2
```

### Sample Output
```text
Step    Page    Frames          Status
-------------------------------------------------
1       8       [ 8 - - ]       PAGE FAULT
2       5       [ 8 5 - ]       PAGE FAULT
3       7       [ 8 5 7 ]       PAGE FAULT
...
Total Page Faults: 11
Total Hits: 4
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is the philosophy behind MFU page replacement?
**Answer:** MFU assumes that a page with the smallest count was probably just brought in and has yet to be used, while the one with the highest count has finished its use.

### Q2. What is LFU page replacement?
**Answer:** Least Frequently Used replaces the page with the lowest reference count.

### Q3. Why are MFU and LFU not commonly used in real OS?
**Answer:** Their implementation is expensive (counters for each page) and they do not approximate optimal replacement as well as LRU.

### Q4. What is the difference between SCAN and C-SCAN?
**Answer:** SCAN reverses direction and services requests on the way back; C-SCAN immediately resets to the beginning without servicing requests on the return journey.

### Q5. What is disk latency?
**Answer:** Disk latency = Seek Time + Rotational Latency + Data Transfer Time.
