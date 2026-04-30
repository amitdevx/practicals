# Slip 12 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Write a program to implement various types of hash functions which are used to place the data in a hash table a. Division Method b. Mid Square Method c. Digit Folding Method Accept n values from the user and display appropriate message in case of collision for each of the above functions.

**Option B:** Q1) Write a C program that accepts the vertices and edges of a graph and store it as an adjacency list. Implement function to traverse the graph using Depth First Search (DFS) traversal.

---

## Option A: Hash Function Types: Division, Mid-Square, Digit Folding

### Concept
Three common hash functions to map keys to table indices:

| Method | Formula |
|--------|---------|
| **Division** | h(k) = k mod TABLE_SIZE |
| **Mid-Square** | Square the key, extract middle digits |
| **Digit Folding** | Split key into parts, sum them |

### Data Structure
```
int hashTable[TABLE_SIZE];
```

### Algorithm
### 1. Division Method
- h(k) = k % TABLE_SIZE
- Simple and fast
- TABLE_SIZE should be prime

### 2. Mid-Square Method
- Square the key: k²
- Extract middle digit(s)
- Use middle digit(s) as hash index

### 3. Digit Folding Method
- Split the key into equal-sized parts
- Sum all parts
- hash = sum % TABLE_SIZE

### Pseudocode
```
FUNCTION divisionHash(key, size):
    RETURN key % size

FUNCTION midSquareHash(key, size):
    square = key * key
    // Extract middle digit
    middle = (square / 10) % 10
    RETURN middle % size

FUNCTION foldingHash(key, size):
    sum = 0
    WHILE key > 0:
        sum = sum + (key % 100)  // Take 2 digits
        key = key / 100
    RETURN sum % size
```

### Time & Space Complexity
All three: **O(1)** time per hash computation.

### Worked Example
**Key = 1234, TABLE_SIZE = 10**

| Method | Calculation | Result |
|--------|-------------|--------|
| Division | 1234 % 10 | **4** |
| Mid-Square | 1234² = 1522756, middle = 2 | **2** |
| Folding | 12 + 34 = 46, 46 % 10 | **6** |

---

## Option B: Depth First Search (DFS) using Adjacency List

### Concept
**DFS** explores as far as possible along each branch before backtracking.
- Uses a **stack** (or recursion which uses the call stack)
- Goes deep first before going wide
- Useful for detecting cycles, topological sorting, connected components

### Data Structure
```
struct Node { int vertex; struct Node* next; };
struct Node* adjList[MAX];
int visited[MAX];
int stack[MAX], top;  // For iterative version
```

### Algorithm
### DFS Algorithm (Iterative with Stack)
1. Push source vertex onto stack
2. While stack is not empty:
   - Pop a vertex `u`
   - If `u` is not visited:
     - Mark `u` as visited, print it
     - Push all unvisited neighbors of `u` onto stack

### Pseudocode
```
FUNCTION DFS(source):
    Initialize visited[] to all FALSE
    PUSH(source)
    WHILE stack NOT empty:
        u = POP()
        IF visited[u] == FALSE:
            visited[u] = TRUE
            PRINT u
            FOR each neighbor v of u (via adjList):
                IF visited[v] == FALSE:
                    PUSH(v)
```

### Time & Space Complexity
| Metric | Adjacency List |
|--------|---------------|
| Time | O(V + E) |
| Space | O(V) |

### Worked Example
**Graph**: 0-1, 0-2, 1-3, 2-3, 3-4. **Start: 0**

```
DFS Order: 0 → 2 → 3 → 4 → 1
(order may vary based on adjacency list order)
```

---

> **Solution Code:** See `Slip_12_Q1_OptionA.c` and `Slip_12_Q1_OptionB.c` in this folder.
