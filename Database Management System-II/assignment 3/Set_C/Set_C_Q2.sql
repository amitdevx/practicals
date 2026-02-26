-- ============================================================
-- Assignment 3: Cursors
-- Set C - Question 2
-- ============================================================
-- Q2. Write a cursor to display the names of persons living
--     in urban area.
-- ============================================================

-- Drop existing tables
DROP TABLE IF EXISTS person CASCADE;
DROP TABLE IF EXISTS area CASCADE;

-- Create tables
CREATE TABLE area (
    aid        INT PRIMARY KEY,
    aname      VARCHAR(20) NOT NULL,
    area_type  VARCHAR(5) NOT NULL
);

CREATE TABLE person (
    pno        INT PRIMARY KEY,
    name       VARCHAR(20) NOT NULL,
    birthdate  DATE NOT NULL,
    income     NUMERIC(10,2) NOT NULL,
    aid        INT REFERENCES area(aid)
);

-- Insert sample data into area
INSERT INTO area VALUES (1, 'Kothrud', 'Urban');
INSERT INTO area VALUES (2, 'Baramati', 'Rural');
INSERT INTO area VALUES (3, 'Deccan', 'Urban');
INSERT INTO area VALUES (4, 'Junnar', 'Rural');
INSERT INTO area VALUES (5, 'Viman Nagar', 'Urban');

-- Insert sample data into person
INSERT INTO person VALUES (1, 'Amit', '1998-03-15', 75000.00, 1);
INSERT INTO person VALUES (2, 'Sneha', '1997-06-22', 45000.00, 2);
INSERT INTO person VALUES (3, 'Rahul', '1999-03-08', 120000.00, 3);
INSERT INTO person VALUES (4, 'Priya', '2000-11-30', 55000.00, 4);
INSERT INTO person VALUES (5, 'Vijay', '1996-03-25', 90000.00, 5);
INSERT INTO person VALUES (6, 'Anjali', '1998-06-10', 62000.00, 1);
INSERT INTO person VALUES (7, 'Suresh', '1995-09-18', 30000.00, 3);
INSERT INTO person VALUES (8, 'Megha', '2001-12-05', 85000.00, 2);

-- Stored function using cursor
CREATE OR REPLACE FUNCTION get_persons_in_urban_area()
RETURNS VOID AS $$
DECLARE
    cur_urban CURSOR FOR
        SELECT p.pno, p.name, a.aname
        FROM person p
        JOIN area a ON p.aid = a.aid
        WHERE a.area_type = 'Urban';
    rec RECORD;
BEGIN
    RAISE NOTICE '--- Persons Living in Urban Areas ---';
    OPEN cur_urban;
    LOOP
        FETCH cur_urban INTO rec;
        EXIT WHEN NOT FOUND;
        RAISE NOTICE 'PNo: %, Name: %, Area: %',
            rec.pno, rec.name, rec.aname;
    END LOOP;
    CLOSE cur_urban;
END;
$$ LANGUAGE plpgsql;

-- Test
SELECT get_persons_in_urban_area();
