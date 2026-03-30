-- ============================================================
-- Slip 02: Person-Area Database
-- Section II: Database Management Systems-II [15 Marks]
-- ============================================================

/*
Consider the following Entities and their Relationships for Person-Area database.

Person (pno integer, pname varchar(20), birthdate date, income money)
Area (aname varchar(20), area_type varchar(5))

The Relationship between Person and Area is Many-to-One (M-1). An area can have one or more
persons living in it, but a person belongs to exactly one area.

Constraints: Primary Key, area_type can be either 'urban' or 'rural'.
*/

-- ============================================================
-- Database Setup
-- ============================================================

DROP DATABASE IF EXISTS slip_02_db;
CREATE DATABASE slip_02_db;
\c slip_02_db

-- ============================================================
-- Table Creation
-- ============================================================

DROP TABLE IF EXISTS Person CASCADE;
DROP TABLE IF EXISTS Area CASCADE;

CREATE TABLE Area (
    aname     VARCHAR(20) PRIMARY KEY,
    area_type VARCHAR(5) CHECK (area_type IN ('urban', 'rural'))
);

CREATE TABLE Person (
    pno       INT PRIMARY KEY,
    pname     VARCHAR(20),
    birthdate DATE,
    income    NUMERIC,
    aname     VARCHAR(20) REFERENCES Area(aname)
);

-- ============================================================
-- Sample Data
-- ============================================================

INSERT INTO Area VALUES ('Kothrud', 'urban');
INSERT INTO Area VALUES ('Hadapsar', 'urban');
INSERT INTO Area VALUES ('Velhe', 'rural');
INSERT INTO Area VALUES ('Mulshi', 'rural');

INSERT INTO Person VALUES (1, 'Amit', '1995-05-10', 50000, 'Kothrud');
INSERT INTO Person VALUES (2, 'Neha', '1998-08-22', 35000, 'Hadapsar');
INSERT INTO Person VALUES (3, 'Rahul', '1990-01-15', 20000, 'Velhe');
INSERT INTO Person VALUES (4, 'Priya', '1992-12-03', 45000, 'Kothrud');
INSERT INTO Person VALUES (5, 'Suresh', '1988-07-19', 15000, 'Mulshi');

-- ============================================================
-- Q2.1 Option A: Write a stored function to print total number
-- of persons of a particular area. Accept area name as input
-- parameter. [10 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION count_persons_in_area(p_aname VARCHAR)
RETURNS INT AS $$
DECLARE
    v_count INT;
BEGIN
    SELECT COUNT(*) INTO v_count
    FROM Person
    WHERE aname = p_aname;

    IF v_count = 0 THEN
        RAISE NOTICE 'No persons found in area: %', p_aname;
    ELSE
        RAISE NOTICE 'Number of persons in %: %', p_aname, v_count;
    END IF;

    RETURN v_count;
END;
$$ LANGUAGE plpgsql;

-- Execute: SELECT count_persons_in_area('Kothrud');  -- 2 persons
-- Execute: SELECT count_persons_in_area('Velhe');    -- 1 person
-- Execute: SELECT count_persons_in_area('Baramati'); -- No persons (doesn't exist)

-- ============================================================
-- Q2.1 Option B (OR): Write a stored function to print sum of
-- income of person living in area type. Accept area type as
-- input parameter. Display appropriate message for invalid
-- area type. [10 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION sum_income_by_area_type(p_area_type VARCHAR)
RETURNS NUMERIC AS $$
DECLARE
    v_total NUMERIC;
BEGIN
    SELECT COALESCE(SUM(p.income), 0) INTO v_total
    FROM Person p
    JOIN Area a ON p.aname = a.aname
    WHERE a.area_type = p_area_type;

    RAISE NOTICE 'Total income for % areas: %', p_area_type, v_total;
    RETURN v_total;
END;
$$ LANGUAGE plpgsql;

-- Execute: SELECT sum_income_by_area_type('urban');  -- 130000 (Amit + Neha + Priya)
-- Execute: SELECT sum_income_by_area_type('rural');  -- 35000 (Rahul + Suresh)
-- Execute: SELECT sum_income_by_area_type('invalid'); -- 0 (invalid type)

-- ============================================================
-- Q2.2: Write a procedure to display division of two numbers.
-- Use raise to display error messages for division by zero
-- error. [5 Marks]
-- ============================================================

CREATE OR REPLACE PROCEDURE divide_two_numbers(a NUMERIC, b NUMERIC)
AS $$
DECLARE
    v_result NUMERIC;
BEGIN
    IF b = 0 THEN
        RAISE EXCEPTION 'Division by zero error: Cannot divide % by 0.', a;
    END IF;

    v_result := a / b;
    RAISE NOTICE '% / % = %', a, b, v_result;
END;
$$ LANGUAGE plpgsql;

-- Execute: CALL divide_two_numbers(10, 2);  -- Result: 5
-- Execute: CALL divide_two_numbers(10, 0);  -- Should raise exception

