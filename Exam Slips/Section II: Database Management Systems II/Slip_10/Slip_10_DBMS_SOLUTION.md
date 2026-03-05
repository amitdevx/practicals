# Slip 10 — DBMS-II Solution Guide

## Question
> See `Slip_10_DBMS.txt` for the full question text.

## Database Schema: Book-Author (M:M)

### Tables
| Table | Columns |
|-------|---------|
| **Book** | b_no (PK), b_name, pub_name (NOT NULL), b_price |
| **Author** | a_no (PK), a_name, qualification, address |
| **Book_Author** | b_no (FK), a_no (FK) |

### ER Description
**Relationship:** Book ↔ Author is **Many-to-Many**.

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

## Q2.1 Option A: Function: Display Books by Author (with Exception)

### Concept
Accepts author name, displays their books. Raises exception for invalid name.

### Algorithm
1. Validate author exists
2. Join Book_Author with Book and Author
3. Display book details

### Pseudocode
```sql
FUNCTION show_books(auth_name VARCHAR) RETURNS VOID
BEGIN
    IF NOT EXISTS (SELECT 1 FROM Author WHERE a_name = auth_name) THEN
        RAISE EXCEPTION 'Invalid author name: %', auth_name;
    FOR rec IN SELECT b.* FROM Book b
        JOIN Book_Author ba ON b.b_no = ba.b_no
        JOIN Author a ON ba.a_no = a.a_no
        WHERE a.a_name = auth_name LOOP
        RAISE NOTICE 'Book: %, Price: %', rec.b_name, rec.b_price;
    END LOOP;
END
```

---

## Q2.1 Option B: Trigger: Alert on High-Price Book Insert

### Concept
AFTER INSERT trigger displays message if book price > 1000.

### Algorithm
1. Check NEW.b_price > 1000
2. If true, raise notice 'price is so high'

### Pseudocode
```sql
FUNCTION check_price() RETURNS TRIGGER
BEGIN
    IF NEW.b_price > 1000 THEN
        RAISE NOTICE 'price is so high';
    END IF;
    RETURN NEW;
END
```

---

## Q2.2: Procedure: Display Even Numbers 1-50

### Pseudocode
```sql
PROCEDURE even_numbers()
BEGIN
    FOR i IN 1..50 LOOP
        IF i % 2 = 0 THEN RAISE NOTICE '%', i;
    END LOOP;
END
```

---

> **Solution Code:** See `Slip_10_DBMS_Solution.sql` in this folder.
