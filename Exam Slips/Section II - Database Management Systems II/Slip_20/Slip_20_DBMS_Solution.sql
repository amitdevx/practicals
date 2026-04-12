-- ============================================================
-- Slip 20: Department-Employee Database
-- Section II: Database Management Systems-II [15 Marks]
-- ============================================================

/*
DATABASE SCHEMA: Department-Employee Database

Tables:
  Department (dno integer, dname varchar(20), city varchar(20))
  Employee (eno integer, ename varchar(20), salary money)
  
Relationship: Department and Employee are related with a one to many
relationship.
*/

-- ============================================================
-- Database Setup
-- ============================================================

DROP DATABASE IF EXISTS slip_20_db;
CREATE DATABASE slip_20_db;
\c slip_20_db

-- ============================================================
-- Table Creation
-- ============================================================

DROP TABLE IF EXISTS Employee CASCADE;
DROP TABLE IF EXISTS Department CASCADE;

CREATE TABLE Department (
    dno INT PRIMARY KEY,
    dname VARCHAR(20) NOT NULL,
    city VARCHAR(20)
);

CREATE TABLE Employee (
    eno INT PRIMARY KEY,
    ename VARCHAR(20) NOT NULL,
    salary NUMERIC,
    dno INT REFERENCES Department(dno) ON DELETE SET NULL
);

-- ============================================================
-- Sample Data
-- ============================================================

INSERT INTO Department VALUES (1, 'IT', 'Pune'), (2, 'HR', 'Mumbai'), (3, 'Finance', 'Delhi');
INSERT INTO Employee VALUES
    (101, 'Amit', 55000, 1), (102, 'Neha', 62000, 1), (103, 'Raj', 48000, 2),
    (104, 'Priya', 70000, 3), (105, 'Suresh', 45000, 2), (106, 'Kavita', 58000, 3);

-- ============================================================
-- Q2.1 Option A: Write a function to accept department name and display the maximum salary of an employee in that department. [10 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION get_max_salary(p_dname VARCHAR)
RETURNS NUMERIC AS $$
DECLARE
    v_dno INT;
    v_max NUMERIC;
    v_ename VARCHAR;
BEGIN
    SELECT dno INTO v_dno FROM Department WHERE dname = p_dname;
    IF NOT FOUND THEN
        RAISE EXCEPTION 'Department not found: %', p_dname;
    END IF;

    SELECT ename, salary INTO v_ename, v_max
    FROM Employee
    WHERE dno = v_dno
    ORDER BY salary DESC
    LIMIT 1;

    IF v_max IS NULL THEN
        RAISE NOTICE 'No employees in department %', p_dname;
        RETURN 0;
    END IF;

    RAISE NOTICE 'Department: %, Max Salary: % (Employee: %)', p_dname, v_max, v_ename;
    RETURN v_max;
END;
$$ LANGUAGE plpgsql;

-- Execute: SELECT get_max_salary('IT');
-- Execute: SELECT get_max_salary('Unknown');  -- Should raise exception

-- ============================================================
-- Q2.1 Option B (OR): Write a trigger before insert/update on an employee record. Raise exception if salary < 0. [10 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION fn_check_salary()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.salary < 0 THEN
        RAISE EXCEPTION 'Salary cannot be negative. Given: %', NEW.salary;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS trg_check_salary ON Employee;
CREATE TRIGGER trg_check_salary
    BEFORE INSERT OR UPDATE ON Employee
    FOR EACH ROW
    EXECUTE FUNCTION fn_check_salary();

-- Execute: INSERT INTO Employee VALUES (107, 'Test', -5000, 1);  -- Should fail (salary < 0)
-- Execute: INSERT INTO Employee VALUES (107, 'Mohan', 55000, 1);  -- Should succeed

-- ============================================================
-- Q2.2: Write a procedure to display multiplication of two numbers. [5 Marks]
-- ============================================================

CREATE OR REPLACE PROCEDURE sp_multiply(p_a NUMERIC, p_b NUMERIC)
LANGUAGE plpgsql AS $$
DECLARE
    v_result NUMERIC;
BEGIN
    v_result := p_a * p_b;
    RAISE NOTICE '% x % = %', p_a, p_b, v_result;
END;
$$;

-- Execute: CALL sp_multiply(7, 8);
