/*
  SLIP 18
  Schema: Item(itemno int PK, itemname varchar(20)),
          Supplier(supplier_no int PK, supplier_name varchar(20), city varchar(20)),
          item_supplier(itemno, supplier_no, rate numeric, quantity int) M:M
  Q2.1A: Cursor display items with rate>500.
  Q2.1B: Trigger before insert/update on rate - if rate<50 raise exception.
  Q2.2:  Procedure max of three numbers.
*/

-- Schema
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

-- Sample Data
INSERT INTO Item VALUES (1, 'Keyboard'), (2, 'Mouse'), (3, 'Monitor'), (4, 'Printer');
INSERT INTO Supplier VALUES (101, 'TechSupply', 'Pune'), (102, 'CompWorld', 'Mumbai'), (103, 'DigiMart', 'Delhi');
INSERT INTO item_supplier VALUES
    (1, 101, 450, 100), (1, 102, 520, 80),
    (2, 101, 250, 200), (2, 103, 300, 150),
    (3, 101, 8000, 30), (3, 102, 7500, 50),
    (4, 103, 12000, 20);

-- Q2.1 Option A: Cursor display items with rate>500
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

-- Q2.1 Option B: Trigger before insert/update on item_supplier - rate<50 raise exception
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

-- Q2.2: Procedure max of three numbers
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

-- Test Calls
SELECT display_items_rate_gt_500();
-- This should fail: INSERT INTO item_supplier VALUES (2, 102, 30, 100);
CALL sp_max_of_three(10, 25, 18);
CALL sp_max_of_three(100, 50, 75);
