# Slip 8 — DBMS-II Solution Guide

## Question
> See `Slip_08_DBMS.txt` for the full question text.

## Database Schema: Train-Passenger (M:M)

### Tables
| Table | Columns |
|-------|---------|
| **Train** | train_no (PK), train_name, depart_time, arrival_time, source_stn, dest_stn, no_of_res_bogies, bogie_capacity |
| **Passenger** | passenger_id (PK), passenger_name, address, age, gender |
| **Ticket** | train_no (FK), passenger_id (FK), ticket_no, bogie_no, no_of_berths, tdate, ticket_amt, status ('W'/'C') |

### ER Description
**Relationship:** Train ↔ Passenger is **Many-to-Many** via Ticket table.

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

## Q2.1 Option A: Function: Display Ticket Details for a Train

### Concept
Function accepts train name, looks up train_no, then displays all tickets. Raises exception for invalid name.

### Algorithm
1. Accept train name
2. Find train_no from Train table
3. If not found, raise exception
4. Display all tickets for that train

### Pseudocode
```sql
FUNCTION show_tickets(tname VARCHAR) RETURNS VOID
BEGIN
    SELECT train_no INTO t_no FROM Train WHERE train_name = tname;
    IF NOT FOUND THEN RAISE EXCEPTION 'Invalid train name: %', tname;
    FOR rec IN SELECT * FROM Ticket WHERE train_no = t_no LOOP
        RAISE NOTICE 'Ticket: %, Passenger: %, Amount: %',
            rec.ticket_no, rec.passenger_id, rec.ticket_amt;
    END LOOP;
END
```

---

## Q2.1 Option B: Trigger: Age-Based Fare Message After Insert

### Concept
AFTER INSERT trigger on Passenger displays fare message if age > 5.

### Algorithm
1. After inserting passenger, check NEW.age
2. If age > 5, raise notice about full fare
3. Return NEW

### Pseudocode
```sql
FUNCTION check_age_fare() RETURNS TRIGGER
BEGIN
    IF NEW.age > 5 THEN
        RAISE NOTICE 'Age above 5 will be charged full fare';
    END IF;
    RETURN NEW;
END
```

---

## Q2.2: Procedure: Addition of Two Numbers

### Pseudocode
```sql
PROCEDURE add_two(a INT, b INT)
BEGIN
    RAISE NOTICE 'Sum: %', a + b;
END
```

---

> **Solution Code:** See `Slip_08_DBMS_Solution.sql` in this folder.
