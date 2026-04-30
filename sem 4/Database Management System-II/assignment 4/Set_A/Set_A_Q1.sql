-- ============================================================
-- Assignment 4: Handling Errors and Exceptions
-- Set A - Question 1
-- ============================================================
-- Q1. Write a function to accept the project name and display
--     the names of employees working on the project along with
--     the total count of employees. Raise an exception for an
--     invalid project name.
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

CREATE OR REPLACE FUNCTION get_employees_by_project(p_name VARCHAR)
RETURNS VOID AS $$
DECLARE
    v_pno       INT;
    v_count     INT := 0;
    rec         RECORD;
BEGIN
    -- Check if the project exists
    SELECT pno INTO v_pno
    FROM Project
    WHERE TRIM(pname) = TRIM(p_name);

    IF NOT FOUND THEN
        RAISE EXCEPTION 'Invalid project name: "%" does not exist.', p_name;
    END IF;

    RAISE NOTICE '--- Employees working on project: % ---', TRIM(p_name);

    FOR rec IN
        SELECT TRIM(e.ename) AS ename
        FROM Employee e
        JOIN project_employee pe ON e.empno = pe.empno
        WHERE pe.pno = v_pno
    LOOP
        v_count := v_count + 1;
        RAISE NOTICE '%', rec.ename;
    END LOOP;

    RAISE NOTICE '--- Total employees: % ---', v_count;

EXCEPTION
    WHEN OTHERS THEN
        RAISE NOTICE 'Error: %', SQLERRM;
END;
$$ LANGUAGE plpgsql;

-- ==================== Test Calls ====================

-- Valid project name
SELECT get_employees_by_project('Alpha');

-- Valid project name (different)
SELECT get_employees_by_project('Gamma');

-- Invalid project name (should raise exception)
SELECT get_employees_by_project('Omega');
