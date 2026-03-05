-- Slip 06: Bus-Route-Driver Database
-- Q2.1 OptionA: Function accept bus_no, print driver name
-- Q2.1 OptionB: Function accept depot name, display drivers age > 50
-- Q2.2: Procedure even or odd

-- ============================================================
-- Table Creation
-- ============================================================

DROP TABLE IF EXISTS bus_driver CASCADE;
DROP TABLE IF EXISTS BUS CASCADE;
DROP TABLE IF EXISTS ROUTE CASCADE;
DROP TABLE IF EXISTS DRIVER CASCADE;

CREATE TABLE ROUTE (
    route_no       INT PRIMARY KEY,
    source         CHAR(20),
    destination    CHAR(20),
    no_of_stations INT
);

CREATE TABLE BUS (
    bus_no     INT PRIMARY KEY,
    capacity   INT NOT NULL,
    depot_name VARCHAR(20),
    route_no   INT REFERENCES ROUTE(route_no)
);

CREATE TABLE DRIVER (
    driver_no   INT PRIMARY KEY,
    driver_name CHAR(20),
    license_no  INT UNIQUE,
    address     CHAR(20),
    d_age       INT,
    salary      FLOAT
);

CREATE TABLE bus_driver (
    bus_no    INT REFERENCES BUS(bus_no),
    driver_no INT REFERENCES DRIVER(driver_no),
    duty_date DATE,
    shift     INT CHECK (shift IN (1, 2)),
    PRIMARY KEY (bus_no, driver_no, duty_date)
);

-- ============================================================
-- Sample Data
-- ============================================================

INSERT INTO ROUTE VALUES (1, 'Pune', 'Mumbai', 15);
INSERT INTO ROUTE VALUES (2, 'Pune', 'Nashik', 10);
INSERT INTO ROUTE VALUES (3, 'Mumbai', 'Goa', 20);

INSERT INTO BUS VALUES (101, 50, 'Swargate', 1);
INSERT INTO BUS VALUES (102, 45, 'Shivajinagar', 2);
INSERT INTO BUS VALUES (103, 55, 'Swargate', 3);

INSERT INTO DRIVER VALUES (1, 'Ramesh', 11001, 'Pune', 52, 35000);
INSERT INTO DRIVER VALUES (2, 'Suresh', 11002, 'Mumbai', 45, 30000);
INSERT INTO DRIVER VALUES (3, 'Mahesh', 11003, 'Nashik', 55, 38000);
INSERT INTO DRIVER VALUES (4, 'Ganesh', 11004, 'Pune', 48, 32000);

INSERT INTO bus_driver VALUES (101, 1, '2024-01-15', 1);
INSERT INTO bus_driver VALUES (101, 3, '2024-01-15', 2);
INSERT INTO bus_driver VALUES (102, 2, '2024-01-16', 1);
INSERT INTO bus_driver VALUES (103, 4, '2024-01-17', 1);

-- ============================================================
-- Q2.1 Option A: Function accept bus_no, print driver name
-- ============================================================

CREATE OR REPLACE FUNCTION get_driver_for_bus(p_bus_no INT)
RETURNS VOID AS $$
DECLARE
    rec RECORD;
    v_found BOOLEAN := FALSE;
BEGIN
    FOR rec IN
        SELECT DISTINCT d.driver_name
        FROM bus_driver bd
        JOIN DRIVER d ON d.driver_no = bd.driver_no
        WHERE bd.bus_no = p_bus_no
    LOOP
        v_found := TRUE;
        RAISE NOTICE 'Driver: %', TRIM(rec.driver_name);
    END LOOP;

    IF NOT v_found THEN
        RAISE NOTICE 'No driver found for bus no: %', p_bus_no;
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Test: SELECT get_driver_for_bus(101);

-- ============================================================
-- Q2.1 Option B: Function accept depot name, display drivers age > 50
-- ============================================================

CREATE OR REPLACE FUNCTION get_senior_drivers(p_depot VARCHAR)
RETURNS VOID AS $$
DECLARE
    rec RECORD;
    v_found BOOLEAN := FALSE;
BEGIN
    FOR rec IN
        SELECT DISTINCT d.driver_name, d.d_age
        FROM DRIVER d
        JOIN bus_driver bd ON bd.driver_no = d.driver_no
        JOIN BUS b ON b.bus_no = bd.bus_no
        WHERE b.depot_name = p_depot AND d.d_age > 50
    LOOP
        v_found := TRUE;
        RAISE NOTICE 'Driver: %, Age: %', TRIM(rec.driver_name), rec.d_age;
    END LOOP;

    IF NOT v_found THEN
        RAISE NOTICE 'No drivers above age 50 found in depot: %', p_depot;
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Test: SELECT get_senior_drivers('Swargate');

-- ============================================================
-- Q2.2: Procedure even or odd
-- ============================================================

CREATE OR REPLACE PROCEDURE check_even_odd(n INT)
AS $$
BEGIN
    IF n % 2 = 0 THEN
        RAISE NOTICE '% is Even.', n;
    ELSE
        RAISE NOTICE '% is Odd.', n;
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Test: CALL check_even_odd(7);
-- Test: CALL check_even_odd(12);
