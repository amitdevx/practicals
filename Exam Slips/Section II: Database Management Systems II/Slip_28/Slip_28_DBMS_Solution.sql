-- ============================================================
-- Slip 28: Company-Person Database
-- Section II: Database Management Systems-II [15 Marks]
-- ============================================================

/*
DATABASE SCHEMA: Company-Person Database

Tables:
  Company (Name varchar(30), address varchar(50), city varchar(20), share_value money)
  Person (pname varchar(30), pcity varchar(20))

Relationship:
  Company and Person are related with M to M relationship.
  Descriptive attribute: No_of_shares

Junction Table:
  company_person (name, pname, no_of_shares int) - M:M relationship
*/

-- ============================================================
-- Database Setup
-- ============================================================

DROP DATABASE IF EXISTS slip_28_db;
CREATE DATABASE slip_28_db;
\c slip_28_db

-- ============================================================
-- Table Creation
-- ============================================================

DROP TABLE IF EXISTS company_person CASCADE;
DROP TABLE IF EXISTS Company CASCADE;
DROP TABLE IF EXISTS Person CASCADE;

CREATE TABLE Company (
    name VARCHAR(30) PRIMARY KEY,
    address VARCHAR(50),
    city VARCHAR(20),
    share_value NUMERIC
);

CREATE TABLE Person (
    pname VARCHAR(30) PRIMARY KEY,
    pcity VARCHAR(20)
);

CREATE TABLE company_person (
    name VARCHAR(30) REFERENCES Company(name),
    pname VARCHAR(30) REFERENCES Person(pname),
    no_of_shares INT,
    PRIMARY KEY (name, pname)
);

-- ============================================================
-- Sample Data
-- ============================================================

INSERT INTO Company VALUES ('TCS', 'Hinjewadi', 'Pune', 3500);
INSERT INTO Company VALUES ('Infosys', 'Electronic City', 'Bangalore', 1500);
INSERT INTO Company VALUES ('Wipro', 'Sarjapur', 'Bangalore', 450);

INSERT INTO Person VALUES ('Amit', 'Pune');
INSERT INTO Person VALUES ('Sneha', 'Mumbai');
INSERT INTO Person VALUES ('Rahul', 'Bangalore');

INSERT INTO company_person VALUES ('TCS', 'Amit', 100);
INSERT INTO company_person VALUES ('Infosys', 'Amit', 200);
INSERT INTO company_person VALUES ('Wipro', 'Sneha', 150);
INSERT INTO company_person VALUES ('TCS', 'Rahul', 50);
INSERT INTO company_person VALUES ('Infosys', 'Rahul', 300);

-- ============================================================
-- Q2.1 Option A: Write a stored function to update the share_values by 20%
-- for Person (Accept person name as input). [10 Marks]
-- ============================================================
CREATE OR REPLACE FUNCTION update_shares_for_person(p_pname VARCHAR)
RETURNS VOID AS $$
DECLARE
    v_count INT;
BEGIN
    UPDATE Company SET share_value = share_value * 1.20
    WHERE name IN (SELECT name FROM company_person WHERE pname = p_pname);

    GET DIAGNOSTICS v_count = ROW_COUNT;

    IF v_count = 0 THEN
        RAISE NOTICE 'No companies found for person: %', p_pname;
    ELSE
        RAISE NOTICE 'Updated share values by 20%% for % company(ies) of person %', v_count, p_pname;
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Execute: SELECT update_shares_for_person('Amit');   -- Should update TCS and Infosys share values by 20%
-- Execute: SELECT update_shares_for_person('Unknown'); -- Should display "No companies found"

-- ============================================================
-- Q2.1 Option B (OR): Write a trigger before deleting company record.
-- Display appropriate message to the user. [10 Marks]
-- ============================================================
CREATE OR REPLACE FUNCTION trg_before_delete_company()
RETURNS TRIGGER AS $$
BEGIN
    RAISE NOTICE 'Company "%" is being deleted from the database', OLD.name;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_company_delete
BEFORE DELETE ON Company
FOR EACH ROW EXECUTE FUNCTION trg_before_delete_company();

-- Execute: DELETE FROM company_person WHERE name = 'Wipro';  -- First remove FK references
-- Execute: DELETE FROM Company WHERE name = 'Wipro';  -- Should display "Company Wipro is being deleted"

-- ============================================================
-- Q2.2: Write a procedure to display division of two numbers
-- use raise to display error messages. [5 Marks]
-- ============================================================
CREATE OR REPLACE PROCEDURE divide_two(p_a NUMERIC, p_b NUMERIC)
LANGUAGE plpgsql AS $$
DECLARE
    v_result NUMERIC;
BEGIN
    IF p_b = 0 THEN
        RAISE EXCEPTION 'Division by zero error: cannot divide % by 0', p_a;
    END IF;
    v_result := p_a / p_b;
    RAISE NOTICE '% / % = %', p_a, p_b, v_result;
END;
$$;

-- Execute: CALL divide_two(100, 5);  -- Should display 100 / 5 = 20
-- Execute: CALL divide_two(50, 0);   -- Should raise "Division by zero error"
