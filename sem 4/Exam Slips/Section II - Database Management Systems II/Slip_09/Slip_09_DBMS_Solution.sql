-- ============================================================
-- Slip 09: Student-Competition Database
-- Section II: Database Management Systems-II [15 Marks]
-- ============================================================

/*
Consider the following Entities and their Relationships:

STUDENT (sreg_no int, name char(30), class char(10))
COMPETITION (c_no int, name char(20), c_type char(15))

Relationship:
- STUDENT-COMPETITION: M-M with described attributes:
  - rank
  - year
  - prize (int)
*/

-- ============================================================
-- Database Setup
-- ============================================================

DROP DATABASE IF EXISTS slip_09_db;
CREATE DATABASE slip_09_db;
\c slip_09_db

-- ============================================================
-- Table Creation
-- ============================================================

DROP TABLE IF EXISTS student_competition CASCADE;
DROP TABLE IF EXISTS STUDENT CASCADE;
DROP TABLE IF EXISTS COMPETITION CASCADE;

CREATE TABLE STUDENT (
    sreg_no INT PRIMARY KEY,
    name    CHAR(30),
    class   CHAR(10)
);

CREATE TABLE COMPETITION (
    c_no   INT PRIMARY KEY,
    name   CHAR(20),
    c_type CHAR(15)
);

CREATE TABLE student_competition (
    sreg_no INT REFERENCES STUDENT(sreg_no),
    c_no    INT REFERENCES COMPETITION(c_no),
    rank    INT,
    year    INT,
    prize   INT,
    PRIMARY KEY (sreg_no, c_no)
);

-- ============================================================
-- Sample Data
-- ============================================================

INSERT INTO STUDENT VALUES (1, 'Amit', 'SY');
INSERT INTO STUDENT VALUES (2, 'Neha', 'TY');
INSERT INTO STUDENT VALUES (3, 'Rahul', 'SY');

INSERT INTO COMPETITION VALUES (101, 'Cricket', 'sport');
INSERT INTO COMPETITION VALUES (102, 'Quiz', 'academic');
INSERT INTO COMPETITION VALUES (103, 'Chess', 'sport');

INSERT INTO student_competition VALUES (1, 101, 1, 2020, 5000);
INSERT INTO student_competition VALUES (1, 102, 2, 2020, 3000);
INSERT INTO student_competition VALUES (2, 103, 1, 2020, 4000);
INSERT INTO student_competition VALUES (3, 101, 3, 2021, 1000);
INSERT INTO student_competition VALUES (2, 101, 2, 2021, 2000);

-- ============================================================
-- Q2.1 Option A: Define a trigger before updating a competition
-- table. Raise a notice and display message "competition record
-- is being updated". [5 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION notify_competition_update()
RETURNS TRIGGER AS $$
BEGIN
    RAISE NOTICE 'competition record is being updated';
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_competition_update
BEFORE UPDATE ON COMPETITION
FOR EACH ROW
EXECUTE FUNCTION notify_competition_update();

-- Execute: UPDATE COMPETITION SET name = 'Cricket Tournament' WHERE c_no = 101;
-- This will display: "competition record is being updated"

-- ============================================================
-- Q2.1 Option B (OR): Write a function using cursor which
-- accepts a name of student and returns the total no of prizes
-- won by that student in the year 2020. [5 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION total_prizes_2020(p_name CHAR)
RETURNS INT AS $$
DECLARE
    cur CURSOR FOR
        SELECT sc.prize, c.name AS comp_name
        FROM student_competition sc
        JOIN STUDENT s ON s.sreg_no = sc.sreg_no
        JOIN COMPETITION c ON c.c_no = sc.c_no
        WHERE TRIM(s.name) = TRIM(p_name) AND sc.year = 2020;
    rec RECORD;
    v_total INT := 0;
BEGIN
    OPEN cur;
    LOOP
        FETCH cur INTO rec;
        EXIT WHEN NOT FOUND;
        v_total := v_total + COALESCE(rec.prize, 0);
        RAISE NOTICE 'Competition: %, Prize: %', TRIM(rec.comp_name), rec.prize;
    END LOOP;
    CLOSE cur;

    IF v_total = 0 THEN
        RAISE NOTICE 'No prizes found for % in 2020.', TRIM(p_name);
    ELSE
        RAISE NOTICE 'Total prizes for % in 2020: %', TRIM(p_name), v_total;
    END IF;

    RETURN v_total;
END;
$$ LANGUAGE plpgsql;

-- Execute: SELECT total_prizes_2020('Amit');   -- 8000 (5000 + 3000)
-- Execute: SELECT total_prizes_2020('Neha');   -- 4000 (Chess)
-- Execute: SELECT total_prizes_2020('Rahul');  -- 0 (no prizes in 2020)

-- ============================================================
-- Q2.2: Write a procedure to display division of two numbers
-- use raise to display divided by zero exception messages.
-- [5 Marks]
-- ============================================================

CREATE OR REPLACE PROCEDURE divide_numbers(a NUMERIC, b NUMERIC)
AS $$
DECLARE
    v_result NUMERIC;
BEGIN
    IF b = 0 THEN
        RAISE EXCEPTION 'Division by zero error: Cannot divide % by 0.', a;
    END IF;

    v_result := a / b;
    RAISE NOTICE '% / % = %', a, b, v_result;
END;
$$ LANGUAGE plpgsql;

-- Execute: CALL divide_numbers(20, 4);  -- Result: 5
-- Execute: CALL divide_numbers(10, 0);  -- Should raise division by zero exception

