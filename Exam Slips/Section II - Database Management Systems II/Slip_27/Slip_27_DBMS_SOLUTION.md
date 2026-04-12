# Slip 27 — DBMS-II Solution Guide

## Question
> See `Slip_27_DBMS.txt` for the full question text.

## Database Schema: Student-Subject (M:M)

### Tables
Same as Slip 11.

### ER Description
Student ↔ Subject M:M with marks_scored.

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

## Q2.1 Option A: Cursor: Students by Class

### Concept
Accepts class name, displays student details.

### Algorithm
1. Accept class
2. Query students where class matches
3. Display via cursor

### Pseudocode
```sql
FUNCTION show_class_students(p_class VARCHAR) RETURNS VOID
BEGIN
    FOR rec IN SELECT * FROM Student WHERE class = p_class LOOP
        RAISE NOTICE 'Roll: %, Name: %', rec.rollno, rec.name;
    END LOOP;
END
```

---

## Q2.1 Option B: Trigger: Validate Marks Before Insert/Update

### Concept
BEFORE INSERT/UPDATE trigger ensures marks are non-negative.

### Algorithm
Check NEW.marks < 0, raise exception.

### Pseudocode
```sql
FUNCTION check_marks() RETURNS TRIGGER
BEGIN
    IF NEW.marks < 0 THEN RAISE EXCEPTION 'Marks cannot be negative';
    RETURN NEW;
END
```

---

## Q2.2: Procedure: Even Numbers 1-50

### Pseudocode
```sql
PROCEDURE even_1_50()
BEGIN
    FOR i IN 1..50 LOOP
        IF i % 2 = 0 THEN RAISE NOTICE '%', i;
    END LOOP;
END
```

---

> **Solution Code:** See `Slip_27_DBMS_Solution.sql` in this folder.
