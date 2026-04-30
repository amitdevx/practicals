# Slip 16 — DBMS-II Solution Guide

## Question
> See `Slip_16_DBMS.txt` for the full question text.

## Database Schema: Student-Subject (M:M)

### Tables
Same as Slip 11.

### ER Description
Student ↔ Subject Many-to-Many with marks_scored.

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

## Q2.1 Option A: Trigger: Notice Before Student Delete

### Concept
Same as Slip 11 Option B.

### Algorithm
BEFORE DELETE trigger raises notice.

### Pseudocode
```sql
-- Same as Slip 11 delete trigger
```

---

## Q2.1 Option B: OR: Cursor Function — Total Marks per Student

### Concept
Same as Slip 11 Option A.

### Algorithm
Cursor iterates students, sums marks.

### Pseudocode
```sql
-- Same as Slip 11 cursor function
```

---

## Q2.2: Procedure: Check Positive or Negative

### Pseudocode
```sql
PROCEDURE check_sign(n INTEGER)
BEGIN
    IF n >= 0 THEN RAISE NOTICE 'Positive';
    ELSE RAISE NOTICE 'Negative';
    END IF;
END
```

---

> **Solution Code:** See `Slip_16_DBMS_Solution.sql` in this folder.
