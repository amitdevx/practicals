-- ============================================================
-- Assignment 2: Stored Functions
-- Set E - Question 3
-- Function using cursors to accept class and display details
-- of students of that class
-- ============================================================

-- Q3. Write a stored function using cursors, to accept class
--     from the user and display the details of the students
--     of that class.

-- Student-Subject Database Schema:
--   Student (roll_no, name, address, class)
--   Subject (scode, subject_name)
--   student_subject (roll_no, scode, marks_scored) — Many-to-Many
--     with descriptive attribute marks_scored

-- Drop existing tables
DROP TABLE IF EXISTS student_subject CASCADE;
DROP TABLE IF EXISTS student CASCADE;
DROP TABLE IF EXISTS subject CASCADE;

-- Create tables
CREATE TABLE student (
    roll_no INTEGER PRIMARY KEY,
    name VARCHAR(30),
    address VARCHAR(50),
    class VARCHAR(10)
);

CREATE TABLE subject (
    scode VARCHAR(10) PRIMARY KEY,
    subject_name VARCHAR(20)
);

CREATE TABLE student_subject (
    roll_no INTEGER REFERENCES student(roll_no),
    scode VARCHAR(10) REFERENCES subject(scode),
    marks_scored INTEGER,
    PRIMARY KEY (roll_no, scode)
);

-- Insert sample data — Students
INSERT INTO student VALUES (1, 'Amit Sharma', '12 MG Road, Pune', 'SY');
INSERT INTO student VALUES (2, 'Priya Desai', '45 FC Road, Mumbai', 'TY');
INSERT INTO student VALUES (3, 'Rahul Patil', '78 JM Road, Pune', 'SY');
INSERT INTO student VALUES (4, 'Sneha More', '23 Station Rd, Nagpur', 'FY');
INSERT INTO student VALUES (5, 'Vikas Joshi', '56 Civil Lines, Delhi', 'TY');
INSERT INTO student VALUES (6, 'Neha Mehta', '89 Andheri West, Mumbai', 'SY');

-- Insert sample data — Subjects
INSERT INTO subject VALUES ('CS101', 'DBMS');
INSERT INTO subject VALUES ('CS102', 'Data Structures');
INSERT INTO subject VALUES ('CS103', 'Operating Systems');
INSERT INTO subject VALUES ('CS104', 'Networks');
INSERT INTO subject VALUES ('CS105', 'Python');

-- Insert sample data — Student-Subject
INSERT INTO student_subject VALUES (1, 'CS101', 85);
INSERT INTO student_subject VALUES (1, 'CS102', 78);
INSERT INTO student_subject VALUES (2, 'CS101', 92);
INSERT INTO student_subject VALUES (2, 'CS103', 88);
INSERT INTO student_subject VALUES (3, 'CS104', 75);
INSERT INTO student_subject VALUES (4, 'CS105', 90);
INSERT INTO student_subject VALUES (5, 'CS101', 82);
INSERT INTO student_subject VALUES (6, 'CS102', 70);

-- Function
CREATE OR REPLACE FUNCTION get_students_by_class(s_class TEXT)
RETURNS VOID AS $$
DECLARE
    cur CURSOR FOR
        SELECT roll_no, TRIM(name) AS name, TRIM(address) AS address,
               TRIM(class) AS class
        FROM student
        WHERE TRIM(class) = TRIM(s_class);
    rec RECORD;
    found BOOLEAN := FALSE;
BEGIN
    OPEN cur;
    LOOP
        FETCH cur INTO rec;
        EXIT WHEN NOT FOUND;
        RAISE NOTICE 'Roll No: %, Name: %, Address: %, Class: %',
            rec.roll_no, rec.name, rec.address, rec.class;
        found := TRUE;
    END LOOP;
    CLOSE cur;

    IF NOT found THEN
        RAISE NOTICE 'No students found in class: %', s_class;
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Test
SELECT get_students_by_class('SY');
SELECT get_students_by_class('TY');
SELECT get_students_by_class('FY');
SELECT get_students_by_class('PG');
