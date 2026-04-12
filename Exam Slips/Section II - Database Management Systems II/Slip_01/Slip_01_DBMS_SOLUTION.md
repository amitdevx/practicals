# Slip 1 — DBMS-II Solution Guide

## Question
> See `Slip_01_DBMS.txt` for the full question text.

## Database Schema: Project-Employee (M:M)

### Tables
| Table | Columns |
|-------|---------|
| **Project** | pno (PK), pname (NOT NULL), ptype, duration (>0) |
| **Employee** | eno (PK), ename, qualification, joining_date |
| **Project_Employee** | pno (FK), eno (FK), start_date, no_of_hours_worked |

### ER Description
**Relationship:** Project ↔ Employee is **Many-to-Many** (M:M)
- One project can have many employees
- One employee can work on many projects
- Junction table `Project_Employee` stores the relationship with descriptive attributes

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

## Q2.1 Option A: Stored Function: Count Projects per Employee

### Concept
A **stored function** in PostgreSQL:
- Accepts input parameters and returns a value
- Uses `CREATE OR REPLACE FUNCTION` syntax
- Body written in PL/pgSQL between `$$ ... $$`

### Algorithm
1. Accept `eno` as input parameter
2. Query `Project_Employee` table counting rows where eno matches
3. Return the count

### Pseudocode
```sql
FUNCTION count_projects(emp_no INTEGER) RETURNS INTEGER
BEGIN
    DECLARE proj_count INTEGER;
    SELECT COUNT(*) INTO proj_count
    FROM Project_Employee
    WHERE eno = emp_no;
    RETURN proj_count;
END
```

---

## Q2.1 Option B: Trigger: Validate Project Duration Before Insert

### Concept
A **trigger** automatically executes a function when a specified event occurs.
- **BEFORE INSERT** trigger fires before the row is inserted
- Can validate data and reject invalid rows using `RAISE EXCEPTION`

### Algorithm
1. Create trigger function that checks `NEW.duration`
2. If duration ≤ 0, raise exception with message
3. If valid, return NEW to allow insert
4. Attach trigger to Project table for BEFORE INSERT events

### Pseudocode
```sql
FUNCTION check_duration() RETURNS TRIGGER
BEGIN
    IF NEW.duration <= 0 THEN
        RAISE EXCEPTION 'Duration must be greater than zero';
    END IF;
    RETURN NEW;
END

TRIGGER trg_check_duration
    BEFORE INSERT ON Project
    FOR EACH ROW EXECUTE check_duration()
```

---

## Q2.2: Procedure: Addition, Subtraction, Multiplication of Three Numbers

### Pseudocode
```sql
PROCEDURE arithmetic_ops(a INTEGER, b INTEGER, c INTEGER)
BEGIN
    RAISE NOTICE 'Addition: %', a + b + c;
    RAISE NOTICE 'Subtraction: %', a - b - c;
    RAISE NOTICE 'Multiplication: %', a * b * c;
END
```

---

> **Solution Code:** See `Slip_01_DBMS_Solution.sql` in this folder.
