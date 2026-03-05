/*
  SLIP 11
  Schema: Student(rollno int PK, s_name varchar(30), class varchar(10)),
          Subject(scode varchar(10) PK, subject_name varchar(20)),
          student_subject(rollno, scode, marks int) M:M
  Q2.1A: Cursor function calc total marks per student and display.
  Q2.1B: Trigger before delete on student - "student record is being deleted".
  Q2.2:  Procedure sum and avg of first n numbers using while.
*/

-- Schema
DROP TABLE IF EXISTS student_subject CASCADE;
DROP TABLE IF EXISTS Student CASCADE;
DROP TABLE IF EXISTS Subject CASCADE;

CREATE TABLE Student (
    rollno INT PRIMARY KEY,
    s_name VARCHAR(30) NOT NULL,
    class VARCHAR(10)
);

CREATE TABLE Subject (
    scode VARCHAR(10) PRIMARY KEY,
    subject_name VARCHAR(20) NOT NULL
);

CREATE TABLE student_subject (
    rollno INT REFERENCES Student(rollno) ON DELETE CASCADE,
    scode VARCHAR(10) REFERENCES Subject(scode) ON DELETE CASCADE,
    marks INT CHECK (marks >= 0 AND marks <= 100),
    PRIMARY KEY (rollno, scode)
);

-- Sample Data
INSERT INTO Student VALUES (1, 'Amit', 'SY'), (2, 'Neha', 'TY'), (3, 'Raj', 'SY');
INSERT INTO Subject VALUES ('CS101', 'DBMS'), ('CS102', 'DS'), ('CS103', 'OS');
INSERT INTO student_subject VALUES
    (1, 'CS101', 85), (1, 'CS102', 90), (1, 'CS103', 78),
    (2, 'CS101', 72), (2, 'CS102', 88),
    (3, 'CS101', 65), (3, 'CS103', 70);

-- Q2.1 Option A: Cursor function to calc total marks per student
CREATE OR REPLACE FUNCTION calc_total_marks()
RETURNS VOID AS $$
DECLARE
    rec RECORD;
    cur CURSOR FOR
        SELECT s.rollno, s.s_name, COALESCE(SUM(ss.marks), 0) AS total_marks
        FROM Student s
        LEFT JOIN student_subject ss ON s.rollno = ss.rollno
        GROUP BY s.rollno, s.s_name
        ORDER BY s.rollno;
BEGIN
    OPEN cur;
    LOOP
        FETCH cur INTO rec;
        EXIT WHEN NOT FOUND;
        RAISE NOTICE 'Roll No: %, Name: %, Total Marks: %', rec.rollno, rec.s_name, rec.total_marks;
    END LOOP;
    CLOSE cur;
END;
$$ LANGUAGE plpgsql;

-- Q2.1 Option B: Trigger before delete on student
CREATE OR REPLACE FUNCTION fn_before_delete_student()
RETURNS TRIGGER AS $$
BEGIN
    RAISE NOTICE 'Student record is being deleted: Roll No %, Name %', OLD.rollno, OLD.s_name;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS trg_before_delete_student ON Student;
CREATE TRIGGER trg_before_delete_student
    BEFORE DELETE ON Student
    FOR EACH ROW
    EXECUTE FUNCTION fn_before_delete_student();

-- Q2.2: Procedure sum and avg of first n numbers using while
CREATE OR REPLACE PROCEDURE sp_sum_avg_n(p_n INT)
LANGUAGE plpgsql AS $$
DECLARE
    v_sum INT := 0;
    v_avg NUMERIC;
    v_i INT := 1;
BEGIN
    IF p_n <= 0 THEN
        RAISE EXCEPTION 'n must be positive';
    END IF;

    WHILE v_i <= p_n LOOP
        v_sum := v_sum + v_i;
        v_i := v_i + 1;
    END LOOP;

    v_avg := v_sum::NUMERIC / p_n;
    RAISE NOTICE 'Sum of first % numbers = %', p_n, v_sum;
    RAISE NOTICE 'Average of first % numbers = %', p_n, ROUND(v_avg, 2);
END;
$$;

-- Test Calls
SELECT calc_total_marks();
DELETE FROM Student WHERE rollno = 3;
CALL sp_sum_avg_n(10);
