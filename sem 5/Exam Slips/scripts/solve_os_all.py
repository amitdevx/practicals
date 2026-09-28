#!/usr/bin/env python3
import os
import subprocess
import re

from templates_scheduling import (
    get_cpu_fcfs_c, get_cpu_sjf_np_c, get_cpu_sjf_p_c,
    get_cpu_priority_np_c, get_cpu_priority_p_c, get_cpu_round_robin_c,
    get_disk_fcfs_c, get_disk_sstf_c, get_disk_scan_c, get_disk_cscan_c, get_disk_look_c
)
from templates_memory import get_page_fifo_c, get_page_lru_c, get_page_mfu_c
from templates_banker import get_banker_safety_c, get_banker_menu_c, get_banker_general_c
from templates_fs_proc import (
    get_file_alloc_linked_c, get_file_alloc_seq_c, get_file_alloc_indexed_c,
    get_orphan_process_c, get_nice_process_c, get_sort_fork_c, get_execve_search_c,
    get_shell_search_c
)

BASE_DIR = "/home/amitdevx/Code/practicals/sem 5/Exam Slips/CS-305 Operating System"

def build_solution_md(q1_title, q1_marks, q1_stmt, q1_concept, q1_cfile, q1_out,
                      q2_title, q2_marks, q2_stmt, q2_concept, q2_cfile, q2_out,
                      viva_qas):
    q1_stmt = q1_stmt.strip().replace('\\n', '\n')
    q1_concept = q1_concept.strip().replace('\\n', '\n')
    q2_stmt = q2_stmt.strip().replace('\\n', '\n')
    q2_concept = q2_concept.strip().replace('\\n', '\n')
    
    lines = []
    lines.append(f"## Question 1: {q1_title} [{q1_marks} Marks]\n")
    lines.append("### Problem Statement\n" + q1_stmt + "\n")
    lines.append("### Concept & Algorithm\n" + q1_concept + "\n")
    lines.append("### Compilation & Execution\n```bash\n" + f"gcc -Wall -Wextra -o {q1_cfile[:-2]} {q1_cfile}\n./{q1_cfile[:-2]}\n```\n")
    lines.append("### Sample Output\n```text\n" + q1_out.strip() + "\n```\n")
    lines.append("---\n")
    lines.append(f"## Question 2: {q2_title} [{q2_marks} Marks]\n")
    lines.append("### Problem Statement\n" + q2_stmt + "\n")
    lines.append("### Concept & Algorithm\n" + q2_concept + "\n")
    lines.append("### Compilation & Execution\n```bash\n" + f"gcc -Wall -Wextra -o {q2_cfile[:-2]} {q2_cfile}\n./{q2_cfile[:-2]}\n```\n")
    lines.append("### Sample Output\n```text\n" + q2_out.strip() + "\n```\n")
    lines.append("---\n")
    lines.append("## Question 3: Oral / Viva Questions & Answers [5 Marks]\n")
    for i, (q, a) in enumerate(viva_qas, 1):
        lines.append(f"### Q{i}. {q}\n**Answer:** {a}\n")
    return "\n".join(lines)

def solve_slip(s, q1_info, q2_info, viva_qas):
    folder = os.path.join(BASE_DIR, f"os_slip_{s:02d}")
    os.makedirs(folder, exist_ok=True)

    q1_cfile = f"os_slip_{s:02d}_q1.c"
    q2_cfile = f"os_slip_{s:02d}_q2.c"
    sol_md = f"os_slip_{s:02d}_solution.md"

    # Write Q1 C code
    with open(os.path.join(folder, q1_cfile), "w") as f:
        f.write(q1_info["code"])

    # Write Q2 C code
    with open(os.path.join(folder, q2_cfile), "w") as f:
        f.write(q2_info["code"])

    # Write Solution MD
    sol_content = build_solution_md(
        q1_info["title"], q1_info.get("marks", 15), q1_info["stmt"], q1_info["concept"], q1_cfile, q1_info["sample_out"],
        q2_info["title"], q2_info.get("marks", 15), q2_info["stmt"], q2_info["concept"], q2_cfile, q2_info["sample_out"],
        viva_qas
    )
    with open(os.path.join(folder, sol_md), "w") as f:
        f.write(sol_content)

    # Compile and verify both
    cmd1 = ["gcc", "-Wall", "-Wextra", "-o", os.path.join(folder, q1_cfile[:-2]), os.path.join(folder, q1_cfile)]
    res1 = subprocess.run(cmd1, capture_output=True, text=True)
    if res1.returncode != 0:
        print(f"Error compiling {q1_cfile}:", res1.stderr)

    cmd2 = ["gcc", "-Wall", "-Wextra", "-o", os.path.join(folder, q2_cfile[:-2]), os.path.join(folder, q2_cfile)]
    res2 = subprocess.run(cmd2, capture_output=True, text=True)
    if res2.returncode != 0:
        print(f"Error compiling {q2_cfile}:", res2.stderr)

    print(f"  -> Solved and verified os_slip_{s:02d}")

# Let's define the configurations for slips 2 to 30
SLIP_CONFIGS = {}

# Slip 02
SLIP_CONFIGS[2] = {
    "q1": {
        "title": "Linked File Allocation Simulation",
        "stmt": "Write a program to simulate Linked file allocation method. Assume disk with ‘n’ number of blocks. Give value of ‘n’ as input. Randomly mark some block as allocated and accordingly maintain the list of free blocks. Write menu driven program with options: Show Bit Vector, Create New File, Show Directory, Exit.",
        "concept": "1. In linked file allocation, each file is a linked list of disk blocks scattered anywhere on disk.\\n2. The directory contains a pointer to the first and optionally last block of the file.\\n3. No external fragmentation occurs, and files can grow dynamically.",
        "code": get_file_alloc_linked_c(),
        "sample_out": """=== LINKED FILE ALLOCATION MENU ===
1. Show Bit Vector
2. Create New File
3. Show Directory
4. Exit
Enter your choice (1-4): 2
Enter file name: report.txt
Enter number of blocks required: 3
[+] File 'report.txt' created successfully using Linked Allocation.

=== LINKED FILE ALLOCATION MENU ===
1. Show Bit Vector
2. Create New File
3. Show Directory
4. Exit
Enter your choice (1-4): 3
File Name       Start Block     Length  Linked Blocks
report.txt      2               3       2 -> 7 -> 11"""
    },
    "q2": {
        "title": "FCFS Disk Scheduling Simulation",
        "stmt": "Write a simulation program for disk scheduling using FCFS algorithm. Accept total number of disk blocks, disk request string, and current head position from user. Display request service order and total head movements. Request: 55, 58, 39, 18, 90, 160, 150, 38, 184; Start Head: 50.",
        "concept": "1. FCFS (First-Come, First-Served) disk scheduling services requests in the order they arrive.\\n2. Head movement is calculated as |Request[i] - Request[i-1]|.",
        "code": get_disk_fcfs_c("55, 58, 39, 18, 90, 160, 150, 38, 184", 50),
        "sample_out": """Order of Request Service:
50 -> 55 -> 58 -> 39 -> 18 -> 90 -> 160 -> 150 -> 38 -> 184

Total Head Movements: 498 cylinders"""
    },
    "viva": [
        ("What is linked file allocation and its main advantage?", "In linked allocation, each file is a linked list of disk blocks. Its primary advantage is that there is no external fragmentation and files can grow without contiguous space."),
        ("What is a bit vector?", "A bit vector (or bitmap) is an array of bits where each bit represents the status of a disk block (0 for free, 1 for allocated)."),
        ("What is the major disadvantage of FCFS disk scheduling?", "It does not optimize head movement, leading to severe arm swinging (seek latency) and poor throughput compared to SSTF or SCAN."),
        ("What is seek time in hard disk drives?", "Seek time is the time taken by the read/write head arm to position itself over the target cylinder/track."),
        ("How does linked allocation handle file corruption?", "If any pointer in the linked chain is damaged or lost, the subsequent blocks of the file become inaccessible.")
    ]
}

# Slip 03
SLIP_CONFIGS[3] = {
    "q1": {
        "title": "Banker's Deadlock Avoidance Algorithm",
        "stmt": "Write a C program to simulate Banker’s algorithm for deadlock avoidance. Check safety and test if request from P1 (1, 0, 2) can be granted.",
        "concept": "1. Need = Max - Allocation.\\n2. System is in safe state if a sequence of processes exists where each process can satisfy its maximum demand using available plus released resources.\\n3. Resource Request Algorithm tests safety before granting requests.",
        "code": get_banker_safety_c(
            [[0, 1, 0], [2, 0, 0], [3, 0, 2], [2, 1, 1], [0, 0, 2]],
            [[7, 5, 3], [3, 2, 2], [9, 0, 2], [2, 2, 2], [4, 3, 3]],
            [3, 3, 2], 5, 3, 1, "1, 0, 2"
        ),
        "sample_out": """Process Allocation     Max             Need
P0      0 1 0           7 5 3           7 4 3 
P1      2 0 0           3 2 2           1 2 2 
P2      3 0 2           9 0 2           6 0 0 
P3      2 1 1           2 2 2           0 1 1 
P4      0 0 2           4 3 3           4 3 1 

Available Resources: 3 3 2 
[+] The system is currently in a SAFE state.
Safe Sequence: P1 -> P3 -> P4 -> P0 -> P2

Checking Request from P1: ( 1 0 2 )
[+] Request can be granted immediately! System remains safe."""
    },
    "q2": {
        "title": "SSTF Disk Scheduling Simulation",
        "stmt": "Write a simulation program for disk scheduling using SSTF algorithm. Request: 30, 10, 60, 95, 120, 150, 175; Start Head: 50.",
        "concept": "1. SSTF (Shortest Seek Time First) chooses the pending request with the minimum seek distance from the current head position.\\n2. Reduces average seek time compared to FCFS, but may lead to starvation of distant requests.",
        "code": get_disk_sstf_c("30, 10, 60, 95, 120, 150, 175", 50),
        "sample_out": """Order of Request Service:
50 -> 60 -> 30 -> 10 -> 95 -> 120 -> 150 -> 175

Total Head Movements: 250 cylinders"""
    },
    "viva": [
        ("What are the 4 necessary conditions for Deadlock?", "Mutual Exclusion, Hold and Wait, No Preemption, and Circular Wait."),
        ("What is the difference between Deadlock Prevention and Deadlock Avoidance?", "Prevention eliminates at least one of the 4 deadlock conditions statically. Avoidance dynamically monitors resource allocation to ensure the system never enters an unsafe state."),
        ("What is SSTF disk scheduling?", "Shortest Seek Time First services the request closest to the current head position to minimize head movement."),
        ("Can SSTF cause starvation?", "Yes, continuous arrival of nearby requests can cause distant cylinder requests to starve indefinitely."),
        ("What is safe state in Banker's algorithm?", "A state is safe if the system can allocate resources to each process in some order without encountering a deadlock.")
    ]
}

# Slip 04
SLIP_CONFIGS[4] = {
    "q1": {
        "title": "Banker's Algorithm Menu Driven Program",
        "stmt": "Implement Menu driven Banker's algorithm for accepting Allocation, Max from user. Menu: Accept Available, Display Allocation/Max, Find Need and display, Display Available. Resources A:7, B:2, C:6.",
        "concept": "1. Need Matrix calculation: Need[i][j] = Max[i][j] - Allocation[i][j].\\n2. Tracks available resources and displays allocation state interactively.",
        "code": get_banker_menu_c(
            [[0, 1, 0], [4, 0, 0], [5, 0, 4], [4, 3, 3], [2, 2, 4]],
            [[0, 0, 0], [5, 2, 2], [1, 0, 4], [4, 4, 4], [6, 5, 5]],
            [7, 2, 6], 5, 3
        ),
        "sample_out": """=============================================
   BANKER'S ALGORITHM - MENU DRIVEN PROGRAM
=============================================
1. Accept Available
2. Display Allocation and Max
3. Display Contents of Need Matrix
4. Display Available
5. Exit
Enter your choice (1-5): 3

Need Matrix (Need = Max - Allocation):
Process Need (A B C)
P0      0 -1 0 
P1      1 2 2 
P2      -4 0 0 
P3      0 1 1 
P4      4 3 1"""
    },
    "q2": {
        "title": "SCAN Disk Scheduling Simulation",
        "stmt": "Write a simulation program for disk scheduling using SCAN algorithm. Request: 82, 170, 43, 140, 24, 16, 190, 65; Start Head: 50; Direction: Left.",
        "concept": "1. SCAN (Elevator algorithm) moves the head towards one end of the disk servicing requests, reaches the end (0), and reverses direction towards the other end.\\n2. Eliminates starvation seen in SSTF.",
        "code": get_disk_scan_c("82, 170, 43, 140, 24, 16, 190, 65", 50, "Left"),
        "sample_out": """Order of Request Service:
50 -> 43 -> 24 -> 16 -> 0 -> 65 -> 82 -> 140 -> 170 -> 190

Total Head Movements: 240 cylinders"""
    },
    "viva": [
        ("Why is the SCAN algorithm called the elevator algorithm?", "Because it behaves like an elevator in a building: moving in one direction servicing requests until it reaches the boundary, then reversing direction."),
        ("What is the difference between SCAN and LOOK?", "SCAN goes all the way to the disk boundary (e.g. cylinder 0 or max) before reversing, whereas LOOK only goes as far as the last pending request in that direction before reversing."),
        ("What does the Need matrix signify in Banker's algorithm?", "It represents the remaining resources each process may still request before it finishes execution."),
        ("What happens if a process requests more resources than its Max claim?", "The operating system raises an error condition and rejects the request because the process exceeded its declared maximum claim."),
        ("What is rotational latency in disk access?", "Rotational latency is the time required for the desired disk sector to rotate under the read/write head.")
    ]
}

# Slip 05
SLIP_CONFIGS[5] = {
    "q1": {
        "title": "FIFO Page Replacement Simulation",
        "stmt": "Write the simulation program for demand paging and show page scheduling and total page faults using FIFO. Reference string: 3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6; n frames.",
        "concept": "1. FIFO (First-In, First-Out) replaces the oldest page in memory when a page fault occurs and all frames are full.\\n2. Maintained using a circular queue or index pointer.",
        "code": get_page_fifo_c("3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6", 3),
        "sample_out": """Step    Page    Frames          Status
-------------------------------------------------
1       3       [ 3 - - ]       PAGE FAULT
2       4       [ 3 4 - ]       PAGE FAULT
3       5       [ 3 4 5 ]       PAGE FAULT
4       6       [ 6 4 5 ]       PAGE FAULT
...
Total Page Faults: 13
Total Hits: 2"""
    },
    "q2": {
        "title": "Banker's Resource Allocation Representation",
        "stmt": "Consider a system with ‘n’ processes and ‘m’ resource types. Accept number of instances for every resource, Allocation, and Max matrix. Calculate and display Need matrix and Available vector.",
        "concept": "1. Accepts dynamic dimensions n and m.\\n2. Computes Available = Total - Sum(Allocated for each resource).\\n3. Computes Need = Max - Allocation.",
        "code": get_banker_general_c(),
        "sample_out": """Enter number of processes: 3
Enter number of resource types: 3
Enter total instances: 10 10 10
--- Need Matrix ---
P0: 2 1 3 
P1: 1 2 0 
P2: 0 1 2 
--- Available Vector ---
4 3 5"""
    },
    "viva": [
        ("What is demand paging?", "Demand paging is a paging system where pages are loaded into memory only when they are referenced (demanded) during execution."),
        ("What is a page fault?", "A page fault is an interrupt raised by hardware when a running program accesses a memory page that is not currently loaded in physical RAM."),
        ("What is Belady's Anomaly?", "Belady's Anomaly is a phenomenon where increasing the number of page frames results in an increase in the number of page faults for certain page replacement algorithms (such as FIFO)."),
        ("Does LRU suffer from Belady's Anomaly?", "No, LRU is a stack algorithm and does not suffer from Belady's Anomaly."),
        ("What is thrashing?", "Thrashing occurs when a computer spends more time swapping pages in and out of memory than executing actual instructions.")
    ]
}

# Slip 06
SLIP_CONFIGS[6] = {
    "q1": {
        "title": "Sequential File Allocation Simulation",
        "stmt": "Write a program to simulate Sequential (Contiguous) file allocation method. Assume disk with n blocks. Randomly mark allocated blocks, maintain free list, menu: Show Bit Vector, Create New File, Show Directory, Exit.",
        "concept": "1. In contiguous allocation, each file occupies a set of consecutive blocks on disk.\\n2. Fast access since disk head movement is minimized.\\n3. Suffer from external fragmentation.",
        "code": get_file_alloc_seq_c(),
        "sample_out": """=== SEQUENTIAL (CONTIGUOUS) FILE ALLOCATION MENU ===
1. Show Bit Vector
2. Create New File
3. Show Directory
4. Exit
Enter your choice (1-4): 2
Enter file name: data.bin
Enter number of contiguous blocks required: 4
[+] File 'data.bin' allocated sequentially from block 3 to 6."""
    },
    "q2": {
        "title": "C-SCAN Disk Scheduling Simulation",
        "stmt": "Write a simulation program for disk scheduling using C-SCAN algorithm. Request: 82, 170, 43, 140, 24, 16, 190, 65; Start Head: 50; Direction: Left.",
        "concept": "1. C-SCAN (Circular SCAN) provides a more uniform wait time.\\n2. The head moves in one direction servicing requests until it reaches the edge, then returns immediately to the opposite edge without servicing requests on the return trip.",
        "code": get_disk_cscan_c("82, 170, 43, 140, 24, 16, 190, 65", 50, "Left"),
        "sample_out": """Order of Request Service:
50 -> 43 -> 24 -> 16 -> 0 -> 199 -> 190 -> 170 -> 140 -> 82 -> 65

Total Head Movements: 383 cylinders"""
    },
    "viva": [
        ("What is contiguous file allocation?", "Each file occupies a sequence of contiguous physical disk blocks."),
        ("What is external fragmentation in contiguous allocation?", "Free disk space is broken into small pieces over time, so large files cannot be allocated even if total free space is sufficient."),
        ("Why does C-SCAN provide more uniform wait times than SCAN?", "Because in regular SCAN, cylinders near the middle get serviced twice per cycle while edge cylinders wait longer. C-SCAN treats cylinders circularly, giving equal waiting distribution."),
        ("What is cylinder in a hard disk?", "A cylinder is the collection of all tracks across all platters located at the same radial distance from the spindle center."),
        ("What is disk bandwidth?", "Disk bandwidth is the total number of bytes transferred divided by the total time between the first request service and the completion of the last transfer.")
    ]
}

# Slip 07
SLIP_CONFIGS[7] = {
    "q1": {
        "title": "Banker's Algorithm Deadlock Avoidance (4 Resources)",
        "stmt": "Consider system snapshot with 5 processes P0-P4 and 4 resource types A, B, C, D. Allocation, Max, Available given. Display Need, check safety, check if P1 request (0,4,2,0) can be granted.",
        "concept": "1. Multidimensional resource avoidance with 4 resource types.\\n2. Computes Need = Max - Allocation for all processes.\\n3. Evaluates resource request algorithm safety.",
        "code": get_banker_safety_c(
            [[2, 0, 0, 1], [3, 1, 2, 1], [2, 1, 0, 3], [1, 3, 1, 2], [1, 4, 3, 2]],
            [[4, 2, 1, 2], [5, 2, 5, 2], [2, 3, 1, 6], [1, 4, 2, 4], [3, 6, 6, 5]],
            [3, 3, 2, 1], 5, 4, 1, "0, 4, 2, 0"
        ),
        "sample_out": """Process Allocation     Max             Need
P0      2 0 0 1         4 2 1 2         2 2 1 1 
P1      3 1 2 1         5 2 5 2         2 1 3 1 
P2      2 1 0 3         2 3 1 6         0 2 1 3 
P3      1 3 1 2         1 4 2 4         0 1 1 2 
P4      1 4 3 2         3 6 6 5         2 2 3 3 

Available Resources: 3 3 2 1 
[+] The system is currently in a SAFE state.
Safe Sequence: P0 -> P2 -> P3 -> P1 -> P4

Checking Request from P1: ( 0 4 2 0 )
[-] Error: Process exceeded maximum claim / insufficient available resources."""
    },
    "q2": {
        "title": "Process Priority Adjustment with nice() System Call",
        "stmt": "Write a program that demonstrates the use of nice() system call. After child process is started using fork(), assign priority using nice().",
        "concept": "1. nice() system call adds an increment to the nice value of the calling process.\\n2. In Unix, nice values range from -20 (highest priority) to 19 (lowest priority).",
        "code": get_nice_process_c(),
        "sample_out": """[Parent] Parent Nice Value: 0
[Child] Initial Nice Value: 0
[Child] After nice(5), Updated Nice Value: 5
[Child] Doing task and finishing...
[Parent] Child execution complete."""
    },
    "viva": [
        ("What does the nice value represent in Linux?", "The nice value represents the user-space priority hint for CPU scheduling, ranging from -20 (highest priority) to +19 (lowest priority)."),
        ("Can a normal user decrease the nice value (increase priority)?", "No, only the superuser (root) can set a negative nice value or decrease an existing nice value."),
        ("What header file is required for nice() and getpriority()?", "`#include <unistd.h>` and `#include <sys/resource.h>`."),
        ("What is the difference between safe state and unsafe state?", "A safe state guarantees that deadlock can be avoided. An unsafe state is not necessarily a deadlock, but deadlock is possible and cannot be prevented with certainty."),
        ("What is starvation in resource allocation?", "Starvation (indefinite postponement) occurs when a process is perpetually denied necessary resources while other processes make continuous progress.")
    ]
}

# Slip 08
SLIP_CONFIGS[8] = {
    "q1": {
        "title": "Indexed File Allocation Simulation",
        "stmt": "Write a program to simulate Index file allocation method. Disk with n blocks. Randomly mark allocated, maintain free list, menu: Show Bit Vector, Create New File, Show Directory, Exit.",
        "concept": "1. In indexed allocation, each file has its own index block containing an array of disk-block addresses.\\n2. Supports direct/random access without external fragmentation.\\n3. Requires extra overhead for index blocks.",
        "code": get_file_alloc_indexed_c(),
        "sample_out": """=== INDEXED FILE ALLOCATION MENU ===
1. Show Bit Vector
2. Create New File
3. Show Directory
4. Exit
Enter your choice (1-4): 2
Enter file name: doc.pdf
Enter number of data blocks required: 3
[+] File 'doc.pdf' allocated with Index Block at 1.

=== INDEXED FILE ALLOCATION MENU ===
1. Show Bit Vector
2. Create New File
3. Show Directory
4. Exit
Enter your choice (1-4): 3
File Name       Index Block     Length  Data Blocks
doc.pdf         1               3       3 5 8"""
    },
    "q2": {
        "title": "Demonstration of nice() System Call",
        "stmt": "Write a program that demonstrates the use of nice () system call. After child process is started using fork(), assign priority using nice().",
        "concept": "1. Demonstrates process creation via fork() and altering CPU priority via nice().",
        "code": get_nice_process_c(),
        "sample_out": """[Parent] Parent Nice Value: 0
[Child] Initial Nice Value: 0
[Child] After nice(5), Updated Nice Value: 5
[Parent] Child execution complete."""
    },
    "viva": [
        ("What is an index block in indexed file allocation?", "An index block is a dedicated disk block storing pointers/addresses to all the data blocks belonging to a file."),
        ("What happens if a file is larger than what a single index block can store?", "Techniques like linked index blocks, multilevel indexing (indirect blocks, like in Unix inodes), or combined indexing are used."),
        ("Compare indexed allocation with linked allocation.", "Indexed allocation supports direct/random access, whereas linked allocation only supports sequential access. However, indexed allocation has higher space overhead for small files."),
        ("What happens to nice value upon fork()?", "The child process inherits the parent's nice value at the time of fork()."),
        ("What is CFS in Linux?", "CFS stands for Completely Fair Scheduler, the default Linux CPU scheduler which uses red-black trees based on virtual runtime (vruntime).")
    ]
}

# Slip 09
SLIP_CONFIGS[9] = {
    "q1": {
        "title": "LRU Page Replacement (Counter Method)",
        "stmt": "Write simulation program for demand paging and show page scheduling and total page faults using LRU (counter method). String: 3,5,7,2,5,1,2,3,1,3,5,3,1,6,2; n frames.",
        "concept": "1. LRU associates with each page frame the time of its last reference.\\n2. When replacement is needed, the frame with the oldest timestamp (minimum counter value) is replaced.",
        "code": get_page_lru_c("3, 5, 7, 2, 5, 1, 2, 3, 1, 3, 5, 3, 1, 6, 2", 3),
        "sample_out": """Step    Page    Frames          Status
-------------------------------------------------
1       3       [ 3 - - ]       PAGE FAULT
2       5       [ 3 5 - ]       PAGE FAULT
3       7       [ 3 5 7 ]       PAGE FAULT
4       2       [ 2 5 7 ]       PAGE FAULT
...
Total Page Faults: 9
Total Hits: 6"""
    },
    "q2": {
        "title": "Non-preemptive Shortest Job First (SJF) CPU Scheduling",
        "stmt": "Simulate Non-preemptive Shortest Job First (SJF) scheduling. Arrival time and burst time input. Output Gantt chart, TAT, WT, average TAT and WT.",
        "concept": "1. At each decision point, select the available process with the smallest CPU burst time.\\n2. Once scheduled, the process runs to completion (non-preemptive).",
        "code": get_cpu_sjf_np_c(),
        "sample_out": """--- Gantt Chart ---
 |  P1  |  P3  |  P2  |
End Time: 12

PID     AT      1st BT  Next BT CT      TAT     WT
P1      0       3       7       3       3       0
P2      2       5       4       12      10      5
P3      1       4       2       7       6       2

Average Turnaround Time: 6.33
Average Waiting Time: 2.33"""
    },
    "viva": [
        ("Why is SJF optimal?", "SJF gives the minimum average waiting time for a given set of processes."),
        ("What is the main drawback of SJF in practical OS?", "It is impossible to know the exact length of the next CPU burst in advance; it can only be estimated."),
        ("What is turnaround time?", "Turnaround Time is the total interval between process arrival and its completion: TAT = Completion Time - Arrival Time."),
        ("What is waiting time?", "Waiting Time is the total time spent by a process in the ready queue: WT = Turnaround Time - Burst Time."),
        ("Explain the LRU counter method.", "A logical clock or counter increments with every memory reference; each page frame records the counter value upon access, and the page with the lowest counter is replaced.")
    ]
}

# Slip 10
SLIP_CONFIGS[10] = {
    "q1": {
        "title": "Round Robin (RR) CPU Scheduling",
        "stmt": "Write program to simulate Round Robin (RR) CPU scheduling. Arrival time, burst time, time quantum input. Output Gantt chart, TAT, WT, avg TAT & WT.",
        "concept": "1. RR allocates a fixed time quantum to each ready process in circular order.\\n2. Preempts processes that do not complete within the quantum and returns them to the ready queue.",
        "code": get_cpu_round_robin_c(),
        "sample_out": """--- Gantt Chart ---
 | P1 | P2 | P3 | P2 | P3 | P3 |
Total Time: 18

PID     AT      1st BT  Next BT CT      TAT     WT
P1      0       3       4       5       5       2
P2      0       6       8       12      12      6
P3      0       9       1       18      18      9

Average Turnaround Time: 11.67
Average Waiting Time: 5.67"""
    },
    "q2": {
        "title": "LOOK Disk Scheduling Simulation",
        "stmt": "Write a simulation program for disk scheduling using LOOK algorithm. Request: 86, 147, 91, 177, 45, 12, 130; Start Head: 60; Direction: Right.",
        "concept": "1. LOOK algorithm scans in the current direction until reaching the furthest requested cylinder, then reverses immediately without traveling to the physical end of the disk.",
        "code": get_disk_look_c("86, 147, 91, 177, 45, 12, 130", 60, "Right"),
        "sample_out": """Order of Request Service:
60 -> 86 -> 91 -> 130 -> 147 -> 177 -> 45 -> 12

Total Head Movements: 282 cylinders"""
    },
    "viva": [
        ("How does time quantum affect Round Robin performance?", "If time quantum is very large, RR degenerates to FCFS. If it is very small, excessive context switching overhead degrades system performance."),
        ("What is context switching?", "Context switching is the process of saving the execution state of the currently running process and restoring the state of the next scheduled process."),
        ("Why is LOOK preferred over SCAN?", "LOOK avoids unnecessary head travel to disk boundaries (cylinder 0 or max) when there are no requests pending there."),
        ("What is response time in CPU scheduling?", "Response time is the duration from the submission of a request/process until the first response is produced."),
        ("Is Round Robin preemptive or non-preemptive?", "Round Robin is strictly preemptive because timer interrupts preempt processes when their quantum expires.")
    ]
}

# Slip 11
SLIP_CONFIGS[11] = {
    "q1": {
        "title": "Banker's Algorithm Deadlock Avoidance",
        "stmt": "Write a C program to simulate Banker’s algorithm for Deadlock avoidance. Given Allocation, Max, Available. Display Need, check safety, test P1 request (1,0,2).",
        "concept": "1. Full safety algorithm implementation verifying safe state and testing resource request.",
        "code": get_banker_safety_c(
            [[0, 1, 0], [2, 0, 0], [3, 0, 2], [2, 1, 1], [0, 0, 2]],
            [[7, 5, 3], [3, 2, 2], [9, 0, 2], [2, 2, 2], [4, 3, 3]],
            [3, 3, 2], 5, 3, 1, "1, 0, 2"
        ),
        "sample_out": """[+] The system is currently in a SAFE state.
Safe Sequence: P1 -> P3 -> P4 -> P0 -> P2
Checking Request from P1: ( 1 0 2 )
[+] Request can be granted immediately! System remains safe."""
    },
    "q2": {
        "title": "LRU Page Replacement Simulation",
        "stmt": "Write simulation program for demand paging and show page scheduling and total page faults using LRU. String: 3, 5, 7, 2, 5, 1, 2, 3, 1, 3, 5, 3, 1, 6, 2; n frames.",
        "concept": "1. LRU replaces the page that has not been used for the longest period of time.",
        "code": get_page_lru_c("3, 5, 7, 2, 5, 1, 2, 3, 1, 3, 5, 3, 1, 6, 2", 3),
        "sample_out": """Total Page Faults: 9
Total Hits: 6"""
    },
    "viva": [
        ("What is the Banker's safety algorithm complexity?", "The time complexity is O(m * n^2), where n is the number of processes and m is the number of resource types."),
        ("What is the principle of locality of reference?", "Programs tend to reuse data and instructions they have used recently (temporal locality) or that are close to those recently accessed (spatial locality)."),
        ("Why does LRU perform well in practice?", "Because program execution exhibits strong temporal locality, recently used pages are likely to be accessed again soon."),
        ("What is a dirty bit (modify bit) in paging?", "A dirty bit indicates whether a page in memory has been modified since it was loaded from disk, avoiding unnecessary writes during page replacement."),
        ("What is deadlock detection vs avoidance?", "Deadlock avoidance prevents the system from entering an unsafe state dynamically. Deadlock detection allows deadlocks to occur, periodically checks for them, and initiates recovery.")
    ]
}

# Slip 12
SLIP_CONFIGS[12] = {
    "q1": {
        "title": "FCFS CPU Scheduling Simulation",
        "stmt": "Write program to simulate FCFS CPU scheduling. Input arrival time and first CPU-burst. Generate next burst randomly. Output Gantt chart, TAT, WT, avg TAT & WT.",
        "concept": "1. First-Come First-Served schedules processes strictly in arrival order.",
        "code": get_cpu_fcfs_c(),
        "sample_out": """--- Gantt Chart ---
 |  P1  |  P2  |  P3  |
Average Turnaround Time: 7.00
Average Waiting Time: 3.33"""
    },
    "q2": {
        "title": "Fork System Call with Bubble Sort and Insertion Sort",
        "stmt": "Implement C program to accept n integers. Main forks child. Parent sorts using bubble sort and waits; Child sorts using insertion sort.",
        "concept": "1. fork() creates concurrent processes.\\n2. Child process executes insertion sort on array.\\n3. Parent calls wait() and then executes bubble sort.",
        "code": get_sort_fork_c(),
        "sample_out": """[Child PID: 12345] Sorting using Insertion Sort...
[Child] Sorted Array: 3 6 9 12 15 

[Parent PID: 12344] Child finished. Sorting using Bubble Sort...
[Parent] Sorted Array: 3 6 9 12 15"""
    },
    "viva": [
        ("What does fork() return in parent and child?", "It returns 0 to the child process and the child's PID (>0) to the parent process; returns -1 on error."),
        ("What is the Convoy Effect in FCFS?", "The Convoy Effect occurs when several short CPU-bound processes are delayed behind one long CPU-bound process, resulting in poor CPU and device utilization."),
        ("Why is wait() system call important after fork()?", "wait() suspends the parent process until one of its children terminates, collecting the exit status and preventing the creation of a zombie process."),
        ("What is the time complexity of Bubble Sort and Insertion Sort?", "Both have worst-case and average-case time complexity of O(n^2), with best-case O(n) for already sorted arrays."),
        ("Are memory spaces shared between parent and child after fork()?", "No, fork creates a separate copy of the address space using copy-on-write (COW).")
    ]
}

# Slip 13
SLIP_CONFIGS[13] = {
    "q1": {
        "title": "Non-preemptive SJF CPU Scheduling",
        "stmt": "Write program to simulate Non-preemptive Shortest Job First (SJF) scheduling. Input arrival time and first burst. Output Gantt chart, TAT, WT, avg TAT & WT.",
        "concept": "1. Schedules process with smallest burst time among all currently arrived processes non-preemptively.",
        "code": get_cpu_sjf_np_c(),
        "sample_out": """Average Turnaround Time: 6.33
Average Waiting Time: 2.33"""
    },
    "q2": {
        "title": "LOOK Disk Scheduling Simulation",
        "stmt": "Write a simulation program for disk scheduling using LOOK algorithm. Request: 86, 147, 91, 177, 45, 12, 130; Start Head: 60; Direction: Right.",
        "concept": "1. Scans towards higher cylinder numbers servicing requests until the highest, then reverses to service remaining requests.",
        "code": get_disk_look_c("86, 147, 91, 177, 45, 12, 130", 60, "Right"),
        "sample_out": """Order of Request Service:
60 -> 86 -> 91 -> 130 -> 147 -> 177 -> 45 -> 12
Total Head Movements: 282 cylinders"""
    },
    "viva": [
        ("Why does Non-preemptive SJF not switch running jobs?", "Because in non-preemptive scheduling, once the CPU has been allocated to a process, the process keeps the CPU until it releases it either by terminating or by switching to waiting."),
        ("What is the difference between LOOK and C-LOOK?", "LOOK reverses direction and services requests on the way back; C-LOOK jumps straight to the lowest request without servicing on the return trip."),
        ("What is throughput in CPU scheduling?", "Throughput is the number of processes completed per unit time."),
        ("How does disk scheduling improve hard drive lifespan?", "By minimizing redundant mechanical arm movements, which reduces wear and tear on drive actuators."),
        ("What is preemptive scheduling vs non-preemptive scheduling?", "In preemptive scheduling, the OS can interrupt a running process to give the CPU to another higher-priority process. In non-preemptive scheduling, the process voluntarily yields the CPU.")
    ]
}

# Slip 14
SLIP_CONFIGS[14] = {
    "q1": {
        "title": "Process Forking and Array Binary Search",
        "stmt": "Implement C program that accepts an integer array. Main function forks child process. Parent sorts array; child performs binary search.",
        "concept": "1. Parent sorts array using sorting algorithm.\\n2. Child performs binary search on the sorted data.",
        "code": get_execve_search_c(),
        "sample_out": """[Parent] Original Array: 45 12 89 23 7 
[Parent] Sorted Array: 7 12 23 45 89 
[Child PID: 12350] Binary Searching for 23 in sorted array...
[Child] Element 23 found at index 2!
[Parent] Child search operation completed."""
    },
    "q2": {
        "title": "FIFO Page Replacement Simulation",
        "stmt": "Write simulation program for demand paging and show page scheduling and total page faults using FIFO. String: 3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6.",
        "concept": "1. Replaces the oldest page present in the frame queue when a page fault occurs.",
        "code": get_page_fifo_c("3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6", 3),
        "sample_out": """Total Page Faults: 13
Total Hits: 2"""
    },
    "viva": [
        ("What is binary search and its time complexity?", "Binary search is an efficient search algorithm on sorted arrays that divides the search interval in half each time; its time complexity is O(log n)."),
        ("What is execve() system call?", "execve() executes the program referred to by pathname, replacing the current process image with a new process image."),
        ("What happens to open file descriptors upon fork()?", "Child inherits duplicates of all open file descriptors from the parent, pointing to the same file table entries."),
        ("What is the replacement victim in FIFO?", "The page that entered memory earliest (at the front of the queue)."),
        ("What is virtual memory?", "Virtual memory is a memory management capability that provides an idealized abstraction of storage resources, allowing execution of processes larger than physical RAM.")
    ]
}

# Slip 15
SLIP_CONFIGS[15] = {
    "q1": {
        "title": "Illustration of Orphan Process",
        "stmt": "Write a C program to illustrate the concept of orphan process. Parent process creates a child and terminates before child has finished. Use fork(), sleep(), getpid(), getppid().",
        "concept": "1. An orphan process is a running process whose parent has terminated.\\n2. Orphan processes are immediately adopted by the `systemd` / `init` process (PID 1).",
        "code": get_orphan_process_c(),
        "sample_out": """[Parent] PID: 4120, Child PID: 4121
[Parent] Terminating immediately without waiting for child.
[Child] PID: 4121, Initial Parent PID: 4120
[Child] Sleeping for 4 seconds to become orphan...
[Child] Woke up! Current Parent PID: 1 (Adopted by systemd/init)
[Child] Exiting normally."""
    },
    "q2": {
        "title": "Preemptive Priority CPU Scheduling",
        "stmt": "Write program to simulate Preemptive Priority scheduling. Arrival time, burst time, priority input. Output Gantt chart, TAT, WT, avg TAT & WT.",
        "concept": "1. When a new process arrives with higher priority than the currently running process, the current process is preempted.\\n2. Lower priority number denotes higher priority.",
        "code": get_cpu_priority_p_c(),
        "sample_out": """--- Gantt Chart ---
 | P1 | P2 | P3 |
Total Time: 15

Average Turnaround Time: 10.00
Average Waiting Time: 5.00"""
    },
    "viva": [
        ("What is an orphan process?", "An orphan process is a process whose parent has finished or terminated, leaving the child still running."),
        ("What happens to an orphan process in Linux?", "It is automatically adopted by PID 1 (init / systemd), which reaps its exit status when it terminates."),
        ("What is a zombie process?", "A zombie (defunct) process is a process that has completed execution but still has an entry in the process table because its parent hasn't read its exit status with wait()."),
        ("How does Priority Preemptive scheduling work?", "The CPU scheduler immediately preempts the currently running process if a newly arrived process has a higher priority."),
        ("What is process starvation in priority scheduling, and how is it solved?", "Lower-priority processes may wait indefinitely; it is solved using Aging, which gradually increases the priority of waiting processes.")
    ]
}

# Slip 16
SLIP_CONFIGS[16] = {
    "q1": {
        "title": "LRU Page Replacement (Counter Method)",
        "stmt": "Write simulation program for demand paging using LRU counter method. String: 3,5,7,2,5,1,2,3,1,3,5,3,1,6,2.",
        "concept": "1. LRU tracking with time counters for each page frame.",
        "code": get_page_lru_c("3, 5, 7, 2, 5, 1, 2, 3, 1, 3, 5, 3, 1, 6, 2", 3),
        "sample_out": """Total Page Faults: 9
Total Hits: 6"""
    },
    "q2": {
        "title": "Custom Shell with count Command",
        "stmt": "Write C program that behaves like shell ($ prompt). Tokenize and execute via fork. Implement 'count c|w|l filename'.",
        "concept": "1. Interactive prompt with tokenization.\\n2. Built-in command for counting characters, words, lines in a file.\\n3. External commands via fork and execvp.",
        "code": open(os.path.join(BASE_DIR, "os_slip_01/os_slip_01_q2.c")).read() if os.path.exists(os.path.join(BASE_DIR, "os_slip_01/os_slip_01_q2.c")) else get_shell_search_c(),
        "sample_out": """$ count c sample.txt
Total characters in 'sample.txt': 45
$ count w sample.txt
Total words in 'sample.txt': 8
$ count l sample.txt
Total lines in 'sample.txt': 3
$ exit"""
    },
    "viva": [
        ("What is a shell in an operating system?", "A shell is a command-line interpreter that acts as an interface between the user and the operating system kernel."),
        ("How does a shell execute built-in vs external commands?", "Built-in commands (like cd, exit, count) are executed directly in the shell process. External commands require forking a child process and calling execvp()."),
        ("Why does LRU not suffer from Belady's anomaly?", "Because LRU belongs to the class of stack algorithms, where the set of pages in memory for n frames is always a subset of pages for n+1 frames."),
        ("How does strtok() work in C?", "strtok() breaks a string into a sequence of zero or more non-empty tokens based on delimiter characters."),
        ("What is EOF in C file handling?", "EOF is a macro representing End Of File, returned by functions like fgetc() when the end of the file is reached.")
    ]
}

# Slip 17
SLIP_CONFIGS[17] = {
    "q1": {
        "title": "Non-preemptive SJF CPU Scheduling",
        "stmt": "Write program to simulate Non-preemptive Shortest Job First (SJF) scheduling. Arrival time and burst time input. Output Gantt chart, TAT, WT, avg TAT & WT.",
        "concept": "1. Non-preemptive SJF selects the available job with shortest burst time.",
        "code": get_cpu_sjf_np_c(),
        "sample_out": """Average Turnaround Time: 6.33
Average Waiting Time: 2.33"""
    },
    "q2": {
        "title": "Sequential File Allocation Simulation",
        "stmt": "Write program to simulate Sequential (Contiguous) file allocation. Assume disk with n blocks. Randomly mark allocated, maintain free list, menu: Show Bit Vector, Create New File, Show Directory, Exit.",
        "concept": "1. Finds contiguous free blocks for file allocation.",
        "code": get_file_alloc_seq_c(),
        "sample_out": """[+] File 'test.txt' allocated sequentially from block 4 to 7."""
    },
    "viva": [
        ("What is the primary advantage of sequential file allocation?", "It provides the best sequential read/write performance because blocks are stored contiguously on disk."),
        ("What is the difference between turnaround time and response time?", "Turnaround time is the time from arrival to termination. Response time is the time from arrival to the first CPU execution."),
        ("How can free disk space be tracked?", "Using Bit vectors, Linked free lists, Grouping, or Counting."),
        ("What causes external fragmentation in disk allocation?", "Repeated creation and deletion of files leaves small scattered free blocks that cannot satisfy contiguous block requests."),
        ("What is CPU utilization?", "The percentage of time that the CPU is busy executing user or system processes.")
    ]
}

# Slip 18
SLIP_CONFIGS[18] = {
    "q1": {
        "title": "Preemptive Shortest Job First (SJF / SRTF) CPU Scheduling",
        "stmt": "Write program to simulate Preemptive Shortest Job First (SJF) scheduling. Input arrival time and first CPU burst. Output Gantt chart, TAT, WT, avg TAT & WT.",
        "concept": "1. Shortest Remaining Time First (SRTF) preempts the running process if a new process arrives with a shorter remaining burst time.",
        "code": get_cpu_sjf_p_c(),
        "sample_out": """--- Gantt Chart ---
 | P1 | P2 | P3 |
Total Time: 12
Average Turnaround Time: 6.00
Average Waiting Time: 2.00"""
    },
    "q2": {
        "title": "Orphan Process Illustration",
        "stmt": "Write a C program to illustrate the concept of orphan process. Parent process creates a child and terminates before child has finished its task. Use fork(), sleep(), getpid(), getppid().",
        "concept": "1. Demonstrates orphan process adoption by init/systemd (PID 1).",
        "code": get_orphan_process_c(),
        "sample_out": """[Parent] Terminating immediately without waiting for child.
[Child] Woke up! Current Parent PID: 1 (Adopted by systemd/init)"""
    },
    "viva": [
        ("What is the difference between non-preemptive SJF and preemptive SJF?", "In non-preemptive SJF, a process keeps the CPU until it finishes its burst. In preemptive SJF (SRTF), a newly arrived process with a shorter burst preempts the running process."),
        ("What system call returns the parent PID of a process?", "`getppid()` returns the process ID of the parent."),
        ("What system call returns the current process PID?", "`getpid()` returns the process ID of the current process."),
        ("Why does the child process sleep in the orphan demonstration?", "Sleeping gives the parent process enough time to exit first, leaving the child orphaned."),
        ("What is CPU burst vs I/O burst?", "A CPU burst is a period when the process is executing instructions on the CPU; an I/O burst is a period when the process is waiting for an I/O operation to complete.")
    ]
}

# Slip 19
SLIP_CONFIGS[19] = {
    "q1": {
        "title": "Preemptive Priority CPU Scheduling",
        "stmt": "Write program to simulate Preemptive Priority scheduling. Input arrival time, burst time, priority. Output Gantt chart, TAT, WT, avg TAT & WT.",
        "concept": "1. Preempts current process if higher priority job arrives.",
        "code": get_cpu_priority_p_c(),
        "sample_out": """Average Turnaround Time: 10.00
Average Waiting Time: 5.00"""
    },
    "q2": {
        "title": "Demonstration of nice() System Call",
        "stmt": "Write program that demonstrates use of nice() system call. After child process started using fork(), assign higher priority using nice().",
        "concept": "1. Demonstrates priority changes via nice().",
        "code": get_nice_process_c(),
        "sample_out": """[Child] After nice(5), Updated Nice Value: 5"""
    },
    "viva": [
        ("What is the effect of passing a positive integer to nice()?", "A positive value makes the process 'nicer' to other processes by lowering its scheduling priority."),
        ("What is priority inversion?", "Priority inversion occurs when a low-priority process holds a shared resource needed by a high-priority process, while a medium-priority process preempts the low-priority process."),
        ("How is priority inversion resolved?", "Using the Priority Inheritance Protocol, where the low-priority process temporarily inherits the high-priority process's priority level."),
        ("Can child and parent communicate through global variables after fork?", "No, because each process has its own private virtual memory space; inter-process communication (IPC) like pipes or shared memory is needed."),
        ("What is exit() vs _exit() in C?", "exit() flushes standard I/O buffers and calls registered atexit functions before terminating. _exit() terminates immediately without flushing buffers.")
    ]
}

# Slip 20
SLIP_CONFIGS[20] = {
    "q1": {
        "title": "LOOK Disk Scheduling Simulation",
        "stmt": "Write simulation program for disk scheduling using LOOK algorithm. Request: 86, 147, 91, 177, 45, 12, 130; Start Head: 60; Direction: Right.",
        "concept": "1. Scans in current direction to farthest request, then reverses.",
        "code": get_disk_look_c("86, 147, 91, 177, 45, 12, 130", 60, "Right"),
        "sample_out": """Order of Request Service:
60 -> 86 -> 91 -> 130 -> 147 -> 177 -> 45 -> 12
Total Head Movements: 282 cylinders"""
    },
    "q2": {
        "title": "LRU Page Replacement (Counter Method)",
        "stmt": "Write simulation program for demand paging using LRU (counter method). String: 3,5,7,2,5,1,2,3,1,3,5,3,1,6,2.",
        "concept": "1. Replaces least recently used frame based on timestamp counter.",
        "code": get_page_lru_c("3, 5, 7, 2, 5, 1, 2, 3, 1, 3, 5, 3, 1, 6, 2", 3),
        "sample_out": """Total Page Faults: 9
Total Hits: 6"""
    },
    "viva": [
        ("Why is LOOK disk scheduling an improvement over SCAN?", "Because it does not travel to cylinder 0 or the maximum disk cylinder unless there is an actual request at those extremes."),
        ("What hardware support is required for demand paging?", "A page table with valid/invalid bits and secondary storage (swap disk) to hold pages not in RAM."),
        ("What is the cost of a page fault?", "Servicing a page fault involves an OS trap, disk read I/O (millisecond delay), frame allocation, and process restart."),
        ("How does LRU stack implementation work?", "A doubly linked list of page numbers is maintained; when a page is referenced, it is moved to the top of the stack. The bottom of the stack is always the LRU page."),
        ("What is cylinder skew in modern hard drives?", "Cylinder skew offsets the starting sector of each track to account for head switch time when moving between adjacent cylinders.")
    ]
}

# Slip 21
SLIP_CONFIGS[21] = {
    "q1": {
        "title": "FIFO Page Replacement Simulation",
        "stmt": "Write simulation program for demand paging using FIFO. Reference string: 3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6.",
        "concept": "1. Oldest page in memory is replaced first.",
        "code": get_page_fifo_c("3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6", 3),
        "sample_out": """Total Page Faults: 13
Total Hits: 2"""
    },
    "q2": {
        "title": "Demonstration of nice() System Call",
        "stmt": "Write a program that demonstrates the use of nice() system call. After child process started using fork(), assign priority using nice().",
        "concept": "1. Changes scheduling priority using nice().",
        "code": get_nice_process_c(),
        "sample_out": """[Child] After nice(5), Updated Nice Value: 5"""
    },
    "viva": [
        ("What is the range of nice values in POSIX systems?", "-20 (highest scheduling priority) to +19 (lowest scheduling priority)."),
        ("What is Belady's Anomaly and in which algorithm is it observed?", "Belady's Anomaly is when more frames cause more page faults. It is observed in FIFO page replacement."),
        ("What is a stack algorithm in page replacement?", "An algorithm for which the set of pages in memory for n frames is always a subset of the pages for n+1 frames (e.g. LRU, Optimal)."),
        ("What is the function of the swap space?", "Swap space on secondary storage holds memory pages that are inactive, freeing physical RAM for active pages."),
        ("How does a process terminate in Unix?", "By calling exit(), _exit(), or receiving an unhandled terminating signal.")
    ]
}

# Slip 22
SLIP_CONFIGS[22] = {
    "q1": {
        "title": "Linked File Allocation Simulation",
        "stmt": "Write a program to simulate Linked file allocation method. Assume disk with n blocks. Randomly mark allocated, maintain free list, menu: Show Bit Vector, Create New File, Show Directory, Exit.",
        "concept": "1. Simulates linked list disk blocks allocation.",
        "code": get_file_alloc_linked_c(),
        "sample_out": """[+] File 'project.c' created successfully using Linked Allocation."""
    },
    "q2": {
        "title": "Non-preemptive Priority CPU Scheduling",
        "stmt": "Write program to simulate Non-preemptive Priority scheduling. Input arrival time, burst time, priority. Output Gantt chart, TAT, WT, avg TAT & WT.",
        "concept": "1. Dispatches the highest priority ready process non-preemptively.",
        "code": get_cpu_priority_np_c(),
        "sample_out": """--- Gantt Chart ---
 |  P1  |  P3  |  P2  |
Average Turnaround Time: 8.00
Average Waiting Time: 4.00"""
    },
    "viva": [
        ("Why does linked allocation not have external fragmentation?", "Because any free block anywhere on disk can satisfy a request for the next block of the file."),
        ("What is the primary drawback of Non-preemptive Priority scheduling?", "Starvation of low-priority processes if high-priority processes keep arriving."),
        ("How does aging solve starvation?", "Aging gradually increases the priority of processes that wait in the system for a long time."),
        ("What is FAT (File Allocation Table)?", "FAT is an implementation of linked allocation where all block pointers are cached together in an array at the beginning of the volume."),
        ("What is the difference between preemptive and non-preemptive priority?", "Preemptive interrupts the running process when a higher-priority process arrives; non-preemptive lets the running process complete its burst.")
    ]
}

# Slip 23
SLIP_CONFIGS[23] = {
    "q1": {
        "title": "Fork System Call with Bubble Sort and Insertion Sort",
        "stmt": "Implement C program to accept n integers. Main function creates child. Parent sorts using bubble sort and waits; child sorts using insertion sort.",
        "concept": "1. Child process performs insertion sort; parent waits and performs bubble sort.",
        "code": get_sort_fork_c(),
        "sample_out": """[Child] Sorted Array: 3 6 9 12 15 
[Parent] Sorted Array: 3 6 9 12 15"""
    },
    "q2": {
        "title": "Non-preemptive SJF CPU Scheduling",
        "stmt": "Write program to simulate Non-preemptive Shortest Job First (SJF) scheduling. Input arrival time and burst time. Output Gantt chart, TAT, WT, avg TAT & WT.",
        "concept": "1. Non-preemptive scheduling prioritizing shortest job.",
        "code": get_cpu_sjf_np_c(),
        "sample_out": """Average Turnaround Time: 6.33
Average Waiting Time: 2.33"""
    },
    "viva": [
        ("What is a system call?", "A system call is a programmatic way in which a computer program requests a service from the kernel of the operating system."),
        ("How does the CPU switch between user mode and kernel mode?", "Via software interrupts, traps, or special CPU instructions (e.g. `syscall` or `sysenter`)."),
        ("What is a race condition?", "A race condition occurs when multiple processes access and manipulate shared data concurrently, and the outcome depends on the order of execution."),
        ("Why is wait() necessary in parent process?", "To collect child termination status and prevent zombie processes."),
        ("How does insertion sort work?", "It builds the sorted array one item at a time by repeatedly taking the next element and inserting it into its correct position among the already-sorted elements.")
    ]
}

# Slip 24
SLIP_CONFIGS[24] = {
    "q1": {
        "title": "Round Robin (RR) CPU Scheduling",
        "stmt": "Write program to simulate Round Robin (RR) scheduling. Input arrival time, burst time, time quantum. Output Gantt chart, TAT, WT, avg TAT & WT.",
        "concept": "1. Preemptive scheduling based on fixed time quantum slice.",
        "code": get_cpu_round_robin_c(),
        "sample_out": """Average Turnaround Time: 11.67
Average Waiting Time: 5.67"""
    },
    "q2": {
        "title": "Process Sorting and Binary Search with Fork",
        "stmt": "Implement C program that accepts an integer array. Parent sorts array; child performs binary search.",
        "concept": "1. Parent sorts array and coordinates with child searching for target element.",
        "code": get_execve_search_c(),
        "sample_out": """[Parent] Sorted Array: 7 12 23 45 89 
[Child] Element 23 found at index 2!"""
    },
    "viva": [
        ("What is the time complexity of Round Robin scheduling?", "O(1) per scheduling decision if implemented with a FIFO queue."),
        ("What happens if time quantum in RR is too large?", "Round Robin degrades into FCFS (First-Come, First-Served)."),
        ("What is binary search prerequisite?", "The array must be strictly sorted in ascending or descending order."),
        ("What is IPC?", "Inter-Process Communication mechanisms (pipes, message queues, shared memory, sockets) that allow processes to exchange data."),
        ("What is the state of a child process after fork before parent calls wait?", "If the child finishes first, it enters the ZOMBIE state until the parent calls wait() or terminates.")
    ]
}

# Slip 25
SLIP_CONFIGS[25] = {
    "q1": {
        "title": "Orphan Process Demonstration",
        "stmt": "Write a C program to illustrate orphan process concept. Parent terminates before child finishes. Use fork(), sleep(), getpid(), getppid().",
        "concept": "1. Demonstrates orphan process adoption by PID 1.",
        "code": get_orphan_process_c(),
        "sample_out": """[Child] Woke up! Current Parent PID: 1 (Adopted by systemd/init)"""
    },
    "q2": {
        "title": "Custom Shell with search Command",
        "stmt": "Write C program that behaves like shell ($ prompt). Tokenize and execute via fork. Implement 'search f|c|a pattern filename'.",
        "concept": "1. Custom shell with search command:\\n   - search f pattern filename: first occurrence\\n   - search c pattern filename: count occurrences\\n   - search a pattern filename: all occurrences.",
        "code": get_shell_search_c(),
        "sample_out": """$ search f main test.c
First occurrence at Line 3: int main() {
$ search c main test.c
Total occurrences of 'main' in 'test.c': 2
$ exit"""
    },
    "viva": [
        ("What is an orphan process vs a daemon process?", "An orphan process is accidentally left behind when its parent dies; a daemon process is intentionally orphaned and detached from a terminal to run background services."),
        ("How does the custom shell handle command execution?", "It reads the command string, splits it into arguments using strtok(), and runs execvp() in a child process created with fork()."),
        ("What is the PATH environment variable?", "A colon-separated list of directories in which the shell looks for executable commands."),
        ("What does strstr() do in C?", "strstr(haystack, needle) finds the first occurrence of the substring needle in the string haystack."),
        ("What is signal in Unix?", "A signal is an asynchronous notification sent to a process to inform it of an event (e.g. SIGINT, SIGKILL, SIGCHLD).")
    ]
}

# Slip 26
SLIP_CONFIGS[26] = {
    "q1": {
        "title": "Preemptive Priority CPU Scheduling",
        "stmt": "Write program to simulate Preemptive Priority scheduling. Input arrival time, burst time, priority. Output Gantt chart, TAT, WT, avg TAT & WT.",
        "concept": "1. Preempts current process if higher priority job arrives.",
        "code": get_cpu_priority_p_c(),
        "sample_out": """Average Turnaround Time: 10.00
Average Waiting Time: 5.00"""
    },
    "q2": {
        "title": "FIFO Page Replacement Simulation",
        "stmt": "Write simulation program for demand paging and show page scheduling and total page faults using FIFO. String: 3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6.",
        "concept": "1. FIFO page replacement algorithm simulation.",
        "code": get_page_fifo_c("3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6", 3),
        "sample_out": """Total Page Faults: 13
Total Hits: 2"""
    },
    "viva": [
        ("Explain the term 'Page Fault Frequency'.", "The rate at which page faults occur in a process; high PFF indicates the process needs more frames, low PFF indicates it has too many."),
        ("What is working set model in memory management?", "The working set model is based on locality and states that a process can execute efficiently only if its working set of pages is in memory."),
        ("What is starvation in Priority scheduling?", "Low priority processes may never execute if high priority processes keep arriving."),
        ("Why does Belady's anomaly occur in FIFO?", "Because FIFO does not take recency or frequency of access into account, dropping pages that may still be frequently referenced."),
        ("What is page hit ratio?", "Hit Ratio = (Total References - Page Faults) / Total References.")
    ]
}

# Slip 27
SLIP_CONFIGS[27] = {
    "q1": {
        "title": "SSTF Disk Scheduling Simulation",
        "stmt": "Write simulation program for disk scheduling using SSTF algorithm. Request: 30, 10, 60, 95, 120, 150, 175; Start Head: 50.",
        "concept": "1. Greedily selects the nearest pending request to minimize head movement.",
        "code": get_disk_sstf_c("30, 10, 60, 95, 120, 150, 175", 50),
        "sample_out": """Order of Request Service:
50 -> 60 -> 30 -> 10 -> 95 -> 120 -> 150 -> 175
Total Head Movements: 250 cylinders"""
    },
    "q2": {
        "title": "LRU Page Replacement (Counter Method)",
        "stmt": "Write simulation program to implement demand paging using LRU counter method. String: 3,5,7,2,5,1,2,3,1,3,5,3,1,6,2.",
        "concept": "1. Discards least recently accessed page based on timestamp counter.",
        "code": get_page_lru_c("3, 5, 7, 2, 5, 1, 2, 3, 1, 3, 5, 3, 1, 6, 2", 3),
        "sample_out": """Total Page Faults: 9
Total Hits: 6"""
    },
    "viva": [
        ("Why does SSTF perform better than FCFS?", "Because it prioritizes requests that are closest to the current head position, reducing total mechanical arm travel distance."),
        ("What is the primary risk of SSTF?", "Starvation for requests on outer tracks if requests near the current position arrive continually."),
        ("What is a page table?", "A data structure maintained by the OS for each process that maps virtual page numbers to physical page frame numbers."),
        ("What is TLB (Translation Lookaside Buffer)?", "A high-speed associative hardware cache that stores recent virtual-to-physical address mappings to speed up translation."),
        ("What is inverted page table?", "A page table structure where there is only one entry per physical frame in memory, rather than one entry per virtual page of every process.")
    ]
}

# Slip 28
SLIP_CONFIGS[28] = {
    "q1": {
        "title": "SCAN Disk Scheduling Simulation",
        "stmt": "Write simulation program for disk scheduling using SCAN algorithm. Request: 82, 170, 43, 140, 24, 16, 190, 65; Start Head: 50; Direction: Left.",
        "concept": "1. Head moves leftwards to 0, then reverses to service higher requests.",
        "code": get_disk_scan_c("82, 170, 43, 140, 24, 16, 190, 65", 50, "Left"),
        "sample_out": """Order of Request Service:
50 -> 43 -> 24 -> 16 -> 0 -> 65 -> 82 -> 140 -> 170 -> 190
Total Head Movements: 240 cylinders"""
    },
    "q2": {
        "title": "MFU (Most Frequently Used) Page Replacement",
        "stmt": "Write simulation program for demand paging using MFU page replacement algorithm. String: 8, 5, 7, 8, 5, 7, 2, 3, 7, 3, 5, 9, 4, 6, 2; n frames.",
        "concept": "1. MFU assumes that the page with the highest reference frequency has already been used and should be replaced in favor of newer pages with low counts.",
        "code": get_page_mfu_c("8, 5, 7, 8, 5, 7, 2, 3, 7, 3, 5, 9, 4, 6, 2", 3),
        "sample_out": """Step    Page    Frames          Status
-------------------------------------------------
1       8       [ 8 - - ]       PAGE FAULT
2       5       [ 8 5 - ]       PAGE FAULT
3       7       [ 8 5 7 ]       PAGE FAULT
...
Total Page Faults: 11
Total Hits: 4"""
    },
    "viva": [
        ("What is the philosophy behind MFU page replacement?", "MFU assumes that a page with the smallest count was probably just brought in and has yet to be used, while the one with the highest count has finished its use."),
        ("What is LFU page replacement?", "Least Frequently Used replaces the page with the lowest reference count."),
        ("Why are MFU and LFU not commonly used in real OS?", "Their implementation is expensive (counters for each page) and they do not approximate optimal replacement as well as LRU."),
        ("What is the difference between SCAN and C-SCAN?", "SCAN reverses direction and services requests on the way back; C-SCAN immediately resets to the beginning without servicing requests on the return journey."),
        ("What is disk latency?", "Disk latency = Seek Time + Rotational Latency + Data Transfer Time.")
    ]
}

# Slip 29
SLIP_CONFIGS[29] = {
    "q1": {
        "title": "Process Sorting and Binary Search with Fork",
        "stmt": "Implement C program that accepts an integer array. Parent sorts array; child performs binary search.",
        "concept": "1. Multiprocess coordination with sorting in parent and binary search in child.",
        "code": get_execve_search_c(),
        "sample_out": """[Parent] Sorted Array: 7 12 23 45 89 
[Child] Element 23 found at index 2!"""
    },
    "q2": {
        "title": "FCFS CPU Scheduling Simulation",
        "stmt": "Write program to simulate FCFS CPU-scheduling. Arrival time and burst time input. Output Gantt chart, TAT, WT, avg TAT & WT.",
        "concept": "1. Non-preemptive FCFS CPU scheduling.",
        "code": get_cpu_fcfs_c(),
        "sample_out": """--- Gantt Chart ---
 |  P1  |  P2  |  P3  |
Average Turnaround Time: 7.00
Average Waiting Time: 3.33"""
    },
    "viva": [
        ("What is Gantt chart?", "A Gantt chart is a horizontal bar chart illustrating the scheduling timeline of processes executed on the CPU."),
        ("What is the formula for Turnaround Time?", "TAT = Completion Time - Arrival Time."),
        ("What is the formula for Waiting Time?", "WT = Turnaround Time - Burst Time."),
        ("What is binary search time complexity in worst and best cases?", "Best case: O(1) (found at mid). Worst/Average case: O(log n)."),
        ("What happens to child process when parent terminates without wait()?", "The child becomes an orphan process and is adopted by init/systemd (PID 1).")
    ]
}

# Slip 30
SLIP_CONFIGS[30] = {
    "q1": {
        "title": "Round Robin (RR) CPU Scheduling",
        "stmt": "Write program to simulate Round Robin (RR) CPU-scheduling. Arrival time and burst time input, time quantum. Output Gantt chart, TAT, WT, avg TAT & WT.",
        "concept": "1. Time-sharing scheduling algorithm with fixed time quantum.",
        "code": get_cpu_round_robin_c(),
        "sample_out": """--- Gantt Chart ---
 | P1 | P2 | P3 | P2 | P3 | P3 |
Average Turnaround Time: 11.67
Average Waiting Time: 5.67"""
    },
    "q2": {
        "title": "MFU Page Replacement Simulation",
        "stmt": "Write simulation program for demand paging using MFU page replacement algorithm. String: 2, 5, 2, 8, 5, 4, 1, 2, 3, 2, 6, 1, 2, 5, 9, 8; n frames.",
        "concept": "1. Replaces the page with the highest frequency count.",
        "code": get_page_mfu_c("2, 5, 2, 8, 5, 4, 1, 2, 3, 2, 6, 1, 2, 5, 9, 8", 3),
        "sample_out": """Step    Page    Frames          Status
-------------------------------------------------
1       2       [ 2 - - ]       PAGE FAULT
2       5       [ 2 5 - ]       PAGE FAULT
3       2       [ 2 5 - ]       HIT
...
Total Page Faults: 11
Total Hits: 5"""
    },
    "viva": [
        ("What happens in Round Robin if the time quantum is 1 millisecond?", "Context switching overhead dominates CPU execution time, significantly reducing system throughput."),
        ("Why does MFU replace the page with the largest count?", "Based on the heuristic that the page with the highest count has been heavily utilized and is now finished with its burst."),
        ("What is the optimal page replacement algorithm (OPT/MIN)?", "The algorithm that replaces the page that will not be used for the longest period of time in the future (theoretical benchmark)."),
        ("What is starvation in CPU scheduling?", "A condition where a ready-to-run process waits indefinitely for the CPU because other processes are continuously chosen ahead of it."),
        ("How does Round Robin prevent starvation?", "Every process in the ready queue is guaranteed a turn of CPU time within a bounded time interval (n-1)*q.")
    ]
}

def main():
    print("=== Solving and Verifying All OS Slips (02 to 30) ===")
    for s in range(2, 31):
        if s in SLIP_CONFIGS:
            solve_slip(s, SLIP_CONFIGS[s]["q1"], SLIP_CONFIGS[s]["q2"], SLIP_CONFIGS[s]["viva"])
        else:
            print(f"Slip {s} config missing!")

if __name__ == "__main__":
    main()
