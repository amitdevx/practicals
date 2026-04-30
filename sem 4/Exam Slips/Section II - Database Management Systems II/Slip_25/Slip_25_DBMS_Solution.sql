-- ============================================================
-- Slip 25: Customer-Account Database
-- Section II: Database Management Systems-II [15 Marks]
-- ============================================================

/*
DATABASE SCHEMA: Customer-Account Database

Tables:
  Customer(cno integer, cname varchar(20), city varchar(20))
  Account(a_no int, a_type varchar(10), opening_date date, balance money)

Relationship:
  Customer and Account are related with one to many relationship.
  (One customer can have many accounts; cno is FK in Account table)

Constraints:
  - cno is Primary Key in Customer
  - a_no is Primary Key in Account
  - cno in Account references Customer(cno)
*/

-- ============================================================
-- Database Setup
-- ============================================================

DROP DATABASE IF EXISTS slip_25_db;
CREATE DATABASE slip_25_db;
\c slip_25_db

-- ============================================================
-- Table Creation
-- ============================================================

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

-- ============================================================
-- Sample Data
-- ============================================================

INSERT INTO Customer VALUES (1, 'Amit', 'Pune');
INSERT INTO Customer VALUES (2, 'Sneha', 'Mumbai');
INSERT INTO Customer VALUES (3, 'Rahul', 'Pune');
INSERT INTO Customer VALUES (4, 'Priya', 'Nagpur');

INSERT INTO Account VALUES (101, 'Savings', '2023-01-15', 50000, 1);
INSERT INTO Account VALUES (102, 'Current', '2023-03-20', 75000, 2);
INSERT INTO Account VALUES (103, 'Savings', '2022-06-10', 30000, 3);
INSERT INTO Account VALUES (104, 'Current', '2023-09-01', 90000, 4);
INSERT INTO Account VALUES (105, 'Savings', '2024-01-05', 45000, 1);

-- ============================================================
-- Q2.1 Option A: Write a function using cursor which accepts city name
-- as input and prints the details of all customers in that city. [10 Marks]
-- ============================================================
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

-- Execute: SELECT get_customers_by_city('Pune');    -- Should display Amit and Rahul
-- Execute: SELECT get_customers_by_city('Mumbai');  -- Should display Sneha
-- Execute: SELECT get_customers_by_city('Chennai'); -- Should display "No customers found"

-- ============================================================
-- Q2.1 Option B (OR): Write a trigger which does not allow deletion
-- of accounts of 'savings' type. [10 Marks]
-- ============================================================
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

-- Execute: DELETE FROM Account WHERE a_no = 101;  -- Should fail (a_no 101 is Savings type)
-- Execute: DELETE FROM Account WHERE a_no = 102;  -- Should succeed (a_no 102 is Current type)

-- ============================================================
-- Q2.2: Write a procedure to display all customers from 'Pune' city. [5 Marks]
-- ============================================================
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

-- Execute: CALL display_pune_customers();  -- Should display Amit and Rahul
