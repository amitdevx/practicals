/*
  SLIP 13
  Schema: BUS(bus_no int PK, capacity int NOT NULL, depot_name varchar(20)),
          ROUTE(route_no int PK, source char(20), destination char(20), no_of_stations int),
          DRIVER(driver_no int PK, driver_name char(20), license_no int UNIQUE, address char(20), d_age int, salary float),
          BUS.route_no FK -> ROUTE,
          bus_driver(bus_no, driver_no, duty_date date, shift int CHECK IN(1,2)) M:M
  Q2.1A: Trigger before insert on driver - age must be between 18 and 50.
  Q2.1B: Function accept bus_no and date, print allotted drivers, raise exception for invalid bus.
  Q2.2:  Procedure check if number is in given range.
*/

-- Schema
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

-- Sample Data
INSERT INTO ROUTE VALUES (1, 'Pune', 'Mumbai', 15), (2, 'Pune', 'Nashik', 10);
INSERT INTO BUS VALUES (101, 50, 'Swargate', 1), (102, 40, 'Shivajinagar', 2);
INSERT INTO DRIVER VALUES (1, 'Suresh', 5001, 'Pune', 35, 25000),
    (2, 'Ramesh', 5002, 'Mumbai', 42, 28000), (3, 'Ganesh', 5003, 'Nashik', 28, 22000);
INSERT INTO bus_driver VALUES
    (101, 1, '2024-01-15', 1), (101, 2, '2024-01-15', 2),
    (102, 3, '2024-01-15', 1), (101, 3, '2024-01-16', 1);

-- Q2.1 Option A: Trigger before insert on driver - age between 18 and 50
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

-- Q2.1 Option B: Function accept bus_no and date, print allotted drivers
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

-- Q2.2: Procedure check if number is in given range
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

-- Test Calls
-- This should fail: INSERT INTO DRIVER VALUES (4, 'Young', 5004, 'Pune', 16, 15000);
SELECT get_bus_drivers(101, '2024-01-15');
CALL sp_check_range(15, 10, 20);
CALL sp_check_range(25, 10, 20);
