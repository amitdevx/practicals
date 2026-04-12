-- ============================================================
-- Slip 19: Project-Employee Database
-- Section II: Database Management Systems-II [15 Marks]
-- ============================================================

/*
DATABASE SCHEMA: Project-Employee Database

Tables:
  Project (pno integer, pname char(30), ptype char(20), duration integer)
  Employee (eno integer, ename char(20), qualification char(15), joining_date date)
  
Relationship: M-M with descriptive attributes start_date date, 
no_of_hours_worked integer.
  
Constraints: Primary Key, duration should be greater than zero,
pname should not be null.
*/

-- ============================================================
-- Database Setup
-- ============================================================

DROP DATABASE IF EXISTS slip_19_db;
CREATE DATABASE slip_19_db;
\c slip_19_db

-- ============================================================
-- Table Creation
-- ============================================================

DROP TABLE IF EXISTS project_employee CASCADE;
DROP TABLE IF EXISTS PROJECT CASCADE;
DROP TABLE IF EXISTS EMPLOYEE CASCADE;

CREATE TABLE PROJECT (
    pno INT PRIMARY KEY,
    p_name CHAR(30) NOT NULL,
    ptype CHAR(20),
    duration INT CHECK (duration > 0)
);

CREATE TABLE EMPLOYEE (
    eno INT PRIMARY KEY,
    e_name CHAR(20) NOT NULL,
    qualification CHAR(15),
    joindate DATE
);

CREATE TABLE project_employee (
    pno INT REFERENCES PROJECT(pno) ON DELETE CASCADE,
    eno INT REFERENCES EMPLOYEE(eno) ON DELETE CASCADE,
    start_date DATE,
    no_of_hours_worked INT,
    PRIMARY KEY (pno, eno)
);

-- ============================================================
-- Sample Data
-- ============================================================

INSERT INTO PROJECT VALUES (1, 'Alpha', 'Software', 12), (2, 'Beta', 'Hardware', 6), (3, 'Gamma', 'Software', 8);
INSERT INTO EMPLOYEE VALUES (101, 'Amit', 'BE', '2020-01-15'), (102, 'Neha', 'MCA', '2019-06-10'),
    (103, 'Raj', 'BSc', '2021-03-20'), (104, 'Priya', 'ME', '2018-09-01');
INSERT INTO project_employee VALUES
    (1, 101, '2020-02-01', 200), (1, 102, '2020-02-01', 180),
    (2, 103, '2021-04-01', 150), (3, 101, '2021-05-01', 100), (3, 104, '2021-05-01', 220);

-- ============================================================
-- Q2.1 Option A: Write a stored function to accept eno as input parameter and count number of projects on which that employee is working. [10 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION count_employee_projects(p_eno INT)
RETURNS INT AS $$
DECLARE
    v_count INT;
    v_name TEXT;
BEGIN
    SELECT TRIM(e_name) INTO v_name FROM EMPLOYEE WHERE eno = p_eno;
    IF NOT FOUND THEN
        RAISE EXCEPTION 'Employee not found with eno: %', p_eno;
    END IF;

    SELECT COUNT(*) INTO v_count FROM project_employee WHERE eno = p_eno;
    RAISE NOTICE 'Employee: % (Eno: %) is working on % project(s)', v_name, p_eno, v_count;
    RETURN v_count;
END;
$$ LANGUAGE plpgsql;

-- Execute: SELECT count_employee_projects(101);
-- Execute: SELECT count_employee_projects(999);  -- Should raise exception

-- ============================================================
-- Q2.1 Option B (OR): Write a trigger before inserting into a project table to check duration should be always greater than zero. Display appropriate message. [10 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION fn_check_project_duration()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.duration <= 0 THEN
        RAISE EXCEPTION 'Project duration must be greater than 0. Given: %', NEW.duration;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS trg_check_project_duration ON PROJECT;
CREATE TRIGGER trg_check_project_duration
    BEFORE INSERT ON PROJECT
    FOR EACH ROW
    EXECUTE FUNCTION fn_check_project_duration();

-- Execute: INSERT INTO PROJECT VALUES (4, 'Delta', 'Testing', 0);  -- Should fail (duration <= 0)
-- Execute: INSERT INTO PROJECT VALUES (4, 'Delta', 'Testing', 5);  -- Should succeed

-- ============================================================
-- Q2.2: Write a procedure to find minimum and maximum from two numbers. [5 Marks]
-- ============================================================

CREATE OR REPLACE PROCEDURE sp_min_max(p_a NUMERIC, p_b NUMERIC)
LANGUAGE plpgsql AS $$
BEGIN
    IF p_a > p_b THEN
        RAISE NOTICE 'Max = %, Min = %', p_a, p_b;
    ELSIF p_b > p_a THEN
        RAISE NOTICE 'Max = %, Min = %', p_b, p_a;
    ELSE
        RAISE NOTICE 'Both numbers are equal: %', p_a;
    END IF;
END;
$$;

-- Execute: CALL sp_min_max(30, 50);
-- Execute: CALL sp_min_max(10, 10);
