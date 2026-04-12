# Slip 5 — DBMS-II Solution Guide

## Question
> See `Slip_05_DBMS.txt` for the full question text.

## Database Schema: Student-Competition (M:M)

### Tables
| Table | Columns |
|-------|---------|
| **Student** | sreg_no (PK), s_name, s_class |
| **Competition** | c_no (PK), c_name, c_type (CHECK: 'sport'/'academic') |
| **Student_Competition** | sreg_no (FK), c_no (FK), rank, year |

### ER Description
**Relationship:** Student ↔ Competition is **Many-to-Many**

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

## Q2.1 Option A: Cursor Function: Display Student Competitions by Year/Class

### Concept
Function uses cursor to filter by year and class, displaying student names with competition details.

### Algorithm
1. Accept year and class as inputs
2. JOIN all three tables
3. Filter by year and class
4. Loop through cursor results

### Pseudocode
```sql
FUNCTION show_competitions(p_year INT, p_class VARCHAR) RETURNS VOID
BEGIN
    FOR rec IN
        SELECT s.s_name, c.c_name, sc.rank
        FROM Student s JOIN Student_Competition sc ...
        WHERE sc.year = p_year AND s.s_class = p_class
    LOOP
        RAISE NOTICE '%, %, Rank: %', rec.s_name, rec.c_name, rec.rank;
    END LOOP;
END
```

---

## Q2.1 Option B: Trigger: Notice on Competition Update

### Concept
BEFORE UPDATE trigger raises a notice message when competition record is updated.

### Algorithm
1. Create function that raises notice 'competition record is being updated'
2. Return NEW to allow update
3. Attach as BEFORE UPDATE trigger on Competition

### Pseudocode
```sql
FUNCTION notify_competition_update() RETURNS TRIGGER
BEGIN
    RAISE NOTICE 'competition record is being updated';
    RETURN NEW;
END
```

---

## Q2.2: Procedure: Max and Min of Three Numbers

### Pseudocode
```sql
PROCEDURE find_max_min_three(a INT, b INT, c INT)
BEGIN
    RAISE NOTICE 'Maximum: %', GREATEST(a, b, c);
    RAISE NOTICE 'Minimum: %', LEAST(a, b, c);
END
```

---

> **Solution Code:** See `Slip_05_DBMS_Solution.sql` in this folder.
