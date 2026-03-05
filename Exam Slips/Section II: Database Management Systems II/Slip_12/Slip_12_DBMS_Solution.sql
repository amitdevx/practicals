/*
  SLIP 12
  Schema: PROJECT(pno int PK, p_name char(30), ptype char(20), duration int),
          EMPLOYEE(eno int PK, e_name char(20), qualification char(15), joindate date),
          project_employee(pno, eno, start_date date, no_of_hours_worked int) M:M
  Q2.1A: Trigger before insert on project - duration must be >0.
  Q2.1B: Function accept project name, print employee names, raise exception for invalid.
  Q2.2:  Procedure count odd numbers from m to n using for loop.
*/

-- Schema
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

-- Sample Data
INSERT INTO PROJECT VALUES (1, 'Alpha', 'Software', 12), (2, 'Beta', 'Hardware', 6), (3, 'Gamma', 'Software', 8);
INSERT INTO EMPLOYEE VALUES (101, 'Amit', 'BE', '2020-01-15'), (102, 'Neha', 'MCA', '2019-06-10'),
    (103, 'Raj', 'BSc', '2021-03-20'), (104, 'Priya', 'ME', '2018-09-01');
INSERT INTO project_employee VALUES
    (1, 101, '2020-02-01', 200), (1, 102, '2020-02-01', 180),
    (2, 103, '2021-04-01', 150), (3, 101, '2021-05-01', 100), (3, 104, '2021-05-01', 220);

-- Q2.1 Option A: Trigger before insert on project - duration must be >0
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

-- Q2.1 Option B: Function accept project name, print employees, raise exception for invalid
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

-- Q2.2: Procedure count odd numbers from m to n using for loop
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

-- Test Calls
-- This should fail: INSERT INTO PROJECT VALUES (4, 'Test', 'Other', -1);
SELECT get_project_employees('Alpha');
CALL sp_count_odd(1, 20);
