# Slip 17 — DBMS-II Solution Guide

## Question
> See `Slip_17_DBMS.txt` for the full question text.

## Database Schema: Student-Competition (M:M) with Prize

### Tables
Same as Slip 9.

### ER Description
Student ↔ Competition M:M with rank, year, prize.

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

## Q2.1 Option A: Trigger: Notice on Competition Update

### Concept
Same as Slip 5/9.

### Algorithm
BEFORE UPDATE trigger raises notice.

### Pseudocode
```sql
-- Same pattern as Slip 5/9
```

---

## Q2.1 Option B: OR: Cursor Function — Total Prizes in 2020

### Concept
Same as Slip 9 Option B.

### Algorithm
Accept student name, count prizes in 2020.

### Pseudocode
```sql
-- Same as Slip 9 cursor function
```

---

## Q2.2: Procedure: Sum of First 50 Numbers (Unconditional Loop)

### Pseudocode
```sql
PROCEDURE sum_50()
BEGIN
    DECLARE i INT := 1; total INT := 0;
    LOOP
        total := total + i;
        i := i + 1;
        EXIT WHEN i > 50;
    END LOOP;
    RAISE NOTICE 'Sum: %', total;
END
```

---

> **Solution Code:** See `Slip_17_DBMS_Solution.sql` in this folder.
