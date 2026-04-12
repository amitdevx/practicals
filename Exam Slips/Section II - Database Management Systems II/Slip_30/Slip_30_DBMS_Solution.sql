-- ============================================================
-- Slip 30: Student-Teacher Database
-- Section II: Database Management Systems-II [15 Marks]
-- ============================================================

/*
DATABASE SCHEMA: Student-Teacher Database

Tables:
  Student (Roll_No int, Sname varchar(20), Sclass char(10))
  Teacher (T_No int, Tname char(20), Experience int)

Relationship:
  Student and Teacher are related with many to many relationship.
  Descriptive attribute: Subject

Junction Table:
  student_teacher (roll_no, t_no, subject varchar(20)) - M:M relationship
*/

-- ============================================================
-- Database Setup
-- ============================================================

DROP DATABASE IF EXISTS slip_30_db;
CREATE DATABASE slip_30_db;
\c slip_30_db

-- ============================================================
-- Table Creation
-- ============================================================

DROP TABLE IF EXISTS student_teacher CASCADE;
DROP TABLE IF EXISTS Student CASCADE;
DROP TABLE IF EXISTS Teacher CASCADE;

CREATE TABLE Student (
    roll_no INT PRIMARY KEY,
    sname VARCHAR(20),
    sclass CHAR(10)
);

CREATE TABLE Teacher (
    t_no INT PRIMARY KEY,
    tname CHAR(20),
    experience INT
);

CREATE TABLE student_teacher (
    roll_no INT REFERENCES Student(roll_no),
    t_no INT REFERENCES Teacher(t_no),
    subject VARCHAR(20),
    PRIMARY KEY (roll_no, t_no)
);

-- ============================================================
-- Sample Data
-- ============================================================

INSERT INTO Student VALUES (1, 'Amit', 'SY');
INSERT INTO Student VALUES (2, 'Sneha', 'TY');
INSERT INTO Student VALUES (3, 'Rahul', 'SY');
INSERT INTO Student VALUES (4, 'Priya', 'FY');

INSERT INTO Teacher VALUES (101, 'Prof. Sharma', 15);
INSERT INTO Teacher VALUES (102, 'Prof. Patil', 8);
INSERT INTO Teacher VALUES (103, 'Prof. Desai', 12);
INSERT INTO Teacher VALUES (104, 'Prof. Joshi', 5);
INSERT INTO Teacher VALUES (105, 'Prof. Kulkarni', 20);

INSERT INTO student_teacher VALUES (1, 101, 'Data Structures');
INSERT INTO student_teacher VALUES (1, 102, 'DBMS');
INSERT INTO student_teacher VALUES (2, 103, 'OS');
INSERT INTO student_teacher VALUES (3, 101, 'Data Structures');
INSERT INTO student_teacher VALUES (4, 104, 'Maths');

-- ============================================================
-- Q2.1 Option A: Write a stored function to count the number of teachers
-- having experience > 10 years. [10 Marks]
-- ============================================================
CREATE OR REPLACE FUNCTION count_experienced_teachers()
RETURNS INT AS $$
DECLARE
    v_count INT;
BEGIN
    SELECT COUNT(*) INTO v_count FROM Teacher WHERE experience > 10;
    RAISE NOTICE 'Number of teachers with experience > 10 years: %', v_count;
    RETURN v_count;
END;
$$ LANGUAGE plpgsql;

-- Execute: SELECT count_experienced_teachers();  -- Should return 3 (Sharma: 15, Desai: 12, Kulkarni: 20)

-- ============================================================
-- Q2.1 Option B (OR): Write a trigger before insert the record of the student
-- in the Student table. If the Roll_No is less than or equal to zero then
-- the trigger gets fired and displays the message "Invalid Roll Number". [10 Marks]
-- ============================================================
CREATE OR REPLACE FUNCTION trg_check_rollno()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.roll_no <= 0 THEN
        RAISE EXCEPTION 'Invalid Roll Number: %. Roll number must be positive.', NEW.roll_no;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_student_rollno
BEFORE INSERT ON Student
FOR EACH ROW EXECUTE FUNCTION trg_check_rollno();

-- Execute: INSERT INTO Student VALUES (0, 'Test', 'SY');   -- Should fail (roll_no = 0)
-- Execute: INSERT INTO Student VALUES (-1, 'Test', 'SY');  -- Should fail (roll_no < 0)
-- Execute: INSERT INTO Student VALUES (10, 'New Student', 'SY');  -- Should succeed

-- ============================================================
-- Q2.2: Write a procedure to find sum and average of first n numbers
-- using conditional loop(while). [5 Marks]
-- ============================================================
CREATE OR REPLACE PROCEDURE sum_avg_n(p_n INT)
LANGUAGE plpgsql AS $$
DECLARE
    v_sum INT := 0;
    v_avg NUMERIC;
    v_i INT := 1;
BEGIN
    WHILE v_i <= p_n LOOP
        v_sum := v_sum + v_i;
        v_i := v_i + 1;
    END LOOP;
    v_avg := v_sum::NUMERIC / p_n;
    RAISE NOTICE 'Sum of first % numbers: %', p_n, v_sum;
    RAISE NOTICE 'Average of first % numbers: %', p_n, v_avg;
END;
$$;

-- Execute: CALL sum_avg_n(10);  -- Should display sum = 55, average = 5.5
-- Execute: CALL sum_avg_n(50);  -- Should display sum = 1275, average = 25.5
