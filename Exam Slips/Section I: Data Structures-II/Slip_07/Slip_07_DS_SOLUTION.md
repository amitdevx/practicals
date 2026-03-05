# Slip 7 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Write a C program for the implementation of Topological sorting.

**Option B:** Q1) Write a C program for the implementation of Dijkstra’s shortest path algorithm for finding shortest path from a given source vertex using adjacency cost matrix.

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

> **Solution Code:** See `Slip_07_Q1_OptionA.c` and `Slip_07_Q1_OptionB.c` in this folder.
