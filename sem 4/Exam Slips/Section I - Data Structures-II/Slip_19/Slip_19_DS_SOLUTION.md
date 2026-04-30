# Slip 19 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Write a C program to maintain a phonebook using Binary Search Tree by name where each node contains contact name and phone number.

**Option B:** Q1) Write a C program that accepts the vertices and edges of a graph and store it as an adjacency list. Implement function to traverse the graph using Breadth First Search (BFS) traversal.

---

## Option A: Phonebook using Binary Search Tree

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

> **Solution Code:** See `Slip_19_Q1_OptionA.c` and `Slip_19_Q1_OptionB.c` in this folder.
