/*
SLIP 24 - SECTION II: DATABASE MANAGEMENT SYSTEMS II

Department(dno int PK, dname varchar(20), city varchar(20))
Employee(eno int PK, ename varchar(20), salary numeric, dno FK) 1:M

Q2.1A: Function accept dept name, display employee name with salary.
Q2.1B: Trigger after insert on employee - display "record inserted" message.
Q2.2: Procedure to display first 20 even numbers.
*/

-- Table Creation
DROP TABLE IF EXISTS Employee CASCADE;
DROP TABLE IF EXISTS Department CASCADE;

CREATE TABLE Department (
    dno INT PRIMARY KEY,
    dname VARCHAR(20),
    city VARCHAR(20)
);

CREATE TABLE Employee (
    eno INT PRIMARY KEY,
    ename VARCHAR(20),
    salary NUMERIC,
    dno INT REFERENCES Department(dno)
);

-- Sample Data
INSERT INTO Department VALUES (1, 'Computer', 'Pune');
INSERT INTO Department VALUES (2, 'Mechanical', 'Mumbai');
INSERT INTO Department VALUES (3, 'Civil', 'Nagpur');

INSERT INTO Employee VALUES (101, 'Amit', 50000, 1);
INSERT INTO Employee VALUES (102, 'Sneha', 55000, 1);
INSERT INTO Employee VALUES (103, 'Rahul', 45000, 2);
INSERT INTO Employee VALUES (104, 'Priya', 60000, 3);
INSERT INTO Employee VALUES (105, 'Kiran', 48000, 2);

-- Q2.1A: Function accept dept name, display employee name with salary
CREATE OR REPLACE FUNCTION get_employees_by_dept(p_dname VARCHAR)
RETURNS TABLE(emp_name VARCHAR, emp_salary NUMERIC) AS $$
BEGIN
    RETURN QUERY
    SELECT e.ename, e.salary
    FROM Employee e JOIN Department d ON e.dno = d.dno
    WHERE d.dname = p_dname;

    IF NOT FOUND THEN
        RAISE NOTICE 'No employees found in department: %', p_dname;
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Q2.1B: Trigger after insert on employee - display "record inserted"
CREATE OR REPLACE FUNCTION trg_after_insert_emp()
RETURNS TRIGGER AS $$
BEGIN
    RAISE NOTICE 'Record inserted: Employee % (eno: %)', NEW.ename, NEW.eno;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_emp_insert
AFTER INSERT ON Employee
FOR EACH ROW EXECUTE FUNCTION trg_after_insert_emp();

-- Q2.2: Procedure to display first 20 even numbers
CREATE OR REPLACE PROCEDURE display_20_even()
LANGUAGE plpgsql AS $$
DECLARE
    v_count INT := 0;
    v_num INT := 2;
BEGIN
    WHILE v_count < 20 LOOP
        RAISE NOTICE 'Even number: %', v_num;
        v_num := v_num + 2;
        v_count := v_count + 1;
    END LOOP;
END;
$$;

-- Test Calls
SELECT * FROM get_employees_by_dept('Computer');
SELECT * FROM get_employees_by_dept('Mechanical');

-- Test trigger
INSERT INTO Employee VALUES (106, 'TestEmp', 35000, 1);

CALL display_20_even();
