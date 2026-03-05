-- Slip 01: Project-Employee Database
-- Q2.1 OptionA: Function to accept eno, count projects
-- Q2.1 OptionB: Trigger before insert on project checking duration > 0
-- Q2.2: Procedure for add, sub, mul of 3 numbers

-- ============================================================
-- Table Creation
-- ============================================================

DROP TABLE IF EXISTS project_employee CASCADE;
DROP TABLE IF EXISTS Employee CASCADE;
DROP TABLE IF EXISTS Project CASCADE;

CREATE TABLE Project (
    pno      INT PRIMARY KEY,
    pname    CHAR(30) NOT NULL,
    ptype    CHAR(20),
    duration INT CHECK (duration > 0)
);

CREATE TABLE Employee (
    eno           INT PRIMARY KEY,
    ename         CHAR(20),
    qualification CHAR(15),
    joining_date  DATE
);

CREATE TABLE project_employee (
    pno              INT REFERENCES Project(pno),
    eno              INT REFERENCES Employee(eno),
    start_date       DATE,
    no_of_hours_worked INT,
    PRIMARY KEY (pno, eno)
);

-- ============================================================
-- Sample Data
-- ============================================================

INSERT INTO Project VALUES (1, 'Alpha', 'Development', 12);
INSERT INTO Project VALUES (2, 'Beta', 'Testing', 6);
INSERT INTO Project VALUES (3, 'Gamma', 'Research', 18);

INSERT INTO Employee VALUES (101, 'Amit', 'MCA', '2020-06-15');
INSERT INTO Employee VALUES (102, 'Neha', 'BE', '2019-03-10');
INSERT INTO Employee VALUES (103, 'Rahul', 'MSc', '2021-01-20');

INSERT INTO project_employee VALUES (1, 101, '2020-07-01', 200);
INSERT INTO project_employee VALUES (2, 101, '2021-01-15', 150);
INSERT INTO project_employee VALUES (3, 102, '2019-04-01', 300);
INSERT INTO project_employee VALUES (1, 103, '2021-02-01', 100);

-- ============================================================
-- Q2.1 Option A: Function to accept eno, count projects
-- ============================================================

CREATE OR REPLACE FUNCTION count_projects(p_eno INT)
RETURNS INT AS $$
DECLARE
    v_count INT;
BEGIN
    SELECT COUNT(*) INTO v_count
    FROM project_employee
    WHERE eno = p_eno;

    IF v_count = 0 THEN
        RAISE NOTICE 'Employee % is not assigned to any project.', p_eno;
    ELSE
        RAISE NOTICE 'Employee % is working on % project(s).', p_eno, v_count;
    END IF;

    RETURN v_count;
END;
$$ LANGUAGE plpgsql;

-- Test: SELECT count_projects(101);

-- ============================================================
-- Q2.1 Option B: Trigger before insert on project checking duration > 0
-- ============================================================

CREATE OR REPLACE FUNCTION check_project_duration()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.duration <= 0 THEN
        RAISE EXCEPTION 'Duration must be greater than 0. Got: %', NEW.duration;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_check_duration
BEFORE INSERT ON Project
FOR EACH ROW
EXECUTE FUNCTION check_project_duration();

-- Test: INSERT INTO Project VALUES (99, 'Bad', 'Test', -1);

-- ============================================================
-- Q2.2: Procedure for add, sub, mul of 3 numbers
-- ============================================================

CREATE OR REPLACE PROCEDURE arithmetic_operations(a NUMERIC, b NUMERIC, c NUMERIC)
AS $$
DECLARE
    v_add NUMERIC;
    v_sub NUMERIC;
    v_mul NUMERIC;
BEGIN
    v_add := a + b + c;
    v_sub := a - b - c;
    v_mul := a * b * c;

    RAISE NOTICE 'Addition:       % + % + % = %', a, b, c, v_add;
    RAISE NOTICE 'Subtraction:    % - % - % = %', a, b, c, v_sub;
    RAISE NOTICE 'Multiplication: % * % * % = %', a, b, c, v_mul;
END;
$$ LANGUAGE plpgsql;

-- Test: CALL arithmetic_operations(10, 5, 3);
