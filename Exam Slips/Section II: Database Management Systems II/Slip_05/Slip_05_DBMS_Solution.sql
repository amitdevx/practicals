-- Slip 05: Student-Competition Database
-- Q2.1 OptionA: Function with cursor to accept year and class, display student name, competition name, rank
-- Q2.1 OptionB: Trigger before update on competition - raise notice "competition record is being updated"
-- Q2.2: Procedure max and min from three numbers

-- ============================================================
-- Table Creation
-- ============================================================

DROP TABLE IF EXISTS student_competition CASCADE;
DROP TABLE IF EXISTS Student CASCADE;
DROP TABLE IF EXISTS Competition CASCADE;

CREATE TABLE Student (
    sreg_no INT PRIMARY KEY,
    s_name  VARCHAR(20),
    s_class CHAR(10)
);

CREATE TABLE Competition (
    c_no   INT PRIMARY KEY,
    c_name VARCHAR(20),
    c_type CHAR(10) NOT NULL CHECK (c_type IN ('sport', 'academic'))
);

CREATE TABLE student_competition (
    sreg_no INT REFERENCES Student(sreg_no),
    c_no    INT REFERENCES Competition(c_no),
    rank    INT,
    year    INT,
    PRIMARY KEY (sreg_no, c_no)
);

-- ============================================================
-- Sample Data
-- ============================================================

INSERT INTO Student VALUES (1, 'Amit', 'SY');
INSERT INTO Student VALUES (2, 'Neha', 'TY');
INSERT INTO Student VALUES (3, 'Rahul', 'SY');
INSERT INTO Student VALUES (4, 'Priya', 'TY');

INSERT INTO Competition VALUES (101, 'Cricket', 'sport');
INSERT INTO Competition VALUES (102, 'Quiz', 'academic');
INSERT INTO Competition VALUES (103, 'Chess', 'sport');

INSERT INTO student_competition VALUES (1, 101, 1, 2023);
INSERT INTO student_competition VALUES (2, 102, 2, 2023);
INSERT INTO student_competition VALUES (3, 103, 1, 2024);
INSERT INTO student_competition VALUES (4, 101, 3, 2024);
INSERT INTO student_competition VALUES (1, 102, 2, 2024);

-- ============================================================
-- Q2.1 Option A: Function with cursor - accept year and class, display details
-- ============================================================

CREATE OR REPLACE FUNCTION get_competition_details(p_year INT, p_class CHAR)
RETURNS VOID AS $$
DECLARE
    cur CURSOR FOR
        SELECT s.s_name, c.c_name, sc.rank
        FROM student_competition sc
        JOIN Student s ON s.sreg_no = sc.sreg_no
        JOIN Competition c ON c.c_no = sc.c_no
        WHERE sc.year = p_year AND TRIM(s.s_class) = TRIM(p_class);
    rec RECORD;
    v_found BOOLEAN := FALSE;
BEGIN
    OPEN cur;
    LOOP
        FETCH cur INTO rec;
        EXIT WHEN NOT FOUND;
        v_found := TRUE;
        RAISE NOTICE 'Student: %, Competition: %, Rank: %', TRIM(rec.s_name), TRIM(rec.c_name), rec.rank;
    END LOOP;
    CLOSE cur;

    IF NOT v_found THEN
        RAISE NOTICE 'No records found for year % and class %', p_year, TRIM(p_class);
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Test: SELECT get_competition_details(2024, 'SY');

-- ============================================================
-- Q2.1 Option B: Trigger before update on competition
-- ============================================================

CREATE OR REPLACE FUNCTION notify_competition_update()
RETURNS TRIGGER AS $$
BEGIN
    RAISE NOTICE 'competition record is being updated';
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_competition_update
BEFORE UPDATE ON Competition
FOR EACH ROW
EXECUTE FUNCTION notify_competition_update();

-- Test: UPDATE Competition SET c_name = 'Football' WHERE c_no = 101;

-- ============================================================
-- Q2.2: Procedure max and min from three numbers
-- ============================================================

CREATE OR REPLACE PROCEDURE find_max_min_three(a NUMERIC, b NUMERIC, c NUMERIC)
AS $$
DECLARE
    v_max NUMERIC;
    v_min NUMERIC;
BEGIN
    v_max := a;
    v_min := a;

    IF b > v_max THEN v_max := b; END IF;
    IF c > v_max THEN v_max := c; END IF;

    IF b < v_min THEN v_min := b; END IF;
    IF c < v_min THEN v_min := c; END IF;

    RAISE NOTICE 'Numbers: %, %, %', a, b, c;
    RAISE NOTICE 'Maximum: %', v_max;
    RAISE NOTICE 'Minimum: %', v_min;
END;
$$ LANGUAGE plpgsql;

-- Test: CALL find_max_min_three(15, 7, 23);
