-- ============================================================
-- Assignment 5: Triggers
-- Set E - Question 2
-- ============================================================
-- Q2. Write a trigger before inserting into a project table to
--     check duration should be always greater than zero. Display
--     appropriate message.
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
INSERT INTO employee VALUES (101, 'Amit Sharma', 'B.Tech', '2023-06-15');
INSERT INTO employee VALUES (102, 'Sneha Patil', 'M.Tech', '2024-01-10');

-- ========================
-- Trigger Function & Trigger
-- ========================
DROP TRIGGER IF EXISTS trg_project_duration ON project;
DROP FUNCTION IF EXISTS fn_project_duration();

CREATE OR REPLACE FUNCTION fn_project_duration()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.duration <= 0 THEN
        RAISE EXCEPTION 'Insertion denied: Duration (%) for project "%" must be greater than zero.', NEW.duration, TRIM(NEW.pname);
    END IF;
    RAISE NOTICE 'Project "%" inserted successfully with duration % months.', TRIM(NEW.pname), NEW.duration;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_project_duration
    BEFORE INSERT ON project
    FOR EACH ROW
    EXECUTE FUNCTION fn_project_duration();

-- ========================
-- Test DML
-- ========================
-- Test 1: Valid insert (duration > 0) — should SUCCEED
INSERT INTO project VALUES (1, 'E-Commerce Platform', 'Web', 12);

-- Test 2: Another valid insert — should SUCCEED
INSERT INTO project VALUES (2, 'Mobile Banking App', 'Mobile', 8);

-- Verify
SELECT * FROM project;

-- Test 3: Invalid insert (duration = 0) — should FAIL
-- Uncomment to test:
-- INSERT INTO project VALUES (3, 'Zero Duration', 'Test', 0);

-- Test 4: Invalid insert (negative duration) — should FAIL
-- Uncomment to test:
-- INSERT INTO project VALUES (4, 'Negative Project', 'Test', -5);
