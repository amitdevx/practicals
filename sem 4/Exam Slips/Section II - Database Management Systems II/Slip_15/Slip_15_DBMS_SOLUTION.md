# Slip 15 — DBMS-II Solution Guide

## Question
> See `Slip_15_DBMS.txt` for the full question text.

## Database Schema: Person-Area (M:1)

### Tables
Same as Slip 2.

### ER Description
Same Person-Area M:1 relationship.

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

## Q2.1 Option A: Cursor: Update Income of Urban Area Persons by 10%

### Concept
Cursor iterates through persons in 'urban' area and updates income by 10%.

### Algorithm
1. Open cursor for persons in urban areas
2. For each person, update income = income * 1.10

### Pseudocode
```sql
FUNCTION update_urban_income() RETURNS VOID
BEGIN
    FOR rec IN SELECT p.pno FROM Person p
        JOIN Area a ON p.aname = a.aname
        WHERE a.area_type = 'urban' LOOP
        UPDATE Person SET income = income * 1.10 WHERE pno = rec.pno;
    END LOOP;
    RAISE NOTICE 'Urban incomes updated by 10%%';
END
```

---

## Q2.1 Option B: Trigger: Validate Person Number Before Insert

### Concept
BEFORE INSERT trigger validates pnumber is positive.

### Algorithm
Check NEW.pno < 0, raise exception if negative.

### Pseudocode
```sql
FUNCTION check_pno() RETURNS TRIGGER
BEGIN
    IF NEW.pno < 0 THEN RAISE EXCEPTION 'Invalid Number';
    RETURN NEW;
END
```

---

## Q2.2: Procedure: Display Odd Numbers 1-100

### Pseudocode
```sql
PROCEDURE odd_numbers()
BEGIN
    FOR i IN 1..100 LOOP
        IF i % 2 != 0 THEN RAISE NOTICE '%', i;
    END LOOP;
END
```

---

> **Solution Code:** See `Slip_15_DBMS_Solution.sql` in this folder.
