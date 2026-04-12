# Slip 15 — Data Structures-II Solution Guide

## Question

**Option A:** See Slip_15_DS.txt for question

**Option B:** Q1) Q1) Implement a Binary search tree (BST) library (btree.h) with operations – create, search, insert, inorder, preorder and postorder. Write a menu driven program that performs the above operations.

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

> **Solution Code:** See `Slip_15_Q1_OptionA.c` and `Slip_15_Q1_OptionB.c` in this folder.
