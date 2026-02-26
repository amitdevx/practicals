-- ============================================================
-- Assignment 5: Triggers
-- Set B - Question 1
-- ============================================================
-- Q1. Write a trigger before insert or update on the Doctor
--     table. If the charges value is less than 0, raise an
--     exception.
-- ============================================================

-- ========================
-- Table Creation
-- ========================
DROP TABLE IF EXISTS doctor CASCADE;
DROP TABLE IF EXISTS hospital CASCADE;

CREATE TABLE hospital (
    h_no   INT PRIMARY KEY,
    h_name VARCHAR(20),
    city   VARCHAR(10)
);

CREATE TABLE doctor (
    d_no           INT PRIMARY KEY,
    d_name         VARCHAR(30),
    specialization VARCHAR(35),
    charges        INT,
    h_no           INT REFERENCES hospital(h_no) ON DELETE SET NULL
);

-- ========================
-- Sample Data
-- ========================
INSERT INTO hospital VALUES (1, 'City Hospital', 'Pune');
INSERT INTO hospital VALUES (2, 'Global Hospital', 'Mumbai');
INSERT INTO hospital VALUES (3, 'Apollo Hospital', 'Delhi');

INSERT INTO doctor VALUES (101, 'Dr. Sharma', 'Cardiology', 300, 1);
INSERT INTO doctor VALUES (102, 'Dr. Patil', 'Neurology', 350, 2);
INSERT INTO doctor VALUES (103, 'Dr. Desai', 'Orthopedics', 250, 1);

-- ========================
-- Trigger Function & Trigger
-- ========================
DROP TRIGGER IF EXISTS trg_doctor_charges_check ON doctor;
DROP FUNCTION IF EXISTS fn_doctor_charges_check();

CREATE OR REPLACE FUNCTION fn_doctor_charges_check()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.charges < 0 THEN
        RAISE EXCEPTION 'Invalid charges: Doctor "%" has charges = %. Charges cannot be negative.', NEW.d_name, NEW.charges;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_doctor_charges_check
    BEFORE INSERT OR UPDATE ON doctor
    FOR EACH ROW
    EXECUTE FUNCTION fn_doctor_charges_check();

-- ========================
-- Test DML
-- ========================
-- Test 1: Valid insert (charges >= 0) — should SUCCEED
INSERT INTO doctor VALUES (104, 'Dr. Mehta', 'Dermatology', 200, 3);

-- Test 2: Valid update — should SUCCEED
UPDATE doctor SET charges = 400 WHERE d_no = 101;

-- Verify
SELECT * FROM doctor;

-- Test 3: Invalid insert (negative charges) — should FAIL
-- Uncomment to test:
-- INSERT INTO doctor VALUES (105, 'Dr. Ghost', 'General', -50, 2);

-- Test 4: Invalid update (negative charges) — should FAIL
-- Uncomment to test:
-- UPDATE doctor SET charges = -100 WHERE d_no = 102;
