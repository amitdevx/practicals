-- ============================================================
-- Assignment 1: Stored Procedures
-- Set B - Question 2 (B)
-- ============================================================
-- Consider the following relationship:
--   Patient (p_no, p_name, p_addr)
--   Doctor  (d_no, d_name, d_addr, city)
-- Relationship between Patient and Doctor is many-to-many
-- with descriptive attributes: disease and no_of_visits.
--
-- a. Write a procedure which displays patient details who
--    have visited more than 3 times to the given doctor
--    for 'Diabetes'.
-- b. Write a procedure which displays total number of visits
--    of Dr. Kumar.
-- ============================================================

-- Drop existing tables
DROP TABLE IF EXISTS patient_doctor CASCADE;
DROP TABLE IF EXISTS patient CASCADE;
DROP TABLE IF EXISTS doctor CASCADE;

-- Create tables
CREATE TABLE patient (
    p_no    INT PRIMARY KEY,
    p_name  VARCHAR(30) NOT NULL,
    p_addr  VARCHAR(50) NOT NULL
);

CREATE TABLE doctor (
    d_no    INT PRIMARY KEY,
    d_name  VARCHAR(30) NOT NULL,
    d_addr  VARCHAR(50) NOT NULL,
    city    VARCHAR(30) NOT NULL
);

-- Junction table for many-to-many relationship
CREATE TABLE patient_doctor (
    p_no          INT REFERENCES patient(p_no),
    d_no          INT REFERENCES doctor(d_no),
    disease       VARCHAR(30) NOT NULL,
    no_of_visits  INT NOT NULL DEFAULT 1,
    PRIMARY KEY (p_no, d_no, disease)
);

-- Insert sample data into patient
INSERT INTO patient VALUES (1, 'Amit', 'Kothrud, Pune');
INSERT INTO patient VALUES (2, 'Sneha', 'Dadar, Mumbai');
INSERT INTO patient VALUES (3, 'Rahul', 'Deccan, Pune');
INSERT INTO patient VALUES (4, 'Priya', 'Baner, Pune');
INSERT INTO patient VALUES (5, 'Rohan', 'Andheri, Mumbai');
INSERT INTO patient VALUES (6, 'Neha', 'Viman Nagar, Pune');

-- Insert sample data into doctor
INSERT INTO doctor VALUES (101, 'Dr. Kumar', 'FC Road, Pune', 'Pune');
INSERT INTO doctor VALUES (102, 'Dr. Sharma', 'Dadar, Mumbai', 'Mumbai');
INSERT INTO doctor VALUES (103, 'Dr. Patil', 'JM Road, Pune', 'Pune');
INSERT INTO doctor VALUES (104, 'Dr. Desai', 'Nashik Road', 'Nashik');

-- Insert sample data into patient_doctor (junction table)
INSERT INTO patient_doctor VALUES (1, 101, 'Diabetes', 5);
INSERT INTO patient_doctor VALUES (2, 101, 'Diabetes', 2);
INSERT INTO patient_doctor VALUES (3, 101, 'Diabetes', 4);
INSERT INTO patient_doctor VALUES (4, 102, 'Diabetes', 6);
INSERT INTO patient_doctor VALUES (5, 101, 'Fever', 3);
INSERT INTO patient_doctor VALUES (1, 102, 'Hypertension', 2);
INSERT INTO patient_doctor VALUES (6, 101, 'Diabetes', 7);
INSERT INTO patient_doctor VALUES (3, 103, 'Cold', 1);
INSERT INTO patient_doctor VALUES (4, 101, 'Diabetes', 1);
INSERT INTO patient_doctor VALUES (2, 103, 'Fever', 4);

-- ============================================================
-- (a) Procedure to display patients who visited more than 3
--     times to a given doctor for 'Diabetes'
-- ============================================================

DROP PROCEDURE IF EXISTS display_diabetes_patients(INT);

CREATE OR REPLACE PROCEDURE display_diabetes_patients(
    IN p_d_no INT
)
LANGUAGE plpgsql
AS $$
DECLARE
    rec RECORD;
    v_count INT := 0;
    v_dname VARCHAR;
BEGIN
    SELECT d_name INTO v_dname FROM doctor WHERE d_no = p_d_no;

    IF NOT FOUND THEN
        RAISE EXCEPTION 'Doctor with d_no % does not exist', p_d_no;
    END IF;

    RAISE NOTICE '--- Patients with more than 3 visits for Diabetes to % ---', v_dname;

    FOR rec IN
        SELECT p.p_no, p.p_name, p.p_addr, pd.no_of_visits
        FROM patient p
        JOIN patient_doctor pd ON p.p_no = pd.p_no
        WHERE pd.d_no = p_d_no
          AND pd.disease = 'Diabetes'
          AND pd.no_of_visits > 3
    LOOP
        RAISE NOTICE 'P_No: %, Name: %, Address: %, Visits: %',
                      rec.p_no, rec.p_name, rec.p_addr, rec.no_of_visits;
        v_count := v_count + 1;
    END LOOP;

    IF v_count = 0 THEN
        RAISE NOTICE 'No patients found with more than 3 visits for Diabetes to %', v_dname;
    ELSE
        RAISE NOTICE 'Total patients found: %', v_count;
    END IF;
END;
$$;

-- ============================================================
-- (b) Procedure to display total number of visits of Dr. Kumar
-- ============================================================

DROP PROCEDURE IF EXISTS display_total_visits_dr_kumar();

CREATE OR REPLACE PROCEDURE display_total_visits_dr_kumar()
LANGUAGE plpgsql
AS $$
DECLARE
    v_total_visits INT;
    v_d_no INT;
BEGIN
    SELECT d_no INTO v_d_no FROM doctor WHERE d_name = 'Dr. Kumar';

    IF NOT FOUND THEN
        RAISE EXCEPTION 'Dr. Kumar does not exist in the database';
    END IF;

    SELECT COALESCE(SUM(no_of_visits), 0)
    INTO v_total_visits
    FROM patient_doctor
    WHERE d_no = v_d_no;

    RAISE NOTICE '--- Visit Summary for Dr. Kumar ---';
    RAISE NOTICE 'Doctor No: %', v_d_no;
    RAISE NOTICE 'Total number of visits: %', v_total_visits;
END;
$$;

-- Test: Display patients visiting Dr. Kumar (d_no=101) for Diabetes > 3 times
CALL display_diabetes_patients(101);

-- Test: Display total visits of Dr. Kumar
CALL display_total_visits_dr_kumar();
