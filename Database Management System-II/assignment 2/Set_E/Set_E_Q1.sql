-- ============================================================
-- Assignment 2: Stored Functions
-- Set E - Question 1
-- Function to accept student name and print all details
-- of that student
-- ============================================================

-- Q1. Write a function which will accept the name and print
--     all the details of that student.

-- Student-Subject Database Schema:
--   Student (roll_no, name, address, class)
--   Subject (scode, subject_name)
--   student_subject (roll_no, scode, marks_scored) — Many-to-Many
--     with descriptive attribute marks_scored

-- Drop existing tables
DROP TABLE IF EXISTS student_subject CASCADE;
DROP TABLE IF EXISTS student CASCADE;
DROP TABLE IF EXISTS subject CASCADE;

-- Create tables
CREATE TABLE student (
    roll_no INTEGER PRIMARY KEY,
    name VARCHAR(30),
    address VARCHAR(50),
    class VARCHAR(10)
);

CREATE TABLE subject (
    scode VARCHAR(10) PRIMARY KEY,
    subject_name VARCHAR(20)
);

CREATE TABLE student_subject (
    roll_no INTEGER REFERENCES student(roll_no),
    scode VARCHAR(10) REFERENCES subject(scode),
    marks_scored INTEGER,
    PRIMARY KEY (roll_no, scode)
);

-- Insert sample data — Students
INSERT INTO student VALUES (1, 'Amit Sharma', '12 MG Road, Pune', 'SY');
INSERT INTO student VALUES (2, 'Priya Desai', '45 FC Road, Mumbai', 'TY');
INSERT INTO student VALUES (3, 'Rahul Patil', '78 JM Road, Pune', 'SY');
INSERT INTO student VALUES (4, 'Sneha More', '23 Station Rd, Nagpur', 'FY');
INSERT INTO student VALUES (5, 'Vikas Joshi', '56 Civil Lines, Delhi', 'TY');
INSERT INTO student VALUES (6, 'Neha Mehta', '89 Andheri West, Mumbai', 'SY');

-- Insert sample data — Subjects
INSERT INTO subject VALUES ('CS101', 'DBMS');
INSERT INTO subject VALUES ('CS102', 'Data Structures');
INSERT INTO subject VALUES ('CS103', 'Operating Systems');
INSERT INTO subject VALUES ('CS104', 'Networks');
INSERT INTO subject VALUES ('CS105', 'Python');

-- Insert sample data — Student-Subject
INSERT INTO student_subject VALUES (1, 'CS101', 85);
INSERT INTO student_subject VALUES (1, 'CS102', 78);
INSERT INTO student_subject VALUES (2, 'CS101', 92);
INSERT INTO student_subject VALUES (2, 'CS103', 88);
INSERT INTO student_subject VALUES (3, 'CS104', 75);
INSERT INTO student_subject VALUES (4, 'CS105', 90);
INSERT INTO student_subject VALUES (5, 'CS101', 82);
INSERT INTO student_subject VALUES (6, 'CS102', 70);

-- Function
CREATE OR REPLACE FUNCTION get_student_by_name(s_name TEXT)
RETURNS VOID AS $$
DECLARE
    rec RECORD;
    found BOOLEAN := FALSE;
BEGIN
    FOR rec IN
        SELECT roll_no, TRIM(name) AS name, TRIM(address) AS address,
               TRIM(class) AS class
        FROM student
        WHERE TRIM(name) = TRIM(s_name)
    LOOP
        RAISE NOTICE 'Roll No: %, Name: %, Address: %, Class: %',
            rec.roll_no, rec.name, rec.address, rec.class;
        found := TRUE;
    END LOOP;

    IF NOT found THEN
        RAISE NOTICE 'No student found with name: %', s_name;
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Test
SELECT get_student_by_name('Amit Sharma');
SELECT get_student_by_name('Priya Desai');
SELECT get_student_by_name('Unknown');
