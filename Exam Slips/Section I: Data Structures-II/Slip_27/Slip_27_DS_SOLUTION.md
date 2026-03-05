# Slip 27 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Write a C program for the Implementation of Prim’s Minimum spanning tree algorithm.

**Option B:** Q1) Write a C program that accepts the vertices and edges of a graph and store it as an adjacency matrix. Implement function to traverse the graph using Breadth First Search (BFS) traversal.

---

## Option A: Prim's Minimum Spanning Tree Algorithm

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

## Option B: Breadth First Search (BFS) using Adjacency Matrix

### Concept
**BFS** explores a graph level by level using a **queue**.
- Visit the starting vertex first
- Then visit all its neighbors
- Then visit neighbors of neighbors, and so on

BFS is useful for finding **shortest path** in unweighted graphs.

### Data Structure
```
int adj[MAX][MAX];   // Adjacency matrix
int visited[MAX];    // Track visited vertices
int queue[MAX];      // Queue for BFS
int front, rear;     // Queue pointers
```

### Algorithm
### BFS Algorithm
1. Mark source vertex as visited, enqueue it
2. While queue is not empty:
   - Dequeue a vertex `u`
   - Print `u`
   - For each neighbor `v` of `u` (check adj[u][v] == 1):
     - If `v` is not visited:
       - Mark `v` as visited
       - Enqueue `v`

### Pseudocode
```
FUNCTION BFS(source):
    Initialize visited[] to all FALSE
    CREATE empty queue
    visited[source] = TRUE
    ENQUEUE(source)

    WHILE queue is NOT empty:
        u = DEQUEUE()
        PRINT u
        FOR v = 0 TO vertices-1:
            IF adj[u][v] == 1 AND visited[v] == FALSE:
                visited[v] = TRUE
                ENQUEUE(v)
```

### Time & Space Complexity
| Metric | Adjacency Matrix |
|--------|-----------------|
| Time | O(V²) |
| Space | O(V) for queue |

### Worked Example
**Graph**: 0-1, 0-2, 1-3, 2-3, 3-4. **Start: 0**

```
Level 0: [0]
Level 1: [1, 2]
Level 2: [3]
Level 3: [4]

BFS Order: 0 → 1 → 2 → 3 → 4
```

---

> **Solution Code:** See `Slip_27_Q1_OptionA.c` and `Slip_27_Q1_OptionB.c` in this folder.
