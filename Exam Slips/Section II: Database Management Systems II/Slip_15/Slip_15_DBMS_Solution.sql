/*
  SLIP 15
  Schema: Person(pnumber int PK, pname varchar(20), birthdate date, income numeric),
          Area(aname varchar(20) PK, area_type varchar(5) CHECK IN('urban','rural')),
          Person-Area M:1 (Person.aname FK -> Area)
  Q2.1A: Cursor to update income of urban persons by 10%.
  Q2.1B: Trigger before insert on person - if pnumber negative give "Invalid Number".
  Q2.2:  Procedure display odd numbers 1 to 100.
*/

-- Schema
DROP TABLE IF EXISTS Person CASCADE;
DROP TABLE IF EXISTS Area CASCADE;

CREATE TABLE Area (
    aname VARCHAR(20) PRIMARY KEY,
    area_type VARCHAR(5) CHECK (area_type IN ('urban', 'rural'))
);

CREATE TABLE Person (
    pnumber INT PRIMARY KEY,
    pname VARCHAR(20) NOT NULL,
    birthdate DATE,
    income NUMERIC,
    aname VARCHAR(20) REFERENCES Area(aname) ON DELETE SET NULL
);

-- Sample Data
INSERT INTO Area VALUES ('Koregaon', 'urban'), ('Hadapsar', 'urban'), ('Velhe', 'rural'), ('Mulshi', 'rural');
INSERT INTO Person VALUES
    (1, 'Amit', '1995-05-10', 50000, 'Koregaon'),
    (2, 'Neha', '1998-08-22', 35000, 'Velhe'),
    (3, 'Raj', '1992-01-15', 60000, 'Hadapsar'),
    (4, 'Priya', '2000-12-01', 40000, 'Mulshi'),
    (5, 'Suresh', '1990-07-30', 45000, 'Koregaon');

-- Q2.1 Option A: Cursor to update income of urban persons by 10%
CREATE OR REPLACE FUNCTION update_urban_income()
RETURNS VOID AS $$
DECLARE
    cur CURSOR FOR
        SELECT p.pnumber, p.pname, p.income
        FROM Person p
        JOIN Area a ON p.aname = a.aname
        WHERE a.area_type = 'urban';
    rec RECORD;
BEGIN
    OPEN cur;
    LOOP
        FETCH cur INTO rec;
        EXIT WHEN NOT FOUND;
        UPDATE Person SET income = income * 1.10 WHERE pnumber = rec.pnumber;
        RAISE NOTICE 'Updated %: % -> %', rec.pname, rec.income, ROUND(rec.income * 1.10, 2);
    END LOOP;
    CLOSE cur;
END;
$$ LANGUAGE plpgsql;

-- Q2.1 Option B: Trigger before insert on person - pnumber negative = invalid
CREATE OR REPLACE FUNCTION fn_check_pnumber()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.pnumber < 0 THEN
        RAISE EXCEPTION 'Invalid Number: pnumber cannot be negative (%)' , NEW.pnumber;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS trg_check_pnumber ON Person;
CREATE TRIGGER trg_check_pnumber
    BEFORE INSERT ON Person
    FOR EACH ROW
    EXECUTE FUNCTION fn_check_pnumber();

-- Q2.2: Procedure display odd numbers 1 to 100
CREATE OR REPLACE PROCEDURE sp_odd_1_to_100()
LANGUAGE plpgsql AS $$
DECLARE
    v_i INT;
    v_result TEXT := '';
BEGIN
    FOR v_i IN 1..100 LOOP
        IF v_i % 2 != 0 THEN
            v_result := v_result || v_i || ' ';
        END IF;
    END LOOP;
    RAISE NOTICE 'Odd numbers from 1 to 100: %', TRIM(v_result);
END;
$$;

-- Test Calls
SELECT update_urban_income();
-- This should fail: INSERT INTO Person VALUES (-1, 'Test', '2000-01-01', 10000, 'Koregaon');
CALL sp_odd_1_to_100();
