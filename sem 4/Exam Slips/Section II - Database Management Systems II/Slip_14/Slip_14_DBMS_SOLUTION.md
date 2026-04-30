# Slip 14 — DBMS-II Solution Guide

## Question
> See `Slip_14_DBMS.txt` for the full question text.

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

## Q2.1 Option A: Trigger: Validate Project Duration

### Concept
Same BEFORE INSERT trigger as Slip 1/12.

### Algorithm
Check duration > 0, raise exception if not.

### Pseudocode
```sql
-- Same pattern as Slip 1 / Slip 12
FUNCTION check_duration() RETURNS TRIGGER
BEGIN
    IF NEW.duration <= 0 THEN RAISE EXCEPTION 'Invalid duration';
    RETURN NEW;
END
```

---

## Q2.1 Option B: OR: Function — Employees by Project (with Exception)

### Concept
Same as Slip 12 Option B.

### Algorithm
Validate project, join tables, display employees.

### Pseudocode
```sql
-- Same pattern as Slip 12 OR option
```

---

## Q2.2: Procedure: Number in Words (Using CASE)

### Pseudocode
```sql
PROCEDURE number_in_words(n INTEGER)
BEGIN
    FOR i IN 0..n LOOP
        word := CASE i
            WHEN 0 THEN 'Zero' WHEN 1 THEN 'One'
            WHEN 2 THEN 'Two'  WHEN 3 THEN 'Three'
            WHEN 4 THEN 'Four' WHEN 5 THEN 'Five'
            WHEN 6 THEN 'Six'  WHEN 7 THEN 'Seven'
            WHEN 8 THEN 'Eight' WHEN 9 THEN 'Nine'
            ELSE 'Unknown'
        END;
        RAISE NOTICE '% = %', i, word;
    END LOOP;
END
```

---

> **Solution Code:** See `Slip_14_DBMS_Solution.sql` in this folder.
