/*
SLIP 23 - SECTION II: DATABASE MANAGEMENT SYSTEMS II

Car(c_no int PK, owner varchar(20), model varchar(10), color varchar(10))
Driver(driver_no int PK, driver_name varchar(20), license_no int, d_age int, salary float)
car_driver(c_no, driver_no) M:M

Q2.1A: Cursor accept driver name, print car details. Handle invalid driver name.
Q2.1B: Trigger before insert/update on driver - if age < 21 raise exception.
Q2.2: Procedure sum of first 100 numbers using unconditional loop (LOOP).
*/

-- Table Creation
DROP TABLE IF EXISTS car_driver CASCADE;
DROP TABLE IF EXISTS Car CASCADE;
DROP TABLE IF EXISTS Driver CASCADE;

CREATE TABLE Car (
    c_no INT PRIMARY KEY,
    owner VARCHAR(20),
    model VARCHAR(10),
    color VARCHAR(10)
);

CREATE TABLE Driver (
    driver_no INT PRIMARY KEY,
    driver_name VARCHAR(20),
    license_no INT,
    d_age INT,
    salary FLOAT
);

CREATE TABLE car_driver (
    c_no INT REFERENCES Car(c_no),
    driver_no INT REFERENCES Driver(driver_no),
    PRIMARY KEY (c_no, driver_no)
);

-- Sample Data
INSERT INTO Car VALUES (1, 'Amit', 'Swift', 'Red');
INSERT INTO Car VALUES (2, 'Sneha', 'i20', 'White');
INSERT INTO Car VALUES (3, 'Rahul', 'Verna', 'Black');

INSERT INTO Driver VALUES (101, 'Raju', 55001, 30, 25000);
INSERT INTO Driver VALUES (102, 'Sunil', 55002, 25, 22000);
INSERT INTO Driver VALUES (103, 'Manoj', 55003, 35, 28000);

INSERT INTO car_driver VALUES (1, 101);
INSERT INTO car_driver VALUES (2, 101);
INSERT INTO car_driver VALUES (3, 102);
INSERT INTO car_driver VALUES (1, 103);

-- Q2.1A: Cursor accept driver name, print car details
CREATE OR REPLACE FUNCTION get_cars_by_driver(p_dname VARCHAR)
RETURNS VOID AS $$
DECLARE
    v_rec RECORD;
    v_found BOOLEAN := FALSE;
    cur_cars CURSOR FOR
        SELECT c.c_no, c.owner, c.model, c.color
        FROM Car c
        JOIN car_driver cd ON c.c_no = cd.c_no
        JOIN Driver d ON cd.driver_no = d.driver_no
        WHERE d.driver_name = p_dname;
BEGIN
    OPEN cur_cars;
    LOOP
        FETCH cur_cars INTO v_rec;
        EXIT WHEN NOT FOUND;
        v_found := TRUE;
        RAISE NOTICE 'Car No: %, Owner: %, Model: %, Color: %',
            v_rec.c_no, v_rec.owner, v_rec.model, v_rec.color;
    END LOOP;
    CLOSE cur_cars;

    IF NOT v_found THEN
        RAISE EXCEPTION 'Invalid driver name: %. No records found.', p_dname;
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Q2.1B: Trigger before insert/update on driver - age < 21 raise exception
CREATE OR REPLACE FUNCTION trg_check_driver_age()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.d_age < 21 THEN
        RAISE EXCEPTION 'Driver age must be at least 21. Given: %', NEW.d_age;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_driver_age
BEFORE INSERT OR UPDATE ON Driver
FOR EACH ROW EXECUTE FUNCTION trg_check_driver_age();

-- Q2.2: Procedure sum of first 100 numbers using unconditional loop
CREATE OR REPLACE PROCEDURE sum_first_100()
LANGUAGE plpgsql AS $$
DECLARE
    v_sum INT := 0;
    v_i INT := 1;
BEGIN
    LOOP
        v_sum := v_sum + v_i;
        v_i := v_i + 1;
        EXIT WHEN v_i > 100;
    END LOOP;
    RAISE NOTICE 'Sum of first 100 numbers: %', v_sum;
END;
$$;

-- Test Calls
SELECT get_cars_by_driver('Raju');
SELECT get_cars_by_driver('Sunil');

-- Test trigger (this should raise exception)
-- INSERT INTO Driver VALUES (104, 'Young', 55004, 18, 15000);

CALL sum_first_100();
