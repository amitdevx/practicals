# Slip 14 - Operating System-I

## Question 1: Binary Search with execve()

**Algorithm:**
1. Parent process accepts an array and a key to search.
2. Parent process sorts the array using Bubble Sort.
3. Parent process forks a child.
4. Child process uses `execve()` to replace its image with `Slip_14_Q1_child`, passing the sorted array and key as command-line arguments.
5. Child process performs a Binary Search and prints the result.
6. Parent waits for the child to finish.

**Compilation:**
```bash
gcc Slip_14_Q1.c -o Slip_14_Q1
gcc Slip_14_Q1_child.c -o Slip_14_Q1_child
```

**Output:**
```
$ ./Slip_14_Q1
Enter number of elements: 5
Enter array elements: 40 10 30 20 50
Enter element to search: 30
Sorted array: 10 20 30 40 50 
Child received sorted array: 10 20 30 40 50 
Element 30 found at position 3
Parent process completed.
```

---

## Question 2: Demand Paging (FIFO)

**Algorithm:**
1. Maintain a queue (`frames` array) for frames.
2. For each page in the reference string, check if it's already in the frames (Hit).
3. If not found (Fault), replace the oldest page in the frames (First In First Out) using a round-robin index `(replace_idx = (replace_idx + 1) % n)`.
4. Calculate and display total Page Faults.

**Compilation:**
```bash
gcc Slip_14_Q2.c -o Slip_14_Q2
```

---

## Question 3: Viva
- **What is `execve()`?** `execve` replaces the current process image with a new process image loaded from an executable file.
- **Why do we need `wait()`?** `wait()` is used by the parent process to suspend execution until a child process terminates, preventing zombie processes.
- **What is FIFO page replacement?** A page replacement algorithm that replaces the oldest page in memory, i.e., the page that was brought in first.
