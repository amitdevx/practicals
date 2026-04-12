DBMS-II Comprehensive Topic Analysis

**Total Slips Analyzed:** 30  
**Database System:** PostgreSQL (PL/pgSQL)


# 1. Topic Overview & Frequency

## Core Topics Summary Table

| Topic | Frequency | Percentage | Key Slips |
|-------|-----------|------------|-----------|
| **SELECT Queries** | 30/30 | 100% | All |
| **Stored Functions** | 30/30 | 100% | All |
| **Stored Procedures** | 30/30 | 100% | All |
| **Triggers** | 30/30 | 100% | All |
| **PL/pgSQL Programming** | 30/30 | 100% | All |
| **Schema Design** | 30/30 | 100% | All |
| **Data Manipulation (INSERT/UPDATE/DELETE)** | 26/30 | 87% | 1,3,5,7,8,9,11,12,13,14,15,16,18,20,21,23,24,25,26,27,28,29,30 |
| **ER Models** | 25/30 | 83% | 1,2,3,4,5,6,7,10,12,13,14,15,18,19,20,21,22,23,25,26,28,29,30 |
| **Database Constraints** | 24/30 | 80% | 1,2,3,7,12,13,14,15,16,18,19,20,21,22,23,25,26,27 |
| **Aggregate Functions** | 21/30 | 70% | 1,2,3,5,7,8,9,11,12,16,17,18,19,20,21,22,23,24,25,30 |
| **JOIN Operations** | 20/30 | 67% | 1,2,3,5,6,7,8,9,10,11,12,13,14,15,18,20,21,23,26,29 |
| **Loops (FOR/WHILE/UNCONDITIONAL)** | 15/30 | 50% | 7,11,14,15,17,21,23,24,27,30 |
| **Cursors** | 12/30 | 40% | 3,4,5,11,15,16,18,23,25,26,27,29 |
| **Exception Handling** | 8/30 | 27% | 2,9,10,14,21,25,28,30 |
| **UPDATE Operations** | 5/30 | 17% | 15,18,26,28 |

## Topic Popularity Distribution

```
Tier 1 (Core - 100%): SELECT, Functions, Procedures, Triggers, PL/pgSQL, Schema
Tier 2 (High - 80-99%): Data Manipulation, ER Models, Constraints
Tier 3 (Medium - 50-79%): Aggregate Functions, JOINs
Tier 4 (Common - 20-49%): Loops, Cursors, Exception Handling
Tier 5 (Specialized - <20%): UPDATE Operations, Transactions
```


# 3. Slip-wise Question Mapping

## Complete Question Matrix (30 Slips)

| Slip | Schema | Q2.1 Option A | Q2.1 Option B | Q2.2 | Topics |
|------|--------|---------------|---------------|------|--------|
| **1** | Project-Employee (M:M) | Function: Count Projects | Trigger: Validate Duration | Add/Sub/Mul | SELECT, Functions, Triggers, Aggregate, JOIN, Constraints |
| **2** | Person-Area (M:1) | Function: Count Persons | OR: Sum Income by Area | Division | SELECT, Functions, Aggregate, JOIN, Constraints |
| **3** | Student-Teacher (M:M) | Cursor: Students/Teachers | Trigger: Validate Student | Min/Max | SELECT, Cursor, Triggers, Aggregate, JOIN |
| **4** | Movies-Actor-Producer | Cursor: Count Movies | Trigger: Budget Validation | Pos/Neg/Zero | SELECT, Cursor, Triggers, Aggregate, JOIN |
| **5** | Student-Competition (M:M) | Cursor: Display Comps | Trigger: Competition Update | Max/Min of 3 | SELECT, Cursor, Triggers, Aggregate, JOIN, Loops |
| **6** | Bus-Route-Driver | Function: Driver Name | OR: Drivers Over 50 | Even/Odd | SELECT, Functions, JOIN, Constraints |
| **7** | Branch-Customer-Loan (Ternary) | Cursor: Count Customers | Trigger: Customer Valid | Sum Loop | SELECT, Cursor, Triggers, Aggregate, JOIN, Loops |
| **8** | Train-Passenger (M:M) | Function: Ticket Details | Trigger: Fare Message | Add 2 Numbers | SELECT, Functions, Triggers, Aggregate, JOIN |
| **9** | Student-Competition (M:M) | Trigger: Comp Update | OR: Total Prizes 2020 | Division | SELECT, Cursor, Triggers, Aggregate, JOIN |
| **10** | Book-Author (M:M) | Function: Books by Author | Trigger: Price Alert | Even Numbers | SELECT, Functions, Triggers, JOIN |
| **11** | Student-Subject (M:M) | Cursor: Total Marks | Trigger: Before Delete | Sum/Avg Loop | SELECT, Cursor, Triggers, Aggregate, JOIN, Loops |
| **12** | Project-Employee (M:M) | Trigger: Duration Check | OR: Employees by Project | Count Odd Loop | SELECT, Triggers, Aggregate, JOIN, Loops |
| **13** | Bus-Route-Driver | Trigger: Age Validation | OR: Drivers for Bus | Number in Range | SELECT, Triggers, JOIN, Constraints |
| **14** | Project-Employee (M:M) | Trigger: Duration Valid | OR: Employees by Project | Number in Words | SELECT, Triggers, JOIN, Loops |
| **15** | Person-Area (M:1) | Cursor: Update Income | Trigger: Person Valid | Odd Numbers | SELECT, Cursor, Update, Triggers, JOIN, Loops |
| **16** | Student-Subject (M:M) | Trigger: Before Delete | OR: Total Marks Cursor | Pos/Negative | SELECT, Cursor, Triggers, Aggregate |
| **17** | Student-Competition (M:M) | Trigger: Comp Update | OR: Prizes 2020 | Sum Loop | SELECT, Triggers, Aggregate, Loops |
| **18** | Item-Supplier (M:M) | Cursor: Items Rate>500 | Trigger: Rate Validation | Max of 3 | SELECT, Cursor, Triggers, Aggregate, JOIN, Constraints |
| **19** | Project-Employee (M:M) | Function: Count Projects | Trigger: Duration Valid | Min/Max of 2 | SELECT, Functions, Triggers, Aggregate, Constraints |
| **20** | Department-Employee (1:M) | Function: Max Salary | Trigger: Salary Valid | Multiply 2 | SELECT, Functions, Triggers, Aggregate, JOIN, Constraints |
| **21** | Doctor-Hospital (M:1) | Function: Avg Charges | Trigger: Charges Valid | Sum/Avg Loop | SELECT, Functions, Triggers, Aggregate, JOIN, Constraints, Loops |
| **22** | Project-Employee (M:M) | Function: Count Projects | Trigger: Duration Valid | Number Range | SELECT, Functions, Triggers, Aggregate, Constraints |
| **23** | Car-Driver (M:M) | Cursor: Cars by Driver | Trigger: Age Validation | Sum 100 Loop | SELECT, Cursor, Triggers, Aggregate, JOIN, Constraints, Loops |
| **24** | Department-Employee (1:M) | Function: Emp by Dept | Trigger: After Insert | Even Numbers | SELECT, Functions, Triggers, Aggregate, JOIN, Loops |
| **25** | Customer-Account (1:M) | Cursor: Customers by City | Trigger: Prevent Delete | Display Customers | SELECT, Cursor, Triggers, Aggregate, Constraints |
| **26** | Item-Supplier (M:M) | Cursor: Rate/Supplier | Trigger: Rate Difference | Subtraction | SELECT, Cursor, Triggers, Update, JOIN, Constraints |
| **27** | Student-Subject (M:M) | Cursor: Students by Class | Trigger: Marks Valid | Even Numbers | SELECT, Cursor, Triggers, Constraints, Loops |
| **28** | Company-Person (M:M) | Function: Update Share | Trigger: Before Delete | Division | SELECT, Functions, Triggers, Update, Constraints |
| **29** | Person-Area (M:1) | Cursor: Urban Persons | Trigger: Before Delete | Subtraction | SELECT, Cursor, Triggers, JOIN |
| **30** | Student-Teacher (M:M) | Function: Teachers Exp>10 | Trigger: Roll Valid | Sum/Avg Loop | SELECT, Functions, Triggers, Aggregate, JOIN, Constraints, Loops |


# 5. Repeated & Similar Questions

## Highly Repeated Questions

### **A. Count Projects per Employee** (4 slips)
- **Slips:** 1, 19, 22, + Slip 12 (reverse)
- **Question:** Create function to count how many projects an employee works on
- **Schema:** Project-Employee (M:M)
- **Pattern:**
  ```sql
  FUNCTION count_projects(eno INTEGER) RETURNS INTEGER
    SELECT COUNT(*) FROM Project_Employee WHERE eno = $1;
  ```
- **Difficulty:** Easy

### **B. Validate Duration > 0** (5 slips)
- **Slips:** 1, 12, 14, 19, 22
- **Question:** Create trigger to ensure project duration is positive
- **Pattern:**
  ```sql
  IF NEW.duration <= 0 THEN
    RAISE EXCEPTION 'Duration must be > 0';
  END IF;
  ```
- **Difficulty:** Easy

### **C. Min and Max of Numbers** (3+ slips)
- **Slips:** 5, 18, 19, 25
- **Question:** Procedure to find min/max of 2-3 numbers
- **Pattern:** Simple IF/ELSE comparisons
- **Difficulty:** Very Easy

### **D. Sum of First N Numbers** (4 slips)
- **Slips:** 7, 17, 23, 30
- **Question:** Use FOR/WHILE loop to sum first N or first 100 numbers
- **Pattern:**
  ```sql
  FOR i IN 1..100 LOOP
    sum := sum + i;
  END LOOP;
  ```
- **Difficulty:** Easy

### **E. Even/Odd Numbers Display** (3+ slips)
- **Slips:** 6, 10, 24, 27
- **Question:** Display even/odd numbers in range 1-50 or 1-100
- **Pattern:** FOR loop with MOD operator
- **Difficulty:** Very Easy

### **F. Trigger Before Delete** (4 slips)
- **Slips:** 5, 16, 25, 29
- **Question:** Create trigger to show message before deleting record
- **Pattern:** BEFORE DELETE trigger with RAISE NOTICE
- **Difficulty:** Easy

### **G. Count Persons/Items in Category** (2+ slips)
- **Slips:** 2, 7
- **Question:** Function to count records by category
- **Difficulty:** Easy

### **H. Cursor with JOIN** (Multiple slips)
- **Slips:** 3, 4, 5, 11, 16, 18, 23, 25, 26, 27, 29
- **Question:** Use cursor to fetch related data from multiple tables
- **Difficulty:** Medium

## Schema Repetition

| Schema | Occurrences | Slips |
|--------|-------------|-------|
| Project-Employee | 5 | 1, 12, 14, 19, 22 |
| Student-Subject | 3 | 11, 16, 27 |
| Student-Competition | 3 | 5, 9, 17 |
| Person-Area | 3 | 2, 15, 29 |
| Bus-Route-Driver | 2 | 6, 13 |
| Item-Supplier | 2 | 18, 26 |
| Department-Employee | 2 | 20, 24 |
| Student-Teacher | 2 | 3, 30 |
| Car-Driver | 1 | 23 |
| Customer-Account | 1 | 25 |
| Doctor-Hospital | 1 | 21 |
| Book-Author | 1 | 10 |
| Train-Passenger | 1 | 8 |
| Movies-Actor-Producer | 1 | 4 |
| Company-Person | 1 | 28 |
| Branch-Customer-Loan | 1 | 7 |


# 7. Difficulty Assessment

## Easy Questions (Beginner Level)

**Characteristics:**
- Simple SELECT queries
- Basic arithmetic operations
- Straightforward IF/ELSE logic
- Single table operations

**Topics:** 9 Slips

| Slip | Q2.1-A | Q2.1-B | Q2.2 | Why Easy |
|------|--------|--------|------|----------|
| **2** | Count persons | Sum income | Division | Simple aggregates |
| **4** | Cursor count | Budget validation | Pos/Neg test | Basic logic |
| **6** | Get name function | Drivers >50 | Even/Odd | Simple SELECT |
| **8** | Ticket details | Fare message | Add numbers | Straightforward |
| **10** | Books by author | Price alert | Even numbers | Simple operations |
| **13** | Age validation | Drivers for bus | Range check | Basic constraints |
| **19** | Count projects | Duration check | Min/Max 2 | Simple aggregate |
| **22** | Count projects | Duration check | Range check | Repeating pattern |
| **25** | Customers by city | Prevent delete | Display customers | Simple cursor |

**Key Points:**
- Most questions are aggregation or validation
- No complex joins required
- Standard PL/pgSQL patterns

## Medium Questions (Intermediate Level)

**Characteristics:**
- Multiple table JOINs
- Stored procedures with loops
- Complex trigger logic
- Aggregate functions with GROUP BY
- Cursor-based updates

**Topics:** 15 Slips

| Slip | Key Complexity | Features |
|------|--------|----------|
| **1** | M:M schema + multiple operations | All core concepts |
| **3** | Cursor with 2-table JOIN + trigger | Moderate complexity |
| **5** | Cursor with date filtering + loop | Multiple conditions |
| **7** | Ternary relationship + loop sum | Relationship complexity |
| **11** | Cursor aggregate + WHILE loop | Loop with calculation |
| **12** | Cursor count odd + loop | Conditional logic + loop |
| **15** | Cursor UPDATE + percentage calculation | Update with computation |
| **16** | Trigger before delete + cursor aggregate | Notification + aggregation |
| **17** | Trigger update notification + loop sum | Multiple trigger actions |
| **18** | Cursor with WHERE + rate validation | Multiple conditions |
| **20** | Department join + salary aggregate | Relationship + constraint |
| **21** | Hospital join + average + loop | Join + aggregate + loop |
| **23** | Cursor + age validation + large loop | Multiple features |
| **26** | Cursor update + rate difference check | Complex comparison |
| **27** | Cursor with class filter + marks validation | Multiple constraints |

**Key Points:**
- Requires understanding of M:M relationships
- Loop constructs with calculations
- Multiple triggers or complex conditions

## Hard Questions (Advanced Level)

**Characteristics:**
- Complex ternary or multi-table relationships
- Advanced cursor operations
- Exception handling
- Complex business logic in triggers
- Transaction-like operations

**Topics:** 6 Slips

| Slip | Key Complexity | Advanced Features |
|------|--------|-----------|
| **7** | Ternary relationship (Branch-Customer-Loan) | 3-way JOIN complexity |
| **9** | Multiple option questions (OR) + exception | Exception handling + choice |
| **14** | CASE statement + number conversion | Advanced PL/pgSQL control |
| **28** | Update function + delete prevention trigger | Update function + trigger |
| **29** | Multiple filters + data update | Complex filtering |
| **30** | Experience calculation + constraint check | Calculation + validation |

**Key Points:**
- Less common relationship types
- Advanced PL/pgSQL features
- Multiple overlapping requirements

## Difficulty Distribution Chart

```
Easy (30%):      9 slips
Medium (50%):    15 slips
Hard (20%):      6 slips
```

## Recommended Study Order

**Phase 1 - Foundation (Easy):** Slips 2, 4, 6, 8, 10, 13, 19, 22, 25
- Master basic patterns
- Understand function/trigger syntax
- Practice simple aggregates

**Phase 2 - Intermediate (Medium):** Slips 1, 3, 5, 11, 12, 15, 16, 17, 18, 20, 21, 23, 26, 27
- Complex JOINs
- Loop constructs
- Cursor iterations

**Phase 3 - Advanced (Hard):** Slips 7, 9, 14, 28, 29, 30
- Ternary relationships
- Exception handling
- Advanced control structures


# 9. Study Priority Guide

## Priority 1: Master These Core Patterns (Foundation)

**These patterns appear in multiple slips and are essential:**

1. **Function to Count Related Records**
   - Pattern: COUNT(*) with JOIN
   - Slips: 1, 19, 22
   - Topic: Stored Functions + Aggregate
   - Complexity: Easy

2. **Trigger to Validate Numeric Range**
   - Pattern: BEFORE INSERT, IF NEW.column <= 0 THEN
   - Slips: 1, 12, 14, 19, 22 (appears in 5 slips!)
   - Topic: Triggers + Constraints
   - Complexity: Easy
   - **ACTION:** Master this pattern first

3. **Cursor to Iterate with JOIN**
   - Pattern: FOR rec IN SELECT * FROM table1 JOIN table2
   - Slips: 3, 4, 5, 11, 18, 23, 25, 26, 27, 29
   - Topic: Cursors + JOINs
   - Complexity: Medium
   - **ACTION:** Second priority pattern

4. **Loop to Sum/Count Series**
   - Pattern: FOR i IN 1..N LOOP sum := sum + i
   - Slips: 7, 12, 17, 23, 24, 27, 30
   - Topic: Loops
   - Complexity: Easy-Medium

5. **Trigger to Notify on Action**
   - Pattern: BEFORE/AFTER event, RAISE NOTICE
   - Slips: 5, 8, 9, 16, 17, 24, 25, 28, 29
   - Topic: Triggers + Notifications
   - Complexity: Easy

## Priority 2: Important Secondary Patterns

6. **Aggregate Functions with GROUP BY**
   - Slips: 2, 5, 7, 11, 16, 17, 20, 21
   - Complexity: Medium

7. **Exception Handling in Functions**
   - Slips: 2, 9, 10, 14, 25, 28, 30
   - Complexity: Medium-Hard

8. **CASE Statements for Conditional Output**
   - Slips: 14
   - Complexity: Medium

## Priority 3: Schema-Specific Knowledge

Learn M:M schemas with highest repetition:

1. **Project-Employee** (5 slips: 1, 12, 14, 19, 22)
   - Tables: Project, Employee, Project_Employee
   - Common ops: Count projects, validate duration

2. **Student-Subject/Competition** (6 slips: 5, 9, 11, 16, 17, 27)
   - Tables: Student, Subject/Competition, junction
   - Common ops: Total marks, prizes, aggregates

3. **Person-Area** (3 slips: 2, 15, 29)
   - M:1 relationship
   - Common ops: Group by area, aggregate by type

## Priority 4: Q2.2 Patterns by Frequency

| Pattern | Frequency | Slips | Key Approach |
|---------|-----------|-------|-------------|
| Sum first N numbers | Very High | 7,17,23,30 | FOR loop 1..N |
| Display even numbers | High | 10,24,27 | FOR loop with MOD |
| Min/Max comparison | High | 5,18,19,25 | IF/ELSE logic |
| Arithmetic operations | High | 1,8,20,26,29 | RAISE NOTICE output |
| Number validation | Medium | 4,13,14,22 | IF/ELSE conditions |
| Display specific rows | Low | 25 | SELECT with WHERE |

## Recommended Study Progression

**Week 1: Foundation**
```
Day 1: Learn PL/pgSQL basics (variables, IF/ELSE, RAISE NOTICE)
Day 2: Study Functions - counting, aggregation
Day 3: Study Triggers - validation patterns
Day 4: Study Cursors - basic iteration
Day 5: Practice Slips 2, 4, 6, 8, 10 (Easy foundation)
Day 6: Practice Slips 13, 19, 22, 25 (More foundation)
Day 7: Review + Revise
```

**Week 2: Core Patterns**
```
Day 1: Project-Employee schema (Slip 1, 19, 22)
Day 2: Student-Subject schema (Slip 11, 16, 27)
Day 3: Cursor patterns (Slip 3, 5, 18, 23)
Day 4: Loop patterns (Slip 7, 12, 17, 30)
Day 5: Trigger patterns (Slip 1, 12, 14, 15, 20, 21)
Day 6-7: Full slip practice
```

**Week 3: Advanced & Weaknesses**
```
- Target slips showing personal weakness
- Practice exception handling (Slip 9, 10, 14, 28)
- Practice ternary relationships (Slip 7)
- Practice option selection (Q2.1 OR questions)
```

## Topic Mastery Checklist

**Essential Topics (Must Know):**
- [ ] SELECT with JOINs
- [ ] CREATE FUNCTION syntax and usage
- [ ] CREATE PROCEDURE syntax and usage
- [ ] CREATE TRIGGER with BEFORE/AFTER
- [ ] IF/ELSE conditional logic
- [ ] FOR loops (numeric range)
- [ ] CURSOR iteration with SELECT
- [ ] RAISE NOTICE (output)
- [ ] RAISE EXCEPTION (validation)
- [ ] COUNT, SUM, AVG aggregate functions
- [ ] PRIMARY KEY, FOREIGN KEY constraints
- [ ] M:M, M:1 relationship design

**Important Topics (Should Know):**
- [ ] WHILE loops with conditions
- [ ] CASE statements
- [ ] GROUP BY with aggregates
- [ ] String operations (concatenation)
- [ ] Math operations (MOD, ABS)
- [ ] CURSOR with multiple joins
- [ ] DECLARE variables with %TYPE

**Nice-to-Have Topics (Good to Know):**
- [ ] Ternary relationships
- [ ] Complex exception handling
- [ ] Transaction control (COMMIT/ROLLBACK)
- [ ] Views and materialized views
- [ ] Index usage and optimization


# Quick Reference: Exam Strategy

## Time Management
- **Q2.1 (30 min):** Choose easier option if unsure
  - Cursor/Function: 15-20 min
  - Trigger: 10-15 min
  
- **Q2.2 (20 min):** Generally faster
  - Arithmetic: 5 min
  - Loops: 10-15 min
  - Conditionals: 8-12 min

## Common Mistakes to Avoid
1.  Forgetting `END IF;`, `END;`, `END LOOP;`
2.  Using `=` instead of `:=` for assignment
3.  Wrong trigger timing (BEFORE vs AFTER)
4.  Not converting function/procedure properly
5.  Returning NULL in validation trigger (prevents operation)
6.  Incorrect cursor loop syntax
7.  Wrong aggregate function used

## Syntax Checklist Before Submission
- [ ] Function/procedure properly closed with `END;`
- [ ] Variables declared with type
- [ ] Assignment uses `:=` not `=`
- [ ] Conditions have closing END IF
- [ ] Loops have closing END LOOP
- [ ] RAISE NOTICE/EXCEPTION syntax correct
- [ ] Trigger function returns TRIGGER type
- [ ] Trigger attached properly with CREATE TRIGGER
- [ ] Parameter names match in function calls


# Conclusion & Final Tips

## Must-Know for Exam
1. **PL/pgSQL syntax** - memorize CREATE FUNCTION/PROCEDURE/TRIGGER
2. **Top 5 patterns** - count, validate, cursor, loop, aggregate
3. **M:M schemas** - especially Project-Employee
4. **Error messages** - proper RAISE syntax
5. **Trigger logic** - BEFORE vs AFTER, RETURN NEW vs NULL

## Recommended Practice Order
1. **Easy foundation** (Day 1-3): Slips 2, 4, 6, 8, 10
2. **Standard patterns** (Day 4-5): Slips 1, 19, 22 (Project-Employee)
3. **Complex patterns** (Day 6): Slips 3, 5, 11, 18, 23 (Cursors)
4. **Advanced scenarios** (Day 7): Slips 7, 9, 14, 28

## Time Allocation During Exam
```
Reading & Understanding:   5 minutes
Q2.1 Solution:            25 minutes (choose easier option)
Q2.2 Solution:            20 minutes
Review & Syntax Check:    10 minutes

Total:                    60 minutes
```
