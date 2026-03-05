/*
SLIP 30 - SECTION II: DATABASE MANAGEMENT SYSTEMS II

Student(roll_no int PK, sname varchar(20), sclass char(10))
Teacher(t_no int PK, tname char(20), experience int)
student_teacher(roll_no, t_no, subject varchar(20)) M:M

Q2.1A: Function to count teachers with experience > 10.
Q2.1B: Trigger before insert on student - if roll_no <= 0 display "Invalid Roll Number".
Q2.2: Procedure to find sum and average of first n numbers using while loop.
*/

-- Table Creation
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

-- Sample Data
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

-- Q2.1A: Function to count teachers with experience > 10
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

-- Q2.1B: Trigger before insert on student - if roll_no <= 0 raise exception
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

-- Q2.2: Procedure sum and average of first n numbers using while loop
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

-- Test Calls
SELECT count_experienced_teachers();

-- Test trigger (this should raise exception)
-- INSERT INTO Student VALUES (0, 'Invalid', 'SY');
-- INSERT INTO Student VALUES (-1, 'Invalid', 'TY');

CALL sum_avg_n(10);
CALL sum_avg_n(50);
