# Slip 9 — DBMS-II Solution Guide

## Question
> See `Slip_09_DBMS.txt` for the full question text.

## Database Schema: Student-Competition (M:M) with Prize

### Tables
| Table | Columns |
|-------|---------|
| **Student** | sreg_no (PK), name, class |
| **Competition** | c_no (PK), name, c_type |
| **Student_Competition** | sreg_no (FK), c_no (FK), rank, year, prize |

### ER Description
Same as Slip 5 schema but with additional `prize` attribute.

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
BEFORE UPDATE trigger that displays notification message.

### Algorithm
1. Create trigger function raising notice
2. Return NEW to allow update

### Pseudocode
```sql
FUNCTION notify_update() RETURNS TRIGGER
BEGIN
    RAISE NOTICE 'competition record is being updated';
    RETURN NEW;
END
```

---

## Q2.1 Option B: OR: Cursor Function — Total Prizes by Student in 2020

### Concept
Function uses cursor to count prizes won by a student in year 2020.

### Algorithm
1. Accept student name
2. Join Student and Student_Competition
3. Filter by name and year = 2020
4. Count prizes using cursor loop

### Pseudocode
```sql
FUNCTION total_prizes(sname VARCHAR) RETURNS INTEGER
BEGIN
    DECLARE cnt INTEGER := 0;
    FOR rec IN SELECT * FROM Student_Competition sc
        JOIN Student s ON sc.sreg_no = s.sreg_no
        WHERE s.name = sname AND sc.year = 2020 LOOP
        cnt := cnt + 1;
    END LOOP;
    RETURN cnt;
END
```

---

## Q2.2: Procedure: Division with Exception

### Pseudocode
```sql
PROCEDURE divide(a NUMERIC, b NUMERIC)
BEGIN
    IF b = 0 THEN RAISE EXCEPTION 'Division by zero!';
    RAISE NOTICE 'Result: %', a / b;
END
```

---

> **Solution Code:** See `Slip_09_DBMS_Solution.sql` in this folder.
