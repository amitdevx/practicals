# Slip 18 — DBMS-II Solution Guide

## Question
> See `Slip_18_DBMS.txt` for the full question text.

## Database Schema: Item-Supplier (M:M)

### Tables
| Table | Columns |
|-------|---------|
| **Item** | itemno (PK), itemname |
| **Supplier** | supplier_no (PK), supplier_name, city |
| **Item_Supplier** | itemno (FK), supplier_no (FK), rate, quantity |

### ER Description
**Relationship:** Item ↔ Supplier is **Many-to-Many** with rate and quantity.

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

## Q2.1 Option A: Cursor: Display Items with Rate > 500

### Concept
Cursor iterates through Item_Supplier to find items with rate > 500.

### Algorithm
1. Open cursor joining Item and Item_Supplier
2. Filter where rate > 500
3. Display item names

### Pseudocode
```sql
FUNCTION high_rate_items() RETURNS VOID
BEGIN
    FOR rec IN SELECT DISTINCT i.itemname, isup.rate
        FROM Item i JOIN Item_Supplier isup ON i.itemno = isup.itemno
        WHERE isup.rate > 500 LOOP
        RAISE NOTICE 'Item: %, Rate: %', rec.itemname, rec.rate;
    END LOOP;
END
```

---

## Q2.1 Option B: Trigger: Validate Rate Before Insert/Update

### Concept
BEFORE INSERT OR UPDATE trigger ensures rate ≥ 50.

### Algorithm
Check NEW.rate < 50, raise exception if too low.

### Pseudocode
```sql
FUNCTION check_rate() RETURNS TRIGGER
BEGIN
    IF NEW.rate < 50 THEN
        RAISE EXCEPTION 'Rate must be at least 50';
    END IF;
    RETURN NEW;
END
```

---

## Q2.2: Procedure: Maximum of Three Numbers

### Pseudocode
```sql
PROCEDURE find_max(a INT, b INT, c INT)
BEGIN
    RAISE NOTICE 'Maximum: %', GREATEST(a, b, c);
END
```

---

> **Solution Code:** See `Slip_18_DBMS_Solution.sql` in this folder.
