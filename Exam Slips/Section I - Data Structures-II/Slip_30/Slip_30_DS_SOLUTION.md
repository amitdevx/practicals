# Slip 30 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Write a C program for the Implementation of Kruskal’s Minimum spanning tree algorithm.

**Option B:** Q1) Write a C program to implement a hash table using open addressing with linear probing. perform the following operations. (Assume all keys are positive integers) a.Insert b.Search c.Display

---

## Option A: Kruskal's Minimum Spanning Tree Algorithm

### Concept
**Kruskal's Algorithm** builds MST by adding edges in order of increasing weight, skipping edges that would create a cycle.

Uses **Union-Find (Disjoint Set)** to efficiently detect cycles.

### Data Structure
```
struct Edge {
    int src, dest, weight;
};
int parent[MAX];  // Union-Find parent array
```

### Algorithm
### Kruskal's Algorithm
1. Sort all edges by weight (ascending)
2. Initialize Union-Find: each vertex is its own parent
3. For each edge (in sorted order):
   - Find sets of both endpoints (using Find)
   - If they are in different sets:
     - Add edge to MST
     - Union the two sets
   - Stop when MST has V-1 edges

### Union-Find Operations
- **Find(x)**: Follow parent pointers to find root of x's set
- **Union(x, y)**: Make root of one set point to root of other

### Pseudocode
```
FUNCTION find(parent, i):
    WHILE parent[i] != i:
        i = parent[i]
    RETURN i

FUNCTION union(parent, x, y):
    xroot = find(parent, x)
    yroot = find(parent, y)
    parent[xroot] = yroot

FUNCTION kruskal(edges, V, E):
    SORT edges by weight
    FOR i = 0 TO V-1: parent[i] = i
    mstEdges = 0, idx = 0
    WHILE mstEdges < V-1:
        edge = edges[idx]
        x = find(parent, edge.src)
        y = find(parent, edge.dest)
        IF x != y:
            ADD edge to MST
            union(parent, x, y)
            mstEdges++
        idx++
```

### Time & Space Complexity
| Operation | Complexity |
|-----------|-----------|
| Sorting edges | O(E log E) |
| Union-Find | O(E × α(V)) ≈ O(E) |
| **Total** | **O(E log E)** |

### Worked Example
**Edges sorted:** (A-B,1), (B-C,2), (A-C,3), (B-D,4), (C-D,5)

| Step | Edge | Weight | Action |
|------|------|--------|--------|
| 1 | A-B | 1 | Add (different sets) |
| 2 | B-C | 2 | Add (different sets) |
| 3 | A-C | 3 | Skip (same set - cycle!) |
| 4 | B-D | 4 | Add (different sets) |

**MST Weight:** 1 + 2 + 4 = 7

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

> **Solution Code:** See `Slip_30_Q1_OptionA.c` and `Slip_30_Q1_OptionB.c` in this folder.
