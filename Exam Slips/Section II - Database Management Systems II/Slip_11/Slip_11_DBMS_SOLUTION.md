# Slip 11 — DBMS-II Solution Guide

## Question
> See `Slip_11_DBMS.txt` for the full question text.

## Database Schema: Student-Subject (M:M)

### Tables
| Table | Columns |
|-------|---------|
| **Student** | rollno (PK), s_name, class |
| **Subject** | scode (PK), subject_name |
| **Student_Subject** | rollno (FK), scode (FK), marks |

### ER Description
**Relationship:** Student ↔ Subject is **Many-to-Many** with marks.

### PL/pgSQL Key Concepts

| Concept | Syntax |
|---------|--------|
| **Function** | `CREATE OR REPLACE FUNCTION name(params) RETURNS type AS $$ ... $$ LANGUAGE plpgsql;` |
| **Procedure** | `CREATE OR REPLACE PROCEDURE name(params) LANGUAGE plpgsql AS $$ ... $$;` |
| **Trigger Function** | Returns `TRIGGER`, uses `NEW`/`OLD` row variables |
| **Create Trigger** | `CREATE TRIGGER name BEFORE/AFTER event ON table FOR EACH ROW EXECUTE FUNCTION func();` |
| **Cursor (implicit)** | `FOR rec IN SELECT ... LOOP ... END LOOP;` |
| **Print message** | `RAISE NOTICE 'message %', variable;` |
| **Raise error** | `RAISE EXCEPTION 'error message';` |
| **Variable** | `DECLARE varname TYPE := value;` |
| **Call function** | `SELECT function_name(args);` |
| **Call procedure** | `CALL procedure_name(args);` |

---

## Q2.1 Option A: Cursor Function: Calculate Total Marks per Student

### Concept
Uses cursor to iterate students and sum their marks across all subjects.

### Algorithm
1. For each student, sum marks from Student_Subject
2. Display student name and total

### Pseudocode
```sql
FUNCTION calc_total_marks() RETURNS VOID
BEGIN
    FOR rec IN SELECT s.rollno, s.s_name, SUM(ss.marks) as total
        FROM Student s JOIN Student_Subject ss ON s.rollno = ss.rollno
        GROUP BY s.rollno, s.s_name LOOP
        RAISE NOTICE 'Student: %, Total: %', rec.s_name, rec.total;
    END LOOP;
END
```

---

## Q2.1 Option B: Trigger: Notice Before Student Delete

### Concept
BEFORE DELETE trigger raises notice when a student record is being deleted.

### Algorithm
1. Raise notice with message
2. Return OLD to allow deletion

### Pseudocode
```sql
FUNCTION notify_delete() RETURNS TRIGGER
BEGIN
    RAISE NOTICE 'student record is being deleted';
    RETURN OLD;
END
```

---

## Q2.2: Procedure: Sum and Average of First N Numbers (While Loop)

### Pseudocode
```sql
PROCEDURE sum_avg_n(n INTEGER)
BEGIN
    DECLARE i INT := 1; total INT := 0;
    WHILE i <= n LOOP
        total := total + i;
        i := i + 1;
    END LOOP;
    RAISE NOTICE 'Sum: %, Average: %', total, total::NUMERIC / n;
END
```

---

> **Solution Code:** See `Slip_11_DBMS_Solution.sql` in this folder.
