-- ============================================================
-- Assignment 5: Triggers
-- Set C - Question 3
-- ============================================================
-- Q3. Write a trigger which will prevent deleting students
--     from 'Mumbai' city.
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
INSERT INTO student VALUES (4, 'Priya', 'Mumbai', 'TE');
INSERT INTO student VALUES (5, 'Karan', 'Delhi', 'SE');

INSERT INTO subject VALUES ('CS101', 'DBMS');
INSERT INTO subject VALUES ('CS102', 'OS');

INSERT INTO student_subject VALUES (1, 'CS101', 85);
INSERT INTO student_subject VALUES (2, 'CS102', 72);
INSERT INTO student_subject VALUES (4, 'CS101', 68);

-- ========================
-- Trigger Function & Trigger
-- ========================
DROP TRIGGER IF EXISTS trg_prevent_mumbai_delete ON student;
DROP FUNCTION IF EXISTS fn_prevent_mumbai_delete();

CREATE OR REPLACE FUNCTION fn_prevent_mumbai_delete()
RETURNS TRIGGER AS $$
BEGIN
    IF OLD.city = 'Mumbai' THEN
        RAISE EXCEPTION 'Deletion denied: Cannot delete student "%" (rollno %) because they belong to Mumbai city.', OLD.name, OLD.rollno;
    END IF;
    RAISE NOTICE 'Student "%" (rollno %) from "%" deleted successfully.', OLD.name, OLD.rollno, OLD.city;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_prevent_mumbai_delete
    BEFORE DELETE ON student
    FOR EACH ROW
    EXECUTE FUNCTION fn_prevent_mumbai_delete();

-- ========================
-- Test DML
-- ========================
-- Test 1: Delete student from Pune — should SUCCEED
DELETE FROM student WHERE rollno = 1;

-- Test 2: Delete student from Nagpur — should SUCCEED
DELETE FROM student WHERE rollno = 3;

-- Verify
SELECT * FROM student;

-- Test 3: Delete student from Mumbai — should FAIL with exception
-- Uncomment to test:
-- DELETE FROM student WHERE rollno = 2;

-- Test 4: Another Mumbai student — should also FAIL
-- Uncomment to test:
-- DELETE FROM student WHERE rollno = 4;
