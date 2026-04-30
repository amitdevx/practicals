-- ============================================================
-- Assignment 3: Cursors
-- Set D - Question 1
-- ============================================================
-- Q1. Write a cursor which will display year wise details of
--     competitions held. (Use parameterized cursor)
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

-- Stored function using parameterized cursor
CREATE OR REPLACE FUNCTION get_competitions_by_year(p_year INT)
RETURNS VOID AS $$
DECLARE
    cur_comp CURSOR (v_year INT) FOR
        SELECT c.comp_no, c.comp_name, c.comp_type,
               s.s_reg_no, s.s_name, sc.rank
        FROM competition c
        JOIN student_competition sc ON c.comp_no = sc.comp_no
        JOIN student s ON sc.s_reg_no = s.s_reg_no
        WHERE sc.year = v_year;
    rec RECORD;
BEGIN
    RAISE NOTICE '--- Competition Details for Year: % ---', p_year;
    OPEN cur_comp(p_year);
    LOOP
        FETCH cur_comp INTO rec;
        EXIT WHEN NOT FOUND;
        RAISE NOTICE 'Comp No: %, Name: %, Type: %, Student: %, Rank: %',
            rec.comp_no, rec.comp_name, rec.comp_type, rec.s_name, rec.rank;
    END LOOP;
    CLOSE cur_comp;
END;
$$ LANGUAGE plpgsql;

-- Test
SELECT get_competitions_by_year(2022);
SELECT get_competitions_by_year(2023);
SELECT get_competitions_by_year(2024);
