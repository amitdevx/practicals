# Slip 14 — Data Structures-II Solution Guide

## Question

**Option A:** Q1) Write a C program to maintain a phonebook using Binary Search Tree by name where each node contains contact name and phone number.

**Option B:** Q1) Write a C program to implement a hash table using open addressing with linear probing. perform the following operations. (Assume all keys are positive integers) a. b. c. Insert Search Display

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

## Option B: Hash Table with Linear Probing (Open Addressing)

### Concept
**Linear probing** handles collisions by checking the next slot sequentially.

If slot `h(key)` is occupied, try `h(key)+1`, `h(key)+2`, ... (wrapping around).

| Term | Meaning |
|------|---------|
| **Open Addressing** | All elements stored in the table itself |
| **Linear Probing** | Probe sequence: h(k), h(k)+1, h(k)+2, ... |
| **Load Factor** | n / TABLE_SIZE (should be < 0.7) |

### Data Structure
```
int hashTable[TABLE_SIZE];
// -1 indicates empty slot
Hash function: h(key) = key % TABLE_SIZE
```

### Algorithm
### Insert
1. index = key % TABLE_SIZE
2. If hashTable[index] is empty, insert key
3. Else, try (index+1) % TABLE_SIZE, (index+2) % TABLE_SIZE, ...
4. Stop when empty slot found or table is full

### Search
1. index = key % TABLE_SIZE
2. Check hashTable[index]; if match, found
3. Else, check next slots linearly
4. Stop when key found, empty slot reached, or full cycle

### Pseudocode
```
FUNCTION insert(key):
    index = key % TABLE_SIZE
    i = 0
    WHILE hashTable[(index + i) % TABLE_SIZE] != -1:
        i = i + 1
        IF i == TABLE_SIZE: PRINT "Table Full"; RETURN
    hashTable[(index + i) % TABLE_SIZE] = key

FUNCTION search(key):
    index = key % TABLE_SIZE
    i = 0
    WHILE hashTable[(index + i) % TABLE_SIZE] != key:
        IF hashTable[(index + i) % TABLE_SIZE] == -1:
            RETURN "Not Found"
        i = i + 1
        IF i == TABLE_SIZE: RETURN "Not Found"
    RETURN "Found at index (index + i) % TABLE_SIZE"
```

### Time & Space Complexity
| Operation | Average | Worst |
|-----------|---------|-------|
| Insert | O(1/(1-α)) | O(n) |
| Search | O(1/(1-α)) | O(n) |

**Clustering problem**: consecutive occupied slots form clusters, degrading performance.

### Worked Example
**TABLE_SIZE = 7, Insert: 10, 20, 15, 7, 22**

| Key | h(key) | Actual Index | Reason |
|-----|--------|-------------|--------|
| 10 | 3 | 3 | Empty |
| 20 | 6 | 6 | Empty |
| 15 | 1 | 1 | Empty |
| 7 | 0 | 0 | Empty |
| 22 | 1 | 2 | Collision at 1, probe to 2 |

---

> **Solution Code:** See `Slip_14_Q1_OptionA.c` and `Slip_14_Q1_OptionB.c` in this folder.
