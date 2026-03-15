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
   - Format: Jupyter Notebook solutions with Flask project folders
   - Topics: Pandas, Matplotlib, Flask, Data Processing

4. **[Section IV: Mathematics for Computer Science-II](./Section%20IV:%20Mathematics%20for%20Computer%20Science-II/)**
   - 20 exam slips on computational geometry
   - Format: Jupyter Notebook solutions with visualizations
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
│   ├── Slip_01_PYTHON_Solution.ipynb  (through Slip_30)
│   ├── Questions/
│   │   ├── Slip_01/ ... Slip_30/      (Question text + metadata)
│   ├── slip_06/ ... slip_24/          (Flask project folders)
│   └── vehicle/                       (Python package)
│
├── Section IV: Mathematics for Computer Science-II/
│   └── Slip_01 ... Slip_20_MATHS_Solution.ipynb
│
├── _references/             ← Reference PDFs and extracted text
│
└── PDF Question Papers (in _references/):
    ├── SYBSc(CS) Slips CS-253 MJP DS II and DBMS II 2025 Sem IV.pdf
    ├── SYBSc(CS) Slips CS-271-VSC-P Adv. Python Prog 25-26.pdf
    └── maths slip sem 4.pdf
```

---

## File Organization Within Each Section

### Section I - Data Structures-II

Inside each `Slip_XX/` you'll find:
- **Slip_XX_Q1_OptionA.c** - Implementation Option A
- **Slip_XX_Q1_OptionB.c** - Implementation Option B
- **Slip_XX_DS_SOLUTION.md** - Markdown solution with code comments
- **Slip_XX_DS_SOLUTION.pdf** - PDF version of solution
- **btree.h** - Header files (if needed for tree-based problems)

### Section II - Database Management Systems-II

Inside each `Slip_XX/` you'll find:
- **Slip_XX_DBMS_Solution.sql** - SQL solution script
- **Slip_XX_DBMS_SOLUTION.md** - Markdown solution with explanations
- **Slip_XX_DBMS_SOLUTION.pdf** - PDF version of solution

### Section III - Advanced Python Programming

At the section root level:
- **Slip_XX_PYTHON_Solution.ipynb** - Jupyter Notebook solutions (30 files)

In `Questions/Slip_XX/`:
- **Slip_XX_PYTHON.txt** - Problem statement
- **metadata.txt** - Slip metadata (topics, marks, difficulty)

Flask project folders (`slip_06/`, `slip_07/`, `slip_08/`, `slip_11/`, `slip_15/`, `slip_24/`):
- **slip_XX_Q1/Q1/** - Flask app for practice/Q1
- **slip_XX_Q2/Q2/** - Flask app for Q2/Q2 OR
- Each contains `QXX_appN.py` and `templates/index.html`

### Section IV - Mathematics for Computer Science-II

At the section root level:
- **Slip_XX_MATHS_Solution.ipynb** - Jupyter Notebook solutions (20 files)
- Notebooks contain mathematical solutions with SymPy and Matplotlib visualizations

---

## How to Access Specific Slips

### By Subject Section
- **Data Structures**: Open `Section I: Data Structures-II/` and navigate to `Slip_01/` through `Slip_30/`
- **Databases**: Open `Section II: Database Management Systems II/` and navigate to `Slip_01/` through `Slip_30/`
- **Python**: Open `Section III: Advanced Python Programming/` and open `Slip_XX_PYTHON_Solution.ipynb`
- **Mathematics**: Open `Section IV: Mathematics for Computer Science-II/` and open `Slip_XX_MATHS_Solution.ipynb`

### By Topic
1. Refer to **TOPICS_INDEX.md** to find which slips cover your topic of interest
2. Open the relevant section folder
3. Navigate to the specific slip number

### By Difficulty
- Generally, slips are organized in increasing order of difficulty within each section
- Start with Slip_01 and progress sequentially

---

## File Access Patterns

### For Question Review (Section III)
```
./Section III: Advanced Python Programming/Questions/Slip_XX/Slip_XX_PYTHON.txt
```

### For Solution Notebooks
```
./Section III: Advanced Python Programming/Slip_XX_PYTHON_Solution.ipynb
./Section IV: Mathematics for Computer Science-II/Slip_XX_MATHS_Solution.ipynb
```

### For Solution Code/Scripts (Sections I & II)
```
./Section I: Data Structures-II/Slip_XX/Slip_XX_Q1_OptionA.c
./Section II: Database Management Systems II/Slip_XX/Slip_XX_DBMS_Solution.sql
```

### For Detailed Explanations
```
./Section I: Data Structures-II/Slip_XX/Slip_XX_DS_SOLUTION.md
./Section II: Database Management Systems II/Slip_XX/Slip_XX_DBMS_SOLUTION.md
```

---

## Quick Commands

### Browse all slips in a section
```bash
ls -d "Section I: Data Structures-II"/Slip_*
```

### Compile and run a C solution
```bash
cd "Section I: Data Structures-II/Slip_05/"
gcc -o solution Slip_05_Q1_OptionA.c
./solution
```

### Open a Python solution notebook
```bash
jupyter notebook "Section III: Advanced Python Programming/Slip_01_PYTHON_Solution.ipynb"
```

### Execute SQL solution
```bash
# Using PostgreSQL
psql -f "Section II: Database Management Systems II/Slip_01/Slip_01_DBMS_Solution.sql"
```

### Run a Flask app
```bash
cd "Section III: Advanced Python Programming/slip_06/slip_06_Q2/Q2/"
python Q06_app2.py
```

---

## Statistics Overview

| Section | Folder Name | Slips | File Type | Approx. Count |
|---------|-------------|-------|-----------|-------|
| I | Data Structures-II | 30 | .c, .md, .pdf, .h | ~135 files |
| II | Database Management Systems II | 30 | .sql, .md, .pdf | ~90 files |
| III | Advanced Python Programming | 30 | .ipynb, .txt, .py, .html | ~120 files |
| IV | Mathematics for Computer Science-II | 20 | .ipynb | ~20 files |
| **TOTAL** | | **110** | **Mixed** | **~365 files** |

---

## Reference Materials

Access supplementary materials in the **_references/** folder:
- Official exam question papers (PDF)
- Extracted plain-text versions of question papers
- Topic index and completion reports

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

**Total Exam Slips**: 110  
**Total Sections**: 4  
**File Formats**: C, SQL, Jupyter Notebooks, Flask, Markdown, PDF  
**Last Updated**: Semester 4, 2025
