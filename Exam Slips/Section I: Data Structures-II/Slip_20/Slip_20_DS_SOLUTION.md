# Slip 20 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Write a C program that accepts the vertices and edges of a graph and store it as an adjacency list. Implement function to traverse the graph using Depth First Search (DFS) traversal.

**Option B:** Q1) Write a C program for the Implementation of Kruskal’s Minimum spanning tree algorithm.

---

## Option A: Depth First Search (DFS) using Adjacency List

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

> **Solution Code:** See `Slip_20_Q1_OptionA.c` and `Slip_20_Q1_OptionB.c` in this folder.
