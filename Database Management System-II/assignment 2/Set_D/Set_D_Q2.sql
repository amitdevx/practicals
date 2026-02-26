-- ============================================================
-- Assignment 2: Stored Functions
-- Set D - Question 2
-- Function to accept employee name and print details of
-- the project which the employee works on
-- ============================================================

-- Q2. Write a function which accepts employee name and prints
--     the details of the project which the employee works on.

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
CREATE OR REPLACE FUNCTION get_projects_by_employee(emp_name TEXT)
RETURNS VOID AS $$
DECLARE
    rec RECORD;
    found BOOLEAN := FALSE;
BEGIN
    FOR rec IN
        SELECT p.pno, TRIM(p.pname) AS pname, TRIM(p.ptype) AS ptype,
               p.duration, pe.start_date
        FROM project p
        JOIN project_employee pe ON p.pno = pe.pno
        JOIN employee e ON pe.empno = e.empno
        WHERE TRIM(e.ename) = TRIM(emp_name)
    LOOP
        RAISE NOTICE 'Project No: %, Name: %, Type: %, Duration: % months, Start Date: %',
            rec.pno, rec.pname, rec.ptype, rec.duration, rec.start_date;
        found := TRUE;
    END LOOP;

    IF NOT found THEN
        RAISE NOTICE 'No projects found for employee: %', emp_name;
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Test
SELECT get_projects_by_employee('Amit Sharma');
SELECT get_projects_by_employee('Priya Desai');
SELECT get_projects_by_employee('Rahul Patil');
SELECT get_projects_by_employee('Unknown');
