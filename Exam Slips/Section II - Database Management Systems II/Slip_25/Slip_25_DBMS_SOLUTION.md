# Slip 25 — DBMS-II Solution Guide

## Question
> See `Slip_25_DBMS.txt` for the full question text.

## Database Schema: Customer-Account (1:M)

### Tables
| Table | Columns |
|-------|---------|
| **Customer** | cno (PK), cname, city |
| **Account** | a_no (PK), a_type, opening_date, balance, cno (FK) |

### ER Description
**Relationship:** Customer → Account is **One-to-Many** (1:M)

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

## Q2.1 Option A: Cursor Function: Customers by City

### Concept
Cursor accepts city name and prints all customers from that city.

### Algorithm
1. Accept city name
2. Query customers where city matches
3. Loop and display

### Pseudocode
```sql
FUNCTION show_city_customers(p_city VARCHAR) RETURNS VOID
BEGIN
    FOR rec IN SELECT * FROM Customer WHERE city = p_city LOOP
        RAISE NOTICE 'Customer: %, City: %', rec.cname, rec.city;
    END LOOP;
END
```

---

## Q2.1 Option B: Trigger: Prevent Deletion of Savings Accounts

### Concept
BEFORE DELETE trigger prevents deletion of accounts with type 'Savings'.

### Algorithm
Check OLD.a_type = 'Savings', raise exception.

### Pseudocode
```sql
FUNCTION prevent_savings_delete() RETURNS TRIGGER
BEGIN
    IF OLD.a_type = 'Savings' THEN
        RAISE EXCEPTION 'Cannot delete Savings accounts';
    RETURN OLD;
END
```

---

## Q2.2: Procedure: Display Customers from Pune

### Pseudocode
```sql
PROCEDURE pune_customers()
BEGIN
    FOR rec IN SELECT * FROM Customer WHERE city = 'Pune' LOOP
        RAISE NOTICE 'Cno: %, Name: %', rec.cno, rec.cname;
    END LOOP;
END
```

---

> **Solution Code:** See `Slip_25_DBMS_Solution.sql` in this folder.
