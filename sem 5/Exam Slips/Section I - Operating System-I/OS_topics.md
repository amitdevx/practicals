# Operating System-I (CS-305-MJ-P) Comprehensive Topic Analysis

> Strategic overview and breakdown of all 30 exam practical slips for SPPU TYBSc Computer Science (Sem V).

---

## 1. Core Practical Topics & Distribution

```
 OPERATING SYSTEM-I PRACTICAL CURRICULUM
 │
 ├── CPU Scheduling Algorithms [10 Slips]
 │   ├── First-Come First-Served (FCFS) [Slips: 02, 10, 20]
 │   ├── Shortest Job First (SJF - Non-Preemptive & Preemptive) [Slips: 03, 11, 21]
 │   ├── Priority Scheduling (Non-Preemptive & Preemptive) [Slips: 04, 12, 22]
 │   └── Round Robin (RR with Time Quantum) [Slips: 05, 13, 23]
 │
 ├── Deadlock Avoidance: Banker's Algorithm [10 Slips]
 │   ├── Data Structures & Need Matrix Calculation [Slips: 01, 14, 24]
 │   ├── Safety Algorithm & Safe Sequence Finding [Slips: 06, 16, 26]
 │   └── Resource Request Algorithm [Slips: 07, 17, 27]
 │
 ├── Page Replacement Algorithms [10 Slips]
 │   ├── First-In-First-Out (FIFO) [Slips: 08, 18, 28]
 │   ├── Least Recently Used (LRU - Counting / Stack) [Slips: 09, 19, 29]
 │   └── Optimal / MFU / LFU Page Replacement [Slips: 15, 25, 30]
 │
 └── Unix Shell Simulation (Extended Shell Commands) [All 30 Slips]
     ├── count Command (lines 'c', words 'w', characters 'l') [Slips: 01, 05, 09, 13, 17, 21, 25, 29]
     ├── typeline Command (+n first n lines, -n last n lines, a all) [Slips: 02, 06, 10, 14, 18, 22, 26, 30]
     ├── search Command (find string occurrences: 'f' first, 'a' all, 'c' count) [Slips: 03, 07, 11, 15, 19, 23, 27]
     └── list Command (list directory files: 'f' files, 'n' count, 'i' inode) [Slips: 04, 08, 12, 16, 20, 24, 28]
```

---

## 2. Complete Slip-wise Question Matrix (30 Slips)

| Slip | Question 1 (15 Marks) | Question 2 (15 Marks) | Total Marks | Key Concepts |
| :---: | :--- | :--- | :---: | :--- |
| **01** | Banker's Algorithm: Data Structures & Need Matrix | Custom Shell: `count` (c, w, l) | 30 + 5 Viva | Need = Max - Allocation, File I/O |
| **02** | CPU Scheduling: First-Come First-Served (FCFS) | Custom Shell: `typeline` (+n, -n, a) | 30 + 5 Viva | Non-preemptive, Gantt chart, Turnaround & Waiting |
| **03** | CPU Scheduling: Shortest Job First (SJF) | Custom Shell: `search` (f, a, c) | 30 + 5 Viva | Burst time sort, Context switching |
| **04** | CPU Scheduling: Priority (Non-Preemptive) | Custom Shell: `list` (f, n, i) | 30 + 5 Viva | Priority queue, Directory traversal (`opendir`) |
| **05** | CPU Scheduling: Round Robin (RR) | Custom Shell: `count` (c, w, l) | 30 + 5 Viva | Ready queue, Time Quantum, Circular queue |
| **06** | Banker's Algorithm: Safety Algorithm | Custom Shell: `typeline` (+n, -n, a) | 30 + 5 Viva | Work, Finish vectors, Safe sequence |
| **07** | Banker's Algorithm: Resource Request Algorithm | Custom Shell: `search` (f, a, c) | 30 + 5 Viva | Request <= Need & Request <= Available |
| **08** | Page Replacement: First-In-First-Out (FIFO) | Custom Shell: `list` (f, n, i) | 30 + 5 Viva | Queue simulation, Page Fault counter |
| **09** | Page Replacement: Least Recently Used (LRU) | Custom Shell: `count` (c, w, l) | 30 + 5 Viva | Timestamp/Counter stack, Locality of reference |
| **10** | CPU Scheduling: FCFS with Arrival Times | Custom Shell: `typeline` (+n, -n, a) | 30 + 5 Viva | Idle CPU handling, Completion times |
| **11** | CPU Scheduling: Preemptive SJF (SRTF) | Custom Shell: `search` (f, a, c) | 30 + 5 Viva | Remaining burst time, Preemption logic |
| **12** | CPU Scheduling: Preemptive Priority Scheduling | Custom Shell: `list` (f, n, i) | 30 + 5 Viva | Dynamic priority evaluation, Starvation |
| **13** | CPU Scheduling: Round Robin with Variable Quantum | Custom Shell: `count` (c, w, l) | 30 + 5 Viva | Context switch overhead, Quantum tuning |
| **14** | Banker's Algorithm: Need Matrix & Verification | Custom Shell: `typeline` (+n, -n, a) | 30 + 5 Viva | Multi-resource vector arithmetic |
| **15** | Page Replacement: Optimal (OPT) Algorithm | Custom Shell: `search` (f, a, c) | 30 + 5 Viva | Future reference distance, Belady's anomaly |
| **16** | Banker's Algorithm: Safe State Determination | Custom Shell: `list` (f, n, i) | 30 + 5 Viva | Deadlock avoidance, Safety state check |
| **17** | Banker's Algorithm: Additional Request Granting | Custom Shell: `count` (c, w, l) | 30 + 5 Viva | Safety validation after temporary allocation |
| **18** | Page Replacement: FIFO with Variable Frame Size | Custom Shell: `typeline` (+n, -n, a) | 30 + 5 Viva | Frame allocation comparison (3 vs 4 frames) |
| **19** | Page Replacement: LRU using Counter Method | Custom Shell: `search` (f, a, c) | 30 + 5 Viva | Clock tick simulation, Page hit/fault ratio |
| **20** | CPU Scheduling: FCFS Scheduling Simulation | Custom Shell: `list` (f, n, i) | 30 + 5 Viva | Process control block representation |
| **21** | CPU Scheduling: Non-Preemptive SJF Simulation | Custom Shell: `count` (c, w, l) | 30 + 5 Viva | Average Turnaround & Waiting time |
| **22** | CPU Scheduling: Priority Scheduling Simulation | Custom Shell: `typeline` (+n, -n, a) | 30 + 5 Viva | Priority order, Process dispatching |
| **23** | CPU Scheduling: Round Robin Algorithm Simulation | Custom Shell: `search` (f, a, c) | 30 + 5 Viva | Time sharing, Fair-share scheduling |
| **24** | Banker's Algorithm: Resource Allocation Matrix | Custom Shell: `list` (f, n, i) | 30 + 5 Viva | Allocation matrix, Available vector |
| **25** | Page Replacement: Most Frequently Used (MFU) | Custom Shell: `count` (c, w, l) | 30 + 5 Viva | Frequency counting, Page eviction |
| **26** | Banker's Algorithm: Complete Safety Algorithm | Custom Shell: `typeline` (+n, -n, a) | 30 + 5 Viva | Safe sequence tracing, Deadlock avoidance |
| **27** | Banker's Algorithm: Immediate Allocation Check | Custom Shell: `search` (f, a, c) | 30 + 5 Viva | State rollback if request unsafe |
| **28** | Page Replacement: FIFO Page Hit & Miss Ratio | Custom Shell: `list` (f, n, i) | 30 + 5 Viva | Fault rate percentage, Performance evaluation |
| **29** | Page Replacement: LRU with Reference Strings | Custom Shell: `count` (c, w, l) | 30 + 5 Viva | Memory footprint, Cache locality |
| **30** | Page Replacement: Least Frequently Used (LFU) | Custom Shell: `typeline` (+n, -n, a) | 30 + 5 Viva | Eviction of least used page, Tie-breaking |

---

## 3. Quick Compilation & Execution Guide

```bash
# Question 1 (C program)
gcc -Wall -Wextra -o Slip_XX_Q1 Slip_XX_Q1.c
./Slip_XX_Q1

# Question 2 (Custom Shell C program)
gcc -Wall -Wextra -o Slip_XX_Q2 Slip_XX_Q2.c
./Slip_XX_Q2
```
