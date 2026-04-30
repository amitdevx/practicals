# Slip 22 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Write a C program to implement a hash table using Open Addressing with Quadratic Probing. Perform the following operations. (Assume all keys are positive integers) a. Insert b. Search c. Display

**Option B:** Q1) Write a C program that accepts the vertices and edges of a graph and stores it as an adjacency matrix. Display the adjacency matrix.

---

## Option A: Hash Table with Quadratic Probing (Open Addressing)

### Concept
**Quadratic probing** handles collisions by checking slots at quadratic intervals.

Probe sequence: h(k), h(k)+1², h(k)+2², h(k)+3², ...

This reduces the **primary clustering** problem of linear probing.

### Data Structure
```
int hashTable[TABLE_SIZE];
// -1 indicates empty slot
Hash function: h(key) = key % TABLE_SIZE
Probe: (h(key) + i²) % TABLE_SIZE for i = 0, 1, 2, ...
```

### Algorithm
### Insert
1. index = key % TABLE_SIZE
2. Try index, (index+1²), (index+2²), (index+3²), ...
3. All modulo TABLE_SIZE
4. Insert when empty slot found

### Search
1. Same probing pattern as insert
2. Stop when key found or empty slot reached

### Pseudocode
```
FUNCTION insert(key):
    index = key % TABLE_SIZE
    i = 0
    WHILE hashTable[(index + i*i) % TABLE_SIZE] != -1:
        i = i + 1
        IF i == TABLE_SIZE: PRINT "Table Full"; RETURN
    hashTable[(index + i*i) % TABLE_SIZE] = key

FUNCTION search(key):
    index = key % TABLE_SIZE
    i = 0
    WHILE hashTable[(index + i*i) % TABLE_SIZE] != key:
        IF hashTable[(index + i*i) % TABLE_SIZE] == -1:
            RETURN "Not Found"
        i = i + 1
        IF i == TABLE_SIZE: RETURN "Not Found"
    RETURN "Found"
```

### Time & Space Complexity
| Operation | Average | Worst |
|-----------|---------|-------|
| Insert | O(1/(1-α)) | O(n) |
| Search | O(1/(1-α)) | O(n) |

**Note:** TABLE_SIZE should be prime for quadratic probing to work correctly.

### Worked Example
**TABLE_SIZE = 7, Insert: 10, 17, 15, 24**

| Key | h(key) | Probes | Final Index |
|-----|--------|--------|-------------|
| 10 | 3 | 3 | 3 |
| 17 | 3 | 3→4 (3+1) | 4 |
| 15 | 1 | 1 | 1 |
| 24 | 3 | 3→4→0 (3+4) | 0 |

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

> **Solution Code:** See `Slip_22_Q1_OptionA.c` and `Slip_22_Q1_OptionB.c` in this folder.
