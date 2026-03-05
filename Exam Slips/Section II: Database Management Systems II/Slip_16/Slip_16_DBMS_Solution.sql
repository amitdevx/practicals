/*
  SLIP 16
  Schema: Student(rollno int PK, name varchar(30), address varchar(50), class varchar(10)),
          Subject(scode varchar(10) PK, subject_name varchar(20)),
          student_subject(rollno, scode, marks_scored int) M:M
  Q2.1A: Trigger before delete on student - "student record is being deleted".
  Q2.1B: Cursor function calc total marks.
  Q2.2:  Procedure check positive/negative.
*/

-- Schema
DROP TABLE IF EXISTS student_subject CASCADE;
DROP TABLE IF EXISTS Student CASCADE;
DROP TABLE IF EXISTS Subject CASCADE;

CREATE TABLE Student (
    rollno INT PRIMARY KEY,
    name VARCHAR(30) NOT NULL,
    address VARCHAR(50),
    class VARCHAR(10)
);

CREATE TABLE Subject (
    scode VARCHAR(10) PRIMARY KEY,
    subject_name VARCHAR(20) NOT NULL
);

CREATE TABLE student_subject (
    rollno INT REFERENCES Student(rollno) ON DELETE CASCADE,
    scode VARCHAR(10) REFERENCES Subject(scode) ON DELETE CASCADE,
    marks_scored INT CHECK (marks_scored >= 0 AND marks_scored <= 100),
    PRIMARY KEY (rollno, scode)
);

-- Sample Data
INSERT INTO Student VALUES (1, 'Amit', 'Pune', 'SY'), (2, 'Neha', 'Mumbai', 'TY'), (3, 'Raj', 'Nashik', 'SY');
INSERT INTO Subject VALUES ('CS101', 'DBMS'), ('CS102', 'DS'), ('CS103', 'OS');
INSERT INTO student_subject VALUES
    (1, 'CS101', 85), (1, 'CS102', 90), (1, 'CS103', 78),
    (2, 'CS101', 72), (2, 'CS102', 88),
    (3, 'CS101', 65), (3, 'CS103', 70);

-- Q2.1 Option A: Trigger before delete on student
CREATE OR REPLACE FUNCTION fn_before_delete_student()
RETURNS TRIGGER AS $$
BEGIN
    RAISE NOTICE 'Student record is being deleted: Roll No %, Name %', OLD.rollno, OLD.name;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS trg_before_delete_student ON Student;
CREATE TRIGGER trg_before_delete_student
    BEFORE DELETE ON Student
    FOR EACH ROW
    EXECUTE FUNCTION fn_before_delete_student();

-- Q2.1 Option B: Cursor function calc total marks per student
CREATE OR REPLACE FUNCTION calc_total_marks()
RETURNS VOID AS $$
DECLARE
    rec RECORD;
    cur CURSOR FOR
        SELECT s.rollno, s.name, COALESCE(SUM(ss.marks_scored), 0) AS total_marks
        FROM Student s
        LEFT JOIN student_subject ss ON s.rollno = ss.rollno
        GROUP BY s.rollno, s.name
        ORDER BY s.rollno;
BEGIN
    OPEN cur;
    LOOP
        FETCH cur INTO rec;
        EXIT WHEN NOT FOUND;
        RAISE NOTICE 'Roll No: %, Name: %, Total Marks: %', rec.rollno, rec.name, rec.total_marks;
    END LOOP;
    CLOSE cur;
END;
$$ LANGUAGE plpgsql;

-- Q2.2: Procedure check positive/negative
CREATE OR REPLACE PROCEDURE sp_check_sign(p_num NUMERIC)
LANGUAGE plpgsql AS $$
BEGIN
    IF p_num > 0 THEN
        RAISE NOTICE '% is Positive', p_num;
    ELSIF p_num < 0 THEN
        RAISE NOTICE '% is Negative', p_num;
    ELSE
        RAISE NOTICE '% is Zero', p_num;
    END IF;
END;
$$;

-- Test Calls
DELETE FROM Student WHERE rollno = 3;
SELECT calc_total_marks();
CALL sp_check_sign(25);
CALL sp_check_sign(-10);
CALL sp_check_sign(0);
