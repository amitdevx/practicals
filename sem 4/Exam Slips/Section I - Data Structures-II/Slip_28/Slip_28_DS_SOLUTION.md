# Slip 28 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Write a C program to implement a hash table using Open Addressing with Quadratic Probing. Perform the following operations. (Assume all keys are positive integers) a. Insert b. Delete c. Display

**Option B:** Q1) Write a C program for the Implementation of Prim’s Minimum spanning tree algorithm.

---

## Option A: Hash Table with Quadratic Probing (Insert, Delete, Display)

### Concept
Same as quadratic probing but with **delete** operation.

Deletion in open addressing requires special handling — use a **DELETED marker** (-2) instead of marking slot empty, otherwise search chains break.

### Data Structure
```
int hashTable[TABLE_SIZE];
// -1 = empty, -2 = deleted
```

### Algorithm
### Delete
1. Search for the key using quadratic probing
2. If found, replace with DELETED marker (-2)
3. DELETED slots can be reused for insertion
4. Search treats DELETED slots as occupied (continues probing)

### Pseudocode
```
FUNCTION delete(key):
    index = key % TABLE_SIZE
    i = 0
    WHILE hashTable[(index + i*i) % TABLE_SIZE] != key:
        IF hashTable[(index + i*i) % TABLE_SIZE] == -1:
            PRINT "Key not found"; RETURN
        i++
    hashTable[(index + i*i) % TABLE_SIZE] = -2  // DELETED
    PRINT "Key deleted"
```

### Time & Space Complexity
Same as quadratic probing search: O(1/(1-α)) average.

### Worked Example
After deleting key 17 from index 4:

| Index | Value | Status |
|-------|-------|--------|
| 0 | 24 | Occupied |
| 1 | 15 | Occupied |
| 3 | 10 | Occupied |
| 4 | -2 | DELETED |

---

## Option B: Prim's Minimum Spanning Tree Algorithm

### Concept
A **Minimum Spanning Tree (MST)** connects all vertices with minimum total edge weight.

**Prim's Algorithm** grows the MST one vertex at a time:
- Start from any vertex
- Always add the cheapest edge connecting MST to a non-MST vertex

### Data Structure
```
int cost[MAX][MAX];   // Adjacency cost matrix (0 or INF for no edge)
int visited[MAX];     // Track vertices in MST
int key[MAX];         // Minimum weight edge to each vertex
int parent[MAX];      // Parent of each vertex in MST
```

### Algorithm
### Prim's Algorithm
1. Initialize: key[0] = 0, all others = ∞, parent[0] = -1
2. Repeat V times:
   - Pick vertex `u` with minimum key value (not yet in MST)
   - Add `u` to MST (mark visited)
   - Update key values of all adjacent vertices of `u`:
     - If cost[u][v] < key[v], update key[v] and parent[v]

### Pseudocode
```
FUNCTION prims(cost, V):
    key[0] = 0, parent[0] = -1
    FOR i = 1 TO V-1: key[i] = INFINITY

    FOR count = 0 TO V-1:
        u = vertex with minimum key, not in MST
        visited[u] = TRUE
        FOR v = 0 TO V-1:
            IF cost[u][v] != 0 AND NOT visited[v]
               AND cost[u][v] < key[v]:
                key[v] = cost[u][v]
                parent[v] = u

    PRINT MST edges using parent[]
```

### Time & Space Complexity
| Implementation | Time Complexity |
|---------------|----------------|
| Adjacency Matrix | O(V²) |
| Binary Heap + Adj List | O(E log V) |

### Worked Example
**Graph:**
```
    2     3
0 ---- 1 ---- 2
|      |      |
6      8      5
|      |      |
3 ---- 4 ---- 5
    9     7
```

**MST Edges:** (0-1, wt=2), (1-2, wt=3), (0-3, wt=6), (2-5, wt=5), (3-4, wt=9)
**Total Weight:** 25

---

> **Solution Code:** See `Slip_28_Q1_OptionA.c` and `Slip_28_Q1_OptionB.c` in this folder.
