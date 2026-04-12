# Slip 2 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Write a C program to find the minimum and maximum values in a Binary Search Tree

**Option B:** Q1) Write a C program that accepts the vertices and edges of a graph. Create and display adjacency list also print indegree, outdegree and total degree of all vertex of graph.

---

## Option A: Finding Minimum and Maximum in BST

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

## Option B: Graph Adjacency List with Indegree/Outdegree

### Concept
An **adjacency list** represents a graph as an array of linked lists.
- Each vertex has a linked list of all vertices it connects to
- More space-efficient than adjacency matrix for sparse graphs

**Degree** concepts for directed graphs:

| Term | Meaning |
|------|---------|
| **Indegree** | Number of edges coming INTO a vertex |
| **Outdegree** | Number of edges going OUT of a vertex |
| **Total Degree** | Indegree + Outdegree |

### Data Structure
```
struct Node {
    int vertex;
    struct Node* next;
};
struct Node* adjList[MAX];  // Array of linked list heads
```

### Algorithm
### Building the Adjacency List
1. Initialize all list heads to NULL
2. For each edge (u, v):
   - Create new node with vertex v
   - Add it to the front of adjList[u]

### Calculate Degrees
1. **Outdegree of vertex v**: Count nodes in adjList[v]
2. **Indegree of vertex v**: Count how many other lists contain v
3. **Total degree** = Indegree + Outdegree

### Pseudocode
```
FUNCTION addEdge(u, v):
    CREATE new node with vertex = v
    newNode.next = adjList[u]
    adjList[u] = newNode

FUNCTION outdegree(v):
    count = 0
    temp = adjList[v]
    WHILE temp is NOT NULL:
        count = count + 1
        temp = temp.next
    RETURN count

FUNCTION indegree(v, totalVertices):
    count = 0
    FOR i = 0 TO totalVertices-1:
        temp = adjList[i]
        WHILE temp is NOT NULL:
            IF temp.vertex == v: count++
            temp = temp.next
    RETURN count
```

### Time & Space Complexity
| Operation | Complexity |
|-----------|-----------|
| Space | O(V + E) |
| Add Edge | O(1) |
| Outdegree | O(degree of v) |
| Indegree | O(V + E) |

### Worked Example
**Directed graph: edges (0→1), (0→2), (1→2), (2→0), (2→3)**

```
Adjacency List:
0 → [2] → [1]
1 → [2]
2 → [3] → [0]
3 → (empty)
```

| Vertex | Indegree | Outdegree | Total |
|--------|----------|-----------|-------|
| 0 | 1 | 2 | 3 |
| 1 | 1 | 1 | 2 |
| 2 | 2 | 2 | 4 |
| 3 | 1 | 0 | 1 |

---

> **Solution Code:** See `Slip_02_Q1_OptionA.c` and `Slip_02_Q1_OptionB.c` in this folder.
