-- ============================================================
-- Assignment 5: Triggers
-- Set C - Question 1
-- ============================================================
-- Q1. Write a trigger before insert or update on the
--     student_subject table. If the marks_scored value is
--     negative, raise an exception.
-- ============================================================

-- ========================
-- Table Creation
-- ========================
DROP TABLE IF EXISTS student_subject CASCADE;
DROP TABLE IF EXISTS subject CASCADE;
DROP TABLE IF EXISTS student CASCADE;

CREATE TABLE student (
    rollno INTEGER PRIMARY KEY,
    name   VARCHAR(30),
    city   VARCHAR(50),
    class  VARCHAR(10)
);

CREATE TABLE subject (
    scode        VARCHAR(10) PRIMARY KEY,
    subject_name VARCHAR(20)
);

CREATE TABLE student_subject (
    rollno       INTEGER REFERENCES student(rollno) ON DELETE CASCADE,
    scode        VARCHAR(10) REFERENCES subject(scode) ON DELETE CASCADE,
    marks_scored INTEGER,
    PRIMARY KEY (rollno, scode)
);

-- ========================
-- Sample Data
-- ========================
INSERT INTO student VALUES (1, 'Amit', 'Pune', 'TE');
INSERT INTO student VALUES (2, 'Sneha', 'Mumbai', 'SE');
INSERT INTO student VALUES (3, 'Rahul', 'Nagpur', 'BE');

INSERT INTO subject VALUES ('CS101', 'DBMS');
INSERT INTO subject VALUES ('CS102', 'OS');
INSERT INTO subject VALUES ('CS103', 'CN');

INSERT INTO student_subject VALUES (1, 'CS101', 85);
INSERT INTO student_subject VALUES (2, 'CS102', 72);

-- ========================
-- Trigger Function & Trigger
-- ========================
DROP TRIGGER IF EXISTS trg_marks_check ON student_subject;
DROP FUNCTION IF EXISTS fn_marks_check();

CREATE OR REPLACE FUNCTION fn_marks_check()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.marks_scored < 0 THEN
        RAISE EXCEPTION 'Invalid marks: marks_scored (%) for rollno % in subject "%" cannot be negative.', NEW.marks_scored, NEW.rollno, NEW.scode;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_marks_check
    BEFORE INSERT OR UPDATE ON student_subject
    FOR EACH ROW
    EXECUTE FUNCTION fn_marks_check();

-- ========================
-- Test DML
-- ========================
-- Test 1: Valid insert (marks >= 0) — should SUCCEED
INSERT INTO student_subject VALUES (3, 'CS103', 60);

-- Test 2: Valid update — should SUCCEED
UPDATE student_subject SET marks_scored = 90 WHERE rollno = 1 AND scode = 'CS101';

-- Verify
SELECT * FROM student_subject;

-- Test 3: Invalid insert (negative marks) — should FAIL
-- Uncomment to test:
-- INSERT INTO student_subject VALUES (1, 'CS102', -10);

-- Test 4: Invalid update (negative marks) — should FAIL
-- Uncomment to test:
-- UPDATE student_subject SET marks_scored = -5 WHERE rollno = 2 AND scode = 'CS102';
