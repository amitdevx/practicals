-- ============================================================
-- Assignment 4: Handling Errors and Exceptions
-- Set D - Question 1
-- ============================================================
-- Q1. Write a stored function to count the number of teachers
--     teaching to a student (Accept student name as input
--     parameter). Raise an exception if student name does not
--     exist.
-- ============================================================

-- ==================== Table Creation ====================

DROP TABLE IF EXISTS student_teacher CASCADE;
DROP TABLE IF EXISTS Teacher CASCADE;
DROP TABLE IF EXISTS Student CASCADE;

CREATE TABLE Student (
    sno      INT PRIMARY KEY,
    s_name   CHAR(30) NOT NULL,
    s_class  CHAR(10),
    s_addr   CHAR(50)
);

CREATE TABLE Teacher (
    tno            INT PRIMARY KEY,
    t_name         CHAR(20) NOT NULL,
    qualification  CHAR(15),
    experience     INT
);

CREATE TABLE student_teacher (
    sno      INT REFERENCES Student(sno),
    tno      INT REFERENCES Teacher(tno),
    subject  VARCHAR(20),
    PRIMARY KEY (sno, tno)
);

-- ==================== Sample Data ====================

INSERT INTO Student VALUES (1, 'Amit',   'SE-A',  'Pune');
INSERT INTO Student VALUES (2, 'Priya',  'TE-B',  'Mumbai');
INSERT INTO Student VALUES (3, 'Rahul',  'BE-A',  'Nagpur');
INSERT INTO Student VALUES (4, 'Sneha',  'SE-B',  'Pune');
INSERT INTO Student VALUES (5, 'Vikram', 'TE-A',  'Mumbai');

INSERT INTO Teacher VALUES (101, 'Dr. Sharma',  'PhD',     10);
INSERT INTO Teacher VALUES (102, 'Prof. Gupta', 'MTech',    8);
INSERT INTO Teacher VALUES (103, 'Dr. Patel',   'PhD',     15);
INSERT INTO Teacher VALUES (104, 'Prof. Singh', 'MSc',      5);
INSERT INTO Teacher VALUES (105, 'Dr. Mehta',   'PhD',     12);

INSERT INTO student_teacher VALUES (1, 101, 'DBMS');
INSERT INTO student_teacher VALUES (1, 102, 'OS');
INSERT INTO student_teacher VALUES (1, 103, 'CN');
INSERT INTO student_teacher VALUES (2, 101, 'DBMS');
INSERT INTO student_teacher VALUES (2, 104, 'Maths');
INSERT INTO student_teacher VALUES (3, 103, 'CN');
INSERT INTO student_teacher VALUES (4, 102, 'OS');
INSERT INTO student_teacher VALUES (4, 105, 'AI');
INSERT INTO student_teacher VALUES (5, 101, 'DBMS');
INSERT INTO student_teacher VALUES (5, 103, 'CN');
INSERT INTO student_teacher VALUES (5, 105, 'AI');

-- ==================== Function ====================

CREATE OR REPLACE FUNCTION count_teachers_for_student(p_name VARCHAR)
RETURNS VOID AS $$
DECLARE
    v_sno    INT;
    v_count  INT := 0;
BEGIN
    -- Check if the student exists
    SELECT sno INTO v_sno
    FROM Student
    WHERE LOWER(TRIM(s_name)) = LOWER(TRIM(p_name));

    IF NOT FOUND THEN
        RAISE EXCEPTION 'Invalid student name: "%" does not exist.', p_name;
    END IF;

    -- Count the number of teachers
    SELECT COUNT(*) INTO v_count
    FROM student_teacher
    WHERE sno = v_sno;

    RAISE NOTICE 'Student "%" (sno: %) has % teacher(s).', TRIM(p_name), v_sno, v_count;

EXCEPTION
    WHEN OTHERS THEN
        RAISE NOTICE 'Error: %', SQLERRM;
END;
$$ LANGUAGE plpgsql;

-- ==================== Test Calls ====================

-- Valid student name
SELECT count_teachers_for_student('Amit');

-- Valid student name (different)
SELECT count_teachers_for_student('Vikram');

-- Valid student name (case-insensitive)
SELECT count_teachers_for_student('priya');

-- Invalid student name (should raise exception)
SELECT count_teachers_for_student('John');

-- Invalid student name (should raise exception)
SELECT count_teachers_for_student('Meera');
