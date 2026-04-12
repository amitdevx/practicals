-- ============================================================
-- Slip 21: Doctor-Hospital Database
-- Section II: Database Management Systems-II [15 Marks]
-- ============================================================

/*
DATABASE SCHEMA: Doctor-Hospital Database

Tables:
  Doctor(d_no int, d_name varchar(30), specialization varchar(35), 
         phone_no int, charges int)
  Hospital(h_no int, h_name varchar(20), city varchar(10))

Relationship:
  Doctor and Hospital are related with many to one relationship.
  (Many doctors can visit one hospital; h_no is FK in Doctor table)

Constraints:
  - d_no is Primary Key in Doctor
  - h_no is Primary Key in Hospital
  - h_no in Doctor references Hospital(h_no)
*/

-- ============================================================
-- Database Setup
-- ============================================================

DROP DATABASE IF EXISTS slip_21_db;
CREATE DATABASE slip_21_db;
\c slip_21_db

-- ============================================================
-- Table Creation
-- ============================================================

DROP TABLE IF EXISTS Doctor CASCADE;
DROP TABLE IF EXISTS Hospital CASCADE;

CREATE TABLE Hospital (
    h_no INT PRIMARY KEY,
    h_name VARCHAR(20),
    city VARCHAR(10)
);

CREATE TABLE Doctor (
    d_no INT PRIMARY KEY,
    d_name VARCHAR(30),
    specialization VARCHAR(35),
    phone_no INT,
    charges INT,
    h_no INT REFERENCES Hospital(h_no)
);

-- ============================================================
-- Sample Data
-- ============================================================

INSERT INTO Hospital VALUES (1, 'City Hospital', 'Pune');
INSERT INTO Hospital VALUES (2, 'Global Hospital', 'Mumbai');
INSERT INTO Hospital VALUES (3, 'Ruby Hospital', 'Pune');

INSERT INTO Doctor VALUES (1, 'Dr. Sharma', 'Cardiology', 9876543, 500, 1);
INSERT INTO Doctor VALUES (2, 'Dr. Patil', 'Neurology', 9876544, 700, 1);
INSERT INTO Doctor VALUES (3, 'Dr. Desai', 'Orthopedics', 9876545, 600, 2);
INSERT INTO Doctor VALUES (4, 'Dr. Joshi', 'Dermatology', 9876546, 400, 2);
INSERT INTO Doctor VALUES (5, 'Dr. Kulkarni', 'ENT', 9876547, 800, 3);

-- ============================================================
-- Q2.1 Option A: Write a function which will accept the name of the hospital
-- and calculate the average charges of doctors visiting that hospital. [10 Marks]
-- ============================================================
CREATE OR REPLACE FUNCTION avg_charges_by_hospital(p_hname VARCHAR)
RETURNS NUMERIC AS $$
DECLARE
    v_avg NUMERIC;
BEGIN
    SELECT AVG(d.charges) INTO v_avg
    FROM Doctor d JOIN Hospital h ON d.h_no = h.h_no
    WHERE h.h_name = p_hname;

    IF v_avg IS NULL THEN
        RAISE NOTICE 'No doctors found for hospital: %', p_hname;
        RETURN 0;
    END IF;

    RAISE NOTICE 'Average charges for hospital %: %', p_hname, v_avg;
    RETURN v_avg;
END;
$$ LANGUAGE plpgsql;

-- Execute: SELECT avg_charges_by_hospital('City Hospital');
-- Execute: SELECT avg_charges_by_hospital('Global Hospital');

-- ============================================================
-- Q2.1 Option B (OR): Write a trigger before insert/update on Doctor.
-- Raise exception if charges are < 0. [10 Marks]
-- ============================================================
CREATE OR REPLACE FUNCTION trg_check_charges()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.charges < 0 THEN
        RAISE EXCEPTION 'Charges cannot be negative. Given: %', NEW.charges;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_doctor_charges
BEFORE INSERT OR UPDATE ON Doctor
FOR EACH ROW EXECUTE FUNCTION trg_check_charges();

-- Execute: INSERT INTO Doctor VALUES (10, 'Dr. Test', 'General', 9876550, -100, 1);  -- Should fail (negative charges)
-- Execute: INSERT INTO Doctor VALUES (10, 'Dr. Test', 'General', 9876550, 450, 1);   -- Should succeed

-- ============================================================
-- Q2.2: Write a procedure to find sum and average of first n numbers
-- using conditional loop (while). [5 Marks]
-- ============================================================
CREATE OR REPLACE PROCEDURE sum_avg_n(p_n INT)
LANGUAGE plpgsql AS $$
DECLARE
    v_sum INT := 0;
    v_avg NUMERIC;
    v_i INT := 1;
BEGIN
    WHILE v_i <= p_n LOOP
        v_sum := v_sum + v_i;
        v_i := v_i + 1;
    END LOOP;
    v_avg := v_sum::NUMERIC / p_n;
    RAISE NOTICE 'Sum of first % numbers: %', p_n, v_sum;
    RAISE NOTICE 'Average of first % numbers: %', p_n, v_avg;
END;
$$;

-- Execute: CALL sum_avg_n(10);
-- Execute: CALL sum_avg_n(50);
