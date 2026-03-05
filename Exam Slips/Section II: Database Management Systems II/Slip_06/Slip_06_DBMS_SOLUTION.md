# Slip 6 — DBMS-II Solution Guide

## Question
> See `Slip_06_DBMS.txt` for the full question text.

## Database Schema: Bus-Route-Driver

### Tables
| Table | Columns |
|-------|---------|
| **Route** | route_no (PK), source, destination, no_of_stations |
| **Bus** | bus_no (PK), capacity (NOT NULL), depot_name, route_no (FK) |
| **Driver** | driver_no (PK), driver_name, license_no (UNIQUE), address, d_age, salary |
| **Bus_Driver** | bus_no (FK), driver_no (FK), duty_date, shift (1/2) |

### ER Description
**Relationships:**
- Bus → Route: Many-to-One (M:1)
- Bus ↔ Driver: Many-to-Many (M:M) with shift info

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

## Q2.1 Option A: Function: Get Driver Name for a Bus

### Concept
Function accepts bus number and returns driver names assigned to that bus.

### Algorithm
1. Accept bus_no
2. JOIN Bus_Driver and Driver tables
3. Return driver names for matching bus_no

### Pseudocode
```sql
FUNCTION get_driver(p_bus_no INT) RETURNS VOID
BEGIN
    FOR rec IN SELECT d.driver_name FROM Driver d
        JOIN Bus_Driver bd ON d.driver_no = bd.driver_no
        WHERE bd.bus_no = p_bus_no LOOP
        RAISE NOTICE 'Driver: %', rec.driver_name;
    END LOOP;
END
```

---

## Q2.1 Option B: OR: Function — Drivers Over 50 by Depot

### Concept
Function accepts depot name and displays drivers aged > 50.

### Algorithm
1. Accept depot name
2. JOIN Bus and Bus_Driver and Driver
3. Filter where depot_name matches and age > 50

### Pseudocode
```sql
FUNCTION old_drivers(p_depot VARCHAR) RETURNS VOID
BEGIN
    FOR rec IN SELECT DISTINCT d.* FROM Driver d
        JOIN Bus_Driver bd ON d.driver_no = bd.driver_no
        JOIN Bus b ON bd.bus_no = b.bus_no
        WHERE b.depot_name = p_depot AND d.d_age > 50 LOOP
        RAISE NOTICE 'Driver: %, Age: %', rec.driver_name, rec.d_age;
    END LOOP;
END
```

---

## Q2.2: Procedure: Even or Odd

### Pseudocode
```sql
PROCEDURE check_even_odd(n INTEGER)
BEGIN
    IF n % 2 = 0 THEN RAISE NOTICE '% is Even', n;
    ELSE RAISE NOTICE '% is Odd', n;
    END IF;
END
```

---

> **Solution Code:** See `Slip_06_DBMS_Solution.sql` in this folder.
