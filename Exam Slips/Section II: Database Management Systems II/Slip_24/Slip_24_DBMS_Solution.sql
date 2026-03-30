-- ============================================================
-- Slip 24: Department-Employee Database
-- Section II: Database Management Systems-II [15 Marks]
-- ============================================================

/*
DATABASE SCHEMA: Department-Employee Database

Tables:
  Department(dno integer, dname varchar(20), city varchar(20))
  Employee(eno integer, ename varchar(20), salary money)

Relationship:
  Department and Employee are related with a one to many relationship.
  (One department has many employees; dno is FK in Employee table)

Constraints:
  - dno is Primary Key in Department
  - eno is Primary Key in Employee
  - dno in Employee references Department(dno)
*/

-- ============================================================
-- Database Setup
-- ============================================================

DROP DATABASE IF EXISTS slip_24_db;
CREATE DATABASE slip_24_db;
\c slip_24_db

-- ============================================================
-- Table Creation
-- ============================================================

DROP TABLE IF EXISTS Employee CASCADE;
DROP TABLE IF EXISTS Department CASCADE;

CREATE TABLE Department (
    dno INT PRIMARY KEY,
    dname VARCHAR(20),
    city VARCHAR(20)
);

CREATE TABLE Employee (
    eno INT PRIMARY KEY,
    ename VARCHAR(20),
    salary NUMERIC,
    dno INT REFERENCES Department(dno)
);

-- ============================================================
-- Sample Data
-- ============================================================

INSERT INTO Department VALUES (1, 'Computer', 'Pune');
INSERT INTO Department VALUES (2, 'Mechanical', 'Mumbai');
INSERT INTO Department VALUES (3, 'Civil', 'Nagpur');

INSERT INTO Employee VALUES (101, 'Amit', 50000, 1);
INSERT INTO Employee VALUES (102, 'Sneha', 55000, 1);
INSERT INTO Employee VALUES (103, 'Rahul', 45000, 2);
INSERT INTO Employee VALUES (104, 'Priya', 60000, 3);
INSERT INTO Employee VALUES (105, 'Kiran', 48000, 2);

-- ============================================================
-- Q2.1 Option A: Write a function to accept department name as input
-- and display employee name along with salary of that department. [10 Marks]
-- ============================================================
CREATE OR REPLACE FUNCTION get_employees_by_dept(p_dname VARCHAR)
RETURNS TABLE(emp_name VARCHAR, emp_salary NUMERIC) AS $$
BEGIN
    RETURN QUERY
    SELECT e.ename, e.salary
    FROM Employee e JOIN Department d ON e.dno = d.dno
    WHERE d.dname = p_dname;

    IF NOT FOUND THEN
        RAISE NOTICE 'No employees found in department: %', p_dname;
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Execute: SELECT * FROM get_employees_by_dept('Computer');    -- Should return Amit (50000) and Sneha (55000)
-- Execute: SELECT * FROM get_employees_by_dept('Mechanical');  -- Should return Rahul (45000) and Kiran (48000)

-- ============================================================
-- Q2.1 Option B (OR): Write a trigger after insert on an employee record.
-- Display appropriate message when the record is inserted. [10 Marks]
-- ============================================================
CREATE OR REPLACE FUNCTION trg_after_insert_emp()
RETURNS TRIGGER AS $$
BEGIN
    RAISE NOTICE 'Record inserted: Employee % (eno: %)', NEW.ename, NEW.eno;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_emp_insert
AFTER INSERT ON Employee
FOR EACH ROW EXECUTE FUNCTION trg_after_insert_emp();

-- Execute: INSERT INTO Employee VALUES (106, 'TestEmp', 35000, 1);  -- Should display "Record inserted: Employee TestEmp (eno: 106)"

-- ============================================================
-- Q2.2: Write a stored procedure to display first 20 even numbers. [5 Marks]
-- ============================================================
CREATE OR REPLACE PROCEDURE display_20_even()
LANGUAGE plpgsql AS $$
DECLARE
    v_count INT := 0;
    v_num INT := 2;
BEGIN
    WHILE v_count < 20 LOOP
        RAISE NOTICE 'Even number: %', v_num;
        v_num := v_num + 2;
        v_count := v_count + 1;
    END LOOP;
END;
$$;

-- Execute: CALL display_20_even();  -- Should display 2, 4, 6, ... 40
