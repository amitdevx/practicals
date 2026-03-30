-- ============================================================
-- Slip 11: Student-Subject Database
-- Section II: Database Management Systems-II [15 Marks]
-- ============================================================

/*
DATABASE SCHEMA: Student-Subject Database

Tables:
  1. Student (rollno, s_name, class)
     - rollno: INT, Primary Key
     - s_name: VARCHAR(30), Student name
     - class: VARCHAR(10), Class/Year

  2. Subject (scode, subject_name)
     - scode: VARCHAR(10), Primary Key
     - subject_name: VARCHAR(20), Subject name

  3. student_subject (rollno, scode, marks) - Junction Table for M:M relationship
     - rollno: INT, Foreign Key -> Student(rollno)
     - scode: VARCHAR(10), Foreign Key -> Subject(scode)
     - marks: INT, Descriptive attribute (marks obtained)
     - PRIMARY KEY (rollno, scode)

Relationship: Student-Subject: M-M with descriptive attribute 'marks'
*/

-- ============================================================
-- Database Setup
-- ============================================================

DROP DATABASE IF EXISTS slip_11_db;
CREATE DATABASE slip_11_db;
\c slip_11_db

-- ============================================================
-- Table Creation
-- ============================================================

DROP TABLE IF EXISTS student_subject CASCADE;
DROP TABLE IF EXISTS Student CASCADE;
DROP TABLE IF EXISTS Subject CASCADE;

CREATE TABLE Student (
    rollno INT PRIMARY KEY,
    s_name VARCHAR(30) NOT NULL,
    class VARCHAR(10)
);

CREATE TABLE Subject (
    scode VARCHAR(10) PRIMARY KEY,
    subject_name VARCHAR(20) NOT NULL
);

CREATE TABLE student_subject (
    rollno INT REFERENCES Student(rollno) ON DELETE CASCADE,
    scode VARCHAR(10) REFERENCES Subject(scode) ON DELETE CASCADE,
    marks INT CHECK (marks >= 0 AND marks <= 100),
    PRIMARY KEY (rollno, scode)
);

-- ============================================================
-- Sample Data
-- ============================================================

INSERT INTO Student VALUES (1, 'Amit', 'SY'), (2, 'Neha', 'TY'), (3, 'Raj', 'SY');
INSERT INTO Subject VALUES ('CS101', 'DBMS'), ('CS102', 'DS'), ('CS103', 'OS');
INSERT INTO student_subject VALUES
    (1, 'CS101', 85), (1, 'CS102', 90), (1, 'CS103', 78),
    (2, 'CS101', 72), (2, 'CS102', 88),
    (3, 'CS101', 65), (3, 'CS103', 70);

-- ============================================================
-- Q2.1 Option A: Write a stored function using cursor to calculate total marks of each student and display it. [10 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION calc_total_marks()
RETURNS VOID AS $$
DECLARE
    rec RECORD;
    cur CURSOR FOR
        SELECT s.rollno, s.s_name, COALESCE(SUM(ss.marks), 0) AS total_marks
        FROM Student s
        LEFT JOIN student_subject ss ON s.rollno = ss.rollno
        GROUP BY s.rollno, s.s_name
        ORDER BY s.rollno;
BEGIN
    OPEN cur;
    LOOP
        FETCH cur INTO rec;
        EXIT WHEN NOT FOUND;
        RAISE NOTICE 'Roll No: %, Name: %, Total Marks: %', rec.rollno, rec.s_name, rec.total_marks;
    END LOOP;
    CLOSE cur;
END;
$$ LANGUAGE plpgsql;

-- Execute: SELECT calc_total_marks();

-- ============================================================
-- Q2.1 Option B (OR): Define a trigger before deleting a student record from student table. Raise a notice and display message "student record is being deleted". [10 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION fn_before_delete_student()
RETURNS TRIGGER AS $$
BEGIN
    RAISE NOTICE 'Student record is being deleted: Roll No %, Name %', OLD.rollno, OLD.s_name;
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
-- Q2.2: Write a procedure to find sum and average of first n numbers using conditional loop (while). [5 Marks]
-- ============================================================

CREATE OR REPLACE PROCEDURE sp_sum_avg_n(p_n INT)
LANGUAGE plpgsql AS $$
DECLARE
    v_sum INT := 0;
    v_avg NUMERIC;
    v_i INT := 1;
BEGIN
    IF p_n <= 0 THEN
        RAISE EXCEPTION 'n must be positive';
    END IF;

    WHILE v_i <= p_n LOOP
        v_sum := v_sum + v_i;
        v_i := v_i + 1;
    END LOOP;

    v_avg := v_sum::NUMERIC / p_n;
    RAISE NOTICE 'Sum of first % numbers = %', p_n, v_sum;
    RAISE NOTICE 'Average of first % numbers = %', p_n, ROUND(v_avg, 2);
END;
$$;

-- Execute: CALL sp_sum_avg_n(10);
