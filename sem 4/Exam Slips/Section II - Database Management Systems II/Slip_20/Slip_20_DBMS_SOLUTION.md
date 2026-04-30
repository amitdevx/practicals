# Slip 20 — DBMS-II Solution Guide

## Question
> See `Slip_20_DBMS.txt` for the full question text.

## Database Schema: Department-Employee (1:M)

### Tables
| Table | Columns |
|-------|---------|
| **Department** | dno (PK), dname, city |
| **Employee** | eno (PK), ename, salary, dno (FK→Department) |

### ER Description
**Relationship:** Department → Employee is **One-to-Many** (1:M)
- One department has many employees
- Foreign key `dno` in Employee references Department

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

## Q2.1 Option A: Function: Max Salary in Department

### Concept
Accepts department name, finds maximum salary of employees in that department.

### Algorithm
1. Join Department and Employee
2. Filter by dname
3. Return MAX(salary)

### Pseudocode
```sql
FUNCTION max_salary(dept_name VARCHAR) RETURNS NUMERIC
BEGIN
    SELECT MAX(e.salary) INTO result FROM Employee e
        JOIN Department d ON e.dno = d.dno WHERE d.dname = dept_name;
    RETURN result;
END
```

---

## Q2.1 Option B: Trigger: Validate Salary Before Insert/Update

### Concept
Raises exception if salary < 0.

### Algorithm
Check NEW.salary < 0, raise exception.

### Pseudocode
```sql
FUNCTION check_salary() RETURNS TRIGGER
BEGIN
    IF NEW.salary < 0 THEN RAISE EXCEPTION 'Salary cannot be negative';
    RETURN NEW;
END
```

---

## Q2.2: Procedure: Multiply Two Numbers

### Pseudocode
```sql
PROCEDURE multiply(a INT, b INT)
BEGIN
    RAISE NOTICE 'Product: %', a * b;
END
```

---

> **Solution Code:** See `Slip_20_DBMS_Solution.sql` in this folder.
