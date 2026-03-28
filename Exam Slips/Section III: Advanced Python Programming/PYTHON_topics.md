Advanced Python Programming - Topic Analysis

> **Subject:** Advanced Python Programming  
> **Total Slips:** 30  
> **Questions per Slip:** Q1 (15 marks) + Q2 (25 marks) with OR option


  2. Main Topics with Subtopics

  2.1 Pandas/DataFrame Operations

| Subtopic | Slips | Count |
|----------|-------|-------|
| **Creation from dict** | 1, 4, 6 | 3 |
| **Creation from CSV** | 12, 29 | 2 |
| **Operations (filter/select/modify)** | 2, 4, 6, 16, 19, 26 | 6 |
| **Merging/Joining** | 9, 13, 22 | 3 |
| **GroupBy** | 20 | 1 |
| **Statistics (sum/mean/median/mode/std)** | 10, 12 | 2 |
| **head/tail operations** | 21 | 1 |

**Key Questions:**
- IPL DataFrame operations (Slip 2, 16, 19)
- Student DataFrame with GroupBy (Slip 9, 20)
- Pencil/Pen DataFrame operations (Slip 4)
- Iris.csv DataFrame operations (Slip 29)
- Statistical operations (Slip 10, 12)


  2.3 Exception Handling

| Subtopic | Slips | Count |
|----------|-------|-------|
| **ZeroDivisionError** | 3, 22 | 2 |
| **TypeError** | 6 | 1 |
| **Custom Exception** | 2 | 1 |
| **General try-except** | 3, 6, 22 | 3 |

**Key Questions:**
- ZeroDivisionError handling (Slip 3, 22)
- TypeError exception (Slip 6)
- Custom exception for marks validation (Slip 2)


  2.5 String Operations

| Subtopic | Slips | Count |
|----------|-------|-------|
| **Count vowels/consonants** | 2, 20 | 2 |
| **Words without vowels** | 5, 11, 23 | 3 |
| **Extract capital words** | 7 | 1 |
| **Remove special chars** | 7 | 1 |
| **Replace patterns** | 17, 30 | 2 |
| **Remove whitespaces** | 26 | 1 |

**Key Questions:**
- Count vowels, consonants, symbols (Slip 2, 20)
- Display words without vowels (Slip 5, 11, 23)
- Extract capital words, remove special chars (Slip 7)
- Replace spacecolon, commadot (Slip 17)
- Replace 'a' with '*' (Slip 30)


  2.7 Flask Web Development

| Subtopic | Slips | Count |
|----------|-------|-------|
| **Portfolio page** | 6 | 1 |
| **Library Book List** | 7, 15 | 2 |
| **College Info page** | 8, 24 | 2 |
| **Task Manager with PostgreSQL** | 11 | 1 |

**Flask Route Examples:**
```python

 Portfolio - Slip 6
@app.route('/portfolio')
def portfolio():
    return render_template('portfolio.html')

 Library Books - Slip 7, 15
@app.route('/books')
def books():
    return render_template('books.html', books=book_list)

 College Info - Slip 8, 24
@app.route('/college')
def college():
    return render_template('college.html')
```


  2.9 Random Module

| Subtopic | Slips | Count |
|----------|-------|-------|
| **Shuffle list** | 4, 19, 25 | 3 |
| **Random from sequences** | 8, 12, 17 | 3 |
| **Random radius for circle** | 27 | 1 |

**Key Functions:**
```python
import random
random.shuffle(list)            Shuffle in place
random.choice(sequence)         Random element
random.sample(sequence, k)      k random elements
random.randint(a, b)            Random integer
```


  2.11 OS Module

| Subtopic | Slips | Count |
|----------|-------|-------|
| **List directory** | 18, 28 | 2 |
| **List .py files** | 1, 27 | 2 |
| **Check file/folder** | 19, 28 | 2 |

**Key Functions:**
```python
import os
os.listdir(path)       List directory contents
os.path.isfile(path)   Check if file
os.path.isdir(path)    Check if directory
os.getcwd()            Current working directory
```


  4. Repeated/Similar Questions

  Identical Questions (Same Question, Different Slips)

| Question | Slips |
|----------|-------|
| ZeroDivisionError handling | 3, 22 |
| Words without vowels | 5, 11, 23 |
| IPL DataFrame operations | 2, 16, 19 |
| Package vehicle/types | 1, 16, 26 |
| Package banking | 5, 21 |
| Package finance_tools | 10, 25 |
| Package education | 18, 28 |
| Module factorial/power/vowels | 3, 14 |
| Flask Library Book List | 7, 15 |
| Flask College Info | 8, 24 |
| Shuffle cards | 19, 25 |
| Random from sequences | 8, 12, 17 |
| URL validation regex | 15, 25 |
| Mobile validation regex | 18, 29 |
| Armstrong & digit sum | 9, 17 |
| Factorial iterator class | 10, 22 |
| Regex 3-letter words | 16, 28 |
| Pass/fail function | 24, 30 |
| List .py files | 1, 27 |
| Directory listing | 19, 28 |
| Time module formatting | 12, 15, 23, 30 |
| File read with stats | 3, 7, 21 |

  Similar Concept Questions

| Concept | Variations | Slips |
|---------|------------|-------|
| String counting | Vowels/consonants/symbols | 2, 20 |
| DataFrame creation | From dict, CSV, list | 1, 4, 6, 12, 29 |
| File operations | Read with seek/tell | 13, 14, 20 |
| Circle calculations | Area vs Circumference | 8, 27 |


  6. OR Question Comparison

| Slip | Q2 Main | Q2 OR | Easier Option | Reason |
|------|---------|-------|---------------|--------|
| 01 | Package vehicle | List .py files |  OR | Simple os module |
| 02 | IPL DataFrame | Custom exception |  Main | DataFrame is formulaic |
| 03 | Module creation | File read stats |  OR | File I/O is simpler |
| 04 | DataFrame ops | File write/append |  OR | Basic file operations |
| 05 | Package banking | Prime list comp |  OR | One-liner solution |
| 06 | DataFrame ops | Flask Portfolio |  Main | DataFrame is predictable |
| 07 | Flask Library | File copy stats |  OR | No web framework needed |
| 08 | Random sampling | Flask College |  Main | Random is very simple |
| 09 | DataFrame join | Armstrong & digit |  OR | Simple loops |
| 10 | Package finance | Factorial iterator |  Main | Package is straightforward |
| 11 | Flask + PostgreSQL | Words without vowels |  OR | String manipulation only |
| 12 | Time module | Random sequences |  OR | Random is simpler |
| 13 | File seek/tell | DataFrame join |  Main | File ops more direct |
| 14 | File byte position | Module creation |  Main | File operations simpler |
| 15 | Flask Library | URL regex |  OR | Single regex pattern |
| 16 | IPL DataFrame | Package vehicle |  Main | DataFrame well-practiced |
| 17 | Random sequences | Armstrong & digit |  Main | Random is simpler |
| 18 | Mobile regex | Package education |  Main | Single regex pattern |
| 19 | Directory listing | IPL DataFrame |  Main | os.listdir is direct |
| 20 | File position | DataFrame GroupBy |  Main | File ops are simpler |
| 21 | File read stats | Package banking |  Main | File ops straightforward |
| 22 | DataFrame merge | Factorial iterator |  Main | Merge is well-documented |
| 23 | Time module | Words without vowels |  OR | String ops are easier |
| 24 | Pass/fail function | Flask College |  Main | Simple function |
| 25 | Package finance | URL validation |  OR | Single regex |
| 26 | Package vehicle | DataFrame ops |  OR | DataFrame well-practiced |
| 27 | Password regex | List .py files |  OR | os.listdir simple |
| 28 | Package education | Directory listing |  OR | os module direct |
| 29 | File append | Mobile validation |  Main | File append simpler |
| 30 | Pass/fail function | Time module |  Main | Function simpler |

 Summary of Easier Options:
- **Choose Main Q2:** 16 slips (53%)
- **Choose OR Q2:** 14 slips (47%)


  8. Quick Reference Code Templates

 DataFrame Template
```python
import pandas as pd

 Create from dict
df = pd.DataFrame({'col1': [1,2,3], 'col2': ['a','b','c']})

 Read CSV
df = pd.read_csv('file.csv')

 Basic operations
df.head(), df.tail(), df.describe()
df[df['col'] > value]   Filter
df.groupby('col').agg({'col2': 'sum'})   GroupBy
pd.merge(df1, df2, on='key')   Merge
```

 File Handling Template
```python

 Read with stats
with open('file.txt', 'r') as f:
    content = f.read()
    chars = len(content)
    words = len(content.split())
    lines = content.count('\n') + 1

 seek/tell
f.seek(10)   Move to position 10
pos = f.tell()   Get current position
```

 Package Template
```
my_package/
 __init__.py  (from .module1 import *)
 module1.py
 subpackage/
     __init__.py
     module2.py
```

 Flask Template
```python
from flask import Flask, render_template
app = Flask(__name__)

@app.route('/')
def home():
    return render_template('index.html', data=data)

if __name__ == '__main__':
    app.run(debug=True)
```

 Regex Template
```python
import re

 URL validation
pattern = r'^https?://[\w.-]+\.[a-z]{2,}'

 Mobile validation
pattern = r'^[6-9]\d{9}$'

 Password validation
pattern = r'^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&]).{8,}$'
```


*Total Questions Analyzed: 90 (30 slips  3 questions each)*
