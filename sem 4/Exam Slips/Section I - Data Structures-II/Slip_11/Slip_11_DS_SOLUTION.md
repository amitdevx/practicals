# Slip 11 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Write a program which uses binary search tree library and counts the total nodes and total leaf nodes in the tree. int count(T) – returns the total number of nodes from BST int countLeaf(T) – returns the total number of leaf nodes from BST

**Option B:** Q1) Write a C program that accepts the vertices and edges of a graph and store it as an adjacency list. Implement function to traverse the graph using Breadth First Search (BFS) traversal.

---

## Option A: BST Count Total Nodes and Leaf Nodes

### Concept
- **Total nodes**: Count of all nodes in the BST
- **Leaf nodes**: Nodes with **no children** (both left and right are NULL)

### Data Structure
Uses BST from btree.h library.

### Algorithm
### Count All Nodes
1. If node is NULL, return 0
2. Return 1 + count(left) + count(right)

### Count Leaf Nodes
1. If node is NULL, return 0
2. If both children are NULL, return 1 (it's a leaf)
3. Return countLeaf(left) + countLeaf(right)

### Pseudocode
```
FUNCTION count(root):
    IF root is NULL: RETURN 0
    RETURN 1 + count(root.left) + count(root.right)

FUNCTION countLeaf(root):
    IF root is NULL: RETURN 0
    IF root.left is NULL AND root.right is NULL:
        RETURN 1
    RETURN countLeaf(root.left) + countLeaf(root.right)
```

### Time & Space Complexity
Both operations: **O(n)** time, **O(h)** space (recursion stack).

### Worked Example
```
      50
     /  \
   30    70
  / \     \
20   40    80
```
- **Total nodes**: 6
- **Leaf nodes**: 20, 40, 80 → **3 leaves**

---

## Option B: Breadth First Search (BFS) using Adjacency List

### Concept
Same BFS algorithm but using **adjacency list** representation.
More efficient for **sparse graphs** since we only iterate over actual neighbors.

### Data Structure
```
struct Node { int vertex; struct Node* next; };
struct Node* adjList[MAX];
int visited[MAX];
int queue[MAX], front, rear;
```

### Algorithm
### BFS with Adjacency List
1. Mark source as visited, enqueue
2. While queue not empty:
   - Dequeue vertex u
   - Traverse adjacency list of u
   - For each unvisited neighbor, mark visited and enqueue

### Pseudocode
```
FUNCTION BFS(source):
    visited[source] = TRUE
    ENQUEUE(source)
    WHILE queue NOT empty:
        u = DEQUEUE()
        PRINT u
        temp = adjList[u]
        WHILE temp is NOT NULL:
            v = temp.vertex
            IF visited[v] == FALSE:
                visited[v] = TRUE
                ENQUEUE(v)
            temp = temp.next
```

### Time & Space Complexity
| Metric | Adjacency List |
|--------|---------------|
| Time | O(V + E) |
| Space | O(V) |

### Worked Example
**Same result as matrix version, but faster for sparse graphs.**

BFS from vertex 0: **0 → 1 → 2 → 3 → 4**

---

> **Solution Code:** See `Slip_11_Q1_OptionA.c` and `Slip_11_Q1_OptionB.c` in this folder.
