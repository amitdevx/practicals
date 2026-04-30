-- ============================================================
-- Assignment 5: Triggers
-- Set E - Question 3
-- ============================================================
-- Q3. Write a trigger before deleting an employee record from
--     the employee table. Raise a notice and display the message
--     "Employee record is being deleted".
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

INSERT INTO employee VALUES (101, 'Amit Sharma', 'B.Tech', '2023-06-15');
INSERT INTO employee VALUES (102, 'Sneha Patil', 'M.Tech', '2024-01-10');
INSERT INTO employee VALUES (103, 'Rahul Desai', 'B.Sc', '2023-09-01');

INSERT INTO project_employee VALUES (1, 101, '2023-07-01', 200);
INSERT INTO project_employee VALUES (1, 102, '2024-02-01', 150);
INSERT INTO project_employee VALUES (2, 103, '2023-10-01', 180);

-- ========================
-- Trigger Function & Trigger
-- ========================
DROP TRIGGER IF EXISTS trg_emp_delete_notice ON employee;
DROP FUNCTION IF EXISTS fn_emp_delete_notice();

CREATE OR REPLACE FUNCTION fn_emp_delete_notice()
RETURNS TRIGGER AS $$
BEGIN
    RAISE NOTICE 'Employee record is being deleted. Eno: %, Name: %', OLD.eno, TRIM(OLD.ename);
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_emp_delete_notice
    BEFORE DELETE ON employee
    FOR EACH ROW
    EXECUTE FUNCTION fn_emp_delete_notice();

-- ========================
-- Test DML
-- ========================
-- This DELETE will fire the trigger and display the notice
DELETE FROM employee WHERE eno = 103;

-- Delete another employee
DELETE FROM employee WHERE eno = 101;

-- Verify
SELECT * FROM employee;
SELECT * FROM project_employee;
