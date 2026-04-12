# Slip 2 — DBMS-II Solution Guide

## Question
> See `Slip_02_DBMS.txt` for the full question text.

## Database Schema: Person-Area (M:1)

### Tables
| Table | Columns |
|-------|---------|
| **Area** | aname (PK), area_type (CHECK: 'urban'/'rural') |
| **Person** | pno (PK), pname, birthdate, income, aname (FK→Area) |

### ER Description
**Relationship:** Person → Area is **Many-to-One** (M:1)
- Many persons can live in one area
- Each person belongs to exactly one area
- Foreign key `aname` in Person references Area

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

## Q2.1 Option A: Stored Function: Count Persons in an Area

### Concept
Function accepts area name and counts persons living there.

### Algorithm
1. Accept area_name as input
2. COUNT persons where aname = input
3. Return the count

### Pseudocode
```sql
FUNCTION count_persons(area_name VARCHAR) RETURNS INTEGER
BEGIN
    DECLARE cnt INTEGER;
    SELECT COUNT(*) INTO cnt FROM Person WHERE aname = area_name;
    RETURN cnt;
END
```

---

## Q2.1 Option B: OR: Stored Function — Sum of Income by Area Type

### Concept
Function accepts area type and sums income. Validates input against 'urban'/'rural'.

### Algorithm
1. Accept area_type as input
2. Validate it's 'urban' or 'rural'
3. SUM income of persons in areas of that type
4. Raise exception for invalid type

### Pseudocode
```sql
FUNCTION sum_income_by_type(a_type VARCHAR) RETURNS NUMERIC
BEGIN
    IF a_type NOT IN ('urban', 'rural') THEN
        RAISE EXCEPTION 'Invalid area type: %', a_type;
    END IF;
    SELECT COALESCE(SUM(p.income), 0) INTO total
    FROM Person p JOIN Area a ON p.aname = a.aname
    WHERE a.area_type = a_type;
    RETURN total;
END
```

---

## Q2.2: Procedure: Division with Error Handling

### Pseudocode
```sql
PROCEDURE divide_numbers(a NUMERIC, b NUMERIC)
BEGIN
    IF b = 0 THEN
        RAISE EXCEPTION 'Division by zero error!';
    END IF;
    RAISE NOTICE 'Result: %', a / b;
END
```

---

> **Solution Code:** See `Slip_02_DBMS_Solution.sql` in this folder.
