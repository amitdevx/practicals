-- ============================================================
-- Slip 16: Student-Subject Database
-- Section II: Database Management Systems-II [15 Marks]
-- ============================================================

/*
DATABASE SCHEMA: Student-Subject Database

Tables:
  Student(rollno integer, name varchar(30), address varchar(50), class varchar(10))
  Subject(scode varchar(10), subject_name varchar(20))
  
Relationship: Student-Subject M-M with attributes marks_scored.
*/

-- ============================================================
-- Database Setup
-- ============================================================

DROP DATABASE IF EXISTS slip_16_db;
CREATE DATABASE slip_16_db;
\c slip_16_db

-- ============================================================
-- Table Creation
-- ============================================================

DROP TABLE IF EXISTS student_subject CASCADE;
DROP TABLE IF EXISTS Student CASCADE;
DROP TABLE IF EXISTS Subject CASCADE;

CREATE TABLE Student (
    rollno INT PRIMARY KEY,
    name VARCHAR(30) NOT NULL,
    address VARCHAR(50),
    class VARCHAR(10)
);

CREATE TABLE Subject (
    scode VARCHAR(10) PRIMARY KEY,
    subject_name VARCHAR(20) NOT NULL
);

CREATE TABLE student_subject (
    rollno INT REFERENCES Student(rollno) ON DELETE CASCADE,
    scode VARCHAR(10) REFERENCES Subject(scode) ON DELETE CASCADE,
    marks_scored INT CHECK (marks_scored >= 0 AND marks_scored <= 100),
    PRIMARY KEY (rollno, scode)
);

-- ============================================================
-- Sample Data
-- ============================================================

INSERT INTO Student VALUES (1, 'Amit', 'Pune', 'SY'), (2, 'Neha', 'Mumbai', 'TY'), (3, 'Raj', 'Nashik', 'SY');
INSERT INTO Subject VALUES ('CS101', 'DBMS'), ('CS102', 'DS'), ('CS103', 'OS');
INSERT INTO student_subject VALUES
    (1, 'CS101', 85), (1, 'CS102', 90), (1, 'CS103', 78),
    (2, 'CS101', 72), (2, 'CS102', 88),
    (3, 'CS101', 65), (3, 'CS103', 70);

-- ============================================================
-- Q2.1 Option A: Define a trigger before deleting a student record from the student table. Raise a notice and display the message "student record is being deleted". [10 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION fn_before_delete_student()
RETURNS TRIGGER AS $$
BEGIN
    RAISE NOTICE 'Student record is being deleted: Roll No %, Name %', OLD.rollno, OLD.name;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS trg_before_delete_student ON Student;
CREATE TRIGGER trg_before_delete_student
    BEFORE DELETE ON Student
    FOR EACH ROW
    EXECUTE FUNCTION fn_before_delete_student();

-- Execute: DELETE FROM Student WHERE rollno = 3;  -- Should show notice before deleting

-- ============================================================
-- Q2.1 Option B (OR): Write a stored function using cursors, to calculate total marks of each student and display it. [10 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION calc_total_marks()
RETURNS VOID AS $$
DECLARE
    rec RECORD;
    cur CURSOR FOR
        SELECT s.rollno, s.name, COALESCE(SUM(ss.marks_scored), 0) AS total_marks
        FROM Student s
        LEFT JOIN student_subject ss ON s.rollno = ss.rollno
        GROUP BY s.rollno, s.name
        ORDER BY s.rollno;
BEGIN
    OPEN cur;
    LOOP
        FETCH cur INTO rec;
        EXIT WHEN NOT FOUND;
        RAISE NOTICE 'Roll No: %, Name: %, Total Marks: %', rec.rollno, rec.name, rec.total_marks;
    END LOOP;
    CLOSE cur;
END;
$$ LANGUAGE plpgsql;

-- Execute: SELECT calc_total_marks();

-- ============================================================
-- Q2.2: Write a procedure to check the number is positive and negative. [5 Marks]
-- ============================================================

CREATE OR REPLACE PROCEDURE sp_check_sign(p_num NUMERIC)
LANGUAGE plpgsql AS $$
BEGIN
    IF p_num > 0 THEN
        RAISE NOTICE '% is Positive', p_num;
    ELSIF p_num < 0 THEN
        RAISE NOTICE '% is Negative', p_num;
    ELSE
        RAISE NOTICE '% is Zero', p_num;
    END IF;
END;
$$;

-- Execute: CALL sp_check_sign(25);
-- Execute: CALL sp_check_sign(-10);
-- Execute: CALL sp_check_sign(0);
