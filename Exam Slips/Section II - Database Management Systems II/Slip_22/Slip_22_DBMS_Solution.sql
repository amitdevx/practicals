-- ============================================================
-- Slip 22: Project-Employee Database
-- Section II: Database Management Systems-II [15 Marks]
-- ============================================================

/*
DATABASE SCHEMA: Project-Employee Database

Tables:
  Project(pno integer, pname char(30), ptype char(20), duration integer)
  Employee(eno integer, ename char(20), qualification char(15), joining_date date)

Relationship:
  Project and Employee are related with Many-to-Many relationship.
  Descriptive attributes: start_date date, no_of_hours_worked integer

Constraints:
  - pno is Primary Key in Project
  - eno is Primary Key in Employee
  - duration should be greater than zero
  - pname should not be null
*/

-- ============================================================
-- Database Setup
-- ============================================================

DROP DATABASE IF EXISTS slip_22_db;
CREATE DATABASE slip_22_db;
\c slip_22_db

-- ============================================================
-- Table Creation
-- ============================================================

DROP TABLE IF EXISTS project_employee CASCADE;
DROP TABLE IF EXISTS Project CASCADE;
DROP TABLE IF EXISTS Employee CASCADE;

CREATE TABLE Project (
    pno INT PRIMARY KEY,
    pname CHAR(30) NOT NULL,
    ptype CHAR(20),
    duration INT CHECK (duration > 0)
);

CREATE TABLE Employee (
    eno INT PRIMARY KEY,
    ename CHAR(20),
    qualification CHAR(15),
    joining_date DATE
);

CREATE TABLE project_employee (
    pno INT REFERENCES Project(pno),
    eno INT REFERENCES Employee(eno),
    start_date DATE,
    no_of_hours_worked INT,
    PRIMARY KEY (pno, eno)
);

-- ============================================================
-- Sample Data
-- ============================================================

INSERT INTO Project VALUES (1, 'ERP System', 'Software', 12);
INSERT INTO Project VALUES (2, 'Bridge Design', 'Construction', 24);
INSERT INTO Project VALUES (3, 'Mobile App', 'Software', 6);

INSERT INTO Employee VALUES (101, 'Amit', 'BE', '2022-01-15');
INSERT INTO Employee VALUES (102, 'Sneha', 'MCA', '2021-06-10');
INSERT INTO Employee VALUES (103, 'Rahul', 'ME', '2023-03-20');

INSERT INTO project_employee VALUES (1, 101, '2022-02-01', 200);
INSERT INTO project_employee VALUES (2, 101, '2022-05-01', 150);
INSERT INTO project_employee VALUES (3, 101, '2023-01-01', 100);
INSERT INTO project_employee VALUES (1, 102, '2022-02-01', 180);
INSERT INTO project_employee VALUES (3, 103, '2023-04-01', 90);

-- ============================================================
-- Q2.1 Option A: Write a stored function to accept eno as input parameter
-- and count number of projects on which that employee is working. [10 Marks]
-- ============================================================
CREATE OR REPLACE FUNCTION count_projects(p_eno INT)
RETURNS INT AS $$
DECLARE
    v_count INT;
BEGIN
    SELECT COUNT(*) INTO v_count
    FROM project_employee WHERE eno = p_eno;

    RAISE NOTICE 'Employee % is working on % project(s)', p_eno, v_count;
    RETURN v_count;
END;
$$ LANGUAGE plpgsql;

-- Execute: SELECT count_projects(101);  -- Should return 3 (Amit works on 3 projects)
-- Execute: SELECT count_projects(103);  -- Should return 1 (Rahul works on 1 project)

-- ============================================================
-- Q2.1 Option B (OR): Write a trigger before inserting into a project table
-- to check duration should be always greater than zero. Display appropriate message. [10 Marks]
-- ============================================================
CREATE OR REPLACE FUNCTION trg_check_duration()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.duration <= 0 THEN
        RAISE EXCEPTION 'Project duration must be greater than 0. Given: %', NEW.duration;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_project_duration
BEFORE INSERT ON Project
FOR EACH ROW EXECUTE FUNCTION trg_check_duration();

-- Execute: INSERT INTO Project VALUES (10, 'Test Project', 'Testing', 0);   -- Should fail (duration = 0)
-- Execute: INSERT INTO Project VALUES (10, 'Test Project', 'Testing', -5);  -- Should fail (negative duration)
-- Execute: INSERT INTO Project VALUES (10, 'Test Project', 'Testing', 6);   -- Should succeed

-- ============================================================
-- Q2.2: Write a procedure to search the given number is in given range. [5 Marks]
-- ============================================================
CREATE OR REPLACE PROCEDURE check_in_range(p_num INT, p_low INT, p_high INT)
LANGUAGE plpgsql AS $$
BEGIN
    IF p_num >= p_low AND p_num <= p_high THEN
        RAISE NOTICE '% is in the range [%, %]', p_num, p_low, p_high;
    ELSE
        RAISE NOTICE '% is NOT in the range [%, %]', p_num, p_low, p_high;
    END IF;
END;
$$;

-- Execute: CALL check_in_range(15, 10, 20);  -- Should display "15 is in the range"
-- Execute: CALL check_in_range(25, 10, 20);  -- Should display "25 is NOT in the range"
