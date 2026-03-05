/*
  SLIP 20
  Schema: Department(dno int PK, dname varchar(20), city varchar(20)),
          Employee(eno int PK, ename varchar(20), salary numeric, dno FK) 1:M
  Q2.1A: Function accept dept name, display max salary.
  Q2.1B: Trigger before insert/update on employee - salary<0 raise exception.
  Q2.2:  Procedure multiplication of two numbers.
*/

-- Schema
DROP TABLE IF EXISTS Employee CASCADE;
DROP TABLE IF EXISTS Department CASCADE;

CREATE TABLE Department (
    dno INT PRIMARY KEY,
    dname VARCHAR(20) NOT NULL,
    city VARCHAR(20)
);

CREATE TABLE Employee (
    eno INT PRIMARY KEY,
    ename VARCHAR(20) NOT NULL,
    salary NUMERIC,
    dno INT REFERENCES Department(dno) ON DELETE SET NULL
);

-- Sample Data
INSERT INTO Department VALUES (1, 'IT', 'Pune'), (2, 'HR', 'Mumbai'), (3, 'Finance', 'Delhi');
INSERT INTO Employee VALUES
    (101, 'Amit', 55000, 1), (102, 'Neha', 62000, 1), (103, 'Raj', 48000, 2),
    (104, 'Priya', 70000, 3), (105, 'Suresh', 45000, 2), (106, 'Kavita', 58000, 3);

-- Q2.1 Option A: Function accept dept name, display max salary
CREATE OR REPLACE FUNCTION get_max_salary(p_dname VARCHAR)
RETURNS NUMERIC AS $$
DECLARE
    v_dno INT;
    v_max NUMERIC;
    v_ename VARCHAR;
BEGIN
    SELECT dno INTO v_dno FROM Department WHERE dname = p_dname;
    IF NOT FOUND THEN
        RAISE EXCEPTION 'Department not found: %', p_dname;
    END IF;

    SELECT ename, salary INTO v_ename, v_max
    FROM Employee
    WHERE dno = v_dno
    ORDER BY salary DESC
    LIMIT 1;

    IF v_max IS NULL THEN
        RAISE NOTICE 'No employees in department %', p_dname;
        RETURN 0;
    END IF;

    RAISE NOTICE 'Department: %, Max Salary: % (Employee: %)', p_dname, v_max, v_ename;
    RETURN v_max;
END;
$$ LANGUAGE plpgsql;

-- Q2.1 Option B: Trigger before insert/update on employee - salary<0 raise exception
CREATE OR REPLACE FUNCTION fn_check_salary()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.salary < 0 THEN
        RAISE EXCEPTION 'Salary cannot be negative. Given: %', NEW.salary;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS trg_check_salary ON Employee;
CREATE TRIGGER trg_check_salary
    BEFORE INSERT OR UPDATE ON Employee
    FOR EACH ROW
    EXECUTE FUNCTION fn_check_salary();

-- Q2.2: Procedure multiplication of two numbers
CREATE OR REPLACE PROCEDURE sp_multiply(p_a NUMERIC, p_b NUMERIC)
LANGUAGE plpgsql AS $$
DECLARE
    v_result NUMERIC;
BEGIN
    v_result := p_a * p_b;
    RAISE NOTICE '% x % = %', p_a, p_b, v_result;
END;
$$;

-- Test Calls
SELECT get_max_salary('IT');
-- This should fail: INSERT INTO Employee VALUES (107, 'Test', -5000, 1);
CALL sp_multiply(12, 15);
CALL sp_multiply(7, 8);
