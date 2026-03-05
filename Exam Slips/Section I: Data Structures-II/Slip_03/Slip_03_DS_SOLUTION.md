# Slip 3 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Write a C program that accepts the vertices and edges of a graph and store it as an adjacency matrix. Implement function to traverse the graph using Breadth First Search (BFS) traversal.

**Option B:** Q1) Write a C program to find the height of the tree and check whether given tree is balanced or not.

---

## Option A: Breadth First Search (BFS) using Adjacency Matrix

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

## Option B: BST Height and Balance Check

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

> **Solution Code:** See `Slip_03_Q1_OptionA.c` and `Slip_03_Q1_OptionB.c` in this folder.
