-- ============================================================
-- Slip 12: Project-Employee Database
-- Section II: Database Management Systems-II [15 Marks]
-- ============================================================

/*
DATABASE SCHEMA: Project-Employee Database

Tables:
  1. PROJECT (pno, p_name, ptype, duration)
     - pno: INTEGER, Primary Key
     - p_name: CHAR(30), Project name
     - ptype: CHAR(20), Project type
     - duration: INTEGER, Project duration

  2. EMPLOYEE (eno, e_name, qualification, joindate)
     - eno: INTEGER, Primary Key
     - e_name: CHAR(20), Employee name
     - qualification: CHAR(15), Employee qualification
     - joindate: DATE, Date of joining

  3. project_employee (pno, eno, start_date, no_of_hours_worked)
     - pno: INTEGER, Foreign Key -> PROJECT(pno)
     - eno: INTEGER, Foreign Key -> EMPLOYEE(eno)
     - start_date: DATE, Start date of assignment
     - no_of_hours_worked: INTEGER, Hours worked on project
     - PRIMARY KEY (pno, eno)

Relationship: PROJECT-EMPLOYEE: M-M with descriptive attributes
              start_date (date), no_of_hours_worked (integer)
*/

-- ============================================================
-- Database Setup
-- ============================================================

DROP DATABASE IF EXISTS slip_12_db;
CREATE DATABASE slip_12_db;
\c slip_12_db

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
    duration INT
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
-- Q2.1 Option A: Write a trigger before inserting into a project table to check duration should be always greater than zero. Display appropriate message. [10 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION fn_check_duration()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.duration <= 0 THEN
        RAISE EXCEPTION 'Project duration must be greater than 0. Given: %', NEW.duration;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS trg_check_duration ON PROJECT;
CREATE TRIGGER trg_check_duration
    BEFORE INSERT ON PROJECT
    FOR EACH ROW
    EXECUTE FUNCTION fn_check_duration();

-- Execute: INSERT INTO PROJECT VALUES (4, 'Delta', 'Testing', 0);  -- Should fail (duration <= 0)
-- Execute: INSERT INTO PROJECT VALUES (4, 'Delta', 'Testing', 5);  -- Should succeed

-- ============================================================
-- Q2.1 Option B (OR): Write a stored function to accept project name as input and print the names of employees working on the project. Raise an exception for an invalid project name. [10 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION get_project_employees(p_pname VARCHAR)
RETURNS VOID AS $$
DECLARE
    v_pno INT;
    rec RECORD;
    v_found BOOLEAN := FALSE;
BEGIN
    SELECT pno INTO v_pno FROM PROJECT WHERE TRIM(p_name) = TRIM(p_pname);
    IF NOT FOUND THEN
        RAISE EXCEPTION 'Invalid project name: %', p_pname;
    END IF;

    RAISE NOTICE 'Employees working on project: %', TRIM(p_pname);
    FOR rec IN
        SELECT TRIM(e.e_name) AS ename
        FROM EMPLOYEE e
        JOIN project_employee pe ON e.eno = pe.eno
        WHERE pe.pno = v_pno
    LOOP
        RAISE NOTICE '  %', rec.ename;
        v_found := TRUE;
    END LOOP;

    IF NOT v_found THEN
        RAISE NOTICE 'No employees assigned to this project.';
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Execute: SELECT get_project_employees('Alpha');
-- Execute: SELECT get_project_employees('InvalidProject');  -- Should raise exception

-- ============================================================
-- Q2.2: Write a procedure to count odd numbers from given range (m to n) (for). [5 Marks]
-- ============================================================

CREATE OR REPLACE PROCEDURE sp_count_odd(p_m INT, p_n INT)
LANGUAGE plpgsql AS $$
DECLARE
    v_count INT := 0;
    v_i INT;
BEGIN
    FOR v_i IN p_m..p_n LOOP
        IF v_i % 2 != 0 THEN
            v_count := v_count + 1;
        END IF;
    END LOOP;
    RAISE NOTICE 'Count of odd numbers from % to % = %', p_m, p_n, v_count;
END;
$$;

-- Execute: CALL sp_count_odd(1, 20);
