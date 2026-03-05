-- Slip 02: Person-Area Database
-- Q2.1 OptionA: Function to count persons in area
-- Q2.1 OptionB: Function for sum of income by area_type
-- Q2.2: Procedure division of two numbers with raise for div by zero

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
-- Q2.1 Option A: Function to count persons in area
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

-- Test: SELECT count_persons_in_area('Kothrud');

-- ============================================================
-- Q2.1 Option B: Function for sum of income by area_type
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

-- Test: SELECT sum_income_by_area_type('urban');

-- ============================================================
-- Q2.2: Procedure division of two numbers with raise for div by zero
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

-- Test: CALL divide_two_numbers(10, 3);
-- Test: CALL divide_two_numbers(10, 0);
