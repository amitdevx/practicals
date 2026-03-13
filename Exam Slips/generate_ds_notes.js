// generate_ds_notes.js – Data Structure II – Condensed Notes (45-50 pages)
'use strict';

const {
  Document, Packer, Paragraph, TextRun, AlignmentType, BorderStyle,
  Table, TableRow, TableCell, WidthType, ImageRun, ShadingType,
  ExternalHyperlink, PageNumber, Footer, Header
} = require('docx');
const fs   = require('fs');
const path = require('path');

// ── STYLE HELPERS ─────────────────────────────────────────────────────────
const t  = (text, o={}) => new TextRun({ text, font:"Times New Roman", size:22, ...o });
const c  = (text, o={}) => new TextRun({ text, font:"Courier New",     size:18, ...o });
const P  = (po, ch)    => new Paragraph({ ...po, children: ch });

const coverTitle = txt => P({ alignment:AlignmentType.CENTER, spacing:{after:160,before:120} },
  [t(txt,{bold:true,size:40,color:"1F3864"})]);

const chHead = txt => P({
  alignment:AlignmentType.CENTER, spacing:{before:200,after:200}, pageBreakBefore:true,
  border:{ top:{style:BorderStyle.THICK,size:8,color:"1F3864"}, bottom:{style:BorderStyle.THICK,size:8,color:"1F3864"} }
}, [t(txt,{bold:true,size:32,color:"1F3864"})]);

const secHead = txt => P({
  spacing:{before:240,after:100}, indent:{left:240},
  border:{ left:{style:BorderStyle.THICK,size:16,color:"2E74B5"} }
}, [t(txt,{bold:true,size:26,color:"2E74B5"})]);

const subHead  = txt => P({ spacing:{before:180,after:60} },
  [t(txt,{bold:true,size:23,color:"C00000",underline:{}})]);
const topicH   = txt => P({ spacing:{before:140,after:40} },
  [t("▶ "+txt,{bold:true,size:21,color:"375623"})]);
const body     = txt => P({ spacing:{after:110} }, [t(txt,{size:22})]);
const bodyB    = (lbl,txt) => P({ spacing:{after:110} },
  [t(lbl+": ",{bold:true,color:"1F3864",size:22}), t(txt,{size:22})]);
const bl       = (txt,lvl=0) => P({
  spacing:{after:70}, indent:{left:400+lvl*360,hanging:240}
}, [t((lvl===0?"● ":"○ "),{bold:true,color:"2E74B5",size:22}), t(txt,{size:22})]);
const np       = (n,txt) => P({
  spacing:{after:80}, indent:{left:440,hanging:300}
}, [t(n+".  ",{bold:true,color:"1F3864",size:22}), t(txt,{size:22})]);
const note     = txt => P({
  spacing:{before:80,after:80}, indent:{left:300},
  border:{ left:{style:BorderStyle.THICK,size:16,color:"2E74B5"} }
}, [t("★ ",{bold:true,color:"2E74B5",size:22}), t(txt,{size:21})]);
const imp      = txt => P({
  spacing:{before:80,after:80}, indent:{left:300},
  border:{ left:{style:BorderStyle.THICK,size:16,color:"C00000"} }
}, [t("⚠ ",{bold:true,color:"C00000",size:22}), t(txt,{size:21})]);
const formula  = txt => P({
  alignment:AlignmentType.CENTER, spacing:{before:80,after:80},
  border:{ top:{style:BorderStyle.SINGLE,size:4,color:"375623"}, bottom:{style:BorderStyle.SINGLE,size:4,color:"375623"} }
}, [c(txt,{bold:true,size:20,color:"375623"})]);
const sp       = (n=80) => P({ spacing:{after:n} }, []);
const divider  = () => P({
  spacing:{before:60,after:60},
  border:{bottom:{style:BorderStyle.SINGLE,size:4,color:"BDC3C7"}}
}, []);
const diagLbl  = txt => P({ spacing:{before:80,after:30} },
  [t("   [Diagram] "+txt,{bold:true,size:20,color:"2E74B5",italics:true})]);

// ── Image embed helper ──────────────────────────────────────────────────
let _dims = null;
function _getDims() {
  if (!_dims) {
    try { _dims = JSON.parse(fs.readFileSync('/tmp/ds_diagrams/dims.json', 'utf8')); }
    catch(e) { _dims = {}; }
  }
  return _dims;
}

function img(filename, widthPt = 440) {
  const base = filename.replace(/\.png$/i, '');
  const fpath = `/tmp/ds_diagrams/${base}.png`;
  if (!fs.existsSync(fpath)) return sp(20);
  const data = fs.readFileSync(fpath);
  const d = _getDims()[base] || { w: 800, h: 400 };
  const heightPt = Math.round(widthPt * (d.h / d.w));
  return new Paragraph({
    alignment: AlignmentType.CENTER,
    spacing: { before: 120, after: 120 },
    children: [new ImageRun({ data, transformation: { width: widthPt, height: heightPt } })]
  });
}

// ── Table helper ────────────────────────────────────────────────────────
function makeTable(headers, rows) {
  const colW = Math.floor(8800 / headers.length);
  return new Table({
    width: { size: 8800, type: WidthType.DXA },
    rows: [
      new TableRow({
        tableHeader: true,
        children: headers.map(h => new TableCell({
          width: { size: colW, type: WidthType.DXA },
          shading: { fill: 'DBEAFE' },
          margins: { top: 60, bottom: 60, left: 100, right: 100 },
          children: [new Paragraph({ children: [new TextRun({ text: h, bold: true, size: 19, color: '1E3A8A', font: 'Times New Roman' })] })]
        }))
      }),
      ...rows.map((row, ri) => new TableRow({
        children: row.map(cell => new TableCell({
          width: { size: colW, type: WidthType.DXA },
          shading: { fill: ri%2===0 ? 'F8FAFC' : 'FFFFFF' },
          margins: { top: 40, bottom: 40, left: 100, right: 100 },
          children: [new Paragraph({ children: [new TextRun({ text: String(cell), size: 18, font: 'Times New Roman' })] })]
        }))
      }))
    ]
  });
}

// ════════════════════════════════════════════════════════════════════════
// COVER PAGE — Beautiful Book Design
// ════════════════════════════════════════════════════════════════════════
const cover = [
  sp(100),
  // Decorative top border
  P({ alignment:AlignmentType.CENTER, spacing:{after:40},
      border:{ top:{style:BorderStyle.DOUBLE,size:12,color:"1F3864"} } }, []),
  sp(120),
  
  // Author name - elegant serif
  P({ alignment:AlignmentType.CENTER, spacing:{after:30} },
    [t("A M I T   D I V E K A R",{bold:true,size:36,color:"1F3864",font:"Georgia"})]),
  
  // Decorative separator
  P({ alignment:AlignmentType.CENTER, spacing:{after:30} },
    [t("❖",{bold:true,size:28,color:"DC2626"})]),
  
  // Website - subtle styling
  P({ alignment:AlignmentType.CENTER, spacing:{after:100} },
    [new ExternalHyperlink({
       link: "https://amitdevx.tech",
       children: [t("www.amitdevx.tech",{size:20,color:"2563EB",italics:true})]
     })]),
  
  // Main title - large and prominent
  P({ alignment:AlignmentType.CENTER, spacing:{before:80,after:40} },
    [t("DATA",{bold:true,size:52,color:"1F3864",font:"Georgia"})]),
  P({ alignment:AlignmentType.CENTER, spacing:{after:40} },
    [t("STRUCTURE",{bold:true,size:52,color:"1F3864",font:"Georgia"})]),
  P({ alignment:AlignmentType.CENTER, spacing:{after:80} },
    [t("II",{bold:true,size:58,color:"DC2626",font:"Georgia"})]),
  
  // Subtitle - elegant italic
  P({ alignment:AlignmentType.CENTER, spacing:{after:20},
      border:{ top:{style:BorderStyle.SINGLE,size:6,color:"2E74B5"},
               bottom:{style:BorderStyle.SINGLE,size:6,color:"2E74B5"} } },
    [t("Complete Study Notes",{italics:true,size:26,color:"2E74B5"})]),
  
  sp(100),
  
  // Content highlights - box style
  P({ alignment:AlignmentType.CENTER, spacing:{after:15} },
    [t("◆",{size:18,color:"DC2626"}), t("  Theory & Concepts  ",{size:22,color:"1F3864"}), t("◆",{size:18,color:"DC2626"})]),
  P({ alignment:AlignmentType.CENTER, spacing:{after:15} },
    [t("◆",{size:18,color:"DC2626"}), t("  Professional Diagrams  ",{size:22,color:"1F3864"}), t("◆",{size:18,color:"DC2626"})]),
  P({ alignment:AlignmentType.CENTER, spacing:{after:15} },
    [t("◆",{size:18,color:"DC2626"}), t("  C Code Examples  ",{size:22,color:"1F3864"}), t("◆",{size:18,color:"DC2626"})]),
  P({ alignment:AlignmentType.CENTER, spacing:{after:120} },
    [t("◆",{size:18,color:"DC2626"}), t("  Worked Examples & Traces  ",{size:22,color:"1F3864"}), t("◆",{size:18,color:"DC2626"})]),
  
  // Chapter listing - compact and elegant
  P({ alignment:AlignmentType.CENTER, spacing:{after:25},
      border:{ top:{style:BorderStyle.SINGLE,size:4,color:"BDC3C7"} } },
    [t("CHAPTERS",{bold:true,size:22,color:"1F3864"})]),
  P({ alignment:AlignmentType.CENTER, spacing:{after:15} },
    [t("I. Trees (10 Hours)",{size:20,color:"2E74B5"})]),
  P({ alignment:AlignmentType.CENTER, spacing:{after:15} },
    [t("II. Search Trees (4 Hours)",{size:20,color:"2E74B5"})]),
  P({ alignment:AlignmentType.CENTER, spacing:{after:15} },
    [t("III. Graph (11 Hours)",{size:20,color:"2E74B5"})]),
  P({ alignment:AlignmentType.CENTER, spacing:{after:80} },
    [t("IV. Hash Table (5 Hours)",{size:20,color:"2E74B5"})]),
  
  // Decorative bottom border
  P({ alignment:AlignmentType.CENTER, spacing:{after:60},
      border:{ bottom:{style:BorderStyle.DOUBLE,size:12,color:"1F3864"} } }, []),
];

// ════════════════════════════════════════════════════════════════════════
// SYLLABUS INDEX PAGE (Page 2)
// ════════════════════════════════════════════════════════════════════════
const syllabusIndex = [
  P({ alignment:AlignmentType.CENTER, spacing:{before:200,after:200}, pageBreakBefore:true,
      border:{ bottom:{style:BorderStyle.THICK,size:8,color:"1F3864"} } },
    [t("SYLLABUS & INDEX",{bold:true,size:32,color:"1F3864"})]),

  // Chapter 1
  secHead("Chapter 1 : Trees (10 Hours) ................................. Page 3"),
  bl("1.1 Concept and Terminologies"),
  bl("1.2 Types of Binary Trees – Binary Tree, Skewed Tree, Strictly Binary Tree, Full Binary Tree, Complete Binary Tree, Expression Tree, BST"),
  bl("1.3 Representation – Static (Array) and Dynamic (Linked)"),
  bl("1.4 BST Operations – Create, Insert, Delete, Search"),
  bl("1.5 Tree Traversals – Preorder, Inorder, Postorder (recursive), Level-order (queue); Count leaf/non-leaf/total nodes; Copy; Mirror"),
  bl("1.6 Applications – Heap Sort (Max Heap, Min Heap)"),
  sp(60),

  // Chapter 2
  secHead("Chapter 2 : Search Trees (4 Hours) ......................... Page 17"),
  bl("2.1 Basic Terminology – Balanced Tree, AVL Tree, Red-Black Tree"),
  bl("2.2 AVL Tree – Rotations (LL, LR, RL, RR)"),
  bl("2.3 Red-Black Tree – Insertion, Deletion"),
  bl("2.4 Multi-way Search Trees – B Tree and B+ Tree (Concept, Insertion)"),
  sp(60),

  // Chapter 3
  secHead("Chapter 3 : Graph (11 Hours) ................................ Page 27"),
  bl("3.1 Concept and Terminologies"),
  bl("3.2 Graph Representation – Adjacency Matrix, Adjacency List, Inverse Adjacency List, Adjacency Multi-List"),
  bl("3.3 Graph Traversals – BFS and DFS (with implementation)"),
  bl("3.4 Applications – Topological Sorting, MST (Prim's, Kruskal's), Dijkstra's Algorithm, Floyd-Warshall, Social Networks"),
  sp(60),

  // Chapter 4
  secHead("Chapter 4 : Hash Table (5 Hours) ........................... Page 38"),
  bl("4.1 Concept of Hashing"),
  bl("4.2 Terminologies – Hash table, Hash function, Bucket, Hash address, Collision, Overflow"),
  bl("4.3 Hash Functions – Properties, Methods (Division, Mid-Square, Folding)"),
  bl("4.4 Collision Resolution – Open Addressing (Linear, Quadratic, Rehashing), Chaining (Coalesced, Separate)"),
  sp(80),

  // References
  P({ spacing:{before:200,after:80}, border:{ top:{style:BorderStyle.SINGLE,size:4,color:"BDC3C7"} } }, []),
  P({ spacing:{after:60} }, [t("Reference Books:",{bold:true,size:22,color:"1F3864"})]),
  np(1,"Fundamentals of Data Structures in C – Ellis Horowitz, Sartaj Sahni, Susan Anderson-Freed, 2nd Ed."),
  np(2,"Data Structures Using C – Reema Thareja"),
  np(3,"Introduction to Algorithms – Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein"),
  np(4,"Data Structures, Algorithms, and Applications in C++ – Sartaj Sahni"),
];

// ════════════════════════════════════════════════════════════════════════
// CHAPTER 1 : TREES (10 Hours) — Target: ~14 pages
// ════════════════════════════════════════════════════════════════════════
const ch1 = [
  chHead("Chapter 1 :  Trees  (10 Hours)"),
  sp(40),

  body("In Data Structures, a Tree is one of the most important non-linear data structures. Unlike arrays, linked lists, stacks, and queues which are linear (elements stored sequentially), trees organize data in a hierarchical parent-child relationship. This makes trees ideal for representing hierarchical information such as file systems, organizational charts, XML/HTML DOM, and decision processes."),
  body("Trees overcome the limitations of linear structures — arrays give O(1) access but O(n) insert/delete; linked lists give O(1) insert/delete but O(n) search. A balanced tree (like BST, AVL) provides O(log n) for all three operations. Trees also form the backbone of many algorithms: expression evaluation, priority queues (heaps), database indexing (B/B+ trees), and efficient searching/sorting."),
  body("Key idea: A tree with n nodes always has exactly (n−1) edges, and there is exactly one path between any two nodes. A binary tree restricts each node to at most 2 children, making it the most widely studied tree variant."),
  sp(40),

  // ─── 1.1 Concepts & Terminologies ─────────────────────────────────
  secHead("1.1  Concept and Terminologies"),
  body("A tree is a non-linear hierarchical data structure consisting of nodes connected by edges. It has exactly one root node with zero or more subtrees."),
  img('ch1_terminology', 380),
  diagLbl("Binary Tree — All Terminologies"),
  img('ch1_tree_terms'),
  makeTable(
    ['Term', 'Definition'],
    [
      ['Root', 'Topmost node with no parent (A in diagram)'],
      ['Leaf/Terminal', 'Node with no children (H, E, F, G)'],
      ['Internal Node', 'Node with at least one child (A, B, C, D)'],
      ['Parent/Child', 'Direct ancestor/descendant relationship'],
      ['Sibling', 'Nodes sharing the same parent (B & C)'],
      ['Degree', 'Number of children of a node; Degree of tree = max degree'],
      ['Height', 'Longest path (edges) from root to leaf. Above tree: height = 3'],
      ['Depth/Level', 'Distance (edges) from root. Root = level 0'],
      ['Subtree', 'A node and all its descendants form a subtree'],
    ]
  ),
  formula("Properties: n nodes → (n-1) edges  |  Level k has at most 2^k nodes"),
  sp(40),

  // ─── 1.2 Types of Binary Trees ───────────────────────────────────
  secHead("1.2  Types of Binary Trees"),

  subHead("(a) Binary Tree"),
  body("Each node has at most 2 children (left and right). The most general form."),
  makeTable(
    ['Property', 'Value for Binary Tree of height h'],
    [
      ['Max nodes at level k', '2^k'],
      ['Max total nodes', '2^(h+1) − 1'],
      ['Min height for n nodes', '⌊log₂ n⌋'],
      ['Max height for n nodes', 'n − 1 (skewed)'],
    ]
  ),
  img('ch1_gen_binary', 340),

  subHead("(b) Skewed Binary Tree"),
  body("All nodes have only one child — either all left (left-skewed) or all right (right-skewed). Degenerates to a linked list. Height = n−1."),
  img('ch1_skewed', 400),

  subHead("(c) Strictly Binary Tree (Proper/2-Tree)"),
  body("Every node has either 0 or 2 children — no node has exactly 1 child. If L = leaf count, then internal nodes = L − 1, total = 2L − 1."),
  img('ch1_strictly_binary', 340),

  subHead("(d) Full Binary Tree (Perfect Binary Tree)"),
  body("All internal nodes have 2 children AND all leaves are at the same level. For height h: Total nodes = 2^(h+1) − 1, Leaves = 2^h."),
  img('ch1_full_bt', 400),
  formula("h=3: Nodes = 2^4 − 1 = 15   |   Leaves = 2^3 = 8"),

  subHead("(e) Complete Binary Tree"),
  body("All levels fully filled except possibly the last, which is filled left-to-right. Used in heaps. Can be stored efficiently in an array."),
  img('ch1_complete_bt', 360),
  makeTable(
    ['Index', '0', '1', '2', '3', '4', '5'],
    [['Value', '10', '20', '30', '40', '50', '60']]
  ),
  formula("Parent(i) = (i-1)/2  |  Left(i) = 2i+1  |  Right(i) = 2i+2"),

  subHead("(f) Expression Tree"),
  body("Leaves = operands, Internal nodes = operators. Inorder traversal gives infix expression; postorder gives postfix."),
  body("Expression: (a + b) × (c − d)"),
  img('ch1_expr1', 340),
  body("Larger expression: ((a + b) × c) + ((d − e) / f)"),
  img('ch1_expr2', 400),
  note("Building expression tree from postfix: scan left to right. Operand → push node. Operator → pop two subtrees, make them children of operator node, push result."),

  subHead("(g) Binary Search Tree (BST)"),
  body("For every node: all keys in left subtree < node key < all keys in right subtree. Enables O(log n) average search."),
  img('ch1_bst', 340),
  note("Inorder traversal of BST gives sorted order. BST with n nodes has height between ⌊log₂n⌋ (balanced) and n−1 (skewed)."),
  body("BST property enables binary search: at each node, eliminate half the remaining tree."),
  sp(40),

  // ─── 1.3 Representation ──────────────────────────────────────────
  secHead("1.3  Representation of Binary Trees"),

  subHead("(a) Static — Array Representation"),
  body("Store in array using index formulas. Root at index 0. Best for complete/full binary trees."),
  makeTable(
    ['Formula', 'Expression'],
    [
      ['Parent of i', '⌊(i−1)/2⌋'],
      ['Left child of i', '2i + 1'],
      ['Right child of i', '2i + 2'],
      ['Has left child?', '2i + 1 < n'],
      ['Is leaf?', '2i + 1 ≥ n'],
    ]
  ),
  body("Example: BST {50,30,70,20,40,60,80} stored in array:"),
  makeTable(
    ['Index', '0', '1', '2', '3', '4', '5', '6'],
    [['Value', '50', '30', '70', '20', '40', '60', '80']]
  ),
  bl("Advantage: O(1) access to parent/children. No pointer overhead."),
  bl("Disadvantage: Wastes space for skewed trees (need 2^h slots for h-height tree). Insertion/deletion requires shifting."),

  subHead("(b) Dynamic — Linked Representation"),
  body("Each node is a struct with data, left pointer, and right pointer."),
  img('code_tree_node.png', 380),
  img('ch1_linked_bst', 420),
  sp(40),

  // ─── 1.4 BST Operations ─────────────────────────────────────────
  secHead("1.4  BST Operations — Create, Insert, Delete, Search"),

  subHead("Create"),
  body("Allocate a new node, set data, left = right = NULL."),
  img('code_bst_create.png', 380),

  subHead("Insert"),
  body("Compare key with current node: go left if smaller, right if larger. Insert at the NULL position found. Time: O(h)."),
  img('code_bst_insert.png', 380),
  diagLbl("BST Insert Steps: Insert 50, 30, 70, 20, 40, 60, 80"),
  img('ch1_bst_steps', 420),
  img('ch1_bst_insert', 380),

  subHead("Delete"),
  topicH("Case 1: Leaf node — simply remove it"),
  img('ch1_bst_del_leaf', 420),
  topicH("Case 2: One child — replace node with its child"),
  img('ch1_bst_del_one_child', 420),
  topicH("Case 3: Two children — replace with inorder successor (smallest in right subtree), then delete successor"),
  img('ch1_bst_del_root', 420),
  img('code_bst_delete.png', 400),

  subHead("Search"),
  body("Compare key with current node. If equal → found. If smaller → go left. If larger → go right. If NULL → not found."),
  img('code_bst_search.png', 380),
  img('ch1_bst_search', 420),

  makeTable(
    ['Operation', 'Average', 'Worst (Skewed)'],
    [
      ['Search', 'O(log n)', 'O(n)'],
      ['Insert', 'O(log n)', 'O(n)'],
      ['Delete', 'O(log n)', 'O(n)'],
      ['Find Min', 'O(log n)', 'O(n)'],
      ['Find Max', 'O(log n)', 'O(n)'],
    ]
  ),
  note("Find Min: Keep going left from root until NULL. Find Max: Keep going right. Inorder Successor: Smallest node in right subtree (used in deletion Case 3)."),
  sp(40),

  // ─── 1.5 Tree Traversals ─────────────────────────────────────────
  secHead("1.5  Tree Traversals"),
  body("Four main traversal methods. All recursive traversals have O(n) time and O(h) space (stack depth = height h)."),
  diagLbl("Traversal Example BST: {50, 30, 70, 20, 40, 60, 80}"),
  img('ch1_traversal', 380),

  subHead("(a) Preorder — NLR (Node, Left, Right)"),
  body("Visit node → traverse left → traverse right. Output: 50, 30, 20, 40, 70, 60, 80"),
  img('code_preorder.png', 380),

  subHead("(b) Inorder — LNR (Left, Node, Right)"),
  body("Traverse left → visit node → traverse right. Output: 20, 30, 40, 50, 60, 70, 80 (sorted!)"),
  img('code_inorder.png', 380),

  subHead("(c) Postorder — LRN (Left, Right, Node)"),
  body("Traverse left → traverse right → visit node. Output: 20, 40, 30, 60, 80, 70, 50"),
  img('code_postorder.png', 380),

  subHead("(d) Level-Order (BFS using Queue)"),
  body("Visit nodes level by level, left to right. Uses a queue. Algorithm: Enqueue root → while queue not empty: dequeue node, visit it, enqueue left and right children."),
  img('code_levelorder.png', 380),
  body("Level-order of BST {50,30,70,20,40,60,80}: Result = 50, 30, 70, 20, 40, 60, 80"),
  makeTable(
    ['Step', 'Dequeue & Visit', 'Enqueue Children', 'Queue After'],
    [
      ['1', '50', '30, 70', '[30, 70]'],
      ['2', '30', '20, 40', '[70, 20, 40]'],
      ['3', '70', '60, 80', '[20, 40, 60, 80]'],
      ['4', '20', '—', '[40, 60, 80]'],
      ['5', '40', '—', '[60, 80]'],
      ['6', '60', '—', '[80]'],
      ['7', '80', '—', '[] done'],
    ]
  ),

  subHead("(e) Count Leaf, Non-Leaf, Total Nodes"),
  body("These operations recursively traverse the tree and count nodes based on conditions."),
  img('code_count_leaves.png', 400),
  img('code_count_nonleaves.png', 380),
  img('code_count_total.png', 380),

  makeTable(
    ['Traversal', 'Order', 'Example Output', 'Use Case'],
    [
      ['Preorder', 'Node→Left→Right', '50,30,20,40,70,60,80', 'Copy tree, prefix expression'],
      ['Inorder', 'Left→Node→Right', '20,30,40,50,60,70,80', 'Sorted order from BST'],
      ['Postorder', 'Left→Right→Node', '20,40,30,60,80,70,50', 'Delete tree, postfix expression'],
      ['Level-order', 'Level by level', '50,30,70,20,40,60,80', 'BFS, print by levels'],
    ]
  ),

  subHead("(f) Copy Tree"),
  body("Create a new tree that is an exact duplicate — recursively copy left subtree, right subtree, then create node. Uses postorder approach."),
  img('code_copy_tree.png', 400),
  body("Pseudocode: If node is NULL return NULL. newNode = createNode(node→data). newNode→left = copyTree(node→left). newNode→right = copyTree(node→right). Return newNode."),

  subHead("(g) Mirror Tree"),
  body("Swap left and right children of every node recursively. The mirror of a BST is NOT a BST (inorder becomes descending)."),
  img('code_mirror.png', 380),
  body("Example: Original BST {50,30,70,20,40,60,80} → Mirror: root=50, left=70(left=80,right=60), right=30(left=40,right=20)."),
  img('ch1_mirror', 420),
  sp(40),

  // ─── 1.6 Heap Sort ──────────────────────────────────────────────
  secHead("1.6  Applications — Heap Sort"),

  subHead("Max Heap & Min Heap"),
  body("Heap is a complete binary tree satisfying heap property. Max Heap: parent ≥ children. Min Heap: parent ≤ children."),
  img('ch1_max_heap', 360),
  img('ch1_min_heap', 360),
  makeTable(
    ['', 'Max Heap', 'Min Heap'],
    [
      ['Root', 'Maximum element', 'Minimum element'],
      ['Property', 'A[parent] ≥ A[child]', 'A[parent] ≤ A[child]'],
      ['Use', 'Heap Sort (ascending)', 'Priority Queue (min first)'],
      ['Insert', 'O(log n)', 'O(log n)'],
      ['Extract root', 'O(log n)', 'O(log n)'],
      ['Build heap', 'O(n)', 'O(n)'],
    ]
  ),
  makeTable(
    ['Index', '0', '1', '2', '3', '4', '5', '6', '7', '8'],
    [['Max Heap', '90', '70', '80', '50', '60', '75', '40', '10', '30']]
  ),
  formula("Array: Parent(i) = (i-1)/2  |  Left(i) = 2i+1  |  Right(i) = 2i+2"),

  subHead("Heap Sort Algorithm"),
  body("Step 1: Build Max Heap from array (O(n)). Step 2: Repeatedly swap root (max) with last element, reduce heap size by 1, heapify root (O(n log n))."),
  body("Key insight: Build Max Heap is O(n), not O(n log n), because most nodes are near the bottom and require few swaps."),

  topicH("MaxHeapify — Fixing a single violation"),
  body("Compare node with its children. If a child is larger, swap and recurse on the affected subtree. Time: O(log n)."),
  img('code_heapify.png', 420),

  topicH("Build Max Heap"),
  body("Call MaxHeapify for each non-leaf node, bottom-up (from index n/2−1 down to 0). Time: O(n)."),
  img('code_build_heap.png', 380),

  topicH("Heap Sort"),
  img('code_heap_sort.png', 400),

  subHead("Worked Example: Heap Sort [4, 10, 3, 5, 1]"),
  body("Build Max Heap: Start from last non-leaf (index 1). After heapifying: [10, 5, 3, 4, 1]."),
  body("Extract phase: Swap root↔last, heapify remaining:"),
  makeTable(
    ['Step', 'Swap', 'Array After Heapify', 'Sorted Region'],
    [
      ['1', '10↔1', '[5, 4, 3, 1, | 10]', '{10}'],
      ['2', '5↔1', '[4, 1, 3, | 5, 10]', '{5,10}'],
      ['3', '4↔3', '[3, 1, | 4, 5, 10]', '{4,5,10}'],
      ['4', '3↔1', '[1, | 3, 4, 5, 10]', '{3,4,5,10}'],
    ]
  ),
  body("Final sorted array: [1, 3, 4, 5, 10] ✓"),
  makeTable(
    ['Property', 'Value'],
    [
      ['Time Complexity', 'O(n log n) — all cases (best, avg, worst)'],
      ['Space', 'O(1) — in-place'],
      ['Stable?', 'No (relative order of equal elements may change)'],
      ['Build Heap', 'O(n)'],
    ]
  ),
  note("Heap Sort vs Quick Sort: Heap Sort is O(n log n) worst case (Quick Sort is O(n²) worst). But Quick Sort is faster in practice due to better cache performance."),
];

// ════════════════════════════════════════════════════════════════════════
// CHAPTER 2 : SEARCH TREES (4 Hours) — Target: ~10 pages
// ════════════════════════════════════════════════════════════════════════
const ch2 = [
  chHead("Chapter 2 :  Search Trees  (4 Hours)"),
  sp(40),

  body("A Binary Search Tree (BST) provides O(log n) average-case performance, but in the worst case (e.g., inserting sorted data), it degenerates into a linked list with O(n) operations. Search Trees solve this problem by automatically rebalancing after every insertion or deletion, guaranteeing O(log n) height at all times."),
  body("The two main self-balancing BSTs are AVL Trees and Red-Black Trees. AVL trees maintain a strict height balance (|BF| ≤ 1 at every node), while Red-Black trees use a coloring scheme that allows slightly more imbalance but requires fewer rotations on updates. Both guarantee O(log n) search, insert, and delete."),
  body("For disk-based storage where each node access is expensive (database files, file systems), Multi-way Search Trees like B-Trees and B+ Trees are used. Instead of 2 children per node, they allow hundreds of children — drastically reducing tree height and disk I/O operations. A B-Tree of order 100 with 1 million keys has height ≤ 3, meaning only 3 disk reads are needed for any search."),
  sp(40),

  // ─── 2.1 Balanced Trees ──────────────────────────────────────────
  secHead("2.1  Basic Terminology — Balanced Trees"),
  body("Balance Factor (BF) = height(left subtree) − height(right subtree). A tree is balanced if |BF| ≤ 1 for every node."),
  img('ch2_balance_factors', 420),

  subHead("AVL Tree"),
  body("Self-balancing BST where |BF| ≤ 1 for every node. Named after Adelson-Velsky & Landis (1962). Guarantees O(log n) height."),
  note("AVL is stricter than Red-Black → faster search but more rotations on insert/delete."),
  body("AVL Insert Pseudocode: (1) BST insert. (2) Update height bottom-up. (3) Compute BF. (4) If |BF|>1 apply rotation (LL/RR/LR/RL). (5) Return updated root."),
  body("AVL Delete Pseudocode: (1) BST delete. (2) Update height. (3) Check BF. (4) If |BF|>1 determine rotation from BF of child. (5) May need multiple rotations up to root."),

  subHead("Red-Black Tree"),
  body("Self-balancing BST using node coloring (red/black). Less strict than AVL — height ≤ 2×log₂(n+1). Used in Linux kernel, Java TreeMap, C++ std::map."),

  makeTable(
    ['Property', 'AVL Tree', 'Red-Black Tree'],
    [
      ['Balance', '|BF| ≤ 1', 'Black-height equal on all paths'],
      ['Height', '≤ 1.44 log₂n', '≤ 2 log₂(n+1)'],
      ['Search', 'Faster (stricter balance)', 'Slightly slower'],
      ['Insert/Delete', 'More rotations', 'Fewer rotations (≤ 3)'],
      ['Best for', 'Read-heavy workloads', 'Write-heavy workloads'],
    ]
  ),
  sp(40),

  // ─── 2.2 AVL Rotations ──────────────────────────────────────────
  secHead("2.2  AVL Tree — Rotations"),
  body("When insertion/deletion causes |BF| > 1, we rebalance using rotations. Four cases:"),

  subHead("LL Rotation (Right Rotation)"),
  body("Imbalance at node A with BF=+2, left child B has BF=+1 or 0. Fix: rotate A right. B becomes new root, A becomes right child of B, B's right subtree moves to A's left."),
  img('ch2_avl_ll', 440),
  img('ch2_ll_case', 440),
  img('code_right_rotate.png', 400),

  subHead("RR Rotation (Left Rotation)"),
  body("Imbalance at node A with BF=−2, right child B has BF=−1 or 0. Fix: rotate A left. B becomes new root, A becomes left child of B, B's left subtree moves to A's right."),
  img('ch2_avl_rr', 440),
  img('ch2_rr_case', 440),
  img('code_left_rotate.png', 400),

  subHead("LR Rotation (Left-Right Double Rotation)"),
  body("BF(A)=+2, BF(B)=−1 (left child's right subtree is heavy). Fix: First left rotate B, then right rotate A. Two rotations needed because single rotation won't fix the zigzag pattern."),
  img('ch2_avl_lr', 440),

  subHead("RL Rotation (Right-Left Double Rotation)"),
  body("BF(A)=−2, BF(B)=+1 (right child's left subtree is heavy). Fix: First right rotate B, then left rotate A. Mirror of LR case."),
  img('ch2_avl_rl', 440),

  makeTable(
    ['Imbalance', 'BF of Node', 'BF of Child', 'Rotation'],
    [
      ['LL', '+2', '+1 or 0', 'Single Right'],
      ['RR', '−2', '−1 or 0', 'Single Left'],
      ['LR', '+2', '−1', 'Left then Right'],
      ['RL', '−2', '+1', 'Right then Left'],
    ]
  ),

  subHead("AVL Insertion Example: Insert 10, 20, 25, 30, 28, 27"),
  body("Step-by-step: Insert 10 (root). Insert 20 (right of 10). Insert 25 → BF(10)=−2, RR case → left rotate at 10. Result: root=20, left=10, right=25."),
  body("Insert 30 → right of 25. Insert 28 → right of 25 has 30, so 28 goes left of 30 → BF(25)=−2, RL case → right rotate 30, left rotate 25."),
  body("Insert 27 → goes left of 28 → BF(20)=−2, RL case → final balanced tree:"),
  img('ch2_avl_final', 300),

  subHead("AVL Deletion"),
  body("Delete using BST rules, then check BF bottom-up. If |BF| > 1, apply appropriate rotation. May need O(log n) rotations (unlike insertion which needs at most 2)."),
  body("Example: Delete 70 from AVL tree {50,30,70,20,40}. After deletion, BF(50)=+2. Left child BF(30)=0 → LL case → Right rotate at 50. New root=30, left=20, right=50(left=40)."),
  img('ch2_avl_delete', 420),
  img('ch2_avl_del_imbal', 420),

  makeTable(
    ['Operation', 'Time', 'Max Rotations'],
    [
      ['Search', 'O(log n)', '0'],
      ['Insert', 'O(log n)', '2 (single or double)'],
      ['Delete', 'O(log n)', 'O(log n)'],
    ]
  ),
  sp(40),

  // ─── 2.3 Red-Black Tree ─────────────────────────────────────────
  secHead("2.3  Red-Black Tree — Operations"),

  topicH("5 Properties of Red-Black Tree:"),
  np(1, "Every node is either RED or BLACK"),
  np(2, "Root is always BLACK"),
  np(3, "Every NULL leaf (NIL) is BLACK"),
  np(4, "If a node is RED, both children must be BLACK (no two consecutive reds)"),
  np(5, "All paths from a node to descendant NILs have the same black-height"),
  img('ch2_rbt', 340),
  img('ch2_black_height', 380),

  subHead("Insertion in RBT"),
  body("Insert as RED node (BST insert), then fix violations:"),
  bl("Case 1: Uncle is RED → Recolor parent, uncle to BLACK; grandparent to RED; check upward"),
  bl("Case 2: Uncle is BLACK, triangle case → Rotate to convert to Case 3"),
  bl("Case 3: Uncle is BLACK, line case → Rotate grandparent + recolor"),
  img('ch2_rbt_insert', 440),
  body("Example: Insert 10, 20, 30 into RBT. Insert 10 (black root). Insert 20 (red, right of 10). Insert 30 → red, uncle=NIL(black), line case → Left rotate at 10, recolor 20=black, 10=red."),

  subHead("Deletion in RBT"),
  body("Delete using BST rules. If deleted/moved node was BLACK, a 'double-black' violation occurs. Fix by case analysis:"),
  bl("Case 1: Sibling is RED → Rotate parent toward double-black node, recolor sibling and parent. Reduces to other cases."),
  bl("Case 2: Sibling BLACK, both nephews BLACK → Recolor sibling RED, push double-black up to parent. May propagate to root."),
  bl("Case 3: Sibling BLACK, near nephew RED, far nephew BLACK → Rotate sibling away from double-black, recolor. Converts to Case 4."),
  bl("Case 4: Sibling BLACK, far nephew RED → Rotate parent toward double-black, recolor sibling=parent's color, parent=BLACK, far nephew=BLACK. DONE (terminates)."),
  note("RBT deletion needs at most 3 rotations (O(1) structural changes). Height is always ≤ 2log₂(n+1)."),
  sp(40),

  // ─── 2.4 B Tree & B+ Tree ───────────────────────────────────────
  secHead("2.4  Multi-way Search Trees — B Tree & B+ Tree"),

  subHead("B-Tree (Order m)"),
  body("Balanced m-way search tree. All leaves at same level. Each node holds ⌈m/2⌉−1 to m−1 keys. Used in databases and file systems for efficient disk access."),
  makeTable(
    ['Property', 'Rule', 'Example (m=5)'],
    [
      ['Max children', 'm', '5'],
      ['Max keys/node', 'm − 1', '4'],
      ['Min keys (non-root)', '⌈m/2⌉ − 1', '2'],
      ['Min children (internal)', '⌈m/2⌉', '3'],
      ['All leaves', 'Same level', '—'],
    ]
  ),
  img('ch2_btree', 400),

  topicH("B-Tree Insertion"),
  body("Insert into leaf. If leaf overflows (m keys), split: middle key goes to parent; left/right halves become two nodes. If parent overflows, split propagates up."),
  body("Example (Order 3): Insert 10, 20 → [10|20]. Insert 5 → overflow! Split: middle=10 goes up. Left=[5], Right=[20]. Root=[10]."),
  body("Insert 15 → goes to [20] → [15|20]. Insert 25 → [15|20] overflows → split: middle=20 goes to root → Root=[10|20], children: [5], [15], [25]."),
  img('ch2_btree_insert', 420),

  topicH("B-Tree Search"),
  body("At each node, sequential/binary search among keys. If found → return. If key < smallest key → go to leftmost child. If key > largest → rightmost child. Else → go to appropriate child between keys."),
  body("Pseudocode: SearchBTree(node, key): For each key k[i] in node: if key==k[i] return found. If key<k[i] recurse on child[i]. If key>all keys, recurse on last child."),

  topicH("B-Tree Deletion (3 Cases)"),
  bl("Case 1: Key in leaf with enough keys → simply remove"),
  bl("Case 2: Key in internal node → replace with predecessor/successor from leaf, delete from leaf"),
  bl("Case 3: Underflow after delete → borrow from sibling or merge with sibling"),

  subHead("B+ Tree"),
  body("Variant of B-Tree where ALL data is stored in leaf nodes (linked as a linked list). Internal nodes store only routing keys."),
  makeTable(
    ['Feature', 'B-Tree', 'B+ Tree'],
    [
      ['Data location', 'All nodes', 'Only leaf nodes'],
      ['Leaf linking', 'No', 'Yes (linked list)'],
      ['Range queries', 'Slow', 'Fast (sequential leaf scan)'],
      ['Used in', 'Rare', 'MySQL InnoDB, PostgreSQL, NTFS'],
    ]
  ),
  img('ch2_bplustree', 420),

  topicH("B+ Tree Insertion"),
  body("Insert into appropriate leaf. If leaf overflows, split: copy middle key to parent (key stays in right leaf). Internal node overflow splits like B-Tree."),
  img('code_bplus_insert.png', 420),

  topicH("B+ Tree Range Query"),
  body("Range query [a, b]: Search for key a in O(log n), then sequentially scan linked leaves until key > b. Time: O(log n + k) where k = number of results."),

  makeTable(
    ['', 'B-Tree', 'B+ Tree'],
    [
      ['Search', 'O(log n)', 'O(log n)'],
      ['Range Query', 'O(n) worst', 'O(log n + k)'],
      ['Insert', 'O(log n)', 'O(log n)'],
      ['Space', 'Less (data everywhere)', 'More (data only in leaves)'],
      ['Used in', 'General purpose', 'MySQL, PostgreSQL, NTFS'],
    ]
  ),
];

// ════════════════════════════════════════════════════════════════════════
// CHAPTER 3 : GRAPH (11 Hours) — Target: ~11 pages
// ════════════════════════════════════════════════════════════════════════
const ch3 = [
  chHead("Chapter 3 :  Graph  (11 Hours)"),
  sp(40),

  body("Graphs are the most general and versatile data structure for representing relationships. While trees model hierarchical (one-to-many) relationships, graphs model arbitrary (many-to-many) connections. Any network — social networks, road maps, internet routing, circuit design, dependency resolution — is naturally represented as a graph."),
  body("Formally, a graph G = (V, E) consists of a set of vertices (nodes) V and a set of edges (connections) E. Graphs can be directed or undirected, weighted or unweighted, cyclic or acyclic. This flexibility makes graphs applicable to a vast range of problems: shortest path (GPS navigation), minimum spanning tree (network design), topological ordering (task scheduling), flow networks (supply chain), and matching (job assignment)."),
  body("Graph algorithms are among the most important in computer science. BFS and DFS are the two fundamental traversal strategies — most graph algorithms build on one of these. Key problems include: finding shortest paths (Dijkstra, Bellman-Ford, Floyd-Warshall), building minimum cost networks (Prim, Kruskal), ordering tasks (topological sort), and detecting cycles and connected components."),
  sp(40),

  // ─── 3.1 Concepts ───────────────────────────────────────────────
  secHead("3.1  Concept and Terminologies"),
  body("A graph G = (V, E) consists of vertices V and edges E connecting pairs of vertices. Unlike trees, graphs can have cycles and multiple paths between vertices."),
  img('ch3_graph_terms', 420),
  makeTable(
    ['Term', 'Definition'],
    [
      ['Directed (Digraph)', 'Edges have direction: (u,v) ≠ (v,u)'],
      ['Undirected', 'Edges have no direction: {u,v} = {v,u}'],
      ['Weighted', 'Edges have associated costs/weights'],
      ['Degree', 'Number of edges incident to a vertex (in-degree + out-degree for directed)'],
      ['Path', 'Sequence of vertices connected by edges'],
      ['Cycle', 'Path that starts and ends at the same vertex'],
      ['Connected', 'Path exists between every pair of vertices (undirected)'],
      ['Strongly Connected', 'Every vertex reachable from every other (directed)'],
      ['DAG', 'Directed Acyclic Graph — directed graph with no cycles'],
      ['Spanning Tree', 'Subgraph that includes all vertices with minimum edges (V−1 edges)'],
      ['Complete Graph', 'Edge between every pair of vertices. V(V−1)/2 edges for undirected.'],
    ]
  ),
  img('ch3_graph', 360),
  img('ch3_directed', 360),
  img('ch3_weighted', 380),
  sp(40),

  // ─── 3.2 Graph Representations ──────────────────────────────────
  secHead("3.2  Graph Representation"),

  subHead("(a) Adjacency Matrix"),
  body("2D array A[n][n] where A[i][j] = 1 (or weight) if edge (i,j) exists, else 0/∞."),
  bl("Space: O(V²). Good for dense graphs. Edge lookup: O(1)."),
  body("Example for undirected graph with 4 vertices {0,1,2,3}, edges: (0,1),(0,2),(1,2),(2,3):"),
  makeTable(
    ['', '0', '1', '2', '3'],
    [
      ['0', '0', '1', '1', '0'],
      ['1', '1', '0', '1', '0'],
      ['2', '1', '1', '0', '1'],
      ['3', '0', '0', '1', '0'],
    ]
  ),
  note("For undirected graphs, adjacency matrix is symmetric: A[i][j] = A[j][i]. For weighted graphs, store weights instead of 1."),

  subHead("(b) Adjacency List"),
  body("Array of linked lists. Each vertex has a list of its adjacent vertices."),
  bl("Space: O(V + E). Good for sparse graphs."),
  bl("Edge lookup: O(degree). Finding all neighbors: O(degree)."),
  img('ch3_adj_list', 420),

  subHead("(c) Inverse Adjacency List"),
  body("For directed graphs: each vertex stores list of vertices that have edges TO it (predecessors)."),
  img('ch3_inv_adj', 420),

  subHead("Adjacency Multi-List"),
  body("Each edge stored as a single node shared between two adjacency lists. Avoids duplicate edge storage in undirected graphs. Each edge node contains: (vertex1, vertex2, link1, link2, mark). Useful when edge operations (marking, deleting) are needed."),

  body("Example: For edge (0,1) — one node appears in both vertex 0's list and vertex 1's list. Mark bit helps in traversal."),

  makeTable(
    ['Representation', 'Space', 'Edge Query', 'Best For'],
    [
      ['Adj. Matrix', 'O(V²)', 'O(1)', 'Dense graphs'],
      ['Adj. List', 'O(V+E)', 'O(deg)', 'Sparse graphs'],
      ['Inverse Adj.', 'O(V+E)', 'O(deg)', 'Finding predecessors'],
      ['Multi-List', 'O(V+E)', 'O(deg)', 'Edge operations (mark/delete)'],
    ]
  ),
  sp(40),

  // ─── 3.3 Graph Traversals ───────────────────────────────────────
  secHead("3.3  Graph Traversals — BFS and DFS"),

  subHead("Breadth-First Search (BFS)"),
  body("Uses a queue. Visit starting vertex → enqueue → while queue not empty: dequeue, visit all unvisited neighbors, enqueue them."),
  img('ch3_bfs', 380),
  img('code_bfs.png', 400),
  body("BFS Example from vertex 0 on graph {0-1, 0-2, 1-3, 2-3, 3-4}:"),
  makeTable(
    ['Step', 'Dequeue', 'Visit', 'Enqueue', 'Queue After'],
    [
      ['1', '—', '0', '1, 2', '[1, 2]'],
      ['2', '1', '1', '3', '[2, 3]'],
      ['3', '2', '2', '—', '[3]'],
      ['4', '3', '3', '4', '[4]'],
      ['5', '4', '4', '—', '[] done'],
    ]
  ),
  body("BFS order: 0, 1, 2, 3, 4"),
  bl("Time: O(V + E). Space: O(V)."),
  bl("Applications: shortest path (unweighted), level-order, connected components."),

  subHead("Depth-First Search (DFS)"),
  body("Uses a stack (or recursion). Visit starting vertex → for each unvisited neighbor, recurse/push. Goes as deep as possible before backtracking."),
  img('ch3_dfs_example', 380),
  img('ch3_dfs', 380),

  topicH("DFS — Recursive Implementation"),
  img('code_dfs_recursive.png', 380),

  topicH("DFS — Iterative Implementation (using explicit stack)"),
  img('code_dfs_iterative.png', 420),

  body("DFS Example from vertex 0 on same graph: Visit 0 → push neighbors 2,1 → pop 1, visit 1 → push 3 → pop 3, visit 3 → push 4 → pop 4, visit 4 → pop 2, visit 2. DFS order: 0, 1, 3, 4, 2."),
  bl("Time: O(V + E). Space: O(V)."),
  bl("Applications: cycle detection, topological sort, SCC, path finding, maze solving."),

  makeTable(
    ['', 'BFS', 'DFS'],
    [
      ['Data Structure', 'Queue', 'Stack/Recursion'],
      ['Order', 'Level by level', 'Deep first, then backtrack'],
      ['Shortest Path', 'Yes (unweighted)', 'No'],
      ['Memory', 'O(V) — can be large for wide graphs', 'O(V) — depth of graph'],
    ]
  ),
  sp(40),

  // ─── 3.4 Applications ──────────────────────────────────────────
  secHead("3.4  Applications of Graph"),

  // 3.4.1 Topological Sort
  subHead("3.4.1  Topological Sorting"),
  body("Linear ordering of DAG vertices such that for every edge (u,v), u comes before v. Possible only for DAGs (no cycles). Uses: task scheduling, build systems, course prerequisites."),
  body("Kahn's Algorithm (BFS-based): Compute in-degree of all vertices. Enqueue all with in-degree 0. Dequeue vertex, add to result, decrease in-degree of neighbors. Repeat until queue empty."),
  body("DFS-based: Run DFS, push vertex to stack after all descendants processed. Pop stack for topological order."),
  img('ch3_topo_sort', 400),
  body("Example: DAG with edges A→B, A→C, B→D, C→D. In-degrees: A=0, B=1, C=1, D=2."),
  makeTable(
    ['Step', 'Queue', 'Process', 'Decrement In-Degree', 'Result So Far'],
    [
      ['Init', '[A]', '—', '—', '[]'],
      ['1', '[]', 'A', 'B(1→0), C(1→0)', '[A]'],
      ['2', '[B,C]', 'B', 'D(2→1)', '[A,B]'],
      ['3', '[C]', 'C', 'D(1→0)', '[A,B,C]'],
      ['4', '[D]', 'D', '—', '[A,B,C,D]'],
    ]
  ),
  body("Topological Order: A, B, C, D ✓ (every edge u→v has u before v)."),
  note("If graph has a cycle, topological sort is impossible — algorithm will leave vertices unprocessed (Kahn's) or detect back edge (DFS)."),
  sp(40),

  // 3.4.2 MST
  subHead("3.4.2  Minimum Spanning Trees — Prim's & Kruskal's"),
  body("MST: Subset of edges connecting all vertices with minimum total weight. For graph with V vertices, MST has exactly V−1 edges."),
  bl("Property: MST is unique if all edge weights are distinct."),
  bl("Cut Property: For any cut of the graph, the minimum weight edge crossing the cut is in the MST."),

  topicH("Prim's Algorithm (Greedy — vertex-based)"),
  body("Start from any vertex. At each step, add the cheapest edge connecting the MST set to a non-MST vertex. Use min-heap for efficiency."),
  img('code_prim.png', 420),
  bl("Time: O((V+E) log V) with binary heap."),
  body("Prim's Example: Graph with 5 vertices, edges: A-B(2), A-C(3), B-C(1), B-D(4), C-D(5), C-E(6), D-E(7). Start at A."),
  makeTable(
    ['Step', 'MST Set', 'Add Edge', 'Cost', 'Total'],
    [
      ['1', '{A}', 'A-B', '2', '2'],
      ['2', '{A,B}', 'B-C', '1', '3'],
      ['3', '{A,B,C}', 'A-C skipped (cycle), B-D', '4', '7'],
      ['4', '{A,B,C,D}', 'C-E', '6', '13'],
    ]
  ),
  body("MST edges: A-B(2), B-C(1), B-D(4), C-E(6). Total MST weight = 13."),

  topicH("Kruskal's Algorithm (Greedy — edge-based)"),
  body("Sort all edges by weight. Add edges in order, skipping any that create a cycle. Uses Union-Find (Disjoint Set) data structure to detect cycles efficiently."),
  body("Union-Find: Each vertex starts in its own set. Union(u,v) merges sets. Find(u) returns set representative. If Find(u)==Find(v), adding edge (u,v) creates a cycle."),
  img('code_kruskal.png', 420),
  bl("Time: O(E log E) dominated by sorting."),
  body("Kruskal's Example (same graph): Sort edges: B-C(1), A-B(2), A-C(3), B-D(4), C-D(5), C-E(6), D-E(7)."),
  makeTable(
    ['Step', 'Edge', 'Weight', 'Action', 'Union-Find Sets'],
    [
      ['1', 'B-C', '1', 'Add ✓', '{A},{B,C},{D},{E}'],
      ['2', 'A-B', '2', 'Add ✓', '{A,B,C},{D},{E}'],
      ['3', 'A-C', '3', 'Skip ✗ (cycle: A,C same set)', '{A,B,C},{D},{E}'],
      ['4', 'B-D', '4', 'Add ✓', '{A,B,C,D},{E}'],
      ['5', 'C-E', '6', 'Add ✓', '{A,B,C,D,E}'],
    ]
  ),
  body("MST: B-C(1), A-B(2), B-D(4), C-E(6). Total = 13. Same result as Prim's ✓"),
  img('ch3_mst', 400),

  makeTable(
    ['', "Prim's", "Kruskal's"],
    [
      ['Approach', 'Grow from one vertex', 'Pick cheapest edges globally'],
      ['Data Structure', 'Min-Heap + Adj. List', 'Sort + Union-Find'],
      ['Better for', 'Dense graphs', 'Sparse graphs'],
      ['Time', 'O((V+E) log V)', 'O(E log E)'],
    ]
  ),
  sp(40),

  // 3.4.3 Dijkstra
  subHead("3.4.3  Dijkstra's Algorithm — Single Source Shortest Path"),
  body("Finds shortest path from source to all vertices in a weighted graph (non-negative weights only). Greedy approach using a min-heap."),
  body("Algorithm: Initialize dist[src]=0, all others=∞. Extract min-dist vertex, relax all its edges. Repeat."),
  body("Relaxation: if dist[u] + w(u,v) < dist[v] then dist[v] = dist[u] + w(u,v)."),
  img('ch3_dijkstra', 400),
  img('code_dijkstra.png', 420),
  body("Dijkstra Example: Source=A. Initial: dist[A]=0, all others=∞."),
  body("Visit A: relax edges → dist[B]=4, dist[C]=2. Visit C(min=2): relax → dist[B]=min(4,2+1)=3, dist[D]=2+5=7. Visit B(min=3): relax → dist[D]=min(7,3+3)=6. Visit D. Done."),
  makeTable(
    ['Step', 'Visit', 'dist[A]', 'dist[B]', 'dist[C]', 'dist[D]', 'Relaxed Edges'],
    [
      ['Init', '—', '0', '∞', '∞', '∞', '—'],
      ['1', 'A', '0', '4', '2', '∞', 'A→B(4), A→C(2)'],
      ['2', 'C', '0', '3', '2', '7', 'C→B(2+1=3), C→D(2+5=7)'],
      ['3', 'B', '0', '3', '2', '6', 'B→D(3+3=6)'],
      ['4', 'D', '0', '3', '2', '6', 'done'],
    ]
  ),
  bl("Time: O((V+E) log V) with binary heap."),
  imp("Does NOT work with negative edge weights. Use Bellman-Ford for negative weights."),

  topicH("Bellman-Ford Algorithm"),
  body("Handles negative edge weights. Relax ALL edges V−1 times. If any edge can still be relaxed after V−1 passes → negative cycle detected."),
  body("Pseudocode: For i=1 to V−1: For each edge (u,v,w): if dist[u]+w < dist[v] then dist[v]=dist[u]+w. After V−1 passes, check all edges once more — if any can be relaxed, negative cycle exists."),
  img('code_bellman_ford.png', 420),
  img('code_bellman_extra.png', 420),
  bl("Time: O(VE). Slower than Dijkstra but works with negative weights."),
  makeTable(
    ['', 'Dijkstra', 'Bellman-Ford'],
    [
      ['Approach', 'Greedy (min-heap)', 'Dynamic Programming'],
      ['Negative weights', 'NO', 'YES'],
      ['Negative cycle detect', 'NO', 'YES'],
      ['Time', 'O((V+E) log V)', 'O(VE)'],
      ['Use when', 'Non-negative weights', 'Negative weights possible'],
    ]
  ),
  sp(40),

  // 3.4.4 Floyd-Warshall
  subHead("3.4.4  Floyd-Warshall — All Pairs Shortest Path"),
  body("Dynamic programming approach. Finds shortest paths between ALL pairs of vertices. Works with negative weights (no negative cycles). Uses a 2D distance matrix."),
  body("Core idea: For each intermediate vertex k, check if path i→k→j is shorter than current i→j."),
  formula("D[i][j] = min(D[i][j], D[i][k] + D[k][j])  for k = 1, 2, ..., V"),
  body("Three nested loops: outer loop on k (intermediate), middle on i (source), inner on j (destination)."),
  img('code_floyd.png', 400),
  img('ch3_floyd', 420),
  bl("Time: O(V³). Space: O(V²)."),
  body("Example: Initial and final distance matrices for graph with 4 vertices:"),
  body("Edges: 1→2(3), 1→3(8), 2→3(−4), 2→4(1), 3→4(7), 4→1(2), 4→3(5)"),
  makeTable(
    ['Initial D', '1', '2', '3', '4'],
    [
      ['1', '0', '3', '8', '∞'],
      ['2', '∞', '0', '−4', '1'],
      ['3', '∞', '∞', '0', '7'],
      ['4', '2', '∞', '5', '0'],
    ]
  ),
  body("Iteration k=1 (through vertex 1): D[4][2] = min(∞, D[4][1]+D[1][2]) = min(∞, 2+3) = 5"),
  body("Iteration k=2 (through vertex 2): D[1][3] = min(8, D[1][2]+D[2][3]) = min(8, 3+(−4)) = −1"),
  body("Iteration k=3 (through vertex 3): D[4][1] stays 2 (no improvement through 3)"),
  body("Iteration k=4 (through vertex 4): D[2][1] = min(∞, D[2][4]+D[4][1]) = min(∞, 1+2) = 3"),
  body("After all 4 iterations — final distance matrix:"),
  makeTable(
    ['Final D', '1', '2', '3', '4'],
    [
      ['1', '0', '3', '−1', '4'],
      ['2', '3', '0', '−4', '1'],
      ['3', '9', '12', '0', '7'],
      ['4', '2', '5', '1', '0'],
    ]
  ),
  body("Verification: D[2][1]=3 via 2→4→1 (1+2=3). D[1][3]=−1 via 1→2→3 (3−4=−1). D[3][1]=9 via 3→4→1 (7+2=9). D[3][2]=12 via 3→4→1→2 (7+2+3=12). ✓"),
  img('code_floyd_extra.png', 420),

  makeTable(
    ['Algorithm', 'Type', 'Time', 'Neg Weights?'],
    [
      ['Dijkstra', 'SSSP', 'O((V+E)logV)', 'No'],
      ['Bellman-Ford', 'SSSP', 'O(VE)', 'Yes'],
      ['Floyd-Warshall', 'APSP', 'O(V³)', 'Yes (no neg cycle)'],
    ]
  ),
  sp(40),

  // 3.4.5 Social Networks
  subHead("3.4.5  Graphs in Social Networks"),
  body("Social networks modeled as graphs: users = vertices, connections = edges."),
  makeTable(
    ['Application', 'Graph Technique', 'Example'],
    [
      ['Friend suggestion', 'BFS 2-hop', 'Friends of friends who are not your friends'],
      ['Shortest connection', 'BFS', 'Degrees of separation between users'],
      ['Community detection', 'Dense subgraph', 'Groups of closely connected users'],
      ['Influencer identification', 'Degree centrality', 'Users with most connections'],
      ['News feed ranking', 'Weighted graph', 'Edge weights = interaction frequency'],
    ]
  ),
  body("Six degrees of separation: Research shows most people in social networks are connected within 6 hops. Facebook average: 3.5 hops."),
  img('ch3_social', 400),

  subHead("Connected Components"),
  body("In an undirected graph, a connected component is a maximal set of vertices reachable from each other. Use BFS/DFS from each unvisited vertex to find all components."),
  img('ch3_components', 400),
  body("Algorithm: Initialize all vertices as unvisited. For each unvisited vertex, run DFS/BFS — all vertices visited in one traversal form one component. Increment component count."),
  img('code_find_components.png', 400),

  subHead("Cycle Detection"),
  body("Undirected graph: DFS — if we visit an already-visited vertex that is NOT the parent → cycle exists."),
  img('code_cycle_undirected.png', 400),
  img('code_cycle_und_extra.png', 400),
  body("Directed graph: DFS with colors (WHITE=unvisited, GRAY=in progress, BLACK=done). If we encounter a GRAY vertex → back edge → cycle."),
  img('code_cycle_directed.png', 400),
  img('code_cycle_dir_extra.png', 400),

  subHead("Strongly Connected Components (Directed Graphs)"),
  body("An SCC is a maximal set of vertices where every vertex is reachable from every other."),
  body("Kosaraju's Algorithm: (1) DFS on G, push vertices to stack by finish time. (2) Create transpose graph G^T (reverse all edges). (3) Pop from stack, DFS on G^T — each DFS tree is one SCC."),
  img('ch3_scc', 400),
  img('code_tarjan_scc.png', 420),

  subHead("Bipartite Graph"),
  body("A graph whose vertices can be divided into two disjoint sets such that every edge connects a vertex in one set to one in the other. Check using BFS: 2-color the graph — if any adjacent vertices have the same color, NOT bipartite."),
  img('ch3_bipartite', 380),
  body("Applications: Job assignment problems, matching problems, scheduling, graph coloring with 2 colors."),
  img('code_is_bipartite.png', 400),
  img('code_bipartite_extra.png', 400),

  // Complexity Summary
  makeTable(
    ['Algorithm', 'Time', 'Space', 'Use Case'],
    [
      ['BFS', 'O(V+E)', 'O(V)', 'Unweighted shortest path'],
      ['DFS', 'O(V+E)', 'O(V)', 'Cycle detection, topo sort'],
      ['Dijkstra', 'O((V+E)logV)', 'O(V)', 'SSSP (non-neg weights)'],
      ['Bellman-Ford', 'O(VE)', 'O(V)', 'SSSP (neg weights OK)'],
      ['Floyd-Warshall', 'O(V³)', 'O(V²)', 'All pairs shortest path'],
      ["Prim's", 'O((V+E)logV)', 'O(V)', 'MST (dense graphs)'],
      ["Kruskal's", 'O(E logE)', 'O(V)', 'MST (sparse graphs)'],
      ['Topo Sort', 'O(V+E)', 'O(V)', 'DAG ordering'],
    ]
  ),
];

// ════════════════════════════════════════════════════════════════════════
// CHAPTER 4 : HASH TABLE (5 Hours) — Target: ~9 pages
// ════════════════════════════════════════════════════════════════════════
const ch4 = [
  chHead("Chapter 4 :  Hash Table  (5 Hours)"),
  sp(40),

  body("All data structures studied so far — arrays, linked lists, trees — require at least O(log n) time for searching in the best case. Hashing provides a fundamentally different approach: instead of comparing keys, it computes the storage location directly from the key value using a mathematical function, achieving O(1) average-case performance for search, insert, and delete."),
  body("The idea is simple: given a key k, apply a hash function h(k) to compute an array index where the value should be stored. If every key maps to a unique index, all operations are O(1). In practice, different keys may produce the same index (collision), so collision resolution techniques are essential. The two main strategies are Open Addressing (store everything in the table, probe for next empty slot) and Chaining (each slot holds a linked list of colliding keys)."),
  body("Hash tables are used everywhere in computing: symbol tables in compilers, database indexing for equality queries, caching (memcached, Redis), dictionaries in Python/Java, routing tables, and duplicate detection. The trade-off is that hashing does not support ordered operations (find min, range queries) — for those, BSTs or B-Trees are preferred."),
  sp(40),

  // ─── 4.1 Concept ────────────────────────────────────────────────
  secHead("4.1  Concept of Hashing"),
  body("Hashing maps keys to array indices using a hash function, enabling O(1) average-case search, insert, and delete."),
  img('ch4_hash_concept', 420),
  formula("index = h(key) = key mod table_size"),
  sp(40),

  // ─── 4.2 Terminologies ─────────────────────────────────────────
  secHead("4.2  Terminologies"),
  makeTable(
    ['Term', 'Definition'],
    [
      ['Hash Table', 'Array of fixed size (m) storing key-value pairs'],
      ['Hash Function', 'Maps key → index in range [0, m−1]'],
      ['Bucket', 'Each slot/index in the hash table'],
      ['Hash Address', 'Index computed by hash function for a given key'],
      ['Collision', 'Two different keys map to the same index'],
      ['Overflow', 'No space to store a colliding key'],
      ['Load Factor (λ)', 'n/m (number of keys / table size)'],
    ]
  ),
  sp(40),

  // ─── 4.3 Hash Functions ─────────────────────────────────────────
  secHead("4.3  Hash Functions"),

  subHead("Properties of a Good Hash Function"),
  bl("Uniform distribution — keys spread evenly across buckets"),
  bl("Deterministic — same key always produces same hash"),
  bl("Efficient — O(1) computation"),
  bl("Minimize collisions"),

  subHead("4.3.1  Division Method"),
  formula("h(k) = k mod m"),
  body("Simple and fast. Choose m as a prime number not close to power of 2 for best distribution."),
  body("Example: m=10, h(54)=4, h(26)=6, h(93)=3, h(17)=7, h(31)=1."),
  imp("Avoid m = 2^p (power of 2) — only looks at last p bits. Avoid m = 10^p — only looks at last p digits."),

  subHead("4.3.2  Mid-Square Method"),
  body("Square the key, extract middle digits as hash. The middle portion depends on all digits of the key, giving better distribution."),
  body("Example with table size 100 (need 2 middle digits):"),
  makeTable(
    ['Key', 'Key²', 'Middle 2 Digits', 'Hash'],
    [
      ['56', '3136', '13', '13'],
      ['73', '5329', '32', '32'],
      ['98', '9604', '60', '60'],
      ['21', '0441', '44', '44'],
    ]
  ),

  subHead("4.3.3  Folding Method"),
  body("Divide key into equal-sized parts, add them together (mod table size)."),
  img('ch4_folding', 380),
  body("Example: key=123456, fold into 12+34+56=102, h=102 mod m."),

  subHead("4.3.4  Multiplication Method"),
  formula("h(k) = ⌊m × (k×A mod 1)⌋    where 0 < A < 1"),
  body("Knuth suggests A ≈ 0.6180339887 (golden ratio conjugate). Works well with any m."),
  body("Example: k=123, m=8, A≈0.618 → k×A=76.014 → frac=0.014 → h(123) = ⌊8 × 0.014⌋ = 0."),

  makeTable(
    ['Method', 'Formula', 'Best When'],
    [
      ['Division', 'k mod m', 'm is prime'],
      ['Mid-Square', 'middle digits of k²', 'Key distribution unknown'],
      ['Folding', 'sum of key parts', 'Long keys (phone numbers, IDs)'],
      ['Multiplication', '⌊m(kA mod 1)⌋', 'Any m; A = (√5−1)/2'],
    ]
  ),
  sp(40),

  // ─── 4.4 Collision Resolution ───────────────────────────────────
  secHead("4.4  Collision Resolution Techniques"),

  subHead("4.4.1  Open Addressing"),
  body("All elements stored in the table itself. On collision, probe for next empty slot."),

  topicH("Linear Probing"),
  formula("h(k, i) = (h(k) + i) mod m      i = 0, 1, 2, ..."),
  body("Simple but suffers from primary clustering — consecutive occupied slots form clusters, degrading performance."),
  body("Example: m=10, h(k)=k mod 10. Insert 25→slot 5, 35→slot 5 collision→probe to 6, 45→slot 5 collision→6→7."),
  makeTable(
    ['Key', 'h(k)', 'Probe 0', 'Probe 1', 'Probe 2', 'Final Slot'],
    [
      ['25', '5', '5 (empty)', '—', '—', '5'],
      ['35', '5', '5 (taken)', '6 (empty)', '—', '6'],
      ['45', '5', '5 (taken)', '6 (taken)', '7 (empty)', '7'],
      ['15', '5', '5 (taken)', '6 (taken)', '7 (taken) → 8', '8'],
    ]
  ),
  img('ch4_linear_probe', 380),

  topicH("Quadratic Probing"),
  formula("h(k, i) = (h(k) + c₁i + c₂i²) mod m"),
  body("Reduces primary clustering but may cause secondary clustering. Typically c₁=0, c₂=1 so probes are h, h+1, h+4, h+9, ..."),
  body("Example: m=10, h(k)=k mod 10. Insert 25→slot 5. Insert 35→h=5, probe h+1²=6. Insert 45→h=5, try 6(taken), try h+2²=9. Insert 55→h=5, try 6,9(taken), try h+3²=14 mod 10=4."),
  img('ch4_quadratic', 380),
  imp("Quadratic probing may not probe all slots. If table is more than half full, insertion may fail even with empty slots. Keep λ < 0.5."),

  topicH("Double Hashing (Rehashing)"),
  formula("h(k, i) = (h₁(k) + i × h₂(k)) mod m"),
  body("Uses second hash function for probe step. Best open addressing method — produces near-uniform probing. No clustering."),
  body("Common choice: h₁(k) = k mod m, h₂(k) = 1 + (k mod (m−1)). h₂ must never be 0."),
  body("Example: m=7, h₁(k)=k mod 7, h₂(k)=1+(k mod 5). Insert 10→h₁=3. Insert 17→h₁=3 (collision), h₂=1+(17%5)=3, probe (3+3)%7=6. Insert 24→h₁=3, h₂=1+(24%5)=5, probe (3+5)%7=1."),
  img('ch4_double_hash', 380),

  subHead("Deletion in Open Addressing"),
  body("Cannot simply mark slot as empty (breaks probe chains). Use tombstone (DELETED marker): search skips tombstones, insert can reuse them."),
  body("Search rule: Continue probing past DELETED slots, stop only at truly EMPTY slots. Insert rule: Can reuse DELETED slots for new insertions."),

  subHead("Rehashing (Dynamic Resize)"),
  body("When load factor exceeds threshold (~0.7), create a new table of double size and reinsert all keys using new hash function h'(k) = k mod m'."),
  img('ch4_rehash', 400),
  bl("Time: O(n) for rehash, but amortized O(1) per insert over many operations."),

  makeTable(
    ['Technique', 'Probe Sequence', 'Clustering', 'Performance'],
    [
      ['Linear', 'h+1, h+2, ...', 'Primary (bad)', 'Degrades fast at high λ'],
      ['Quadratic', 'h+1, h+4, h+9, ...', 'Secondary', 'Better than linear'],
      ['Double Hash', 'h+h₂, h+2h₂, ...', 'None', 'Best open addressing'],
    ]
  ),
  sp(40),

  subHead("4.4.2  Chaining"),

  topicH("Separate Chaining"),
  body("Each bucket is a linked list. Colliding keys are appended to the list. Load factor can exceed 1."),
  img('ch4_chaining', 400),
  body("Example: m=7, h(k)=k mod 7. Insert 14→slot 0, 21→slot 0 (chain with 14), 7→slot 0 (chain). Slot 0 has list: 14→21→7."),
  bl("Search: O(1 + λ) average. Insert: O(1) (insert at head). Delete: O(1 + λ)."),
  bl("Advantage: Simple, handles high load, no clustering. Disadvantage: Extra memory for pointers."),

  topicH("Coalesced Chaining"),
  body("Combines open addressing and chaining. Colliding keys stored in the table with links forming chains. No external memory needed."),
  body("Example (m=7, h(k)=k mod 7): Insert 3→slot 3, Insert 10→h=3 collision→store at slot 6, link 3→6. Insert 17→h=3→store at slot 5, link 6→5."),
  makeTable(
    ['Step', 'Key', 'h(k)', 'Stored At', 'Chain'],
    [
      ['1', '3', '3', 'Slot 3', '3→nil'],
      ['2', '10', '3', 'Slot 6', '3→6'],
      ['3', '17', '3', 'Slot 5', '3→6→5'],
      ['4', '4', '4', 'Slot 4', '4→nil'],
      ['5', '11', '4', 'Slot 2', '4→2'],
    ]
  ),

  makeTable(
    ['', 'Separate Chaining', 'Coalesced Chaining'],
    [
      ['Storage', 'External linked lists', 'Inside table with links'],
      ['Extra Memory', 'Pointers per node', 'Link field per slot'],
      ['Load Factor', 'Can exceed 1', 'Must be ≤ 1'],
      ['Performance', 'O(1+λ)', 'Between separate and open addr.'],
    ]
  ),
  sp(40),

  // ─── Performance Summary ────────────────────────────────────────
  subHead("Performance Comparison (Expected Probes)"),
  makeTable(
    ['Technique', 'λ=0.5 (Success)', 'λ=0.5 (Fail)', 'λ=0.9 (Success)', 'λ=0.9 (Fail)'],
    [
      ['Linear Probing', '1.50', '2.50', '5.50', '50.5'],
      ['Double Hashing', '1.39', '2.00', '2.56', '10.0'],
      ['Separate Chain', '1.25', '1.10', '1.45', '1.50'],
    ]
  ),
  imp("Keep load factor below 0.7 for open addressing. Separate chaining works well even at λ > 1."),
  sp(40),

  // Applications
  subHead("Applications of Hash Tables"),
  makeTable(
    ['Application', 'How Hashing is Used'],
    [
      ['Symbol Tables (Compilers)', 'Variable names → memory locations. O(1) lookup during compilation.'],
      ['Database Indexing', 'Hash index for equality queries (WHERE id = 42). Faster than B-tree for exact match.'],
      ['Caching/Memoization', 'Store computed results: key=input, value=output. Avoid recomputation.'],
      ['Spell Checkers', 'Dictionary stored in hash table. O(1) word lookup.'],
      ['Duplicate Detection', 'Insert items into hash set. If already present → duplicate found.'],
      ['Counting Frequencies', 'key=element, value=count. Increment on each occurrence.'],
    ]
  ),

  // Final comparison
  subHead("Comparison of All Collision Resolution Techniques"),
  makeTable(
    ['Technique', 'Space', 'Search', 'Insert', 'Delete', 'λ Range'],
    [
      ['Linear Probing', 'O(m)', 'O(1/(1−λ))', 'O(1/(1−λ))', 'Tombstone', '< 0.7'],
      ['Quadratic', 'O(m)', 'O(1/(1−λ))', 'O(1/(1−λ))', 'Tombstone', '< 0.5'],
      ['Double Hash', 'O(m)', 'O(1/(1−λ))', 'O(1/(1−λ))', 'Tombstone', '< 0.7'],
      ['Separate Chain', 'O(m+n)', 'O(1+λ)', 'O(1)', 'O(1+λ)', 'Any (>1 ok)'],
      ['Coalesced', 'O(m)', 'O(1+λ)', 'O(1)', 'Complex', '< 1'],
    ]
  ),
  sp(40),

  // End of notes — Beautiful book ending
  sp(200),
  
  // Decorative top border
  P({ alignment:AlignmentType.CENTER, spacing:{after:80},
      border:{ top:{style:BorderStyle.DOUBLE,size:12,color:"1F3864"} } }, []),
  
  // Main ending message
  P({ alignment:AlignmentType.CENTER, spacing:{after:40} },
    [t("✦",{bold:true,size:32,color:"DC2626"})]),
  P({ alignment:AlignmentType.CENTER, spacing:{after:40} },
    [t("END OF NOTES",{bold:true,size:38,color:"1F3864",font:"Georgia"})]),
  P({ alignment:AlignmentType.CENTER, spacing:{after:80} },
    [t("✦",{bold:true,size:32,color:"DC2626"})]),
  
  // Summary box
  P({ alignment:AlignmentType.CENTER, spacing:{after:20},
      border:{ top:{style:BorderStyle.SINGLE,size:6,color:"2E74B5"},
               bottom:{style:BorderStyle.SINGLE,size:6,color:"2E74B5"} } },
    [t("DATA STRUCTURE II — Complete Coverage",{bold:true,size:24,color:"2E74B5"})]),
  
  sp(80),
  
  // Chapter completion marks
  P({ alignment:AlignmentType.CENTER, spacing:{after:15} },
    [t("✓",{bold:true,size:22,color:"059669"}), t("  Chapter 1: Trees  ",{size:21,color:"1F3864"}), t("✓",{bold:true,size:22,color:"059669"})]),
  P({ alignment:AlignmentType.CENTER, spacing:{after:15} },
    [t("✓",{bold:true,size:22,color:"059669"}), t("  Chapter 2: Search Trees  ",{size:21,color:"1F3864"}), t("✓",{bold:true,size:22,color:"059669"})]),
  P({ alignment:AlignmentType.CENTER, spacing:{after:15} },
    [t("✓",{bold:true,size:22,color:"059669"}), t("  Chapter 3: Graph  ",{size:21,color:"1F3864"}), t("✓",{bold:true,size:22,color:"059669"})]),
  P({ alignment:AlignmentType.CENTER, spacing:{after:100} },
    [t("✓",{bold:true,size:22,color:"059669"}), t("  Chapter 4: Hash Table  ",{size:21,color:"1F3864"}), t("✓",{bold:true,size:22,color:"059669"})]),
  
  // Content summary
  P({ alignment:AlignmentType.CENTER, spacing:{after:15} },
    [t("50 Pages",{bold:true,size:20,color:"2E74B5"}), t("  ◆  ",{size:18,color:"DC2626"}),
     t("99 Diagrams & Code Blocks",{bold:true,size:20,color:"2E74B5"})]),
  P({ alignment:AlignmentType.CENTER, spacing:{after:100} },
    [t("45 Tables",{bold:true,size:20,color:"2E74B5"}), t("  ◆  ",{size:18,color:"DC2626"}),
     t("Complete Theory & Examples",{bold:true,size:20,color:"2E74B5"})]),
  
  // Author signature style
  P({ alignment:AlignmentType.CENTER, spacing:{after:30},
      border:{ top:{style:BorderStyle.SINGLE,size:4,color:"BDC3C7"} } },
    [t("Prepared with care by",{italics:true,size:19,color:"6B7280"})]),
  P({ alignment:AlignmentType.CENTER, spacing:{after:15} },
    [t("AMIT DIVEKAR",{bold:true,size:28,color:"1F3864",font:"Georgia"})]),
  P({ alignment:AlignmentType.CENTER, spacing:{after:100} },
    [new ExternalHyperlink({
       link: "https://amitdevx.tech",
       children: [t("www.amitdevx.tech",{size:20,color:"2563EB",italics:true})]
     })]),
  
  // Decorative bottom border
  P({ alignment:AlignmentType.CENTER, spacing:{after:60},
      border:{ bottom:{style:BorderStyle.DOUBLE,size:12,color:"1F3864"} } }, []),
  
  sp(60),
];

// ════════════════════════════════════════════════════════════════════════
// BUILD DOCUMENT
// ════════════════════════════════════════════════════════════════════════
const allChildren = [
  ...cover,
  ...syllabusIndex,
  ...ch1,
  ...ch2,
  ...ch3,
  ...ch4,
];

const doc = new Document({
  styles: {
    default: {
      document: { run: { font: "Times New Roman", size: 22 } }
    },
    paragraphStyles: [
      {
        id: "Heading2", name: "Heading 2", basedOn: "Normal", next: "Normal",
        run: { size: 27, bold: true, font: "Times New Roman" },
        paragraph: { spacing: { before: 200, after: 100 }, outlineLevel: 1 }
      }
    ]
  },
  sections: [{
    properties: {
      page: {
        size: { width: 11906, height: 16838 },  // A4
        margin: { top: 1080, right: 1080, bottom: 1080, left: 1280 },
        pageNumbers: { start: 1 }
      }
    },
    headers: {
      default: new Header({
        children: [
          P({ alignment: AlignmentType.RIGHT, spacing: { after: 0 } }, [
            t("Data Structure II", { size: 18, italics: true, color: "808080" }),
          ])
        ]
      })
    },
    footers: {
      default: new Footer({
        children: [
          P({ alignment: AlignmentType.CENTER, spacing: { before: 0 } }, [
            t("— ", { size: 18, color: "808080" }),
            new TextRun({
              children: [PageNumber.CURRENT],
              font: "Times New Roman",
              size: 18,
              color: "808080"
            }),
            t(" —", { size: 18, color: "808080" }),
          ])
        ]
      })
    },
    children: allChildren
  }]
});

const outDocx = path.join(__dirname, 'DS_Notes_Complete.docx');
Packer.toBuffer(doc).then(buf => {
  fs.writeFileSync(outDocx, buf);
  console.log('✅ DOCX written to:', outDocx);
  console.log('   Size:', Math.round(buf.length/1024), 'KB');
}).catch(err => {
  console.error('Error:', err.message);
  process.exit(1);
});
