-- ============================================================
-- Assignment 5: Triggers
-- Set B - Question 2
-- ============================================================
-- Q2. Write a trigger that restricts insertion of a charges
--     value greater than 400 in the Doctor table.
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
DROP TRIGGER IF EXISTS trg_doctor_max_charges ON doctor;
DROP FUNCTION IF EXISTS fn_doctor_max_charges();

CREATE OR REPLACE FUNCTION fn_doctor_max_charges()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.charges > 400 THEN
        RAISE EXCEPTION 'Insertion denied: Charges (%) for Doctor "%" exceed the maximum allowed limit of 400.', NEW.charges, NEW.d_name;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_doctor_max_charges
    BEFORE INSERT ON doctor
    FOR EACH ROW
    EXECUTE FUNCTION fn_doctor_max_charges();

-- ========================
-- Test DML
-- ========================
-- Test 1: Valid insert (charges <= 400) — should SUCCEED
INSERT INTO doctor VALUES (104, 'Dr. Mehta', 'Dermatology', 200, 3);

-- Test 2: Boundary insert (charges = 400) — should SUCCEED
INSERT INTO doctor VALUES (105, 'Dr. Joshi', 'ENT', 400, 2);

-- Verify
SELECT * FROM doctor;

-- Test 3: Invalid insert (charges > 400) — should FAIL
-- Uncomment to test:
-- INSERT INTO doctor VALUES (106, 'Dr. Expensive', 'Plastic Surgery', 500, 1);
