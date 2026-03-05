/*
SLIP 21 - SECTION II: DATABASE MANAGEMENT SYSTEMS II

Doctor(d_no int PK, d_name varchar(30), specialization varchar(35), phone_no int, charges int)
Hospital(h_no int PK, h_name varchar(20), city varchar(10))
Doctor and Hospital are related with many to one relationship (d.h_no FK).

Q2.1A: Function accept hospital name, calculate average charges of doctors visiting that hospital.
Q2.1B: Trigger before insert/update on Doctor - if charges < 0 raise exception.
Q2.2: Procedure to find sum and average of first n numbers using while loop.
*/

-- Table Creation
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

-- Sample Data
INSERT INTO Hospital VALUES (1, 'City Hospital', 'Pune');
INSERT INTO Hospital VALUES (2, 'Global Hospital', 'Mumbai');
INSERT INTO Hospital VALUES (3, 'Ruby Hospital', 'Pune');

INSERT INTO Doctor VALUES (1, 'Dr. Sharma', 'Cardiology', 9876543, 500, 1);
INSERT INTO Doctor VALUES (2, 'Dr. Patil', 'Neurology', 9876544, 700, 1);
INSERT INTO Doctor VALUES (3, 'Dr. Desai', 'Orthopedics', 9876545, 600, 2);
INSERT INTO Doctor VALUES (4, 'Dr. Joshi', 'Dermatology', 9876546, 400, 2);
INSERT INTO Doctor VALUES (5, 'Dr. Kulkarni', 'ENT', 9876547, 800, 3);

-- Q2.1A: Function to calculate average charges for a given hospital name
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

-- Q2.1B: Trigger before insert/update on Doctor - charges < 0 raise exception
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

-- Q2.2: Procedure sum and average of first n numbers using while loop
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

-- Test Calls
SELECT avg_charges_by_hospital('City Hospital');
SELECT avg_charges_by_hospital('Global Hospital');

-- Test trigger (this should raise exception)
-- INSERT INTO Doctor VALUES (6, 'Dr. Test', 'General', 9999999, -100, 1);

CALL sum_avg_n(10);
CALL sum_avg_n(50);
