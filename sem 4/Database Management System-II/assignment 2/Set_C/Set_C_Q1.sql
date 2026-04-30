-- ============================================================
-- Assignment 2: Stored Functions
-- Set C - Question 1
-- Function to find name of the most experienced teacher
-- for "Computer" subject
-- ============================================================

-- Q1. Write a function to find the name of the most experienced
--     teacher who teaches the "Computer" subject.

-- Student-Teacher Database Schema:
--   student (sno, s_name, s_class, s_addr)
--   teacher (tno, t_name, qualification, experience)
--   student_teacher (sno, tno, subject) — Many-to-Many with
--     descriptive attribute SUBJECT

-- Drop existing tables
DROP TABLE IF EXISTS student_teacher CASCADE;
DROP TABLE IF EXISTS student CASCADE;
DROP TABLE IF EXISTS teacher CASCADE;

-- Create tables
CREATE TABLE student (
    sno INTEGER PRIMARY KEY,
    s_name CHAR(30),
    s_class CHAR(10),
    s_addr CHAR(50)
);

CREATE TABLE teacher (
    tno INTEGER PRIMARY KEY,
    t_name CHAR(20),
    qualification CHAR(15),
    experience INTEGER
);

CREATE TABLE student_teacher (
    sno INTEGER REFERENCES student(sno),
    tno INTEGER REFERENCES teacher(tno),
    subject CHAR(20),
    PRIMARY KEY (sno, tno, subject)
);

-- Insert sample data — Teachers
INSERT INTO teacher VALUES (1, 'Dr. Patil', 'PhD', 15);
INSERT INTO teacher VALUES (2, 'Prof. Shah', 'NET', 10);
INSERT INTO teacher VALUES (3, 'Dr. Kulkarni', 'PhD', 20);
INSERT INTO teacher VALUES (4, 'Prof. Desai', 'NET', 8);
INSERT INTO teacher VALUES (5, 'Dr. Joshi', 'PhD', 12);
INSERT INTO teacher VALUES (6, 'Prof. Mehta', 'SET', 5);

-- Insert sample data — Students
INSERT INTO student VALUES (101, 'Amit Sharma', 'SY', '12 MG Road, Pune');
INSERT INTO student VALUES (102, 'Priya Desai', 'TY', '45 FC Road, Mumbai');
INSERT INTO student VALUES (103, 'Rahul Patil', 'SY', '78 JM Road, Pune');
INSERT INTO student VALUES (104, 'Sneha More', 'FY', '23 Station Rd, Nagpur');
INSERT INTO student VALUES (105, 'Vikas Joshi', 'TY', '56 Civil Lines, Delhi');

-- Insert sample data — Student-Teacher (subject)
INSERT INTO student_teacher VALUES (101, 1, 'Computer');
INSERT INTO student_teacher VALUES (101, 2, 'Mathematics');
INSERT INTO student_teacher VALUES (102, 3, 'Computer');
INSERT INTO student_teacher VALUES (102, 4, 'English');
INSERT INTO student_teacher VALUES (103, 1, 'Computer');
INSERT INTO student_teacher VALUES (103, 5, 'Physics');
INSERT INTO student_teacher VALUES (104, 3, 'Computer');
INSERT INTO student_teacher VALUES (104, 6, 'Chemistry');
INSERT INTO student_teacher VALUES (105, 2, 'Mathematics');
INSERT INTO student_teacher VALUES (105, 5, 'Physics');

-- Function
CREATE OR REPLACE FUNCTION most_experienced_teacher_for_subject(subj TEXT)
RETURNS VOID AS $$
DECLARE
    tname TEXT;
    exp INTEGER;
BEGIN
    SELECT TRIM(t.t_name), t.experience INTO tname, exp
    FROM teacher t
    JOIN student_teacher st ON t.tno = st.tno
    WHERE TRIM(st.subject) = TRIM(subj)
    ORDER BY t.experience DESC
    LIMIT 1;

    IF tname IS NULL THEN
        RAISE NOTICE 'No teacher found for subject: %', subj;
    ELSE
        RAISE NOTICE 'Most experienced teacher for "%": % (% years)', subj, tname, exp;
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Test
SELECT most_experienced_teacher_for_subject('Computer');
SELECT most_experienced_teacher_for_subject('Mathematics');
SELECT most_experienced_teacher_for_subject('History');
