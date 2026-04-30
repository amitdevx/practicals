-- ============================================================
-- Slip 14: Project-Employee Database
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

DROP DATABASE IF EXISTS slip_14_db;
CREATE DATABASE slip_14_db;
\c slip_14_db

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

-- Execute: INSERT INTO PROJECT VALUES (4, 'Delta', 'Testing', -1);  -- Should fail (duration <= 0)
-- Execute: INSERT INTO PROJECT VALUES (4, 'Delta', 'Testing', 10);  -- Should succeed

-- ============================================================
-- Q2.1 Option B (OR): Write a stored function to accept project name as input and print the names of employees working on the project. Raise an exception for an invalid project name. [10 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION get_employees_by_project(p_pname VARCHAR)
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
        SELECT TRIM(e.e_name) AS ename, TRIM(e.qualification) AS qual
        FROM EMPLOYEE e
        JOIN project_employee pe ON e.eno = pe.eno
        WHERE pe.pno = v_pno
    LOOP
        RAISE NOTICE '  Name: %, Qualification: %', rec.ename, rec.qual;
        v_found := TRUE;
    END LOOP;

    IF NOT v_found THEN
        RAISE NOTICE 'No employees assigned to this project.';
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Execute: SELECT get_employees_by_project('Alpha');
-- Execute: SELECT get_employees_by_project('Unknown');  -- Should raise exception

-- ============================================================
-- Q2.2: Write a procedure to display a number in word (Using Case) and loop. [5 Marks]
-- ============================================================

CREATE OR REPLACE PROCEDURE sp_number_in_words(p_num INT)
LANGUAGE plpgsql AS $$
DECLARE
    v_str TEXT := '';
    v_n INT;
    v_digit INT;
    v_word TEXT;
BEGIN
    IF p_num < 0 THEN
        v_str := 'Negative ';
        v_n := ABS(p_num);
    ELSIF p_num = 0 THEN
        RAISE NOTICE 'Zero';
        RETURN;
    ELSE
        v_n := p_num;
    END IF;

    DECLARE
        v_temp TEXT := '';
        v_num_str TEXT := v_n::TEXT;
        v_i INT;
    BEGIN
        FOR v_i IN 1..LENGTH(v_num_str) LOOP
            v_digit := SUBSTRING(v_num_str FROM v_i FOR 1)::INT;
            v_word := CASE v_digit
                WHEN 0 THEN 'Zero'
                WHEN 1 THEN 'One'
                WHEN 2 THEN 'Two'
                WHEN 3 THEN 'Three'
                WHEN 4 THEN 'Four'
                WHEN 5 THEN 'Five'
                WHEN 6 THEN 'Six'
                WHEN 7 THEN 'Seven'
                WHEN 8 THEN 'Eight'
                WHEN 9 THEN 'Nine'
            END;
            v_temp := v_temp || v_word || ' ';
        END LOOP;
        v_str := v_str || TRIM(v_temp);
    END;

    RAISE NOTICE '% in words: %', p_num, v_str;
END;
$$;

-- Execute: CALL sp_number_in_words(123);
-- Execute: CALL sp_number_in_words(-45);
