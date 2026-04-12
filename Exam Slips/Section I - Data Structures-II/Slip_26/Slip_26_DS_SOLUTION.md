# Slip 26 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Write a C program that accepts the vertices and edges of a graph and store it as an adjacency matrix. Implement function to traverse the graph using Depth First Search (DFS) traversal.

**Option B:** Q1) Write a C program to find the minimum and maximum values in a Binary Search Tree.

---

## Option A: Depth First Search (DFS) using Adjacency Matrix

### Concept
Same DFS logic using **adjacency matrix** representation. Checks `adj[u][v] == 1` for all vertices to find neighbors.

### Data Structure
```
int adj[MAX][MAX];
int visited[MAX];
int stack[MAX], top;
```

### Algorithm
### DFS with Adjacency Matrix
1. Push source onto stack
2. While stack not empty:
   - Pop vertex u
   - If not visited, mark visited and print
   - Check all vertices v: if adj[u][v]==1 and not visited, push v

### Pseudocode
```
FUNCTION DFS(source):
    PUSH(source)
    WHILE stack NOT empty:
        u = POP()
        IF NOT visited[u]:
            visited[u] = TRUE
            PRINT u
            FOR v = vertices-1 DOWN TO 0:
                IF adj[u][v] == 1 AND NOT visited[v]:
                    PUSH(v)
```

### Time & Space Complexity
| Metric | Adjacency Matrix |
|--------|-----------------|
| Time | O(V²) |
| Space | O(V) |

### Worked Example
Same traversal result as adjacency list DFS, but O(V²) time due to matrix scan.

---

## Option B: Finding Minimum and Maximum in BST

### Concept
In a BST:
- The **minimum** value is always at the **leftmost** node
- The **maximum** value is always at the **rightmost** node

This is because BST property ensures smaller values go left and larger values go right.

### Data Structure
Same BST node structure with `data`, `left`, and `right` pointers.

### Algorithm
### Find Minimum
1. Start at root
2. Keep going to the left child
3. When left child is NULL, current node has minimum

### Find Maximum
1. Start at root
2. Keep going to the right child
3. When right child is NULL, current node has maximum

### Pseudocode
```
FUNCTION findMin(root):
    IF root is NULL: PRINT "Tree is empty"
    current = root
    WHILE current.left is NOT NULL:
        current = current.left
    RETURN current.data

FUNCTION findMax(root):
    IF root is NULL: PRINT "Tree is empty"
    current = root
    WHILE current.right is NOT NULL:
        current = current.right
    RETURN current.data
```

### Time & Space Complexity
| Operation | Average | Worst |
|-----------|---------|-------|
| Find Min | O(log n) | O(n) |
| Find Max | O(log n) | O(n) |

### Worked Example
```
         50
        /  \
      30    70
     / \   / \
   20  40 60  80
```
- **Minimum**: Follow left → 50 → 30 → **20**
- **Maximum**: Follow right → 50 → 70 → **80**

---

> **Solution Code:** See `Slip_26_Q1_OptionA.c` and `Slip_26_Q1_OptionB.c` in this folder.
