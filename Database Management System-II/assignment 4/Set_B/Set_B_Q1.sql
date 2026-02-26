-- ============================================================
-- Assignment 4: Handling Errors and Exceptions
-- Set B - Question 1
-- ============================================================
-- Q1. Write a function that accepts area name and displays the
--     details of all persons living in that area. Raise an
--     exception if the area name is invalid.
-- ============================================================

-- ==================== Table Creation ====================

DROP TABLE IF EXISTS Person CASCADE;
DROP TABLE IF EXISTS Area CASCADE;

CREATE TABLE Area (
    aid        INT PRIMARY KEY,
    aname      VARCHAR(20) NOT NULL,
    area_type  VARCHAR(5)
);

CREATE TABLE Person (
    pno        INT PRIMARY KEY,
    name       VARCHAR(20) NOT NULL,
    birthdate  DATE,
    income     NUMERIC(10,2),
    aid        INT REFERENCES Area(aid)
);

-- ==================== Sample Data ====================

INSERT INTO Area VALUES (1, 'Kothrud',    'Urban');
INSERT INTO Area VALUES (2, 'Hadapsar',   'Urban');
INSERT INTO Area VALUES (3, 'Balewadi',   'Urban');
INSERT INTO Area VALUES (4, 'Mulshi',     'Rural');
INSERT INTO Area VALUES (5, 'Hinjewadi',  'Urban');

INSERT INTO Person VALUES (101, 'Amit',    '1995-05-10', 55000.00, 1);
INSERT INTO Person VALUES (102, 'Priya',   '1998-08-22', 42000.00, 1);
INSERT INTO Person VALUES (103, 'Rahul',   '1992-01-15', 68000.00, 2);
INSERT INTO Person VALUES (104, 'Sneha',   '1997-11-30', 35000.00, 3);
INSERT INTO Person VALUES (105, 'Vikram',  '1990-03-18', 72000.00, 2);
INSERT INTO Person VALUES (106, 'Neha',    '1996-07-05', 48000.00, 4);
INSERT INTO Person VALUES (107, 'Rohan',   '1993-09-12', 61000.00, 1);
INSERT INTO Person VALUES (108, 'Kavita',  '1999-02-28', 39000.00, 5);

-- ==================== Function ====================

CREATE OR REPLACE FUNCTION get_persons_by_area(p_aname VARCHAR)
RETURNS VOID AS $$
DECLARE
    v_aid    INT;
    v_count  INT := 0;
    rec      RECORD;
BEGIN
    -- Check if the area exists
    SELECT aid INTO v_aid
    FROM Area
    WHERE LOWER(TRIM(aname)) = LOWER(TRIM(p_aname));

    IF NOT FOUND THEN
        RAISE EXCEPTION 'Invalid area name: "%" does not exist.', p_aname;
    END IF;

    RAISE NOTICE '--- Persons living in area: % ---', TRIM(p_aname);
    RAISE NOTICE 'PNO    | NAME            | BIRTHDATE   | INCOME';
    RAISE NOTICE '-------|-----------------|-------------|----------';

    FOR rec IN
        SELECT p.pno, p.name, p.birthdate, p.income
        FROM Person p
        WHERE p.aid = v_aid
        ORDER BY p.pno
    LOOP
        v_count := v_count + 1;
        RAISE NOTICE '%  | %  | %  | %',
            rec.pno, TRIM(rec.name), rec.birthdate, rec.income;
    END LOOP;

    RAISE NOTICE '-------|-----------------|-------------|----------';
    RAISE NOTICE 'Total persons in %: %', TRIM(p_aname), v_count;

EXCEPTION
    WHEN OTHERS THEN
        RAISE NOTICE 'Error: %', SQLERRM;
END;
$$ LANGUAGE plpgsql;

-- ==================== Test Calls ====================

-- Valid area name (multiple persons)
SELECT get_persons_by_area('Kothrud');

-- Valid area name (single person)
SELECT get_persons_by_area('Mulshi');

-- Invalid area name (should raise exception)
SELECT get_persons_by_area('Wakad');

-- Case-insensitive test
SELECT get_persons_by_area('hadapsar');
