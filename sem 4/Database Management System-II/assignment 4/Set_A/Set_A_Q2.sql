-- ============================================================
-- Assignment 4: Handling Errors and Exceptions
-- Set A - Question 2
-- ============================================================
-- Q2. Write a function to accept the employee number and count
--     the number of projects that employee is working on.
--     Raise an exception if the employee number is invalid.
-- ============================================================

-- ==================== Table Creation ====================

DROP TABLE IF EXISTS project_employee CASCADE;
DROP TABLE IF EXISTS Employee CASCADE;
DROP TABLE IF EXISTS Project CASCADE;

CREATE TABLE Project (
    pno       INT PRIMARY KEY,
    pname     CHAR(30) NOT NULL,
    ptype     CHAR(20),
    duration  INT
);

CREATE TABLE Employee (
    empno         INT PRIMARY KEY,
    ename         CHAR(20) NOT NULL,
    joining_date  DATE
);

CREATE TABLE project_employee (
    pno         INT REFERENCES Project(pno),
    empno       INT REFERENCES Employee(empno),
    start_date  DATE,
    PRIMARY KEY (pno, empno)
);

-- ==================== Sample Data ====================

INSERT INTO Project VALUES (101, 'Alpha',   'Development', 12);
INSERT INTO Project VALUES (102, 'Beta',    'Testing',     6);
INSERT INTO Project VALUES (103, 'Gamma',   'Research',    18);
INSERT INTO Project VALUES (104, 'Delta',   'Development', 9);
INSERT INTO Project VALUES (105, 'Epsilon', 'Maintenance', 24);

INSERT INTO Employee VALUES (1, 'Amit',   '2022-01-15');
INSERT INTO Employee VALUES (2, 'Priya',  '2021-06-10');
INSERT INTO Employee VALUES (3, 'Rahul',  '2023-03-20');
INSERT INTO Employee VALUES (4, 'Sneha',  '2020-11-05');
INSERT INTO Employee VALUES (5, 'Vikram', '2022-08-25');
INSERT INTO Employee VALUES (6, 'Neha',   '2021-12-01');

INSERT INTO project_employee VALUES (101, 1, '2022-02-01');
INSERT INTO project_employee VALUES (101, 2, '2022-02-01');
INSERT INTO project_employee VALUES (101, 3, '2023-04-01');
INSERT INTO project_employee VALUES (102, 2, '2021-07-01');
INSERT INTO project_employee VALUES (102, 4, '2021-07-01');
INSERT INTO project_employee VALUES (103, 5, '2022-09-01');
INSERT INTO project_employee VALUES (103, 6, '2022-09-01');
INSERT INTO project_employee VALUES (103, 1, '2022-09-01');
INSERT INTO project_employee VALUES (104, 3, '2023-05-01');

-- ==================== Function ====================

CREATE OR REPLACE FUNCTION count_projects_by_employee(p_empno INT)
RETURNS VOID AS $$
DECLARE
    v_ename     VARCHAR;
    v_count     INT;
BEGIN
    -- Check if the employee exists
    SELECT TRIM(ename) INTO v_ename
    FROM Employee
    WHERE empno = p_empno;

    IF NOT FOUND THEN
        RAISE EXCEPTION 'Invalid employee number: % does not exist.', p_empno;
    END IF;

    -- Count projects for this employee
    SELECT COUNT(*) INTO v_count
    FROM project_employee
    WHERE empno = p_empno;

    RAISE NOTICE 'Employee: % (Empno: %)', v_ename, p_empno;
    RAISE NOTICE 'Number of projects: %', v_count;

EXCEPTION
    WHEN OTHERS THEN
        RAISE NOTICE 'Error: %', SQLERRM;
END;
$$ LANGUAGE plpgsql;

-- ==================== Test Calls ====================

-- Valid employee with multiple projects
SELECT count_projects_by_employee(1);

-- Valid employee with projects
SELECT count_projects_by_employee(2);

-- Valid employee with one project
SELECT count_projects_by_employee(6);

-- Invalid employee number (should raise exception)
SELECT count_projects_by_employee(99);
