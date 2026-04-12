# Slip 29 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Write a program to sort n randomly generated elements using Heapsort method.

**Option B:** Q1) Write a C program for the Implementation of Kruskal’s Minimum spanning tree algorithm.

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

## Option B: Kruskal's Minimum Spanning Tree Algorithm

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

> **Solution Code:** See `Slip_29_Q1_OptionA.c` and `Slip_29_Q1_OptionB.c` in this folder.
