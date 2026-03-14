# Navigation Guide - Exam Slips Directory Map

## Quick Navigation

### Main Sections

1. **[Section I: Data Structures-II](./Section%20I:%20Data%20Structures-II/)** 
   - 30 exam slips on advanced data structures
   - Format: C language implementations with detailed solutions
   - Topics: Trees, Graphs, Hashing, Searching, Sorting

2. **[Section II: Database Management Systems-II](./Section%20II:%20Database%20Management%20Systems%20II/)**
   - 30 exam slips on advanced SQL and PL/pgSQL
   - Format: SQL implementations with explanations
   - Topics: Stored Procedures, Triggers, Advanced Queries, CTEs

3. **[Section III: Advanced Python Programming](./Section%20III:%20Advanced%20Python%20Programming/)**
   - 30 exam slips on practical Python applications
   - Format: Python scripts with markdown explanations
   - Topics: Pandas, Matplotlib, Flask, Data Processing

4. **[Section IV: Mathematics for Computer Science-II](./Section%20IV:%20Mathematics%20for%20Computer%20Science-II/)**
   - 30 exam slips on computational geometry
   - Format: Python scripts with visualizations
   - Topics: Geometric algorithms, Transformations, Visualization

---

## Document Structure

```
Exam Slips/
│
├── README.md                 ← Start here for overview & instructions
├── TOPICS_INDEX.md          ← Find slips by topic
├── NAVIGATION.md            ← This file (directory map)
│
├── Section I: Data Structures-II/
│   ├── Slip_01/
│   ├── Slip_02/
│   ├── ... (Slips 03-29)
│   └── Slip_30/
│
├── Section II: Database Management Systems II/
│   ├── Slip_01/
│   ├── Slip_02/
│   ├── ... (Slips 03-29)
│   └── Slip_30/
│
├── Section III: Advanced Python Programming/
│   ├── Slip_01/
│   ├── Slip_02/
│   ├── ... (Slips 03-29)
│   └── Slip_30/
│
├── Section IV: Mathematics for Computer Science-II/
│   ├── Slip_01/
│   ├── Slip_02/
│   ├── ... (Slips 03-29)
│   └── Slip_30/
│
├── _references/             ← Supplementary materials
│
└── PDF Question Papers:
    ├── SYBSc(CS) Slips CS-253 MJP DS II and DBMS II 2025 Sem IV.pdf
    ├── SYBSc(CS) Slips CS-271-VSC-P Adv. Python Prog 25-26.pdf
    └── maths slip sem 4.pdf
```

---

## File Organization Within Each Slip

### Example: Section I - Data Structures-II

Inside `Slip_01/` you'll find:
- **Slip_01_DS.txt** - Question statement
- **Slip_01_Q1_OptionA.c** - Implementation Option A
- **Slip_01_Q1_OptionB.c** - Implementation Option B
- **Slip_01_DS_SOLUTION.txt** - Text solution explanation
- **Slip_01_DS_SOLUTION.md** - Markdown solution with code comments
- **Slip_01_DS_SOLUTION.pdf** - PDF version of solution
- **metadata.txt** - Slip metadata
- **btree.h** - Header files (if needed)

### Example: Section II - Database Management Systems-II

Inside `Slip_01/` you'll find:
- **Slip_01_DBMS.txt** - SQL/PL-pgSQL problem statement
- **Slip_01_DBMS_Solution.sql** - SQL solution script
- **Slip_01_DBMS_SOLUTION.txt** - Text explanation
- **Slip_01_DBMS_SOLUTION.md** - Markdown solution with explanations
- **Slip_01_DBMS_SOLUTION.pdf** - PDF version of solution
- **metadata.txt** - Slip metadata

### Example: Section III - Advanced Python Programming

Inside `Slip_01/` you'll find:
- **Slip_01_PYTHON.txt** - Problem statement
- **Slip_01_PYTHON_Solution.py** - Python solution script
- **Slip_01_PYTHON_SOLUTION.md** - Markdown explanation and code walkthrough
- **metadata.txt** - Slip metadata

### Example: Section IV - Mathematics for Computer Science-II

Inside `Slip_01/` you'll find:
- **Slip_01_MATHS.txt** - Mathematical problem statement
- **Slip_01_MATHS_Solution.py** - Python solution with visualization
- **Slip_01_MATHS_SOLUTION.md** - Detailed mathematical explanation
- **metadata.txt** - Slip metadata

---

## How to Access Specific Slips

### By Subject Section
- **Data Structures**: Open `Section I: Data Structures-II/` and navigate to Slip_01 through Slip_30
- **Databases**: Open `Section II: Database Management Systems II/` and navigate to Slip_01 through Slip_30
- **Python**: Open `Section III: Advanced Python Programming/` and navigate to Slip_01 through Slip_30
- **Mathematics**: Open `Section IV: Mathematics for Computer Science-II/` and navigate to Slip_01 through Slip_30

### By Topic
1. Refer to **TOPICS_INDEX.md** to find which slips cover your topic of interest
2. Open the relevant section folder
3. Navigate to the specific slip number

### By Difficulty
- Generally, slips are organized in increasing order of difficulty within each section
- Start with Slip_01 and progress sequentially through Slip_30

---

## File Access Patterns

### For Quick Question Review
```
./Section [I-IV]/Slip_XX/Slip_XX_[SUBJECT].txt
```

### For Solution Code/Scripts
```
./Section [I-IV]/Slip_XX/Slip_XX_[SUBJECT]_Solution.[c|sql|py]
```

### For Detailed Explanations
```
./Section [I-IV]/Slip_XX/Slip_XX_[SUBJECT]_SOLUTION.md
```

### For Visual Solutions (PDF)
```
./Section [I-IV]/Slip_XX/Slip_XX_[SUBJECT]_SOLUTION.pdf
```

---

## Quick Commands

### Browse all slips in a section
```bash
ls -d "Section I: Data Structures-II"/Slip_*
```

### View a specific question
```bash
cat "Section I: Data Structures-II/Slip_05/Slip_05_DS.txt"
```

### Compile and run a C solution
```bash
cd "Section I: Data Structures-II/Slip_05/"
gcc -o solution Slip_05_Q1_OptionA.c
./solution
```

### Run a Python solution
```bash
python "Section III: Advanced Python Programming/Slip_01/Slip_01_PYTHON_Solution.py"
```

### Execute SQL solution
```bash
# Using PostgreSQL
psql -f "Section II: Database Management Systems II/Slip_01/Slip_01_DBMS_Solution.sql"
```

---

## Statistics Overview

| Section | Folder Name | Slips | File Type | Count |
|---------|-------------|-------|-----------|-------|
| I | Data Structures-II | 30 | .c, .txt, .md, .pdf | ~180 files |
| II | Database Management Systems II | 30 | .sql, .txt, .md, .pdf | ~150 files |
| III | Advanced Python Programming | 30 | .py, .txt, .md | ~90 files |
| IV | Mathematics for Computer Science-II | 30 | .py, .txt, .md | ~90 files |
| **TOTAL** | | **120** | **Mixed** | **~510 files** |

---

## Reference Materials

Access supplementary materials in the **_references/** folder:
- Library headers and utilities
- Common algorithms and data structures
- Documentation for frameworks and libraries

---

## Navigation Tips

1. **Use README.md** for:
   - Overview of all sections
   - General instructions on how to use each section
   - Statistics and organization details

2. **Use TOPICS_INDEX.md** for:
   - Finding slips by specific topic or algorithm
   - Understanding how topics are distributed across slips
   - Identifying related slips for deeper learning

3. **Use NAVIGATION.md** (this file) for:
   - Understanding directory structure
   - Locating specific files
   - Quick command reference

---

**Total Exam Slips**: 120  
**Total Sections**: 4  
**File Formats**: C, SQL, Python, Markdown, PDF  
**Last Updated**: Semester 4, 2025
