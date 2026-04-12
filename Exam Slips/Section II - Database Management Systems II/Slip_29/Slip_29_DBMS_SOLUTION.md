# Slip 29 — DBMS-II Solution Guide

## Question
> See `Slip_29_DBMS.txt` for the full question text.

## Database Schema: Person-Area (M:1)

### Tables
| Table | Columns |
|-------|---------|
| **Area** | aid (PK), aname, area_type ('urban'/'rural') |
| **Person** | pno (PK), pname, birthdate, income, aid (FK) |

### ER Description
**Relationship:** Person → Area is **Many-to-One**.

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

## Q2.1 Option A: Cursor: Persons in Urban Area

### Concept
Cursor displays names of persons living in urban areas.

### Algorithm
1. Join Person and Area
2. Filter where area_type = 'urban'
3. Display names

### Pseudocode
```sql
FUNCTION urban_persons() RETURNS VOID
BEGIN
    FOR rec IN SELECT p.pname FROM Person p
        JOIN Area a ON p.aid = a.aid
        WHERE a.area_type = 'urban' LOOP
        RAISE NOTICE 'Person: %', rec.pname;
    END LOOP;
END
```

---

## Q2.1 Option B: Trigger: Notice Before Person Delete

### Concept
BEFORE DELETE trigger displays message when person record is being deleted.

### Algorithm
Raise notice, return OLD.

### Pseudocode
```sql
FUNCTION notify_person_delete() RETURNS TRIGGER
BEGIN
    RAISE NOTICE 'person record is being deleted';
    RETURN OLD;
END
```

---

## Q2.2: Procedure: Subtraction of Three Numbers

### Pseudocode
```sql
PROCEDURE subtract_three(a INT, b INT, c INT)
BEGIN
    RAISE NOTICE 'Result: %', a - b - c;
END
```

---

> **Solution Code:** See `Slip_29_DBMS_Solution.sql` in this folder.
