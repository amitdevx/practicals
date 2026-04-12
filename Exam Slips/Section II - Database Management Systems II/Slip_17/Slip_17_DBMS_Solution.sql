-- ============================================================
-- Slip 17: Student-Competition Database
-- Section II: Database Management Systems-II [15 Marks]
-- ============================================================

/*
DATABASE SCHEMA: Student-Competition Database

Tables:
  STUDENT (sreg_no int, name char(30), class char(10))
  COMPETITION (c_no int, name char(20), C_type char(15))
  
Relationship: STUDENT-COMPETITION: M-M with described attributes rank, year
and prize(int).
*/

-- ============================================================
-- Database Setup
-- ============================================================

DROP DATABASE IF EXISTS slip_17_db;
CREATE DATABASE slip_17_db;
\c slip_17_db

-- ============================================================
-- Table Creation
-- ============================================================

DROP TABLE IF EXISTS student_competition CASCADE;
DROP TABLE IF EXISTS STUDENT CASCADE;
DROP TABLE IF EXISTS COMPETITION CASCADE;

CREATE TABLE STUDENT (
    sreg_no INT PRIMARY KEY,
    name CHAR(30) NOT NULL,
    class CHAR(10)
);

CREATE TABLE COMPETITION (
    c_no INT PRIMARY KEY,
    name CHAR(20) NOT NULL,
    c_type CHAR(15)
);

CREATE TABLE student_competition (
    sreg_no INT REFERENCES STUDENT(sreg_no) ON DELETE CASCADE,
    c_no INT REFERENCES COMPETITION(c_no) ON DELETE CASCADE,
    rank INT,
    year INT,
    prize INT,
    PRIMARY KEY (sreg_no, c_no, year)
);

-- ============================================================
-- Sample Data
-- ============================================================

INSERT INTO STUDENT VALUES (1, 'Amit', 'SY'), (2, 'Neha', 'TY'), (3, 'Raj', 'SY');
INSERT INTO COMPETITION VALUES (101, 'Quiz', 'Academic'), (102, 'Debate', 'Cultural'), (103, 'Coding', 'Technical');
INSERT INTO student_competition VALUES
    (1, 101, 1, 2020, 5000), (1, 103, 2, 2020, 3000), (1, 102, 1, 2021, 4000),
    (2, 101, 3, 2020, 1000), (2, 102, 1, 2020, 5000),
    (3, 103, 2, 2021, 3000);

-- ============================================================
-- Q2.1 Option A: Define a trigger before updating a competition table. Raise a notice and display message "competition record is being updated". [10 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION fn_before_update_competition()
RETURNS TRIGGER AS $$
BEGIN
    RAISE NOTICE 'Competition record is being updated: C_No %, Name %', OLD.c_no, TRIM(OLD.name);
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS trg_before_update_competition ON COMPETITION;
CREATE TRIGGER trg_before_update_competition
    BEFORE UPDATE ON COMPETITION
    FOR EACH ROW
    EXECUTE FUNCTION fn_before_update_competition();

-- Execute: UPDATE COMPETITION SET c_type = 'Sports' WHERE c_no = 101;  -- Should show notice

-- ============================================================
-- Q2.1 Option B (OR): Write a function using cursor which accepts a name of student and returns the total no of prizes won by that student in the year 2020. [10 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION get_total_prizes_2020(p_sname VARCHAR)
RETURNS INT AS $$
DECLARE
    v_sreg_no INT;
    v_total INT := 0;
    rec RECORD;
    cur CURSOR FOR
        SELECT sc.prize, TRIM(c.name) AS cname
        FROM student_competition sc
        JOIN COMPETITION c ON sc.c_no = c.c_no
        WHERE sc.sreg_no = v_sreg_no AND sc.year = 2020;
BEGIN
    SELECT sreg_no INTO v_sreg_no FROM STUDENT WHERE TRIM(name) = TRIM(p_sname);
    IF NOT FOUND THEN
        RAISE EXCEPTION 'Student not found: %', p_sname;
    END IF;

    OPEN cur;
    LOOP
        FETCH cur INTO rec;
        EXIT WHEN NOT FOUND;
        v_total := v_total + COALESCE(rec.prize, 0);
        RAISE NOTICE 'Competition: %, Prize: %', rec.cname, rec.prize;
    END LOOP;
    CLOSE cur;

    RAISE NOTICE 'Total prizes for % in 2020: %', TRIM(p_sname), v_total;
    RETURN v_total;
END;
$$ LANGUAGE plpgsql;

-- Execute: SELECT get_total_prizes_2020('Amit');
-- Execute: SELECT get_total_prizes_2020('Unknown');  -- Should raise exception

-- ============================================================
-- Q2.2: Write a procedure to find sum of first 50 numbers (using unconditional loop). [5 Marks]
-- ============================================================

CREATE OR REPLACE PROCEDURE sp_sum_first_50()
LANGUAGE plpgsql AS $$
DECLARE
    v_sum INT := 0;
    v_i INT := 1;
BEGIN
    LOOP
        v_sum := v_sum + v_i;
        v_i := v_i + 1;
        EXIT WHEN v_i > 50;
    END LOOP;
    RAISE NOTICE 'Sum of first 50 numbers = %', v_sum;
END;
$$;

-- Execute: CALL sp_sum_first_50();
