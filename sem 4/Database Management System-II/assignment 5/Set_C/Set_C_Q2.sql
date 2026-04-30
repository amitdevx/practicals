-- ============================================================
-- Assignment 5: Triggers
-- Set C - Question 2
-- ============================================================
-- Q2. Write a trigger that is executed when an insertion is
--     made in the student_subject table. If marks_scored < 0,
--     give a message and do not allow the insertion.
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
DROP TRIGGER IF EXISTS trg_marks_insert_check ON student_subject;
DROP FUNCTION IF EXISTS fn_marks_insert_check();

CREATE OR REPLACE FUNCTION fn_marks_insert_check()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.marks_scored < 0 THEN
        RAISE EXCEPTION 'Insertion denied: marks_scored (%) for rollno % is negative. Marks must be zero or positive.', NEW.marks_scored, NEW.rollno;
    END IF;
    RAISE NOTICE 'Record inserted successfully: rollno=%, scode=%, marks=%', NEW.rollno, NEW.scode, NEW.marks_scored;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_marks_insert_check
    BEFORE INSERT ON student_subject
    FOR EACH ROW
    EXECUTE FUNCTION fn_marks_insert_check();

-- ========================
-- Test DML
-- ========================
-- Test 1: Valid insert (marks >= 0) — should SUCCEED with notice
INSERT INTO student_subject VALUES (3, 'CS103', 55);

-- Test 2: Boundary insert (marks = 0) — should SUCCEED
INSERT INTO student_subject VALUES (1, 'CS102', 0);

-- Verify
SELECT * FROM student_subject;

-- Test 3: Invalid insert (negative marks) — should FAIL with exception
-- Uncomment to test:
-- INSERT INTO student_subject VALUES (2, 'CS103', -20);
