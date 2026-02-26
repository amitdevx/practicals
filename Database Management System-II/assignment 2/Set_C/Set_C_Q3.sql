-- ============================================================
-- Assignment 2: Stored Functions
-- Set C - Question 3
-- Function to find the number of teachers having
-- qualification "NET"
-- ============================================================

-- Q3. Write a function to find the number of teachers having
--     qualification "NET".

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
CREATE OR REPLACE FUNCTION count_teachers_by_qualification(qual TEXT)
RETURNS INTEGER AS $$
DECLARE
    cnt INTEGER;
BEGIN
    SELECT COUNT(*) INTO cnt
    FROM teacher
    WHERE TRIM(qualification) = TRIM(qual);

    RAISE NOTICE 'Number of teachers with qualification "%": %', qual, cnt;
    RETURN cnt;
END;
$$ LANGUAGE plpgsql;

-- Test
SELECT count_teachers_by_qualification('NET');
SELECT count_teachers_by_qualification('PhD');
SELECT count_teachers_by_qualification('SET');
