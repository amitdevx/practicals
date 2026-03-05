/*
SLIP 26 - SECTION II: DATABASE MANAGEMENT SYSTEMS II

Item(itemno int PK, itemname varchar(20), quantity int)
Supplier(supplierno int PK, supplier_name varchar(20), city varchar(20))
item_supplier(itemno, supplierno, rate numeric) M:M

Q2.1A: Cursor function accept item name, display rate and supplier name.
Q2.1B: Trigger before update on rate - if difference > 2000 raise exception.
Q2.2: Procedure for subtraction of three numbers.
*/

-- Table Creation
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

-- Sample Data
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

-- Q2.1A: Cursor function accept item name, display rate and supplier name
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

-- Q2.1B: Trigger before update on rate - if difference > 2000 raise exception
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

-- Q2.2: Procedure for subtraction of three numbers
CREATE OR REPLACE PROCEDURE subtract_three(p_a NUMERIC, p_b NUMERIC, p_c NUMERIC)
LANGUAGE plpgsql AS $$
DECLARE
    v_result NUMERIC;
BEGIN
    v_result := p_a - p_b - p_c;
    RAISE NOTICE '% - % - % = %', p_a, p_b, p_c, v_result;
END;
$$;

-- Test Calls
SELECT get_suppliers_for_item('Keyboard');
SELECT get_suppliers_for_item('Mouse');

-- Test trigger (this should raise exception)
-- UPDATE item_supplier SET rate = 6000 WHERE itemno = 1 AND supplierno = 101;

CALL subtract_three(100, 30, 20);
CALL subtract_three(50, 10, 5);
