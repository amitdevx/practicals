/*
SLIP 25 - SECTION II: DATABASE MANAGEMENT SYSTEMS II

Customer(cno int PK, cname varchar(20), city varchar(20))
Account(a_no int PK, a_type varchar(10), opening_date date, balance numeric, cno FK) 1:M

Q2.1A: Cursor function accept city name, print customer details.
Q2.1B: Trigger to prevent deletion of 'Savings' type accounts.
Q2.2: Procedure to display customers from 'Pune'.
*/

-- Table Creation
DROP TABLE IF EXISTS Account CASCADE;
DROP TABLE IF EXISTS Customer CASCADE;

CREATE TABLE Customer (
    cno INT PRIMARY KEY,
    cname VARCHAR(20),
    city VARCHAR(20)
);

CREATE TABLE Account (
    a_no INT PRIMARY KEY,
    a_type VARCHAR(10),
    opening_date DATE,
    balance NUMERIC,
    cno INT REFERENCES Customer(cno)
);

-- Sample Data
INSERT INTO Customer VALUES (1, 'Amit', 'Pune');
INSERT INTO Customer VALUES (2, 'Sneha', 'Mumbai');
INSERT INTO Customer VALUES (3, 'Rahul', 'Pune');
INSERT INTO Customer VALUES (4, 'Priya', 'Nagpur');

INSERT INTO Account VALUES (101, 'Savings', '2023-01-15', 50000, 1);
INSERT INTO Account VALUES (102, 'Current', '2023-03-20', 75000, 2);
INSERT INTO Account VALUES (103, 'Savings', '2022-06-10', 30000, 3);
INSERT INTO Account VALUES (104, 'Current', '2023-09-01', 90000, 4);
INSERT INTO Account VALUES (105, 'Savings', '2024-01-05', 45000, 1);

-- Q2.1A: Cursor function accept city name, print customer details
CREATE OR REPLACE FUNCTION get_customers_by_city(p_city VARCHAR)
RETURNS VOID AS $$
DECLARE
    v_rec RECORD;
    v_found BOOLEAN := FALSE;
    cur_cust CURSOR FOR
        SELECT cno, cname, city FROM Customer WHERE city = p_city;
BEGIN
    OPEN cur_cust;
    LOOP
        FETCH cur_cust INTO v_rec;
        EXIT WHEN NOT FOUND;
        v_found := TRUE;
        RAISE NOTICE 'Cno: %, Name: %, City: %', v_rec.cno, v_rec.cname, v_rec.city;
    END LOOP;
    CLOSE cur_cust;

    IF NOT v_found THEN
        RAISE NOTICE 'No customers found in city: %', p_city;
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Q2.1B: Trigger to prevent deletion of 'Savings' type accounts
CREATE OR REPLACE FUNCTION trg_prevent_savings_delete()
RETURNS TRIGGER AS $$
BEGIN
    IF OLD.a_type = 'Savings' THEN
        RAISE EXCEPTION 'Cannot delete Savings type account (a_no: %)', OLD.a_no;
    END IF;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_no_delete_savings
BEFORE DELETE ON Account
FOR EACH ROW EXECUTE FUNCTION trg_prevent_savings_delete();

-- Q2.2: Procedure to display customers from 'Pune'
CREATE OR REPLACE PROCEDURE display_pune_customers()
LANGUAGE plpgsql AS $$
DECLARE
    v_rec RECORD;
BEGIN
    FOR v_rec IN SELECT cno, cname, city FROM Customer WHERE city = 'Pune' LOOP
        RAISE NOTICE 'Cno: %, Name: %, City: %', v_rec.cno, v_rec.cname, v_rec.city;
    END LOOP;
END;
$$;

-- Test Calls
SELECT get_customers_by_city('Pune');
SELECT get_customers_by_city('Mumbai');

-- Test trigger (this should raise exception)
-- DELETE FROM Account WHERE a_no = 101;

-- Test deleting current account (should succeed)
-- DELETE FROM Account WHERE a_no = 102;

CALL display_pune_customers();
