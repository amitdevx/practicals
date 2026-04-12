# Slip 24 — DBMS-II Solution Guide

## Question
> See `Slip_24_DBMS.txt` for the full question text.

## Database Schema: Department-Employee (1:M)

### Tables
Same as Slip 20.

### ER Description
Same Department-Employee 1:M.

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

## Q2.1 Option A: Function: Employees by Department Name

### Concept
Accepts department name, displays employee names and salaries.

### Algorithm
1. Join Department and Employee
2. Filter by dname
3. Display employee details

### Pseudocode
```sql
FUNCTION show_employees(dept_name VARCHAR) RETURNS VOID
BEGIN
    FOR rec IN SELECT e.ename, e.salary FROM Employee e
        JOIN Department d ON e.dno = d.dno
        WHERE d.dname = dept_name LOOP
        RAISE NOTICE 'Employee: %, Salary: %', rec.ename, rec.salary;
    END LOOP;
END
```

---

## Q2.1 Option B: Trigger: After Insert Message on Employee

### Concept
AFTER INSERT trigger displays message when record is inserted.

### Algorithm
Raise notice confirming insertion.

### Pseudocode
```sql
FUNCTION notify_insert() RETURNS TRIGGER
BEGIN
    RAISE NOTICE 'Employee record inserted: %', NEW.ename;
    RETURN NEW;
END
```

---

## Q2.2: Procedure: First 20 Even Numbers

### Pseudocode
```sql
PROCEDURE first_20_even()
BEGIN
    DECLARE cnt INT := 0; i INT := 1;
    WHILE cnt < 20 LOOP
        IF i % 2 = 0 THEN RAISE NOTICE '%', i; cnt := cnt + 1;
        i := i + 1;
    END LOOP;
END
```

---

> **Solution Code:** See `Slip_24_DBMS_Solution.sql` in this folder.
