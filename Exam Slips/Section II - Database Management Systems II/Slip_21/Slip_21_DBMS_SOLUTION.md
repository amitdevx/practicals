# Slip 21 — DBMS-II Solution Guide

## Question
> See `Slip_21_DBMS.txt` for the full question text.

## Database Schema: Doctor-Hospital (M:1)

### Tables
| Table | Columns |
|-------|---------|
| **Hospital** | h_no (PK), h_name, city |
| **Doctor** | d_no (PK), d_name, specialization, phone_no, charges, h_no (FK) |

### ER Description
**Relationship:** Doctor → Hospital is **Many-to-One** (M:1)

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

## Q2.1 Option A: Function: Average Charges by Hospital

### Concept
Accepts hospital name and calculates average doctor charges.

### Algorithm
1. Join Doctor and Hospital
2. Filter by h_name
3. Return AVG(charges)

### Pseudocode
```sql
FUNCTION avg_charges(hosp_name VARCHAR) RETURNS NUMERIC
BEGIN
    SELECT AVG(d.charges) INTO result FROM Doctor d
        JOIN Hospital h ON d.h_no = h.h_no WHERE h.h_name = hosp_name;
    RETURN result;
END
```

---

## Q2.1 Option B: Trigger: Validate Doctor Charges

### Concept
BEFORE INSERT/UPDATE trigger ensures charges ≥ 0.

### Algorithm
Check NEW.charges < 0, raise exception.

### Pseudocode
```sql
FUNCTION check_charges() RETURNS TRIGGER
BEGIN
    IF NEW.charges < 0 THEN RAISE EXCEPTION 'Charges cannot be negative';
    RETURN NEW;
END
```

---

## Q2.2: Procedure: Sum and Average of First N (While Loop)

### Pseudocode
```sql
PROCEDURE sum_avg_while(n INT)
BEGIN
    DECLARE i INT := 1; total INT := 0;
    WHILE i <= n LOOP total := total + i; i := i + 1; END LOOP;
    RAISE NOTICE 'Sum: %, Avg: %', total, total::NUMERIC / n;
END
```

---

> **Solution Code:** See `Slip_21_DBMS_Solution.sql` in this folder.
