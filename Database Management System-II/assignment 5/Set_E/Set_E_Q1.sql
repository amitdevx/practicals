-- ============================================================
-- Assignment 5: Triggers
-- Set E - Question 1
-- ============================================================
-- Q1. Write a trigger before inserting into an employee table
--     to check current date should be always greater than
--     joining date. Display appropriate message.
-- ============================================================

-- ========================
-- Table Creation
-- ========================
DROP TABLE IF EXISTS project_employee CASCADE;
DROP TABLE IF EXISTS employee CASCADE;
DROP TABLE IF EXISTS project CASCADE;

CREATE TABLE project (
    pno      INTEGER PRIMARY KEY,
    pname    CHAR(30) NOT NULL,
    ptype    CHAR(20),
    duration INTEGER
);

CREATE TABLE employee (
    eno           INTEGER PRIMARY KEY,
    ename         CHAR(20),
    qualification CHAR(15),
    joining_date  DATE
);

CREATE TABLE project_employee (
    pno              INTEGER REFERENCES project(pno) ON DELETE CASCADE,
    eno              INTEGER REFERENCES employee(eno) ON DELETE CASCADE,
    start_date       DATE,
    no_of_hours_worked INTEGER,
    PRIMARY KEY (pno, eno)
);

-- ========================
-- Sample Data
-- ========================
INSERT INTO project VALUES (1, 'E-Commerce Platform', 'Web', 12);
INSERT INTO project VALUES (2, 'Mobile Banking App', 'Mobile', 8);

-- ========================
-- Trigger Function & Trigger
-- ========================
DROP TRIGGER IF EXISTS trg_emp_joining_date ON employee;
DROP FUNCTION IF EXISTS fn_emp_joining_date();

CREATE OR REPLACE FUNCTION fn_emp_joining_date()
RETURNS TRIGGER AS $$
BEGIN
    IF CURRENT_DATE <= NEW.joining_date THEN
        RAISE EXCEPTION 'Insertion denied: Joining date (%) for employee "%" must be before the current date (%).', NEW.joining_date, TRIM(NEW.ename), CURRENT_DATE;
    END IF;
    RAISE NOTICE 'Employee "%" inserted successfully with joining date %.', TRIM(NEW.ename), NEW.joining_date;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_emp_joining_date
    BEFORE INSERT ON employee
    FOR EACH ROW
    EXECUTE FUNCTION fn_emp_joining_date();

-- ========================
-- Test DML
-- ========================
-- Test 1: Valid insert (joining_date in the past) — should SUCCEED
INSERT INTO employee VALUES (101, 'Amit Sharma', 'B.Tech', '2023-06-15');

-- Test 2: Another valid insert — should SUCCEED
INSERT INTO employee VALUES (102, 'Sneha Patil', 'M.Tech', '2024-01-10');

-- Verify
SELECT * FROM employee;

-- Test 3: Invalid insert (joining_date in future) — should FAIL
-- Uncomment to test:
-- INSERT INTO employee VALUES (103, 'Future Guy', 'PhD', '2030-12-31');
