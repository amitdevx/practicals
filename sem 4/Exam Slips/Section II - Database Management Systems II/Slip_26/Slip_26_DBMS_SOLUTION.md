# Slip 26 — DBMS-II Solution Guide

## Question
> See `Slip_26_DBMS.txt` for the full question text.

## Database Schema: Item-Supplier (M:M)

### Tables
| Table | Columns |
|-------|---------|
| **Item** | itemno (PK), itemname, quantity |
| **Supplier** | supplierno (PK), supplier_name, city |
| **Item_Supplier** | itemno (FK), supplierno (FK), rate |

### ER Description
**Relationship:** Item ↔ Supplier is **Many-to-Many** with rate.

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

## Q2.1 Option A: Cursor: Rate and Supplier for an Item

### Concept
Cursor accepts item name, displays rate and supplier name.

### Algorithm
1. Accept item name
2. Join Item, Item_Supplier, Supplier
3. Display rate and supplier

### Pseudocode
```sql
FUNCTION item_details(iname VARCHAR) RETURNS VOID
BEGIN
    FOR rec IN SELECT s.supplier_name, isup.rate
        FROM Item_Supplier isup
        JOIN Item i ON isup.itemno = i.itemno
        JOIN Supplier s ON isup.supplierno = s.supplierno
        WHERE i.itemname = iname LOOP
        RAISE NOTICE 'Supplier: %, Rate: %', rec.supplier_name, rec.rate;
    END LOOP;
END
```

---

## Q2.1 Option B: Trigger: Rate Difference Check Before Update

### Concept
BEFORE UPDATE trigger checks if rate difference > 2000.

### Algorithm
Calculate |NEW.rate - OLD.rate|, if > 2000, raise exception.

### Pseudocode
```sql
FUNCTION check_rate_diff() RETURNS TRIGGER
BEGIN
    IF ABS(NEW.rate - OLD.rate) > 2000 THEN
        RAISE EXCEPTION 'Rate change exceeds Rs 2000 limit';
    RETURN NEW;
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

> **Solution Code:** See `Slip_26_DBMS_Solution.sql` in this folder.
