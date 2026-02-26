-- ============================================================
-- Assignment 4: Handling Errors and Exceptions
-- Set D - Question 3
-- ============================================================
-- Q3. Write a stored function to display teacher details who
--     have a given qualification (Accept teacher's qualification
--     as input parameter). Raise an exception for invalid
--     qualification.
-- ============================================================

-- ==================== Table Creation ====================

DROP TABLE IF EXISTS student_teacher CASCADE;
DROP TABLE IF EXISTS Teacher CASCADE;
DROP TABLE IF EXISTS Student CASCADE;

CREATE TABLE Student (
    sno      INT PRIMARY KEY,
    s_name   CHAR(30) NOT NULL,
    s_class  CHAR(10),
    s_addr   CHAR(50)
);

CREATE TABLE Teacher (
    tno            INT PRIMARY KEY,
    t_name         CHAR(20) NOT NULL,
    qualification  CHAR(15),
    experience     INT
);

CREATE TABLE student_teacher (
    sno      INT REFERENCES Student(sno),
    tno      INT REFERENCES Teacher(tno),
    subject  VARCHAR(20),
    PRIMARY KEY (sno, tno)
);

-- ==================== Sample Data ====================

INSERT INTO Student VALUES (1, 'Amit',   'SE-A',  'Pune');
INSERT INTO Student VALUES (2, 'Priya',  'TE-B',  'Mumbai');
INSERT INTO Student VALUES (3, 'Rahul',  'BE-A',  'Nagpur');
INSERT INTO Student VALUES (4, 'Sneha',  'SE-B',  'Pune');
INSERT INTO Student VALUES (5, 'Vikram', 'TE-A',  'Mumbai');

INSERT INTO Teacher VALUES (101, 'Dr. Sharma',  'PhD',     10);
INSERT INTO Teacher VALUES (102, 'Prof. Gupta', 'MTech',    8);
INSERT INTO Teacher VALUES (103, 'Dr. Patel',   'PhD',     15);
INSERT INTO Teacher VALUES (104, 'Prof. Singh', 'MSc',      5);
INSERT INTO Teacher VALUES (105, 'Dr. Mehta',   'PhD',     12);

INSERT INTO student_teacher VALUES (1, 101, 'DBMS');
INSERT INTO student_teacher VALUES (1, 102, 'OS');
INSERT INTO student_teacher VALUES (1, 103, 'CN');
INSERT INTO student_teacher VALUES (2, 101, 'DBMS');
INSERT INTO student_teacher VALUES (2, 104, 'Maths');
INSERT INTO student_teacher VALUES (3, 103, 'CN');
INSERT INTO student_teacher VALUES (4, 102, 'OS');
INSERT INTO student_teacher VALUES (4, 105, 'AI');
INSERT INTO student_teacher VALUES (5, 101, 'DBMS');
INSERT INTO student_teacher VALUES (5, 103, 'CN');
INSERT INTO student_teacher VALUES (5, 105, 'AI');

-- ==================== Function ====================

CREATE OR REPLACE FUNCTION get_teachers_by_qualification(p_qual VARCHAR)
RETURNS VOID AS $$
DECLARE
    v_count  INT := 0;
    rec      RECORD;
BEGIN
    -- Check if any teacher has the given qualification
    SELECT COUNT(*) INTO v_count
    FROM Teacher
    WHERE LOWER(TRIM(qualification)) = LOWER(TRIM(p_qual));

    IF v_count = 0 THEN
        RAISE EXCEPTION 'Invalid qualification: "%" does not exist.', p_qual;
    END IF;

    RAISE NOTICE '--- Teachers with qualification: % ---', TRIM(p_qual);

    FOR rec IN
        SELECT tno, TRIM(t_name) AS t_name, TRIM(qualification) AS qualification, experience
        FROM Teacher
        WHERE LOWER(TRIM(qualification)) = LOWER(TRIM(p_qual))
    LOOP
        RAISE NOTICE 'Tno: %, Name: %, Qualification: %, Experience: % years',
            rec.tno, rec.t_name, rec.qualification, rec.experience;
    END LOOP;

    RAISE NOTICE '--- Total teachers found: % ---', v_count;

EXCEPTION
    WHEN OTHERS THEN
        RAISE NOTICE 'Error: %', SQLERRM;
END;
$$ LANGUAGE plpgsql;

-- ==================== Test Calls ====================

-- Valid qualification
SELECT get_teachers_by_qualification('PhD');

-- Valid qualification (different)
SELECT get_teachers_by_qualification('MTech');

-- Valid qualification (case-insensitive)
SELECT get_teachers_by_qualification('msc');

-- Invalid qualification (should raise exception)
SELECT get_teachers_by_qualification('BCA');

-- Invalid qualification (should raise exception)
SELECT get_teachers_by_qualification('MBA');
