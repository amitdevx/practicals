# Slip 22 — DBMS-II Solution Guide

## Question
> See `Slip_22_DBMS.txt` for the full question text.

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
Same as Slip 1.

### Algorithm
Accept eno, count projects.

### Pseudocode
```sql
-- Same as Slip 1
```

---

## Q2.1 Option B: Trigger: Validate Duration

### Concept
Same as Slip 1.

### Algorithm
Check duration > 0.

### Pseudocode
```sql
-- Same as Slip 1
```

---

## Q2.2: Procedure: Check Number in Range

### Pseudocode
```sql
PROCEDURE check_range(num INT, low INT, high INT)
BEGIN
    IF num >= low AND num <= high THEN
        RAISE NOTICE '% is in range', num;
    ELSE RAISE NOTICE '% is out of range', num;
    END IF;
END
```

---

> **Solution Code:** See `Slip_22_DBMS_Solution.sql` in this folder.
