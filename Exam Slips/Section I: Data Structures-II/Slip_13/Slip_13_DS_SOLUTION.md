# Slip 13 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Write a C program to implement a hash table using separate chaining with linked lists with following operation. a. Insert a key b. Search a key c. Display the hash table

**Option B:** Q1) Write a C program that accepts the vertices and edges of a graph. Create and display adjacency list also print indegree, outdegree and total degree of all vertex of graph.

---

## Option A: Hash Table with Separate Chaining

### Concept
**Separate chaining** handles hash collisions by maintaining a **linked list** at each hash table slot.

Multiple keys that hash to the same index are stored in a linked list at that index.

### Data Structure
```
struct Node { int key; struct Node* next; };
struct Node* hashTable[TABLE_SIZE];
Hash function: h(key) = key % TABLE_SIZE
```

### Algorithm
### Insert
1. Calculate index = key % TABLE_SIZE
2. Create new node, insert at head of list at hashTable[index]

### Search
1. Calculate index = key % TABLE_SIZE
2. Traverse linked list at hashTable[index]
3. If key found → return success; if end reached → not found

### Display
1. For each slot, traverse and print the linked list

### Pseudocode
```
FUNCTION insert(key):
    index = key % TABLE_SIZE
    CREATE new node with key
    newNode.next = hashTable[index]
    hashTable[index] = newNode

FUNCTION search(key):
    index = key % TABLE_SIZE
    temp = hashTable[index]
    WHILE temp is NOT NULL:
        IF temp.key == key: RETURN "Found"
        temp = temp.next
    RETURN "Not Found"
```

### Time & Space Complexity
| Operation | Average | Worst |
|-----------|---------|-------|
| Insert | O(1) | O(1) |
| Search | O(1 + α) | O(n) |
| Delete | O(1 + α) | O(n) |

Where α = n/TABLE_SIZE (load factor)

### Worked Example
**TABLE_SIZE = 7, Insert: 10, 20, 15, 7, 22, 17**

| Index | Chain |
|-------|-------|
| 0 | 7 → 21 |
| 1 | 22 → 15 |
| 2 | (empty) |
| 3 | 10 → 17 |
| 4 | (empty) |
| 5 | (empty) |
| 6 | 20 |

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

> **Solution Code:** See `Slip_13_Q1_OptionA.c` and `Slip_13_Q1_OptionB.c` in this folder.
