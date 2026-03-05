-- Slip 03: Student-Teacher Database
-- Q2.1 OptionA: Cursor - accept student number, display student name + teacher name who taught 'RDBMS'
-- Q2.1 OptionB: Trigger before insert on student - if s_no<=0 give "Invalid Number"
-- Q2.2: Procedure min and max from two numbers

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
-- Q2.1 Option A: Cursor - accept student number, display student + teacher for 'RDBMS'
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

-- Test: SELECT get_rdbms_teacher(1);

-- ============================================================
-- Q2.1 Option B: Trigger before insert on student - if s_no<=0 give "Invalid Number"
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

-- Test: INSERT INTO Student VALUES (-1, 'Test', 'Test', 'SY');

-- ============================================================
-- Q2.2: Procedure min and max from two numbers
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

-- Test: CALL find_min_max(10, 25);
