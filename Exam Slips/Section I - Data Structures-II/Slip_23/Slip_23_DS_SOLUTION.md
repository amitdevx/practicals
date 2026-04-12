# Slip 23 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Write a C program to find the height of the tree and check whether given tree is balanced or not.

**Option B:** Q1) Write a C program for the implementation of Topological sorting.

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

## Option B: Topological Sorting of a Directed Acyclic Graph (DAG)

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

> **Solution Code:** See `Slip_23_Q1_OptionA.c` and `Slip_23_Q1_OptionB.c` in this folder.
