# Slip 13 — DBMS-II Solution Guide

## Question
> See `Slip_13_DBMS.txt` for the full question text.

## Database Schema: Bus-Route-Driver

### Tables
Same as Slip 6: Bus, Route, Driver, Bus_Driver tables.

### ER Description
Same relationships as Slip 6.

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

## Q2.1 Option A: Trigger: Validate Driver Age (18-50)

### Concept
BEFORE INSERT trigger ensures driver age is between 18 and 50.

### Algorithm
1. Check if NEW.d_age < 18 OR NEW.d_age > 50
2. If invalid, raise exception 'invalid entry'

### Pseudocode
```sql
FUNCTION check_driver_age() RETURNS TRIGGER
BEGIN
    IF NEW.d_age < 18 OR NEW.d_age > 50 THEN
        RAISE EXCEPTION 'invalid entry';
    END IF;
    RETURN NEW;
END
```

---

## Q2.1 Option B: OR: Function — Drivers for Bus on Date

### Concept
Accepts bus_no and date, displays allotted drivers. Raises exception for invalid bus.

### Algorithm
1. Validate bus exists
2. Join Bus_Driver and Driver
3. Filter by bus_no and date
4. Display driver details

### Pseudocode
```sql
FUNCTION get_bus_drivers(p_bus INT, p_date DATE) RETURNS VOID
BEGIN
    IF NOT EXISTS (SELECT 1 FROM Bus WHERE bus_no = p_bus) THEN
        RAISE EXCEPTION 'Invalid bus number';
    FOR rec IN SELECT d.driver_name FROM Driver d
        JOIN Bus_Driver bd ON d.driver_no = bd.driver_no
        WHERE bd.bus_no = p_bus AND bd.duty_date = p_date LOOP
        RAISE NOTICE 'Driver: %', rec.driver_name;
    END LOOP;
END
```

---

## Q2.2: Procedure: Check Number in Range

### Pseudocode
```sql
PROCEDURE check_range(num INT, low INT, high INT)
BEGIN
    IF num >= low AND num <= high THEN
        RAISE NOTICE '% is in range [%, %]', num, low, high;
    ELSE
        RAISE NOTICE '% is NOT in range [%, %]', num, low, high;
    END IF;
END
```

---

> **Solution Code:** See `Slip_13_DBMS_Solution.sql` in this folder.
