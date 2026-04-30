-- ============================================================
-- Slip 26: Item-Supplier Database
-- Section II: Database Management Systems-II [15 Marks]
-- ============================================================

/*
DATABASE SCHEMA: Item-Supplier Database

Tables:
  Item (itemno integer, Itemname varchar(20), quantity integer)
  Supplier (supplierno integer, Supplier_name varchar(20), city varchar(20))

Relationship:
  Item and Supplier are related with many to many relationship.
  Descriptive attribute: Rate

Junction Table:
  item_supplier (itemno, supplierno, rate numeric) - M:M relationship
*/

-- ============================================================
-- Database Setup
-- ============================================================

DROP DATABASE IF EXISTS slip_26_db;
CREATE DATABASE slip_26_db;
\c slip_26_db

-- ============================================================
-- Table Creation
-- ============================================================

DROP TABLE IF EXISTS item_supplier CASCADE;
DROP TABLE IF EXISTS Item CASCADE;
DROP TABLE IF EXISTS Supplier CASCADE;

CREATE TABLE Item (
    itemno INT PRIMARY KEY,
    itemname VARCHAR(20),
    quantity INT
);

CREATE TABLE Supplier (
    supplierno INT PRIMARY KEY,
    supplier_name VARCHAR(20),
    city VARCHAR(20)
);

CREATE TABLE item_supplier (
    itemno INT REFERENCES Item(itemno),
    supplierno INT REFERENCES Supplier(supplierno),
    rate NUMERIC,
    PRIMARY KEY (itemno, supplierno)
);

-- ============================================================
-- Sample Data
-- ============================================================

INSERT INTO Item VALUES (1, 'Keyboard', 100);
INSERT INTO Item VALUES (2, 'Mouse', 200);
INSERT INTO Item VALUES (3, 'Monitor', 50);

INSERT INTO Supplier VALUES (101, 'TechSupply', 'Pune');
INSERT INTO Supplier VALUES (102, 'CompWorld', 'Mumbai');
INSERT INTO Supplier VALUES (103, 'DigiMart', 'Delhi');

INSERT INTO item_supplier VALUES (1, 101, 500);
INSERT INTO item_supplier VALUES (1, 102, 550);
INSERT INTO item_supplier VALUES (2, 101, 300);
INSERT INTO item_supplier VALUES (3, 103, 12000);
INSERT INTO item_supplier VALUES (2, 103, 350);

-- ============================================================
-- Q2.1 Option A: Write a stored function using cursors, to accept Item name
-- from the user and display the Rate and Supplier Name for that Item. [10 Marks]
-- ============================================================
CREATE OR REPLACE FUNCTION get_suppliers_for_item(p_iname VARCHAR)
RETURNS VOID AS $$
DECLARE
    v_rec RECORD;
    v_found BOOLEAN := FALSE;
    cur_items CURSOR FOR
        SELECT s.supplier_name, isp.rate
        FROM item_supplier isp
        JOIN Item i ON isp.itemno = i.itemno
        JOIN Supplier s ON isp.supplierno = s.supplierno
        WHERE i.itemname = p_iname;
BEGIN
    OPEN cur_items;
    LOOP
        FETCH cur_items INTO v_rec;
        EXIT WHEN NOT FOUND;
        v_found := TRUE;
        RAISE NOTICE 'Supplier: %, Rate: %', v_rec.supplier_name, v_rec.rate;
    END LOOP;
    CLOSE cur_items;

    IF NOT v_found THEN
        RAISE NOTICE 'No suppliers found for item: %', p_iname;
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Execute: SELECT get_suppliers_for_item('Keyboard');  -- Should display TechSupply (500) and CompWorld (550)
-- Execute: SELECT get_suppliers_for_item('Mouse');     -- Should display TechSupply (300) and DigiMart (350)
-- Execute: SELECT get_suppliers_for_item('Unknown');   -- Should display "No suppliers found"

-- ============================================================
-- Q2.1 Option B (OR): Write a trigger before update on rate field.
-- If the difference in the old rate and new rate is more than Rs 2000,
-- raise an exception and display the corresponding message. [10 Marks]
-- ============================================================
CREATE OR REPLACE FUNCTION trg_check_rate_diff()
RETURNS TRIGGER AS $$
BEGIN
    IF ABS(NEW.rate - OLD.rate) > 2000 THEN
        RAISE EXCEPTION 'Rate change too large. Old: %, New: %, Difference: %',
            OLD.rate, NEW.rate, ABS(NEW.rate - OLD.rate);
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_rate_update
BEFORE UPDATE ON item_supplier
FOR EACH ROW EXECUTE FUNCTION trg_check_rate_diff();

-- Execute: UPDATE item_supplier SET rate = 3000 WHERE itemno = 1 AND supplierno = 101;  -- Should fail (diff = 2500 > 2000)
-- Execute: UPDATE item_supplier SET rate = 600 WHERE itemno = 1 AND supplierno = 101;   -- Should succeed (diff = 100 < 2000)

-- ============================================================
-- Q2.2: Write a procedure to display subtraction of three numbers. [5 Marks]
-- ============================================================
CREATE OR REPLACE PROCEDURE subtract_three(p_a NUMERIC, p_b NUMERIC, p_c NUMERIC)
LANGUAGE plpgsql AS $$
DECLARE
    v_result NUMERIC;
BEGIN
    v_result := p_a - p_b - p_c;
    RAISE NOTICE '% - % - % = %', p_a, p_b, p_c, v_result;
END;
$$;

-- Execute: CALL subtract_three(100, 30, 20);  -- Should display 100 - 30 - 20 = 50
-- Execute: CALL subtract_three(50, 10, 5);    -- Should display 50 - 10 - 5 = 35
