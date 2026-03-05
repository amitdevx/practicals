/*
SLIP 29 - SECTION II: DATABASE MANAGEMENT SYSTEMS II

Person(pno int PK, pname varchar(20), birthdate date, income numeric)
Area(aid int PK, aname varchar(20), area_type varchar(5) CHECK IN ('urban','rural'))
Person and Area are related with many to one relationship (p.aid FK).

Q2.1A: Cursor to display persons in urban area.
Q2.1B: Trigger before delete on person - display "person record is being deleted".
Q2.2: Procedure for subtraction of three numbers.
*/

-- Table Creation
DROP TABLE IF EXISTS Person CASCADE;
DROP TABLE IF EXISTS Area CASCADE;

CREATE TABLE Area (
    aid INT PRIMARY KEY,
    aname VARCHAR(20),
    area_type VARCHAR(5) CHECK (area_type IN ('urban', 'rural'))
);

CREATE TABLE Person (
    pno INT PRIMARY KEY,
    pname VARCHAR(20),
    birthdate DATE,
    income NUMERIC,
    aid INT REFERENCES Area(aid)
);

-- Sample Data
INSERT INTO Area VALUES (1, 'Kothrud', 'urban');
INSERT INTO Area VALUES (2, 'Baramati', 'rural');
INSERT INTO Area VALUES (3, 'Deccan', 'urban');
INSERT INTO Area VALUES (4, 'Shirur', 'rural');

INSERT INTO Person VALUES (1, 'Amit', '1995-05-15', 50000, 1);
INSERT INTO Person VALUES (2, 'Sneha', '1998-08-20', 35000, 2);
INSERT INTO Person VALUES (3, 'Rahul', '1992-12-10', 60000, 3);
INSERT INTO Person VALUES (4, 'Priya', '2000-03-25', 28000, 4);
INSERT INTO Person VALUES (5, 'Kiran', '1996-07-30', 45000, 1);

-- Q2.1A: Cursor to display persons in urban area
CREATE OR REPLACE FUNCTION display_urban_persons()
RETURNS VOID AS $$
DECLARE
    v_rec RECORD;
    v_found BOOLEAN := FALSE;
    cur_persons CURSOR FOR
        SELECT p.pno, p.pname, p.birthdate, p.income, a.aname
        FROM Person p JOIN Area a ON p.aid = a.aid
        WHERE a.area_type = 'urban';
BEGIN
    OPEN cur_persons;
    LOOP
        FETCH cur_persons INTO v_rec;
        EXIT WHEN NOT FOUND;
        v_found := TRUE;
        RAISE NOTICE 'Pno: %, Name: %, Birthdate: %, Income: %, Area: %',
            v_rec.pno, v_rec.pname, v_rec.birthdate, v_rec.income, v_rec.aname;
    END LOOP;
    CLOSE cur_persons;

    IF NOT v_found THEN
        RAISE NOTICE 'No persons found in urban areas';
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Q2.1B: Trigger before delete on person - display message
CREATE OR REPLACE FUNCTION trg_before_delete_person()
RETURNS TRIGGER AS $$
BEGIN
    RAISE NOTICE 'Person record is being deleted: % (pno: %)', OLD.pname, OLD.pno;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_person_delete
BEFORE DELETE ON Person
FOR EACH ROW EXECUTE FUNCTION trg_before_delete_person();

-- Q2.2: Procedure for subtraction of three numbers
CREATE OR REPLACE PROCEDURE subtract_three(p_a NUMERIC, p_b NUMERIC, p_c NUMERIC)
LANGUAGE plpgsql AS $$
DECLARE
    v_result NUMERIC;
BEGIN
    v_result := p_a - p_b - p_c;
    RAISE NOTICE '% - % - % = %', p_a, p_b, p_c, v_result;
END;
$$;

-- Test Calls
SELECT display_urban_persons();

-- Test trigger
-- DELETE FROM Person WHERE pno = 1;

CALL subtract_three(100, 30, 20);
CALL subtract_three(50, 10, 5);
