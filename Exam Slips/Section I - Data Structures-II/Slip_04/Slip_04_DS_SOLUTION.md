# Slip 4 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Write a C program to find the height of the tree and check whether given tree is balanced or not.

**Option B:** Q1) Write a C program that accepts the vertices and edges of a graph and store it as an adjacency list. Implement function to traverse the graph using Depth First Search (DFS) traversal.

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

## Option B: Depth First Search (DFS) using Adjacency List

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

> **Solution Code:** See `Slip_04_Q1_OptionA.c` and `Slip_04_Q1_OptionB.c` in this folder.
