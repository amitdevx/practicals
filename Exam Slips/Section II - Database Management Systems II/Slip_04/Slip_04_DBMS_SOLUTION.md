# Slip 4 — DBMS-II Solution Guide

## Question
> See `Slip_04_DBMS.txt` for the full question text.

## Database Schema: Movies-Actor-Producer

### Tables
| Table | Columns |
|-------|---------|
| **Movies** | m_name (PK), release_year, budget |
| **Actor** | a_name (PK), role, charges, a_address |
| **Producer** | producer_id (PK), name, p_address |
| **Movie_Actor** | m_name (FK), a_name (FK), role |
| **Movie_Producer** | m_name (FK), producer_id (FK) |

### ER Description
**Relationships:**
- Actor ↔ Movie: M:M (an actor acts in many movies, a movie has many actors)
- Producer ↔ Movie: M:M (a producer produces many movies)

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

## Q2.1 Option A: Cursor: Count Movies for an Actor

### Concept
Cursor-based function accepts actor name and counts their movies.

### Algorithm
1. Accept actor name
2. Count entries in Movie_Actor where a_name matches
3. Return total count

### Pseudocode
```sql
FUNCTION count_actor_movies(actor VARCHAR) RETURNS INTEGER
BEGIN
    DECLARE cnt INTEGER := 0;
    FOR rec IN SELECT * FROM Movie_Actor WHERE a_name = actor LOOP
        cnt := cnt + 1;
    END LOOP;
    RETURN cnt;
END
```

---

## Q2.1 Option B: Trigger: Validate Movie Budget (Min 50 Lakh)

### Concept
BEFORE INSERT trigger ensures movie budget ≥ 5000000 (50 lakh).

### Algorithm
1. Check NEW.budget < 5000000
2. If invalid, raise exception
3. If valid, allow insert

### Pseudocode
```sql
FUNCTION check_budget() RETURNS TRIGGER
BEGIN
    IF NEW.budget < 5000000 THEN
        RAISE EXCEPTION 'Budget must be minimum 50 lakh';
    END IF;
    RETURN NEW;
END
```

---

## Q2.2: Procedure: Check Positive/Negative/Zero

### Pseudocode
```sql
PROCEDURE check_number(n INTEGER)
BEGIN
    IF n > 0 THEN RAISE NOTICE 'Positive';
    ELSIF n < 0 THEN RAISE NOTICE 'Negative';
    ELSE RAISE NOTICE 'Zero';
    END IF;
END
```

---

> **Solution Code:** See `Slip_04_DBMS_Solution.sql` in this folder.
