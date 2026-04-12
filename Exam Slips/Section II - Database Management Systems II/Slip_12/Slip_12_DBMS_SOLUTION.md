# Slip 12 — DBMS-II Solution Guide

## Question
> See `Slip_12_DBMS.txt` for the full question text.

## Database Schema: Project-Employee (M:M)

### Tables
Same as Slip 1: Project, Employee, Project_Employee tables.

### ER Description
Same M:M relationship between Project and Employee.

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

## Q2.1 Option A: Trigger: Validate Project Duration Before Insert

### Concept
Same trigger pattern as Slip 1 Option B.

### Algorithm
1. Check NEW.duration ≤ 0
2. Raise exception if invalid

### Pseudocode
```sql
FUNCTION check_duration() RETURNS TRIGGER
BEGIN
    IF NEW.duration <= 0 THEN
        RAISE EXCEPTION 'Duration must be greater than zero';
    END IF;
    RETURN NEW;
END
```

---

## Q2.1 Option B: OR: Function — Employees by Project Name (with Exception)

### Concept
Accepts project name, displays employee names. Raises exception for invalid project.

### Algorithm
1. Validate project exists
2. Join tables to find employees
3. Display names

### Pseudocode
```sql
FUNCTION get_employees(pname VARCHAR) RETURNS VOID
BEGIN
    IF NOT EXISTS (SELECT 1 FROM Project WHERE p_name = pname) THEN
        RAISE EXCEPTION 'Invalid project name';
    FOR rec IN SELECT e.e_name FROM Employee e
        JOIN Project_Employee pe ON e.eno = pe.eno
        JOIN Project p ON pe.pno = p.pno
        WHERE p.p_name = pname LOOP
        RAISE NOTICE '%', rec.e_name;
    END LOOP;
END
```

---

## Q2.2: Procedure: Count Odd Numbers in Range (For Loop)

### Pseudocode
```sql
PROCEDURE count_odd(m INT, n INT)
BEGIN
    DECLARE cnt INT := 0;
    FOR i IN m..n LOOP
        IF i % 2 != 0 THEN cnt := cnt + 1;
    END LOOP;
    RAISE NOTICE 'Odd numbers from % to %: %', m, n, cnt;
END
```

---

> **Solution Code:** See `Slip_12_DBMS_Solution.sql` in this folder.
