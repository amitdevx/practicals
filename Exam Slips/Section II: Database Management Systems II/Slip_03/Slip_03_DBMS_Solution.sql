-- ============================================================
-- Slip 03: Student-Teacher Database
-- Section II: Database Management Systems-II [15 Marks]
-- ============================================================

/*
Consider the following Entities and their Relationships for Student-Teacher database.

Student (s_no integer, s_name char(20), address char(25), class char(10))
Teacher (t_no integer, t_name char(10), qualification char(10), experience integer)

The Relationship between Student and Teacher is Many-to-Many (M-M) with descriptive attributes
subject and marks_scored.

Constraints: Primary Key, s_name, t_name should not be null, marks_scored > 0
*/

-- ============================================================
-- Database Setup
-- ============================================================

DROP DATABASE IF EXISTS slip_03_db;
CREATE DATABASE slip_03_db;
\c slip_03_db

-- ============================================================
-- Table Creation
-- ============================================================

DROP TABLE IF EXISTS student_teacher CASCADE;
DROP TABLE IF EXISTS Student CASCADE;
DROP TABLE IF EXISTS Teacher CASCADE;

CREATE TABLE Student (
    s_no    INT PRIMARY KEY,
    s_name  CHAR(20) NOT NULL,
    address CHAR(25),
    class   CHAR(10)
);

CREATE TABLE Teacher (
    t_no          INT PRIMARY KEY,
    t_name        CHAR(10) NOT NULL,
    qualification CHAR(10),
    experience    INT
);

CREATE TABLE student_teacher (
    s_no          INT REFERENCES Student(s_no),
    t_no          INT REFERENCES Teacher(t_no),
    subject       VARCHAR(20),
    marks_scored  INT CHECK (marks_scored > 0),
    PRIMARY KEY (s_no, t_no)
);

-- ============================================================
-- Sample Data
-- ============================================================

INSERT INTO Student VALUES (1, 'Amit', 'Pune', 'SY');
INSERT INTO Student VALUES (2, 'Neha', 'Mumbai', 'TY');
INSERT INTO Student VALUES (3, 'Rahul', 'Nashik', 'SY');

INSERT INTO Teacher VALUES (101, 'Dr. Patil', 'PhD', 15);
INSERT INTO Teacher VALUES (102, 'Prof. Shah', 'MCA', 10);
INSERT INTO Teacher VALUES (103, 'Dr. Joshi', 'PhD', 20);

INSERT INTO student_teacher VALUES (1, 101, 'RDBMS', 85);
INSERT INTO student_teacher VALUES (2, 102, 'RDBMS', 72);
INSERT INTO student_teacher VALUES (3, 103, 'DSA', 90);
INSERT INTO student_teacher VALUES (1, 103, 'DSA', 78);

-- ============================================================
-- Q2.1 Option A: Write a cursor which will accept student number
-- from the user and display student name along with teacher name
-- who taught 'RDBMS' subject. [10 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION get_rdbms_teacher(p_sno INT)
RETURNS VOID AS $$
DECLARE
    cur CURSOR FOR
        SELECT s.s_name, t.t_name
        FROM student_teacher st
        JOIN Student s ON s.s_no = st.s_no
        JOIN Teacher t ON t.t_no = st.t_no
        WHERE st.s_no = p_sno AND st.subject = 'RDBMS';
    rec RECORD;
    v_found BOOLEAN := FALSE;
BEGIN
    OPEN cur;
    LOOP
        FETCH cur INTO rec;
        EXIT WHEN NOT FOUND;
        v_found := TRUE;
        RAISE NOTICE 'Student: %, Teacher: %', TRIM(rec.s_name), TRIM(rec.t_name);
    END LOOP;
    CLOSE cur;

    IF NOT v_found THEN
        RAISE NOTICE 'No RDBMS record found for student no: %', p_sno;
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Execute: SELECT get_rdbms_teacher(1);  -- Amit taught by Dr. Patil
-- Execute: SELECT get_rdbms_teacher(2);  -- Neha taught by Prof. Shah
-- Execute: SELECT get_rdbms_teacher(3);  -- Rahul has no RDBMS record

-- ============================================================
-- Q2.1 Option B (OR): Write a trigger before insert the record
-- of student. If student number is less than or equal to zero
-- give message "Invalid Number". [10 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION check_student_sno()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.s_no <= 0 THEN
        RAISE EXCEPTION 'Invalid Number: Student number must be greater than 0.';
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_check_sno
BEFORE INSERT ON Student
FOR EACH ROW
EXECUTE FUNCTION check_student_sno();

-- Execute: INSERT INTO Student VALUES (-1, 'Invalid', 'Delhi', 'FY');  -- Should fail
-- Execute: INSERT INTO Student VALUES (0, 'Zero', 'Delhi', 'FY');      -- Should fail
-- Execute: INSERT INTO Student VALUES (10, 'Valid', 'Delhi', 'FY');    -- Should succeed

-- ============================================================
-- Q2.2: Write a procedure to find minimum and maximum from two
-- numbers. [5 Marks]
-- ============================================================

CREATE OR REPLACE PROCEDURE find_min_max(a NUMERIC, b NUMERIC)
AS $$
BEGIN
    IF a > b THEN
        RAISE NOTICE 'Max = %, Min = %', a, b;
    ELSIF b > a THEN
        RAISE NOTICE 'Max = %, Min = %', b, a;
    ELSE
        RAISE NOTICE 'Both numbers are equal: %', a;
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Execute: CALL find_min_max(10, 5);   -- Max = 10, Min = 5
-- Execute: CALL find_min_max(3, 7);    -- Max = 7, Min = 3
-- Execute: CALL find_min_max(5, 5);    -- Both equal

