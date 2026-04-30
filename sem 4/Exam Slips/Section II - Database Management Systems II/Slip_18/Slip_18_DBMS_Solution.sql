-- ============================================================
-- Slip 18: Item-Supplier Database
-- Section II: Database Management Systems-II [15 Marks]
-- ============================================================

/*
DATABASE SCHEMA: Item-Supplier Database

Tables:
  Item(itemno integer, itemname varchar(20))
  Supplier(supplier_no integer, supplier_name varchar(20), city varchar(20))
  
Relationship: Item-Supplier: M-M with rate(money) and quantity(integer) as
descriptive attributes.
*/

-- ============================================================
-- Database Setup
-- ============================================================

DROP DATABASE IF EXISTS slip_18_db;
CREATE DATABASE slip_18_db;
\c slip_18_db

-- ============================================================
-- Table Creation
-- ============================================================

DROP TABLE IF EXISTS item_supplier CASCADE;
DROP TABLE IF EXISTS Item CASCADE;
DROP TABLE IF EXISTS Supplier CASCADE;

CREATE TABLE Item (
    itemno INT PRIMARY KEY,
    itemname VARCHAR(20) NOT NULL
);

CREATE TABLE Supplier (
    supplier_no INT PRIMARY KEY,
    supplier_name VARCHAR(20) NOT NULL,
    city VARCHAR(20)
);

CREATE TABLE item_supplier (
    itemno INT REFERENCES Item(itemno) ON DELETE CASCADE,
    supplier_no INT REFERENCES Supplier(supplier_no) ON DELETE CASCADE,
    rate NUMERIC,
    quantity INT,
    PRIMARY KEY (itemno, supplier_no)
);

-- ============================================================
-- Sample Data
-- ============================================================

INSERT INTO Item VALUES (1, 'Keyboard'), (2, 'Mouse'), (3, 'Monitor'), (4, 'Printer');
INSERT INTO Supplier VALUES (101, 'TechSupply', 'Pune'), (102, 'CompWorld', 'Mumbai'), (103, 'DigiMart', 'Delhi');
INSERT INTO item_supplier VALUES
    (1, 101, 450, 100), (1, 102, 520, 80),
    (2, 101, 250, 200), (2, 103, 300, 150),
    (3, 101, 8000, 30), (3, 102, 7500, 50),
    (4, 103, 12000, 20);

-- ============================================================
-- Q2.1 Option A: Write a cursor to display the names of items whose rate is more than 500. [10 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION display_items_rate_gt_500()
RETURNS VOID AS $$
DECLARE
    cur CURSOR FOR
        SELECT i.itemno, i.itemname, s.supplier_name, isup.rate
        FROM item_supplier isup
        JOIN Item i ON isup.itemno = i.itemno
        JOIN Supplier s ON isup.supplier_no = s.supplier_no
        WHERE isup.rate > 500
        ORDER BY isup.rate DESC;
    rec RECORD;
BEGIN
    RAISE NOTICE 'Items with rate > 500:';
    OPEN cur;
    LOOP
        FETCH cur INTO rec;
        EXIT WHEN NOT FOUND;
        RAISE NOTICE '  Item: %, Supplier: %, Rate: %', rec.itemname, rec.supplier_name, rec.rate;
    END LOOP;
    CLOSE cur;
END;
$$ LANGUAGE plpgsql;

-- Execute: SELECT display_items_rate_gt_500();

-- ============================================================
-- Q2.1 Option B (OR): Write a trigger before insert or update on rate field. If the rate is less than 50 then raise the appropriate exception. [10 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION fn_check_rate()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.rate < 50 THEN
        RAISE EXCEPTION 'Rate cannot be less than 50. Given: %', NEW.rate;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS trg_check_rate ON item_supplier;
CREATE TRIGGER trg_check_rate
    BEFORE INSERT OR UPDATE ON item_supplier
    FOR EACH ROW
    EXECUTE FUNCTION fn_check_rate();

-- Execute: INSERT INTO item_supplier VALUES (4, 101, 30, 50);  -- Should fail (rate < 50)
-- Execute: INSERT INTO item_supplier VALUES (4, 101, 100, 50);  -- Should succeed

-- ============================================================
-- Q2.2: Write a procedure to find the maximum number from three numbers. [5 Marks]
-- ============================================================

CREATE OR REPLACE PROCEDURE sp_max_of_three(p_a NUMERIC, p_b NUMERIC, p_c NUMERIC)
LANGUAGE plpgsql AS $$
DECLARE
    v_max NUMERIC;
BEGIN
    v_max := p_a;
    IF p_b > v_max THEN
        v_max := p_b;
    END IF;
    IF p_c > v_max THEN
        v_max := p_c;
    END IF;
    RAISE NOTICE 'Maximum of %, %, % is %', p_a, p_b, p_c, v_max;
END;
$$;

-- Execute: CALL sp_max_of_three(10, 25, 15);
