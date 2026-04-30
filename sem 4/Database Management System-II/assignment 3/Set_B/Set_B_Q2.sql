-- ============================================================
-- Assignment 3: Cursors
-- Set B - Question 2
-- ============================================================
-- Q2. Write a cursor to accept the subject's name from the
--     user as an input and display names of all teachers
--     teaching that subject.
-- ============================================================

-- Drop existing tables
DROP TABLE IF EXISTS teacher_subject CASCADE;
DROP TABLE IF EXISTS teacher CASCADE;
DROP TABLE IF EXISTS subject CASCADE;

-- Create tables
CREATE TABLE teacher (
    t_no           INT PRIMARY KEY,
    t_name         VARCHAR(20) NOT NULL,
    age            INT NOT NULL,
    yr_experience  INT NOT NULL
);

CREATE TABLE subject (
    s_no    INT PRIMARY KEY,
    s_name  VARCHAR(15) NOT NULL
);

CREATE TABLE teacher_subject (
    t_no  INT REFERENCES teacher(t_no),
    s_no  INT REFERENCES subject(s_no),
    PRIMARY KEY (t_no, s_no)
);

-- Insert sample data into teacher
INSERT INTO teacher VALUES (1, 'Mr. Sharma', 45, 20);
INSERT INTO teacher VALUES (2, 'Ms. Patil', 35, 10);
INSERT INTO teacher VALUES (3, 'Mr. Deshmukh', 50, 25);
INSERT INTO teacher VALUES (4, 'Ms. Kulkarni', 40, 15);
INSERT INTO teacher VALUES (5, 'Mr. Joshi', 38, 12);
INSERT INTO teacher VALUES (6, 'Ms. Rane', 32, 8);

-- Insert sample data into subject
INSERT INTO subject VALUES (101, 'DBMS');
INSERT INTO subject VALUES (102, 'OS');
INSERT INTO subject VALUES (103, 'CN');
INSERT INTO subject VALUES (104, 'SE');
INSERT INTO subject VALUES (105, 'Maths');

-- Insert sample data into teacher_subject
INSERT INTO teacher_subject VALUES (1, 101);
INSERT INTO teacher_subject VALUES (1, 102);
INSERT INTO teacher_subject VALUES (2, 101);
INSERT INTO teacher_subject VALUES (2, 103);
INSERT INTO teacher_subject VALUES (3, 104);
INSERT INTO teacher_subject VALUES (3, 101);
INSERT INTO teacher_subject VALUES (4, 105);
INSERT INTO teacher_subject VALUES (5, 102);
INSERT INTO teacher_subject VALUES (5, 103);
INSERT INTO teacher_subject VALUES (6, 101);
INSERT INTO teacher_subject VALUES (6, 105);

-- Stored function using parameterized cursor
CREATE OR REPLACE FUNCTION display_teachers_for_subject(p_subject_name VARCHAR)
RETURNS VOID AS $$
DECLARE
    -- Parameterized cursor
    cur_teachers CURSOR (subj_name VARCHAR) FOR
        SELECT t.t_name
        FROM teacher t
        JOIN teacher_subject ts ON t.t_no = ts.t_no
        JOIN subject s ON ts.s_no = s.s_no
        WHERE s.s_name = subj_name;
    v_name VARCHAR(20);
BEGIN
    RAISE NOTICE '--- Teachers Teaching: % ---', p_subject_name;
    OPEN cur_teachers(p_subject_name);
    LOOP
        FETCH cur_teachers INTO v_name;
        EXIT WHEN NOT FOUND;
        RAISE NOTICE 'Teacher Name: %', v_name;
    END LOOP;
    CLOSE cur_teachers;
END;
$$ LANGUAGE plpgsql;

-- Test
SELECT display_teachers_for_subject('OS');
