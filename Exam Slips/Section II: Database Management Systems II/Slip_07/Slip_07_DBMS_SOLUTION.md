# Slip 7 — DBMS-II Solution Guide

## Question
> See `Slip_07_DBMS.txt` for the full question text.

## Database Schema: Branch-Customer-Loan (Ternary)

### Tables
| Table | Columns |
|-------|---------|
| **Branch** | br_id (PK), br_name, br_city |
| **Customer** | cno (PK), c_name, caddr, city |
| **Loan_Application** | lno (PK), l_amt_required (>0), l_amt_approved, l_date |
| **Ternary** | br_id (FK), cno (FK), lno (FK) |

### ER Description
**Relationship:** Branch-Customer-Loan is a **Ternary** relationship (3-way association).

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

## Q2.1 Option A: Cursor Function: Count Customers per Branch

### Concept
Uses cursor to count customers of a particular branch by joining through Ternary table.

### Algorithm
1. Accept branch name
2. Find br_id for that branch name
3. Count distinct customers in Ternary for that br_id

### Pseudocode
```sql
FUNCTION count_branch_customers(bname VARCHAR) RETURNS INTEGER
BEGIN
    DECLARE cnt INTEGER := 0;
    FOR rec IN SELECT DISTINCT cno FROM Ternary t
        JOIN Branch b ON t.br_id = b.br_id
        WHERE b.br_name = bname LOOP
        cnt := cnt + 1;
    END LOOP;
    RETURN cnt;
END
```

---

## Q2.1 Option B: Trigger: Validate Customer Number

### Concept
BEFORE INSERT trigger ensures customer number is positive.

### Algorithm
1. Check NEW.cno ≤ 0
2. If invalid, raise exception

### Pseudocode
```sql
FUNCTION check_cno() RETURNS TRIGGER
BEGIN
    IF NEW.cno <= 0 THEN
        RAISE EXCEPTION 'Customer number must be positive';
    END IF;
    RETURN NEW;
END
```

---

## Q2.2: Procedure: Sum of First 20 Numbers (Loop)

### Pseudocode
```sql
PROCEDURE sum_first_20()
BEGIN
    DECLARE i INT := 1; total INT := 0;
    LOOP
        total := total + i;
        i := i + 1;
        EXIT WHEN i > 20;
    END LOOP;
    RAISE NOTICE 'Sum of first 20 numbers: %', total;
END
```

---

> **Solution Code:** See `Slip_07_DBMS_Solution.sql` in this folder.
