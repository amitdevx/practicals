# Slip 28 — DBMS-II Solution Guide

## Question
> See `Slip_28_DBMS.txt` for the full question text.

## Database Schema: Company-Person (M:M)

### Tables
| Table | Columns |
|-------|---------|
| **Company** | name (PK), address, city, share_value |
| **Person** | pname (PK), pcity |
| **Company_Person** | name (FK), pname (FK), no_of_shares |

### ER Description
**Relationship:** Company ↔ Person is **Many-to-Many** with no_of_shares.

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

## Q2.1 Option A: Function: Update Share Values by 20% for a Person

### Concept
Updates share_value by 20% for all companies where a person holds shares.

### Algorithm
1. Accept person name
2. Find companies where person has shares
3. Update share_value by 20%

### Pseudocode
```sql
FUNCTION update_shares(p_person VARCHAR) RETURNS VOID
BEGIN
    UPDATE Company SET share_value = share_value * 1.20
    WHERE name IN (SELECT name FROM Company_Person
                   WHERE pname = p_person);
    RAISE NOTICE 'Share values updated by 20%%';
END
```

---

## Q2.1 Option B: Trigger: Message Before Company Delete

### Concept
BEFORE DELETE trigger displays message when company is being deleted.

### Algorithm
Raise notice with company name.

### Pseudocode
```sql
FUNCTION notify_company_delete() RETURNS TRIGGER
BEGIN
    RAISE NOTICE 'Company % is being deleted', OLD.name;
    RETURN OLD;
END
```

---

## Q2.2: Procedure: Division with Error Handling

### Pseudocode
```sql
PROCEDURE divide(a NUMERIC, b NUMERIC)
BEGIN
    IF b = 0 THEN RAISE EXCEPTION 'Division by zero error!';
    RAISE NOTICE 'Result: %', a / b;
END
```

---

> **Solution Code:** See `Slip_28_DBMS_Solution.sql` in this folder.
