# Slip 10 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Write a C program for the implementation of Floyd Warshall’s algorithm for finding all pairs shortest path using adjacency cost matrix.

**Option B:** Q1) Write a C program to find the minimum and maximum values in a Binary Search Tree.

---

## Option A: Floyd-Warshall All-Pairs Shortest Path Algorithm

### Concept
Finds shortest paths between **all pairs** of vertices simultaneously.

Works with **negative weights** (but not negative cycles).

Uses **dynamic programming**: for each intermediate vertex k, check if path through k is shorter.

### Data Structure
```
int dist[MAX][MAX];  // Distance matrix
// dist[i][j] = weight of edge (i,j), or INF if no edge
// dist[i][i] = 0
```

### Algorithm
### Floyd-Warshall Algorithm
For each intermediate vertex k (0 to V-1):
  For each source i (0 to V-1):
    For each destination j (0 to V-1):
      If dist[i][k] + dist[k][j] < dist[i][j]:
        dist[i][j] = dist[i][k] + dist[k][j]

Three nested loops — simple but powerful!

### Pseudocode
```
FUNCTION floydWarshall(dist, V):
    // dist[][] initialized with edge weights, INF for no edge

    FOR k = 0 TO V-1:
        FOR i = 0 TO V-1:
            FOR j = 0 TO V-1:
                IF dist[i][k] + dist[k][j] < dist[i][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]

    PRINT dist[][] matrix
```

### Time & Space Complexity
| Metric | Complexity |
|--------|-----------|
| Time | O(V³) |
| Space | O(V²) |

### Worked Example
**Initial Distance Matrix:**
```
     0    1    2    3
0 [  0    3    INF  7  ]
1 [  8    0    2    INF]
2 [  5    INF  0    1  ]
3 [  2    INF  INF  0  ]
```

**After Floyd-Warshall:**
```
     0    1    2    3
0 [  0    3    5    6  ]
1 [  5    0    2    3  ]
2 [  3    6    0    1  ]
3 [  2    5    7    0  ]
```

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

> **Solution Code:** See `Slip_10_Q1_OptionA.c` and `Slip_10_Q1_OptionB.c` in this folder.
