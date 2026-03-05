# Slip 23 — DBMS-II Solution Guide

## Question
> See `Slip_23_DBMS.txt` for the full question text.

## Database Schema: Car-Driver (M:M)

### Tables
| Table | Columns |
|-------|---------|
| **Car** | c_no (PK), owner, model, color |
| **Driver** | driver_no (PK), driver_name, license_no (UNIQUE), d_age, salary |
| **Car_Driver** | c_no (FK), driver_no (FK) |

### ER Description
**Relationship:** Car ↔ Driver is **Many-to-Many**.

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

## Q2.1 Option A: Cursor: Cars Driven by a Driver

### Concept
Cursor function accepts driver name, displays all cars. Handles invalid name.

### Algorithm
1. Check driver exists
2. Join Car_Driver and Car
3. Display car details via cursor

### Pseudocode
```sql
FUNCTION get_cars(dname VARCHAR) RETURNS VOID
BEGIN
    IF NOT EXISTS (SELECT 1 FROM Driver WHERE driver_name = dname) THEN
        RAISE NOTICE 'Invalid driver name';
        RETURN;
    FOR rec IN SELECT c.* FROM Car c
        JOIN Car_Driver cd ON c.c_no = cd.c_no
        JOIN Driver d ON cd.driver_no = d.driver_no
        WHERE d.driver_name = dname LOOP
        RAISE NOTICE 'Car: %, Model: %, Color: %',
            rec.c_no, rec.model, rec.color;
    END LOOP;
END
```

---

## Q2.1 Option B: Trigger: Validate Driver Age (≥ 21)

### Concept
BEFORE INSERT/UPDATE trigger ensures driver age ≥ 21.

### Algorithm
Check NEW.d_age < 21, raise exception.

### Pseudocode
```sql
FUNCTION check_age() RETURNS TRIGGER
BEGIN
    IF NEW.d_age < 21 THEN RAISE EXCEPTION 'Driver age must be >= 21';
    RETURN NEW;
END
```

---

## Q2.2: Procedure: Sum of First 100 Numbers (Loop)

### Pseudocode
```sql
PROCEDURE sum_100()
BEGIN
    DECLARE i INT := 1; total INT := 0;
    LOOP total := total + i; i := i + 1; EXIT WHEN i > 100; END LOOP;
    RAISE NOTICE 'Sum: %', total;  -- 5050
END
```

---

> **Solution Code:** See `Slip_23_DBMS_Solution.sql` in this folder.
