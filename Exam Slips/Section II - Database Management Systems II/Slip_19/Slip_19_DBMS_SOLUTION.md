# Slip 19 — DBMS-II Solution Guide

## Question
> See `Slip_19_DBMS.txt` for the full question text.

## Database Schema: Project-Employee (M:M)

### Tables
Same as Slip 1.

### ER Description
Same M:M relationship.

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

## Q2.1 Option A: Function: Count Projects per Employee

### Concept
Same as Slip 1 Option A.

### Algorithm
Accept eno, count projects.

### Pseudocode
```sql
-- Same as Slip 1 function
```

---

## Q2.1 Option B: Trigger: Validate Project Duration

### Concept
Same as Slip 1 Option B.

### Algorithm
Check duration > 0.

### Pseudocode
```sql
-- Same as Slip 1 trigger
```

---

## Q2.2: Procedure: Min and Max of Two Numbers

### Pseudocode
```sql
PROCEDURE find_min_max(a INT, b INT)
BEGIN
    IF a > b THEN RAISE NOTICE 'Max: %, Min: %', a, b;
    ELSE RAISE NOTICE 'Max: %, Min: %', b, a;
    END IF;
END
```

---

> **Solution Code:** See `Slip_19_DBMS_Solution.sql` in this folder.
