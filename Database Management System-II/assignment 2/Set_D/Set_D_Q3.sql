-- ============================================================
-- Assignment 2: Stored Functions
-- Set D - Question 3
-- Function to accept project name and return the number of
-- employees working on the project
-- ============================================================

-- Q3. Write a function to accept project name as input and
--     returns the number of employees working on the project.

-- Project-Employee Database Schema:
--   Project (pno, pname, ptype, duration)
--   Employee (empno, ename, joining_date)
--   project_employee (pno, empno, start_date) — Many-to-Many
--     with descriptive attribute start_date

-- Drop existing tables
DROP TABLE IF EXISTS project_employee CASCADE;
DROP TABLE IF EXISTS project CASCADE;
DROP TABLE IF EXISTS employee CASCADE;

-- Create tables
CREATE TABLE project (
    pno INTEGER PRIMARY KEY,
    pname CHAR(30),
    ptype CHAR(20),
    duration INTEGER
);

CREATE TABLE employee (
    empno INTEGER PRIMARY KEY,
    ename CHAR(20),
    joining_date DATE
);

CREATE TABLE project_employee (
    pno INTEGER REFERENCES project(pno),
    empno INTEGER REFERENCES employee(empno),
    start_date DATE,
    PRIMARY KEY (pno, empno)
);

-- Insert sample data — Projects
INSERT INTO project VALUES (1, 'E-Commerce Portal', 'Web', 12);
INSERT INTO project VALUES (2, 'Inventory System', 'Desktop', 8);
INSERT INTO project VALUES (3, 'Banking App', 'Web', 18);
INSERT INTO project VALUES (4, 'HR Management', 'Desktop', 10);
INSERT INTO project VALUES (5, 'Chat Application', 'Mobile', 6);
INSERT INTO project VALUES (6, 'Weather Tracker', 'Mobile', 4);

-- Insert sample data — Employees
INSERT INTO employee VALUES (101, 'Amit Sharma', '2022-01-15');
INSERT INTO employee VALUES (102, 'Priya Desai', '2021-06-20');
INSERT INTO employee VALUES (103, 'Rahul Patil', '2023-03-10');
INSERT INTO employee VALUES (104, 'Sneha Kulkarni', '2020-09-05');
INSERT INTO employee VALUES (105, 'Vikas Joshi', '2022-11-12');

-- Insert sample data — Project-Employee
INSERT INTO project_employee VALUES (1, 101, '2023-01-01');
INSERT INTO project_employee VALUES (1, 102, '2023-01-15');
INSERT INTO project_employee VALUES (2, 103, '2023-04-01');
INSERT INTO project_employee VALUES (3, 104, '2023-02-10');
INSERT INTO project_employee VALUES (3, 101, '2023-03-01');
INSERT INTO project_employee VALUES (4, 105, '2023-05-20');
INSERT INTO project_employee VALUES (5, 102, '2023-06-01');
INSERT INTO project_employee VALUES (6, 103, '2023-07-15');

-- Function
CREATE OR REPLACE FUNCTION count_employees_on_project(p_name TEXT)
RETURNS INTEGER AS $$
DECLARE
    cnt INTEGER;
BEGIN
    SELECT COUNT(*) INTO cnt
    FROM project_employee pe
    JOIN project p ON pe.pno = p.pno
    WHERE TRIM(p.pname) = TRIM(p_name);

    IF cnt = 0 THEN
        RAISE NOTICE 'No employees found for project: %', p_name;
    ELSE
        RAISE NOTICE 'Number of employees on project "%": %', p_name, cnt;
    END IF;

    RETURN cnt;
END;
$$ LANGUAGE plpgsql;

-- Test
SELECT count_employees_on_project('E-Commerce Portal');
SELECT count_employees_on_project('Banking App');
SELECT count_employees_on_project('HR Management');
SELECT count_employees_on_project('Unknown Project');
