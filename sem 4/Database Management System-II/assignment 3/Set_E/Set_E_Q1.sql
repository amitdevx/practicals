-- ============================================================
-- Assignment 3: Cursors
-- Set E - Question 1
-- ============================================================
-- Q1. Write a stored function with cursor which accepts the
--     color and prints the names of all owners who own a car
--     of that color.
-- ============================================================

-- Drop existing tables
DROP TABLE IF EXISTS car_driver CASCADE;
DROP TABLE IF EXISTS car CASCADE;
DROP TABLE IF EXISTS driver CASCADE;

-- Create tables
CREATE TABLE car (
    c_no    INT PRIMARY KEY,
    owner   VARCHAR(20) NOT NULL,
    model   VARCHAR(10) NOT NULL,
    color   VARCHAR(10) NOT NULL
);

CREATE TABLE driver (
    driver_no    INT PRIMARY KEY,
    driver_name  VARCHAR(20) NOT NULL,
    license_no   INT NOT NULL,
    d_age        INT NOT NULL,
    salary       FLOAT NOT NULL
);

CREATE TABLE car_driver (
    c_no       INT REFERENCES car(c_no),
    driver_no  INT REFERENCES driver(driver_no),
    PRIMARY KEY (c_no, driver_no)
);

-- Insert sample data into car
INSERT INTO car VALUES (1, 'Amit', 'Swift', 'Red');
INSERT INTO car VALUES (2, 'Sneha', 'i20', 'White');
INSERT INTO car VALUES (3, 'Rahul', 'City', 'Red');
INSERT INTO car VALUES (4, 'Priya', 'Creta', 'Black');
INSERT INTO car VALUES (5, 'Vijay', 'Polo', 'White');
INSERT INTO car VALUES (6, 'Anjali', 'Baleno', 'Red');

-- Insert sample data into driver
INSERT INTO driver VALUES (101, 'Ramesh', 5001, 30, 25000.00);
INSERT INTO driver VALUES (102, 'Suresh', 5002, 35, 28000.00);
INSERT INTO driver VALUES (103, 'Mahesh', 5003, 28, 22000.00);
INSERT INTO driver VALUES (104, 'Ganesh', 5004, 40, 30000.00);
INSERT INTO driver VALUES (105, 'Dinesh', 5005, 32, 26000.00);

-- Insert sample data into car_driver
INSERT INTO car_driver VALUES (1, 101);
INSERT INTO car_driver VALUES (2, 102);
INSERT INTO car_driver VALUES (3, 103);
INSERT INTO car_driver VALUES (4, 104);
INSERT INTO car_driver VALUES (5, 105);
INSERT INTO car_driver VALUES (1, 102);
INSERT INTO car_driver VALUES (3, 101);
INSERT INTO car_driver VALUES (6, 105);

-- Stored function using cursor
CREATE OR REPLACE FUNCTION get_owners_by_color(p_color VARCHAR)
RETURNS VOID AS $$
DECLARE
    cur_owners CURSOR FOR
        SELECT DISTINCT c.c_no, c.owner, c.model
        FROM car c
        WHERE c.color = p_color;
    rec RECORD;
BEGIN
    RAISE NOTICE '--- Owners of % Cars ---', p_color;
    OPEN cur_owners;
    LOOP
        FETCH cur_owners INTO rec;
        EXIT WHEN NOT FOUND;
        RAISE NOTICE 'Car No: %, Owner: %, Model: %',
            rec.c_no, rec.owner, rec.model;
    END LOOP;
    CLOSE cur_owners;
END;
$$ LANGUAGE plpgsql;

-- Test
SELECT get_owners_by_color('Red');
SELECT get_owners_by_color('White');
