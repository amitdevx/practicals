# Slip 30 — DBMS-II Solution Guide

## Question
> See `Slip_30_DBMS.txt` for the full question text.

## Database Schema: Student-Teacher (M:M)

### Tables
| Table | Columns |
|-------|---------|
| **Student** | roll_no (PK), sname, sclass |
| **Teacher** | t_no (PK), tname, experience |
| **Student_Teacher** | roll_no (FK), t_no (FK), subject |

### ER Description
**Relationship:** Student ↔ Teacher is **Many-to-Many** with subject.

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

## Q2.1 Option A: Function: Count Teachers with Experience > 10

### Concept
Counts teachers having more than 10 years experience.

### Algorithm
1. Count from Teacher where experience > 10
2. Return count

### Pseudocode
```sql
FUNCTION exp_teachers() RETURNS INTEGER
BEGIN
    SELECT COUNT(*) INTO cnt FROM Teacher WHERE experience > 10;
    RETURN cnt;
END
```

---

## Q2.1 Option B: Trigger: Validate Roll Number Before Insert

### Concept
BEFORE INSERT trigger ensures roll_no is positive.

### Algorithm
Check NEW.roll_no ≤ 0, raise exception.

### Pseudocode
```sql
FUNCTION check_rollno() RETURNS TRIGGER
BEGIN
    IF NEW.roll_no <= 0 THEN
        RAISE EXCEPTION 'Invalid Roll Number';
    RETURN NEW;
END
```

---

## Q2.2: Procedure: Sum and Average of First N (While Loop)

### Pseudocode
```sql
PROCEDURE sum_avg(n INT)
BEGIN
    DECLARE i INT := 1; total INT := 0;
    WHILE i <= n LOOP total := total + i; i := i + 1; END LOOP;
    RAISE NOTICE 'Sum: %, Avg: %', total, total::NUMERIC / n;
END
```

---

> **Solution Code:** See `Slip_30_DBMS_Solution.sql` in this folder.
