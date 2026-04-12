# Slip 18 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Write a C program to find the height of the tree and check whether given tree is balanced or not.

**Option B:** Q1) Write a C program that accepts the vertices and edges of a graph and stores it as an adjacency matrix. Display the adjacency matrix.

---

## Option A: BST Height and Balance Check

### Concept
**Height** of a tree is the number of edges on the longest path from root to a leaf.

A tree is **balanced** if for every node, the height difference between left and right subtrees is at most 1.

| Tree Type | Height |
|-----------|--------|
| Balanced BST | O(log n) |
| Skewed BST | O(n) |

### Data Structure
Uses BST node structure from btree.h library.

### Algorithm
### Height Calculation (Recursive)
1. If node is NULL, return -1 (or 0 depending on convention)
2. Left height = height(left subtree)
3. Right height = height(right subtree)
4. Return max(left_height, right_height) + 1

### Balance Check
1. For each node, calculate left and right heights
2. If |left_height - right_height| > 1 → NOT balanced
3. Also recursively check if left and right subtrees are balanced

### Pseudocode
```
FUNCTION height(root):
    IF root is NULL: RETURN -1
    leftH = height(root.left)
    rightH = height(root.right)
    RETURN max(leftH, rightH) + 1

FUNCTION isBalanced(root):
    IF root is NULL: RETURN TRUE
    leftH = height(root.left)
    rightH = height(root.right)
    IF |leftH - rightH| > 1: RETURN FALSE
    RETURN isBalanced(root.left) AND isBalanced(root.right)
```

### Time & Space Complexity
| Operation | Complexity |
|-----------|-----------|
| Height | O(n) |
| Balance Check | O(n²) naive, O(n) optimized |

### Worked Example
**Balanced Tree:**
```
      50
     /  \
   30    70
  / \
20   40
```
Height = 2, |left_h - right_h| = |1 - 0| = 1 ≤ 1 → **Balanced**

**Unbalanced Tree:**
```
    50
   /
  30
 /
20
```
Height = 2, |left_h - right_h| = |2 - (-1)| = 3 > 1 → **NOT Balanced**

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

> **Solution Code:** See `Slip_18_Q1_OptionA.c` and `Slip_18_Q1_OptionB.c` in this folder.
