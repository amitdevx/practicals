# Slip 5 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Write a C program which uses Binary search tree library and display the following i. ii. iii. Node value at each level Count of node at each level Total levels in the tree.

**Option B:** Q1) Write a C program for the Implementation of Prim’s Minimum spanning tree algorithm.

---

## Option A: BST Level-wise Display

### Concept
Display node values at each level of the BST using BFS-like level-order traversal.
Also count nodes at each level and total number of levels.

### Data Structure
Uses BST from btree.h + a queue for level-order traversal.

### Algorithm
### Level-wise Traversal
1. Use a queue, start with root
2. For each level:
   - Count nodes currently in queue (= nodes at this level)
   - Process all nodes at this level
   - Enqueue their children for next level
3. Track level number and node count

### Pseudocode
```
FUNCTION levelWise(root):
    IF root is NULL: RETURN
    ENQUEUE(root)
    level = 0
    WHILE queue NOT empty:
        count = size of queue
        PRINT "Level", level, ":"
        FOR i = 1 TO count:
            node = DEQUEUE()
            PRINT node.data
            IF node.left: ENQUEUE(node.left)
            IF node.right: ENQUEUE(node.right)
        PRINT "Count:", count
        level = level + 1
    PRINT "Total levels:", level
```

### Time & Space Complexity
| Operation | Complexity |
|-----------|-----------|
| Time | O(n) |
| Space | O(n) for queue |

### Worked Example
```
      50
     /  \
   30    70
  / \   / \
20  40 60  80
```
```
Level 0: 50       (Count: 1)
Level 1: 30 70    (Count: 2)
Level 2: 20 40 60 80  (Count: 4)
Total levels: 3
```

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

> **Solution Code:** See `Slip_05_Q1_OptionA.c` and `Slip_05_Q1_OptionB.c` in this folder.
