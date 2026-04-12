# Slip 1 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Implement a Binary search tree (BST) library (btree.h) with operations – create, search, insert, inorder, preorder and postorder. Write a menu driven program that performs the above operations.

**Option B:** Q1) Write a C program that accepts the vertices and edges of a graph and stores it as an adjacency matrix. Display the adjacency matrix.

---

## Option A: Binary Search Tree (BST) Library with Menu-Driven Program

### Concept
A **Binary Search Tree (BST)** is a binary tree where for each node:
- All values in the **left subtree** are **less** than the node's value
- All values in the **right subtree** are **greater** than the node's value

This property makes search, insert, and traversal operations efficient.

### Data Structure
```
struct node {
    int data;
    struct node *left, *right;
};
```
Each node stores an integer and pointers to left/right children.

### Algorithm
### Insert Operation
1. If tree is empty, create new node as root
2. If value < current node, go to left subtree
3. If value > current node, go to right subtree
4. Repeat until an empty spot is found

### Search Operation
1. Start at root
2. If value == current node's data → found
3. If value < current node → search left subtree
4. If value > current node → search right subtree
5. If node is NULL → not found

### Traversal Orders

| Traversal | Order | Use Case |
|-----------|-------|----------|
| **Inorder** | Left → Root → Right | Sorted output |
| **Preorder** | Root → Left → Right | Copy tree structure |
| **Postorder** | Left → Right → Root | Delete tree |

### Pseudocode
```
FUNCTION insert(root, value):
    IF root is NULL:
        CREATE new node with value
        RETURN new node
    IF value < root.data:
        root.left = insert(root.left, value)
    ELSE IF value > root.data:
        root.right = insert(root.right, value)
    RETURN root

FUNCTION search(root, key):
    IF root is NULL: RETURN NULL
    IF key == root.data: RETURN root
    IF key < root.data: RETURN search(root.left, key)
    RETURN search(root.right, key)

FUNCTION inorder(root):
    IF root is NOT NULL:
        inorder(root.left)
        PRINT root.data
        inorder(root.right)
```

### Time & Space Complexity
| Operation | Average Case | Worst Case |
|-----------|-------------|------------|
| Search | O(log n) | O(n) |
| Insert | O(log n) | O(n) |
| Traversal | O(n) | O(n) |

Worst case occurs when tree becomes a skewed (linked list-like) structure.

### Worked Example
**Insert sequence: 50, 30, 70, 20, 40, 60, 80**

```
         50
        /  \
      30    70
     / \   / \
   20  40 60  80
```

- **Inorder**: 20, 30, 40, 50, 60, 70, 80 (sorted!)
- **Preorder**: 50, 30, 20, 40, 70, 60, 80
- **Postorder**: 20, 40, 30, 60, 80, 70, 50

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

> **Solution Code:** See `Slip_01_Q1_OptionA.c` and `Slip_01_Q1_OptionB.c` in this folder.
