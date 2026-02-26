-- ============================================================
-- Assignment 3: Cursors
-- Set E - Question 2
-- ============================================================
-- Q2. Write a cursor which accepts the driver name and prints
--     the details of all cars that this driver has driven, if
--     the driver name is invalid, print an appropriate message.
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
CREATE OR REPLACE FUNCTION get_cars_by_driver(p_driver_name VARCHAR)
RETURNS VOID AS $$
DECLARE
    cur_cars CURSOR FOR
        SELECT c.c_no, c.owner, c.model, c.color
        FROM car c
        JOIN car_driver cd ON c.c_no = cd.c_no
        JOIN driver d ON cd.driver_no = d.driver_no
        WHERE d.driver_name = p_driver_name;
    rec RECORD;
    v_count INT;
BEGIN
    -- Check if driver exists
    SELECT COUNT(*) INTO v_count FROM driver WHERE driver_name = p_driver_name;
    IF v_count = 0 THEN
        RAISE NOTICE 'Error: Driver "%" not found. Please enter a valid driver name.', p_driver_name;
        RETURN;
    END IF;

    RAISE NOTICE '--- Cars Driven by: % ---', p_driver_name;
    OPEN cur_cars;
    LOOP
        FETCH cur_cars INTO rec;
        EXIT WHEN NOT FOUND;
        RAISE NOTICE 'Car No: %, Owner: %, Model: %, Color: %',
            rec.c_no, rec.owner, rec.model, rec.color;
    END LOOP;
    CLOSE cur_cars;
END;
$$ LANGUAGE plpgsql;

-- Test
SELECT get_cars_by_driver('Ramesh');
SELECT get_cars_by_driver('Dinesh');
SELECT get_cars_by_driver('InvalidName');
