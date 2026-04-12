# Slip 21 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Write a C program for the implementation of Topological sorting.

**Option B:** Q1) Write a C program to implement a hash table using open addressing with linear probing. perform the following operations.( Assume all keys are positive integers) Insert Search Display

---

## Option A: Topological Sorting of a Directed Acyclic Graph (DAG)

### Concept
**Topological sort** gives a linear ordering of vertices such that for every directed edge (u, v), vertex u comes before v.

- Only works on **DAGs** (Directed Acyclic Graphs)
- Used for: task scheduling, build systems, course prerequisites

### Data Structure
```
int adj[MAX][MAX];    // Adjacency matrix
int indegree[MAX];    // Indegree of each vertex
int queue[MAX];       // Queue for processing
```

### Algorithm
### Kahn's Algorithm (BFS-based)
1. Calculate indegree of all vertices
2. Enqueue all vertices with indegree 0
3. While queue is not empty:
   - Dequeue vertex u, add to result
   - For each neighbor v of u:
     - Reduce indegree[v] by 1
     - If indegree[v] becomes 0, enqueue v
4. If result has all vertices → valid topological order
   Otherwise → graph has a cycle

### Pseudocode
```
FUNCTION topologicalSort(adj, V):
    Calculate indegree[] for all vertices
    FOR i = 0 TO V-1:
        IF indegree[i] == 0: ENQUEUE(i)

    count = 0
    WHILE queue NOT empty:
        u = DEQUEUE()
        PRINT u
        count++
        FOR v = 0 TO V-1:
            IF adj[u][v] == 1:
                indegree[v]--
                IF indegree[v] == 0: ENQUEUE(v)

    IF count != V: PRINT "Cycle detected!"
```

### Time & Space Complexity
| Metric | Complexity |
|--------|-----------|
| Time | O(V + E) |
| Space | O(V) |

### Worked Example
**DAG:** 5→0, 5→2, 4→0, 4→1, 2→3, 3→1

```
5 → 0
5 → 2 → 3 → 1
4 → 0
4 → 1
```

**One valid topological order:** 4, 5, 2, 0, 3, 1

---

## Option B: Hash Table with Linear Probing (Open Addressing)

### Concept
**Linear probing** handles collisions by checking the next slot sequentially.

If slot `h(key)` is occupied, try `h(key)+1`, `h(key)+2`, ... (wrapping around).

| Term | Meaning |
|------|---------|
| **Open Addressing** | All elements stored in the table itself |
| **Linear Probing** | Probe sequence: h(k), h(k)+1, h(k)+2, ... |
| **Load Factor** | n / TABLE_SIZE (should be < 0.7) |

### Data Structure
```
int hashTable[TABLE_SIZE];
// -1 indicates empty slot
Hash function: h(key) = key % TABLE_SIZE
```

### Algorithm
### Insert
1. index = key % TABLE_SIZE
2. If hashTable[index] is empty, insert key
3. Else, try (index+1) % TABLE_SIZE, (index+2) % TABLE_SIZE, ...
4. Stop when empty slot found or table is full

### Search
1. index = key % TABLE_SIZE
2. Check hashTable[index]; if match, found
3. Else, check next slots linearly
4. Stop when key found, empty slot reached, or full cycle

### Pseudocode
```
FUNCTION insert(key):
    index = key % TABLE_SIZE
    i = 0
    WHILE hashTable[(index + i) % TABLE_SIZE] != -1:
        i = i + 1
        IF i == TABLE_SIZE: PRINT "Table Full"; RETURN
    hashTable[(index + i) % TABLE_SIZE] = key

FUNCTION search(key):
    index = key % TABLE_SIZE
    i = 0
    WHILE hashTable[(index + i) % TABLE_SIZE] != key:
        IF hashTable[(index + i) % TABLE_SIZE] == -1:
            RETURN "Not Found"
        i = i + 1
        IF i == TABLE_SIZE: RETURN "Not Found"
    RETURN "Found at index (index + i) % TABLE_SIZE"
```

### Time & Space Complexity
| Operation | Average | Worst |
|-----------|---------|-------|
| Insert | O(1/(1-α)) | O(n) |
| Search | O(1/(1-α)) | O(n) |

**Clustering problem**: consecutive occupied slots form clusters, degrading performance.

### Worked Example
**TABLE_SIZE = 7, Insert: 10, 20, 15, 7, 22**

| Key | h(key) | Actual Index | Reason |
|-----|--------|-------------|--------|
| 10 | 3 | 3 | Empty |
| 20 | 6 | 6 | Empty |
| 15 | 1 | 1 | Empty |
| 7 | 0 | 0 | Empty |
| 22 | 1 | 2 | Collision at 1, probe to 2 |

---

> **Solution Code:** See `Slip_21_Q1_OptionA.c` and `Slip_21_Q1_OptionB.c` in this folder.
