-- ============================================================
-- Slip 27: Student-Subject Database
-- Section II: Database Management Systems-II [15 Marks]
-- ============================================================

/*
DATABASE SCHEMA: Student-Subject Database

Tables:
  Student (rollno integer, name varchar(30), class varchar(10))
  Subject (Scode varchar(10), subject_name varchar(20))

Relationship:
  Student and Subject are related with M-M relationship.
  Descriptive attribute: marks_scored

Junction Table:
  student_subject (rollno, scode, marks_scored int) - M:M relationship
*/

-- ============================================================
-- Database Setup
-- ============================================================

DROP DATABASE IF EXISTS slip_27_db;
CREATE DATABASE slip_27_db;
\c slip_27_db

-- ============================================================
-- Table Creation
-- ============================================================

DROP TABLE IF EXISTS student_subject CASCADE;
DROP TABLE IF EXISTS Student CASCADE;
DROP TABLE IF EXISTS Subject CASCADE;

CREATE TABLE Student (
    rollno INT PRIMARY KEY,
    name VARCHAR(30),
    class VARCHAR(10)
);

CREATE TABLE Subject (
    scode VARCHAR(10) PRIMARY KEY,
    subject_name VARCHAR(20)
);

CREATE TABLE student_subject (
    rollno INT REFERENCES Student(rollno),
    scode VARCHAR(10) REFERENCES Subject(scode),
    marks_scored INT,
    PRIMARY KEY (rollno, scode)
);

-- ============================================================
-- Sample Data
-- ============================================================

INSERT INTO Student VALUES (1, 'Amit', 'SY');
INSERT INTO Student VALUES (2, 'Sneha', 'TY');
INSERT INTO Student VALUES (3, 'Rahul', 'SY');
INSERT INTO Student VALUES (4, 'Priya', 'TY');
INSERT INTO Student VALUES (5, 'Kiran', 'FY');

INSERT INTO Subject VALUES ('CS101', 'Data Structures');
INSERT INTO Subject VALUES ('CS102', 'DBMS');
INSERT INTO Subject VALUES ('CS103', 'OS');

INSERT INTO student_subject VALUES (1, 'CS101', 85);
INSERT INTO student_subject VALUES (1, 'CS102', 78);
INSERT INTO student_subject VALUES (2, 'CS101', 90);
INSERT INTO student_subject VALUES (3, 'CS103', 72);
INSERT INTO student_subject VALUES (4, 'CS102', 88);

-- ============================================================
-- Q2.1 Option A: Write a stored function using cursors, to accept class
-- from the user and display the details of the students of that class. [10 Marks]
-- ============================================================
CREATE OR REPLACE FUNCTION get_students_by_class(p_class VARCHAR)
RETURNS VOID AS $$
DECLARE
    v_rec RECORD;
    v_found BOOLEAN := FALSE;
    cur_stud CURSOR FOR
        SELECT rollno, name, class FROM Student WHERE class = p_class;
BEGIN
    OPEN cur_stud;
    LOOP
        FETCH cur_stud INTO v_rec;
        EXIT WHEN NOT FOUND;
        v_found := TRUE;
        RAISE NOTICE 'Roll No: %, Name: %, Class: %', v_rec.rollno, v_rec.name, v_rec.class;
    END LOOP;
    CLOSE cur_stud;

    IF NOT v_found THEN
        RAISE NOTICE 'No students found in class: %', p_class;
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Execute: SELECT get_students_by_class('SY');  -- Should display Amit and Rahul
-- Execute: SELECT get_students_by_class('TY');  -- Should display Sneha and Priya
-- Execute: SELECT get_students_by_class('PG');  -- Should display "No students found"

-- ============================================================
-- Q2.1 Option B (OR): Write a trigger before insert/update the marks_scored.
-- Raise exception if Marks are negative. [10 Marks]
-- ============================================================
CREATE OR REPLACE FUNCTION trg_check_marks()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.marks_scored < 0 THEN
        RAISE EXCEPTION 'Marks cannot be negative. Given: %', NEW.marks_scored;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_marks_check
BEFORE INSERT OR UPDATE ON student_subject
FOR EACH ROW EXECUTE FUNCTION trg_check_marks();

-- Execute: INSERT INTO student_subject VALUES (5, 'CS101', -10);  -- Should fail (negative marks)
-- Execute: INSERT INTO student_subject VALUES (5, 'CS101', 75);   -- Should succeed

-- ============================================================
-- Q2.2: Write a procedure to display all even numbers from 1 to 50. [5 Marks]
-- ============================================================
CREATE OR REPLACE PROCEDURE display_even_1_to_50()
LANGUAGE plpgsql AS $$
DECLARE
    v_i INT := 2;
BEGIN
    WHILE v_i <= 50 LOOP
        RAISE NOTICE 'Even number: %', v_i;
        v_i := v_i + 2;
    END LOOP;
END;
$$;

-- Execute: CALL display_even_1_to_50();  -- Should display 2, 4, 6, ... 50
