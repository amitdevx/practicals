# Slip 3 — DBMS-II Solution Guide

## Question
> See `Slip_03_DBMS.txt` for the full question text.

## Database Schema: Student-Teacher (M:M)

### Tables
| Table | Columns |
|-------|---------|
| **Student** | s_no (PK), s_name (NOT NULL), address, class |
| **Teacher** | t_no (PK), t_name (NOT NULL), qualification, experience |
| **Student_Teacher** | s_no (FK), t_no (FK), subject, marks_scored (>0) |

### ER Description
**Relationship:** Student ↔ Teacher is **Many-to-Many**
- A student can be taught by many teachers
- A teacher can teach many students
- Junction table stores subject and marks

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

## Q2.1 Option A: Cursor: Students and Teachers for RDBMS Subject

### Concept
A **cursor** iterates over query results row by row.
- Declared with `FOR rec IN SELECT ... LOOP`
- Each iteration processes one row

### Algorithm
1. Accept student number as input
2. Open cursor joining Student, Teacher, Student_Teacher
3. Filter where subject = 'RDBMS' and s_no matches
4. Loop through results displaying student and teacher names

### Pseudocode
```sql
FUNCTION get_rdbms_teachers(stud_no INTEGER) RETURNS VOID
BEGIN
    FOR rec IN
        SELECT s.s_name, t.t_name
        FROM Student s
        JOIN Student_Teacher st ON s.s_no = st.s_no
        JOIN Teacher t ON st.t_no = t.t_no
        WHERE st.subject = 'RDBMS' AND s.s_no = stud_no
    LOOP
        RAISE NOTICE 'Student: %, Teacher: %', rec.s_name, rec.t_name;
    END LOOP;
END
```

---

## Q2.1 Option B: Trigger: Validate Student Number Before Insert

### Concept
BEFORE INSERT trigger validates that student number is positive.

### Algorithm
1. Check NEW.s_no ≤ 0
2. If invalid, raise exception 'Invalid Number'
3. If valid, return NEW

### Pseudocode
```sql
FUNCTION check_student_no() RETURNS TRIGGER
BEGIN
    IF NEW.s_no <= 0 THEN
        RAISE EXCEPTION 'Invalid Number';
    END IF;
    RETURN NEW;
END

TRIGGER before Student INSERT → EXECUTE check_student_no()
```

---

## Q2.2: Procedure: Min and Max of Two Numbers

### Pseudocode
```sql
PROCEDURE find_min_max(a INTEGER, b INTEGER)
BEGIN
    IF a > b THEN
        RAISE NOTICE 'Max: %, Min: %', a, b;
    ELSE
        RAISE NOTICE 'Max: %, Min: %', b, a;
    END IF;
END
```

---

> **Solution Code:** See `Slip_03_DBMS_Solution.sql` in this folder.
