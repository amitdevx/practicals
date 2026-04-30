# Slip 8 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Write a program to sort n randomly generated elements using Heapsort method.

**Option B:** Q1) Write a C program that accepts the vertices and edges of a graph and stores it as an adjacency matrix. Display the adjacency matrix.

---

## Option A: Heap Sort Algorithm

### Concept
**Heap Sort** uses a **binary heap** data structure to sort elements.

A **Max-Heap** property: parent ≥ children.

| Step | Action |
|------|--------|
| 1 | Build a max-heap from the array |
| 2 | Repeatedly extract max and place at end |

### Data Structure
```
int arr[MAX];  // Array to be sorted
int n;         // Number of elements
```
Array represents a complete binary tree where for index i:
- Left child: 2i + 1
- Right child: 2i + 2
- Parent: (i-1) / 2

### Algorithm
### Heapify (Maintain Heap Property)
1. Compare root with left and right children
2. If largest is not root, swap root with largest child
3. Recursively heapify the affected subtree

### Heap Sort
1. Build max-heap (heapify from last non-leaf to root)
2. For i = n-1 down to 1:
   - Swap arr[0] (max) with arr[i]
   - Heapify arr[0..i-1]

### Pseudocode
```
FUNCTION heapify(arr, n, i):
    largest = i
    left = 2*i + 1
    right = 2*i + 2
    IF left < n AND arr[left] > arr[largest]:
        largest = left
    IF right < n AND arr[right] > arr[largest]:
        largest = right
    IF largest != i:
        SWAP arr[i] and arr[largest]
        heapify(arr, n, largest)

FUNCTION heapSort(arr, n):
    // Build max heap
    FOR i = n/2 - 1 DOWN TO 0:
        heapify(arr, n, i)
    // Extract elements one by one
    FOR i = n-1 DOWN TO 1:
        SWAP arr[0] and arr[i]
        heapify(arr, i, 0)
```

### Time & Space Complexity
| Metric | Complexity |
|--------|-----------|
| Time (all cases) | O(n log n) |
| Space | O(1) - in-place |
| Stable? | No |

### Worked Example
**Sort: [4, 10, 3, 5, 1]**

| Step | Array | Action |
|------|-------|--------|
| Build Heap | [10, 5, 3, 4, 1] | Max-heap built |
| Extract 10 | [5, 4, 3, 1, **10**] | Swap & heapify |
| Extract 5 | [4, 1, 3, **5, 10**] | Swap & heapify |
| Extract 4 | [3, 1, **4, 5, 10**] | Swap & heapify |
| Extract 3 | [1, **3, 4, 5, 10**] | Sorted! |

---

## Option B: Graph Representation using Adjacency Matrix

### Concept
An **adjacency matrix** is a 2D array of size V×V (where V = number of vertices).
- `matrix[i][j] = 1` if there is an edge from vertex i to vertex j
- `matrix[i][j] = 0` if there is no edge

For undirected graphs, the matrix is **symmetric** (matrix[i][j] = matrix[j][i]).

### Data Structure
```
int adj[MAX][MAX];  // 2D array (MAX = max vertices)
int vertices, edges;
```

### Algorithm
### Building the Matrix
1. Initialize all entries to 0
2. For each edge (u, v):
   - Set `adj[u][v] = 1`
   - For undirected graph, also set `adj[v][u] = 1`

### Display the Matrix
1. Print column headers (vertex numbers)
2. For each row i:
   - Print row header (vertex number)
   - Print each value `adj[i][j]`

### Pseudocode
```
FUNCTION createGraph(vertices, edges):
    Initialize adj[V][V] to all 0s
    FOR each edge:
        READ u, v
        adj[u][v] = 1
        adj[v][u] = 1    // for undirected graph

FUNCTION displayMatrix(adj, V):
    FOR i = 0 TO V-1:
        FOR j = 0 TO V-1:
            PRINT adj[i][j]
        PRINT newline
```

### Time & Space Complexity
| Operation | Complexity |
|-----------|-----------|
| Space | O(V²) |
| Add Edge | O(1) |
| Check Edge | O(1) |
| Display | O(V²) |

### Worked Example
**Graph with 4 vertices and edges: (0,1), (0,2), (1,2), (2,3)**

```
Adjacency Matrix:
    0  1  2  3
0 [ 0  1  1  0 ]
1 [ 1  0  1  0 ]
2 [ 1  1  0  1 ]
3 [ 0  0  1  0 ]
```

---

> **Solution Code:** See `Slip_08_Q1_OptionA.c` and `Slip_08_Q1_OptionB.c` in this folder.
