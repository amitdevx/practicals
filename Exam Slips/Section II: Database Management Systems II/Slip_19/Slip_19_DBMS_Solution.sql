/*
  SLIP 19
  Schema: PROJECT(pno int PK, p_name char(30) NOT NULL, ptype char(20), duration int CHECK >0),
          EMPLOYEE(eno int PK, e_name char(20), qualification char(15), joindate date),
          project_employee(pno, eno, start_date date, no_of_hours_worked int) M:M
  Q2.1A: Function accept eno, count projects.
  Q2.1B: Trigger before insert on project duration>0.
  Q2.2:  Procedure min and max from two numbers.
*/

-- Schema
DROP TABLE IF EXISTS project_employee CASCADE;
DROP TABLE IF EXISTS PROJECT CASCADE;
DROP TABLE IF EXISTS EMPLOYEE CASCADE;

CREATE TABLE PROJECT (
    pno INT PRIMARY KEY,
    p_name CHAR(30) NOT NULL,
    ptype CHAR(20),
    duration INT CHECK (duration > 0)
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

-- Sample Data
INSERT INTO PROJECT VALUES (1, 'Alpha', 'Software', 12), (2, 'Beta', 'Hardware', 6), (3, 'Gamma', 'Software', 8);
INSERT INTO EMPLOYEE VALUES (101, 'Amit', 'BE', '2020-01-15'), (102, 'Neha', 'MCA', '2019-06-10'),
    (103, 'Raj', 'BSc', '2021-03-20'), (104, 'Priya', 'ME', '2018-09-01');
INSERT INTO project_employee VALUES
    (1, 101, '2020-02-01', 200), (1, 102, '2020-02-01', 180),
    (2, 103, '2021-04-01', 150), (3, 101, '2021-05-01', 100), (3, 104, '2021-05-01', 220);

-- Q2.1 Option A: Function accept eno, count projects
CREATE OR REPLACE FUNCTION count_employee_projects(p_eno INT)
RETURNS INT AS $$
DECLARE
    v_count INT;
    v_name TEXT;
BEGIN
    SELECT TRIM(e_name) INTO v_name FROM EMPLOYEE WHERE eno = p_eno;
    IF NOT FOUND THEN
        RAISE EXCEPTION 'Employee not found with eno: %', p_eno;
    END IF;

    SELECT COUNT(*) INTO v_count FROM project_employee WHERE eno = p_eno;
    RAISE NOTICE 'Employee: % (Eno: %) is working on % project(s)', v_name, p_eno, v_count;
    RETURN v_count;
END;
$$ LANGUAGE plpgsql;

-- Q2.1 Option B: Trigger before insert on project - duration>0
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

-- Q2.2: Procedure min and max from two numbers
CREATE OR REPLACE PROCEDURE sp_min_max(p_a NUMERIC, p_b NUMERIC)
LANGUAGE plpgsql AS $$
BEGIN
    IF p_a > p_b THEN
        RAISE NOTICE 'Max = %, Min = %', p_a, p_b;
    ELSIF p_b > p_a THEN
        RAISE NOTICE 'Max = %, Min = %', p_b, p_a;
    ELSE
        RAISE NOTICE 'Both numbers are equal: %', p_a;
    END IF;
END;
$$;

-- Test Calls
SELECT count_employee_projects(101);
-- This should fail: INSERT INTO PROJECT VALUES (4, 'Test', 'Other', -1);
CALL sp_min_max(15, 42);
CALL sp_min_max(100, 100);
