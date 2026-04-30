-- ============================================================
-- Assignment 3: Cursors
-- Set A - Question 1
-- ============================================================
-- Q1. Write a stored function using cursor, which will give
--     details of all routes on which bus no 108 is running.
-- ============================================================

-- Drop existing tables
DROP TABLE IF EXISTS bus_route CASCADE;
DROP TABLE IF EXISTS bus CASCADE;
DROP TABLE IF EXISTS route CASCADE;

-- Create tables
CREATE TABLE bus (
    bus_no      INT PRIMARY KEY,
    capacity    INT NOT NULL,
    depot_name  VARCHAR(20) NOT NULL
);

CREATE TABLE route (
    route_no        INT PRIMARY KEY,
    source          VARCHAR(20) NOT NULL,
    destination     VARCHAR(20) NOT NULL,
    no_of_stations  INT NOT NULL
);

CREATE TABLE bus_route (
    bus_no    INT REFERENCES bus(bus_no),
    route_no  INT REFERENCES route(route_no),
    PRIMARY KEY (bus_no, route_no)
);

-- Insert sample data into bus
INSERT INTO bus VALUES (101, 50, 'Kothrud');
INSERT INTO bus VALUES (104, 40, 'Swargate');
INSERT INTO bus VALUES (108, 55, 'Shivajinagar');
INSERT INTO bus VALUES (112, 45, 'Hadapsar');
INSERT INTO bus VALUES (115, 60, 'Deccan');
INSERT INTO bus VALUES (120, 35, 'Katraj');

-- Insert sample data into route
INSERT INTO route VALUES (1, 'Station', 'Airport', 12);
INSERT INTO route VALUES (2, 'Swargate', 'Hadapsar', 8);
INSERT INTO route VALUES (3, 'Katraj', 'Nigdi', 18);
INSERT INTO route VALUES (4, 'Deccan', 'Kothrud', 5);
INSERT INTO route VALUES (5, 'Shivajinagar', 'Hinjewadi', 15);
INSERT INTO route VALUES (6, 'Station', 'Kharadi', 10);

-- Insert sample data into bus_route
INSERT INTO bus_route VALUES (108, 1);
INSERT INTO bus_route VALUES (108, 3);
INSERT INTO bus_route VALUES (108, 5);
INSERT INTO bus_route VALUES (101, 2);
INSERT INTO bus_route VALUES (101, 4);
INSERT INTO bus_route VALUES (104, 1);
INSERT INTO bus_route VALUES (104, 6);
INSERT INTO bus_route VALUES (112, 2);
INSERT INTO bus_route VALUES (115, 3);
INSERT INTO bus_route VALUES (120, 6);

-- Stored function using cursor
CREATE OR REPLACE FUNCTION get_routes_for_bus_108()
RETURNS VOID AS $$
DECLARE
    cur_routes CURSOR FOR
        SELECT r.route_no, r.source, r.destination, r.no_of_stations
        FROM route r
        JOIN bus_route br ON r.route_no = br.route_no
        WHERE br.bus_no = 108;
    rec RECORD;
BEGIN
    RAISE NOTICE '--- Routes for Bus No 108 ---';
    OPEN cur_routes;
    LOOP
        FETCH cur_routes INTO rec;
        EXIT WHEN NOT FOUND;
        RAISE NOTICE 'Route No: %, Source: %, Destination: %, Stations: %',
            rec.route_no, rec.source, rec.destination, rec.no_of_stations;
    END LOOP;
    CLOSE cur_routes;
END;
$$ LANGUAGE plpgsql;

-- Test
SELECT get_routes_for_bus_108();
