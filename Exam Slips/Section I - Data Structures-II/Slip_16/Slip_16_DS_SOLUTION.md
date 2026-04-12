# Slip 16 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Write a program to sort n randomly generated elements using Heapsort method.

**Option B:** Q1) Write a C program for the implementation of Dijkstra’s shortest path algorithm for finding shortest path from a given source vertex using adjacency cost matrix.

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

## Option B: Dijkstra's Shortest Path Algorithm

### Concept
Finds the **shortest path** from a source vertex to all other vertices in a graph with **non-negative** edge weights.

Uses a **greedy** approach: always processes the vertex with the smallest known distance.

### Data Structure
```
int cost[MAX][MAX];    // Adjacency cost matrix
int dist[MAX];         // Shortest distance from source
int visited[MAX];      // Processed vertices
int parent[MAX];       // For path reconstruction
```

### Algorithm
### Dijkstra's Algorithm
1. Set dist[source] = 0, all others = ∞
2. Repeat V times:
   - Pick unvisited vertex `u` with minimum dist value
   - Mark `u` as visited
   - For each neighbor `v` of `u`:
     - If dist[u] + cost[u][v] < dist[v]:
       - Update dist[v] = dist[u] + cost[u][v]
       - parent[v] = u

### Pseudocode
```
FUNCTION dijkstra(cost, source, V):
    dist[source] = 0
    FOR i = 0 TO V-1 (i != source): dist[i] = INFINITY

    FOR count = 0 TO V-1:
        u = unvisited vertex with min dist
        visited[u] = TRUE
        FOR v = 0 TO V-1:
            IF NOT visited[v] AND cost[u][v] != 0
               AND dist[u] + cost[u][v] < dist[v]:
                dist[v] = dist[u] + cost[u][v]

    PRINT dist[] for all vertices
```

### Time & Space Complexity
| Implementation | Time |
|---------------|------|
| Adjacency Matrix | O(V²) |
| Min-Heap + Adj List | O((V+E) log V) |

### Worked Example
**Graph with source = 0:**
```
     1      4
0 ------1------2
|       |      |
4       2      1
|       |      |
3 ------4------
     3
```

| Vertex | Shortest Distance from 0 |
|--------|--------------------------|
| 0 | 0 |
| 1 | 1 |
| 2 | 5 |
| 3 | 4 |
| 4 | 3 |

---

> **Solution Code:** See `Slip_16_Q1_OptionA.c` and `Slip_16_Q1_OptionB.c` in this folder.
