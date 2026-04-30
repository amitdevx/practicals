-- ============================================================
-- Assignment 1: Stored Procedures
-- Set B - Question 1 (A)
-- ============================================================
-- Consider the following relationship:
--   Route (route_no, source, destination, no_of_station)
--   Bus   (bus_no, capacity, depot_name)
-- Relationship between Route and Bus is one-to-many.
--
-- a. Write a procedure which displays all bus details for a
--    given route.
-- b. Write a procedure to update source of route no 101.
-- ============================================================

-- Drop existing tables
DROP TABLE IF EXISTS bus CASCADE;
DROP TABLE IF EXISTS route CASCADE;

-- Create tables
CREATE TABLE route (
    route_no        INT PRIMARY KEY,
    source          VARCHAR(30) NOT NULL,
    destination     VARCHAR(30) NOT NULL,
    no_of_station   INT NOT NULL
);

CREATE TABLE bus (
    bus_no      INT PRIMARY KEY,
    capacity    INT NOT NULL,
    depot_name  VARCHAR(30) NOT NULL,
    route_no    INT REFERENCES route(route_no)
);

-- Insert sample data into route
INSERT INTO route VALUES (101, 'Pune', 'Mumbai', 12);
INSERT INTO route VALUES (102, 'Mumbai', 'Nashik', 8);
INSERT INTO route VALUES (103, 'Pune', 'Nagpur', 15);
INSERT INTO route VALUES (104, 'Nashik', 'Aurangabad', 6);
INSERT INTO route VALUES (105, 'Mumbai', 'Goa', 10);

-- Insert sample data into bus
INSERT INTO bus VALUES (201, 50, 'Swargate', 101);
INSERT INTO bus VALUES (202, 40, 'Shivajinagar', 101);
INSERT INTO bus VALUES (203, 55, 'Dadar', 102);
INSERT INTO bus VALUES (204, 45, 'Hadapsar', 103);
INSERT INTO bus VALUES (205, 60, 'Kothrud', 101);
INSERT INTO bus VALUES (206, 35, 'Katraj', 104);

-- ============================================================
-- (a) Procedure to display all bus details for a given route
-- ============================================================

DROP PROCEDURE IF EXISTS display_buses_for_route(INT);

CREATE OR REPLACE PROCEDURE display_buses_for_route(
    IN p_route_no INT
)
LANGUAGE plpgsql
AS $$
DECLARE
    rec RECORD;
    v_count INT := 0;
BEGIN
    RAISE NOTICE '--- Bus details for Route No: % ---', p_route_no;

    FOR rec IN
        SELECT b.bus_no, b.capacity, b.depot_name, r.source, r.destination
        FROM bus b
        JOIN route r ON b.route_no = r.route_no
        WHERE b.route_no = p_route_no
    LOOP
        RAISE NOTICE 'Bus No: %, Capacity: %, Depot: %, Source: %, Destination: %',
                      rec.bus_no, rec.capacity, rec.depot_name,
                      rec.source, rec.destination;
        v_count := v_count + 1;
    END LOOP;

    IF v_count = 0 THEN
        RAISE NOTICE 'No buses found for Route No: %', p_route_no;
    ELSE
        RAISE NOTICE 'Total buses on Route %: %', p_route_no, v_count;
    END IF;
END;
$$;

-- ============================================================
-- (b) Procedure to update source of route no 101
-- ============================================================

DROP PROCEDURE IF EXISTS update_route_source(INT, VARCHAR);

CREATE OR REPLACE PROCEDURE update_route_source(
    IN p_route_no  INT,
    IN p_new_source VARCHAR
)
LANGUAGE plpgsql
AS $$
DECLARE
    v_old_source VARCHAR;
BEGIN
    SELECT source INTO v_old_source
    FROM route
    WHERE route_no = p_route_no;

    IF NOT FOUND THEN
        RAISE EXCEPTION 'Route No % does not exist', p_route_no;
    END IF;

    UPDATE route
    SET source = p_new_source
    WHERE route_no = p_route_no;

    RAISE NOTICE 'Route % source updated from "%" to "%"',
                  p_route_no, v_old_source, p_new_source;
END;
$$;

-- Test: Display all buses for route 101
CALL display_buses_for_route(101);

-- Test: Display buses for a route with no buses
CALL display_buses_for_route(105);

-- Test: Update source of route 101
CALL update_route_source(101, 'Satara');

-- Verify the update
SELECT * FROM route WHERE route_no = 101;
