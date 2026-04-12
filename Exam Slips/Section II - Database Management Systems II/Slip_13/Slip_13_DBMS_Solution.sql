-- ============================================================
-- Slip 13: Bus-Route-Driver Database
-- Section II: Database Management Systems-II [15 Marks]
-- ============================================================

/*
DATABASE SCHEMA: Bus-Route-Driver Database

Tables:
  1. BUS (bus_no, capacity, depot_name)
     - bus_no: INT, Primary Key
     - capacity: INT, NOT NULL - Bus capacity
     - depot_name: VARCHAR(20), Depot name
     - route_no: INT, Foreign Key -> ROUTE(route_no)

  2. ROUTE (route_no, source, destination, no_of_stations)
     - route_no: INT, Primary Key
     - source: CHAR(20), Source location
     - destination: CHAR(20), Destination location
     - no_of_stations: INT, Number of stations

  3. DRIVER (driver_no, driver_name, license_no, address, d_age, salary)
     - driver_no: INT, Primary Key
     - driver_name: CHAR(20), Driver name
     - license_no: INT, UNIQUE - License number
     - address: CHAR(20), Driver address
     - d_age: INT, Driver age
     - salary: FLOAT, Driver salary

  4. bus_driver (bus_no, driver_no, duty_date, shift) - Junction Table
     - bus_no: INT, Foreign Key -> BUS(bus_no)
     - driver_no: INT, Foreign Key -> DRIVER(driver_no)
     - duty_date: DATE, Date of duty allotted
     - shift: INT, CHECK (1 for Morning, 2 for Evening)
     - PRIMARY KEY (bus_no, driver_no, duty_date, shift)

Relationships:
  - BUS_ROUTE: M-1 (Many buses to one route)
  - BUS_DRIVER: M-M with descriptive attributes Date of duty allotted and
                Shift (1 for Morning, 2 for Evening)

Constraints:
  - License no is unique
  - Bus capacity is not null
*/

-- ============================================================
-- Database Setup
-- ============================================================

DROP DATABASE IF EXISTS slip_13_db;
CREATE DATABASE slip_13_db;
\c slip_13_db

-- ============================================================
-- Table Creation
-- ============================================================

DROP TABLE IF EXISTS bus_driver CASCADE;
DROP TABLE IF EXISTS BUS CASCADE;
DROP TABLE IF EXISTS ROUTE CASCADE;
DROP TABLE IF EXISTS DRIVER CASCADE;

CREATE TABLE ROUTE (
    route_no INT PRIMARY KEY,
    source CHAR(20),
    destination CHAR(20),
    no_of_stations INT
);

CREATE TABLE BUS (
    bus_no INT PRIMARY KEY,
    capacity INT NOT NULL,
    depot_name VARCHAR(20),
    route_no INT REFERENCES ROUTE(route_no) ON DELETE SET NULL
);

CREATE TABLE DRIVER (
    driver_no INT PRIMARY KEY,
    driver_name CHAR(20) NOT NULL,
    license_no INT UNIQUE,
    address CHAR(20),
    d_age INT,
    salary FLOAT
);

CREATE TABLE bus_driver (
    bus_no INT REFERENCES BUS(bus_no) ON DELETE CASCADE,
    driver_no INT REFERENCES DRIVER(driver_no) ON DELETE CASCADE,
    duty_date DATE,
    shift INT CHECK (shift IN (1, 2)),
    PRIMARY KEY (bus_no, driver_no, duty_date, shift)
);

-- ============================================================
-- Sample Data
-- ============================================================

INSERT INTO ROUTE VALUES (1, 'Pune', 'Mumbai', 15), (2, 'Pune', 'Nashik', 10);
INSERT INTO BUS VALUES (101, 50, 'Swargate', 1), (102, 40, 'Shivajinagar', 2);
INSERT INTO DRIVER VALUES (1, 'Suresh', 5001, 'Pune', 35, 25000),
    (2, 'Ramesh', 5002, 'Mumbai', 42, 28000), (3, 'Ganesh', 5003, 'Nashik', 28, 22000);
INSERT INTO bus_driver VALUES
    (101, 1, '2024-01-15', 1), (101, 2, '2024-01-15', 2),
    (102, 3, '2024-01-15', 1), (101, 3, '2024-01-16', 1);

-- ============================================================
-- Q2.1 Option A: Define a trigger before insert the record of driver if the age is not between 18 and 50, raise an error message "invalid entry". [10 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION fn_check_driver_age()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.d_age < 18 OR NEW.d_age > 50 THEN
        RAISE EXCEPTION 'Driver age must be between 18 and 50. Given: %', NEW.d_age;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS trg_check_driver_age ON DRIVER;
CREATE TRIGGER trg_check_driver_age
    BEFORE INSERT ON DRIVER
    FOR EACH ROW
    EXECUTE FUNCTION fn_check_driver_age();

-- Execute: INSERT INTO DRIVER VALUES (4, 'Mohan', 5004, 'Pune', 55, 20000);  -- Should fail (age > 50)
-- Execute: INSERT INTO DRIVER VALUES (4, 'Mohan', 5004, 'Pune', 30, 20000);  -- Should succeed

-- ============================================================
-- Q2.1 Option B (OR): Write a stored function to accept the bus_no and date and print its allotted drivers. Raise an exception in case of invalid bus number. [10 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION get_bus_drivers(p_bus_no INT, p_date DATE)
RETURNS VOID AS $$
DECLARE
    rec RECORD;
    v_found BOOLEAN := FALSE;
BEGIN
    IF NOT EXISTS (SELECT 1 FROM BUS WHERE bus_no = p_bus_no) THEN
        RAISE EXCEPTION 'Invalid bus number: %', p_bus_no;
    END IF;

    RAISE NOTICE 'Drivers allotted to Bus % on %:', p_bus_no, p_date;
    FOR rec IN
        SELECT TRIM(d.driver_name) AS dname, bd.shift
        FROM DRIVER d
        JOIN bus_driver bd ON d.driver_no = bd.driver_no
        WHERE bd.bus_no = p_bus_no AND bd.duty_date = p_date
        ORDER BY bd.shift
    LOOP
        RAISE NOTICE '  Driver: %, Shift: %', rec.dname, rec.shift;
        v_found := TRUE;
    END LOOP;

    IF NOT v_found THEN
        RAISE NOTICE 'No drivers allotted for this bus on the given date.';
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Execute: SELECT get_bus_drivers(101, '2024-01-15');
-- Execute: SELECT get_bus_drivers(999, '2024-01-15');  -- Should raise exception (invalid bus)

-- ============================================================
-- Q2.2: Write a procedure to search the given number is in given range. [5 Marks]
-- ============================================================

CREATE OR REPLACE PROCEDURE sp_check_range(p_num INT, p_low INT, p_high INT)
LANGUAGE plpgsql AS $$
BEGIN
    IF p_num >= p_low AND p_num <= p_high THEN
        RAISE NOTICE '% is within the range [%, %]', p_num, p_low, p_high;
    ELSE
        RAISE NOTICE '% is NOT within the range [%, %]', p_num, p_low, p_high;
    END IF;
END;
$$;

-- Execute: CALL sp_check_range(15, 10, 20);
-- Execute: CALL sp_check_range(5, 10, 20);
