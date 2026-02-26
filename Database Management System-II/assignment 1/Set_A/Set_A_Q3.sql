-- ============================================================
-- Assignment 1: Stored Procedures
-- Set A - Question 3
-- ============================================================
-- Q3. Create table Department (dno, dname, empname, city).
--     i)  Write a procedure to insert values in Department table.
--     ii) Write a procedure to display all employees working
--         in 'Pune' city.
-- ============================================================

-- Drop existing table
DROP TABLE IF EXISTS department CASCADE;

-- Create table
CREATE TABLE department (
    dno      INT PRIMARY KEY,
    dname    VARCHAR(30) NOT NULL,
    empname  VARCHAR(30) NOT NULL,
    city     VARCHAR(30) NOT NULL
);

-- Insert sample data
INSERT INTO department VALUES (1, 'Computer Science', 'Amit', 'Pune');
INSERT INTO department VALUES (2, 'Information Technology', 'Sneha', 'Mumbai');
INSERT INTO department VALUES (3, 'Electronics', 'Rahul', 'Pune');
INSERT INTO department VALUES (4, 'Mechanical', 'Priya', 'Nagpur');
INSERT INTO department VALUES (5, 'Civil', 'Rohan', 'Pune');
INSERT INTO department VALUES (6, 'Electrical', 'Neha', 'Mumbai');

-- ============================================================
-- (i) Procedure to insert values in Department table
-- ============================================================

DROP PROCEDURE IF EXISTS insert_department(INT, VARCHAR, VARCHAR, VARCHAR);

CREATE OR REPLACE PROCEDURE insert_department(
    IN p_dno      INT,
    IN p_dname    VARCHAR,
    IN p_empname  VARCHAR,
    IN p_city     VARCHAR
)
LANGUAGE plpgsql
AS $$
BEGIN
    INSERT INTO department (dno, dname, empname, city)
    VALUES (p_dno, p_dname, p_empname, p_city);

    RAISE NOTICE 'Inserted: dno=%, dname=%, empname=%, city=%',
                  p_dno, p_dname, p_empname, p_city;
END;
$$;

-- ============================================================
-- (ii) Procedure to display all employees working in 'Pune'
-- ============================================================

DROP PROCEDURE IF EXISTS display_pune_employees();

CREATE OR REPLACE PROCEDURE display_pune_employees()
LANGUAGE plpgsql
AS $$
DECLARE
    rec RECORD;
    v_count INT := 0;
BEGIN
    RAISE NOTICE '--- Employees working in Pune ---';

    FOR rec IN
        SELECT dno, dname, empname, city
        FROM department
        WHERE city = 'Pune'
    LOOP
        RAISE NOTICE 'Dno: %, Dname: %, Empname: %, City: %',
                      rec.dno, rec.dname, rec.empname, rec.city;
        v_count := v_count + 1;
    END LOOP;

    RAISE NOTICE 'Total employees in Pune: %', v_count;
END;
$$;

-- Test: Insert a new department entry
CALL insert_department(7, 'Biotech', 'Sakshi', 'Pune');

-- Test: Display all employees working in Pune
CALL display_pune_employees();
