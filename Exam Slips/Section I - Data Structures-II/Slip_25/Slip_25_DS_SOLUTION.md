# Slip 25 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Write a C program for the implementation of Dijkstra’s shortest path algorithm for finding shortest path from a given source vertex using adjacency cost matrix.

**Option B:** Q1) Implement a Binary search tree (BST) library (btree.h) with operations – create, search, insert, inorder, preorder and postorder. Write a menu driven program that performs the above operations.

---

## Option A: Dijkstra's Shortest Path Algorithm

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

## Option B: Binary Search Tree (BST) Library with Menu-Driven Program

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

> **Solution Code:** See `Slip_25_Q1_OptionA.c` and `Slip_25_Q1_OptionB.c` in this folder.
