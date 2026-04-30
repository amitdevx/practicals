# Slip 24 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Write a C program for the implementation of Floyd Warshall’s algorithm for finding all pairs shortest path using adjacency cost matrix.

**Option B:** Q1) Write a C program to maintain a phonebook using Binary Search Tree by name where each node contains contact name and phone number.

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

## Option B: Phonebook using Binary Search Tree

### Concept
A phonebook implemented using BST where:
- Each node stores a **name** and **phone number**
- Nodes are ordered **alphabetically by name** (using strcmp)
- Supports: insert, search by name, display all contacts

### Data Structure
```
struct PhoneNode {
    char name[50];
    char phone[15];
    struct PhoneNode *left, *right;
};
```

### Algorithm
### Insert Contact
1. Compare name with current node (using strcmp)
2. If name < current → go left
3. If name > current → go right
4. Insert at NULL position

### Search Contact
1. Compare search name with current node
2. Navigate left/right based on comparison
3. Return phone number if found

### Display (Inorder)
- Inorder traversal gives contacts in **alphabetical order**

### Pseudocode
```
FUNCTION insertContact(root, name, phone):
    IF root is NULL:
        CREATE node with name, phone
        RETURN new node
    cmp = strcmp(name, root.name)
    IF cmp < 0:
        root.left = insertContact(root.left, name, phone)
    ELSE IF cmp > 0:
        root.right = insertContact(root.right, name, phone)
    RETURN root

FUNCTION searchContact(root, name):
    IF root is NULL: PRINT "Not found"; RETURN
    cmp = strcmp(name, root.name)
    IF cmp == 0: PRINT root.phone
    ELSE IF cmp < 0: searchContact(root.left, name)
    ELSE: searchContact(root.right, name)
```

### Time & Space Complexity
| Operation | Average | Worst |
|-----------|---------|-------|
| Insert | O(log n) | O(n) |
| Search | O(log n) | O(n) |
| Display all | O(n) | O(n) |

### Worked Example
**Insert: (Charlie, 333), (Alice, 111), (Bob, 222), (David, 444)**

```
       Charlie(333)
      /             \
 Alice(111)     David(444)
      \
   Bob(222)
```
**Inorder (alphabetical):** Alice→Bob→Charlie→David

---

> **Solution Code:** See `Slip_24_Q1_OptionA.c` and `Slip_24_Q1_OptionB.c` in this folder.
