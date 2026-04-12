# Slip 9 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Write a C program to implement a hash table using separate chaining with linked lists with following operation. a. b. c. Insert a key Search a key Display the hash table

**Option B:** Q1) Write a C program to find the height of the tree and check whether given tree is balanced or not.

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

## Option B: BST Height and Balance Check

### Concept
**Height** of a tree is the number of edges on the longest path from root to a leaf.

A tree is **balanced** if for every node, the height difference between left and right subtrees is at most 1.

| Tree Type | Height |
|-----------|--------|
| Balanced BST | O(log n) |
| Skewed BST | O(n) |

### Data Structure
Uses BST node structure from btree.h library.

### Algorithm
### Height Calculation (Recursive)
1. If node is NULL, return -1 (or 0 depending on convention)
2. Left height = height(left subtree)
3. Right height = height(right subtree)
4. Return max(left_height, right_height) + 1

### Balance Check
1. For each node, calculate left and right heights
2. If |left_height - right_height| > 1 → NOT balanced
3. Also recursively check if left and right subtrees are balanced

### Pseudocode
```
FUNCTION height(root):
    IF root is NULL: RETURN -1
    leftH = height(root.left)
    rightH = height(root.right)
    RETURN max(leftH, rightH) + 1

FUNCTION isBalanced(root):
    IF root is NULL: RETURN TRUE
    leftH = height(root.left)
    rightH = height(root.right)
    IF |leftH - rightH| > 1: RETURN FALSE
    RETURN isBalanced(root.left) AND isBalanced(root.right)
```

### Time & Space Complexity
| Operation | Complexity |
|-----------|-----------|
| Height | O(n) |
| Balance Check | O(n²) naive, O(n) optimized |

### Worked Example
**Balanced Tree:**
```
      50
     /  \
   30    70
  / \
20   40
```
Height = 2, |left_h - right_h| = |1 - 0| = 1 ≤ 1 → **Balanced**

**Unbalanced Tree:**
```
    50
   /
  30
 /
20
```
Height = 2, |left_h - right_h| = |2 - (-1)| = 3 > 1 → **NOT Balanced**

---

> **Solution Code:** See `Slip_09_Q1_OptionA.c` and `Slip_09_Q1_OptionB.c` in this folder.
