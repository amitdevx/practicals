-- ============================================================
-- Assignment 3: Cursors
-- Set D - Question 2
-- ============================================================
-- Q2. Write a cursor which will display student wise total
--     count of competition participated.
-- ============================================================

-- Drop existing tables
DROP TABLE IF EXISTS student_competition CASCADE;
DROP TABLE IF EXISTS student CASCADE;
DROP TABLE IF EXISTS competition CASCADE;

-- Create tables
CREATE TABLE student (
    s_reg_no  INT PRIMARY KEY,
    s_name    VARCHAR(20) NOT NULL,
    s_class   VARCHAR(20) NOT NULL
);

CREATE TABLE competition (
    comp_no    INT PRIMARY KEY,
    comp_name  VARCHAR(20) NOT NULL,
    comp_type  VARCHAR(20) NOT NULL
);

CREATE TABLE student_competition (
    s_reg_no  INT REFERENCES student(s_reg_no),
    comp_no   INT REFERENCES competition(comp_no),
    rank      INT NOT NULL,
    year      INT NOT NULL,
    PRIMARY KEY (s_reg_no, comp_no, year)
);

-- Insert sample data into student
INSERT INTO student VALUES (1, 'Amit', 'SY-CS');
INSERT INTO student VALUES (2, 'Sneha', 'TY-CS');
INSERT INTO student VALUES (3, 'Rahul', 'SY-IT');
INSERT INTO student VALUES (4, 'Priya', 'TY-IT');
INSERT INTO student VALUES (5, 'Vijay', 'SY-CS');
INSERT INTO student VALUES (6, 'Anjali', 'TY-CS');

-- Insert sample data into competition
INSERT INTO competition VALUES (101, 'CodeSprint', 'Technical');
INSERT INTO competition VALUES (102, 'Quiz Bowl', 'Academic');
INSERT INTO competition VALUES (103, 'Debate', 'Cultural');
INSERT INTO competition VALUES (104, 'Hackathon', 'Technical');
INSERT INTO competition VALUES (105, 'Essay Writing', 'Literary');

-- Insert sample data into student_competition
INSERT INTO student_competition VALUES (1, 101, 1, 2022);
INSERT INTO student_competition VALUES (2, 102, 2, 2022);
INSERT INTO student_competition VALUES (3, 103, 1, 2023);
INSERT INTO student_competition VALUES (4, 101, 3, 2023);
INSERT INTO student_competition VALUES (5, 104, 2, 2023);
INSERT INTO student_competition VALUES (1, 105, 1, 2024);
INSERT INTO student_competition VALUES (6, 102, 1, 2024);
INSERT INTO student_competition VALUES (2, 104, 2, 2024);
INSERT INTO student_competition VALUES (3, 101, 3, 2022);

-- Stored function using cursor
CREATE OR REPLACE FUNCTION get_student_competition_count()
RETURNS VOID AS $$
DECLARE
    cur_students CURSOR FOR
        SELECT s.s_reg_no, s.s_name, s.s_class,
               COUNT(sc.comp_no) AS total_competitions
        FROM student s
        LEFT JOIN student_competition sc ON s.s_reg_no = sc.s_reg_no
        GROUP BY s.s_reg_no, s.s_name, s.s_class
        ORDER BY s.s_reg_no;
    rec RECORD;
BEGIN
    RAISE NOTICE '--- Student Wise Competition Count ---';
    OPEN cur_students;
    LOOP
        FETCH cur_students INTO rec;
        EXIT WHEN NOT FOUND;
        RAISE NOTICE 'Reg No: %, Name: %, Class: %, Competitions: %',
            rec.s_reg_no, rec.s_name, rec.s_class, rec.total_competitions;
    END LOOP;
    CLOSE cur_students;
END;
$$ LANGUAGE plpgsql;

-- Test
SELECT get_student_competition_count();
