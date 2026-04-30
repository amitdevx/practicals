# Slip 6 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Write a C program for the Implementation of Kruskal’s Minimum spanning tree algorithm.

**Option B:** Q1) Write a C program which uses Binary search tree library and implements following function with recursion: int copy(T) – create another BST which is exact copy of BST which is passed as parameter. int compare(T1, T2) – compares two binary search trees and returns 1 if they are equal and 0 otherwise.

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

## Option B: BST Copy and Compare Operations

### Concept
- **Copy**: Create an exact duplicate of a BST using recursion
- **Compare**: Check if two BSTs are structurally identical with same values

### Data Structure
Uses BST from btree.h library.

### Algorithm
### Copy (Recursive)
1. If node is NULL, return NULL
2. Create new node with same data
3. Recursively copy left subtree
4. Recursively copy right subtree

### Compare (Recursive)
1. If both are NULL → equal (return 1)
2. If one is NULL and other isn't → not equal (return 0)
3. Compare data, then recursively compare left and right subtrees

### Pseudocode
```
FUNCTION copy(root):
    IF root is NULL: RETURN NULL
    newNode = CREATE node(root.data)
    newNode.left = copy(root.left)
    newNode.right = copy(root.right)
    RETURN newNode

FUNCTION compare(T1, T2):
    IF T1 is NULL AND T2 is NULL: RETURN 1
    IF T1 is NULL OR T2 is NULL: RETURN 0
    RETURN (T1.data == T2.data)
       AND compare(T1.left, T2.left)
       AND compare(T1.right, T2.right)
```

### Time & Space Complexity
| Operation | Complexity |
|-----------|-----------|
| Copy | O(n) |
| Compare | O(n) |

### Worked Example
**Original Tree:**
```
    50
   / \
  30  70
```
**After Copy:** Identical tree at different memory location.
**Compare(original, copy)** → Returns **1** (equal)

---

> **Solution Code:** See `Slip_06_Q1_OptionA.c` and `Slip_06_Q1_OptionB.c` in this folder.
