-- ============================================================
-- Slip 08: Train-Passenger-Ticket Database
-- Section II: Database Management Systems-II [15 Marks]
-- ============================================================

/*
Consider the following Entities and their Relationships:

TRAIN (train_no int, train_name varchar(20), depart_time time, arrival_time time, 
       source_stn varchar(20), dest_stn varchar(20), no_of_res_bogies int, bogie_capacity int)
PASSENGER (passenger_id int, passenger_name varchar(20), address varchar(30), age int, gender char)

Relationships:
- Train_Passenger: M-M relationship named ticket with descriptive attributes.
- TICKET (train_no int, passenger_id int, ticket_no int, bogie_no int, no_of_berths int, 
         tdate date, ticket_amt decimal(7,2), status char)

Constraints:
- The status of a berth can be 'W' (waiting) or 'C' (confirmed).
*/

-- ============================================================
-- Database Setup
-- ============================================================

DROP DATABASE IF EXISTS slip_08_db;
CREATE DATABASE slip_08_db;
\c slip_08_db

-- ============================================================
-- Table Creation
-- ============================================================

DROP TABLE IF EXISTS TICKET CASCADE;
DROP TABLE IF EXISTS PASSENGER CASCADE;
DROP TABLE IF EXISTS TRAIN CASCADE;

CREATE TABLE TRAIN (
    train_no        INT PRIMARY KEY,
    train_name      VARCHAR(20),
    depart_time     TIME,
    arrival_time    TIME,
    source_stn      VARCHAR(20),
    dest_stn        VARCHAR(20),
    no_of_res_bogies INT,
    bogie_capacity  INT
);

CREATE TABLE PASSENGER (
    passenger_id   INT PRIMARY KEY,
    passenger_name VARCHAR(20),
    address        VARCHAR(30),
    age            INT,
    gender         CHAR(1)
);

CREATE TABLE TICKET (
    train_no      INT REFERENCES TRAIN(train_no),
    passenger_id  INT REFERENCES PASSENGER(passenger_id),
    ticket_no     INT,
    bogie_no      INT,
    no_of_berths  INT,
    tdate         DATE,
    ticket_amt    DECIMAL(7,2),
    status        CHAR CHECK (status IN ('W', 'C')),
    PRIMARY KEY (train_no, passenger_id)
);

-- ============================================================
-- Sample Data
-- ============================================================

INSERT INTO TRAIN VALUES (12001, 'Shatabdi', '06:00', '12:00', 'Pune', 'Mumbai', 10, 72);
INSERT INTO TRAIN VALUES (12002, 'Rajdhani', '16:00', '08:00', 'Mumbai', 'Delhi', 15, 72);
INSERT INTO TRAIN VALUES (12003, 'Duronto', '20:00', '10:00', 'Pune', 'Delhi', 12, 72);

INSERT INTO PASSENGER VALUES (1, 'Amit', 'Pune', 25, 'M');
INSERT INTO PASSENGER VALUES (2, 'Neha', 'Mumbai', 30, 'F');
INSERT INTO PASSENGER VALUES (3, 'Rahul', 'Delhi', 4, 'M');
INSERT INTO PASSENGER VALUES (4, 'Priya', 'Pune', 8, 'F');

INSERT INTO TICKET VALUES (12001, 1, 5001, 3, 1, '2024-03-15', 750.00, 'C');
INSERT INTO TICKET VALUES (12002, 2, 5002, 5, 2, '2024-03-16', 2500.00, 'C');
INSERT INTO TICKET VALUES (12001, 3, 5003, 3, 1, '2024-03-15', 0.00, 'C');
INSERT INTO TICKET VALUES (12003, 4, 5004, 7, 1, '2024-03-17', 1800.00, 'W');

-- ============================================================
-- Q2.1 Option A: Write a stored function to display the ticket
-- details of a train. Accept train name as input parameter.
-- Raise an exception in case of invalid train name. [5 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION get_ticket_details(p_train_name VARCHAR)
RETURNS VOID AS $$
DECLARE
    v_train_no INT;
    rec RECORD;
    v_found BOOLEAN := FALSE;
BEGIN
    SELECT train_no INTO v_train_no
    FROM TRAIN
    WHERE train_name = p_train_name;

    IF NOT FOUND THEN
        RAISE EXCEPTION 'Invalid train name: %', p_train_name;
    END IF;

    FOR rec IN
        SELECT t.ticket_no, p.passenger_name, t.bogie_no, t.no_of_berths,
               t.tdate, t.ticket_amt, t.status
        FROM TICKET t
        JOIN PASSENGER p ON p.passenger_id = t.passenger_id
        WHERE t.train_no = v_train_no
    LOOP
        v_found := TRUE;
        RAISE NOTICE 'Ticket#: %, Passenger: %, Bogie: %, Berths: %, Date: %, Amount: %, Status: %',
            rec.ticket_no, TRIM(rec.passenger_name), rec.bogie_no, rec.no_of_berths,
            rec.tdate, rec.ticket_amt, rec.status;
    END LOOP;

    IF NOT v_found THEN
        RAISE NOTICE 'No tickets found for train: %', p_train_name;
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Execute: SELECT get_ticket_details('Shatabdi');  -- Shows tickets for Shatabdi
-- Execute: SELECT get_ticket_details('Rajdhani');  -- Shows tickets for Rajdhani
-- Execute: SELECT get_ticket_details('Invalid');   -- Should raise exception

-- ============================================================
-- Q2.1 Option B (OR): Write a trigger after insert on passenger
-- to display message "Age above 5 will be charged full fare"
-- if age of passenger is more than 5. [5 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION check_passenger_age()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.age > 5 THEN
        RAISE NOTICE 'Age above 5 will be charged full fare';
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_passenger_age
AFTER INSERT ON PASSENGER
FOR EACH ROW
EXECUTE FUNCTION check_passenger_age();

-- Execute: INSERT INTO PASSENGER VALUES (10, 'Adult', 'Mumbai', 25, 'M');  -- Shows fare message
-- Execute: INSERT INTO PASSENGER VALUES (11, 'Child', 'Pune', 4, 'F');     -- No message (age <= 5)

-- ============================================================
-- Q2.2: Write a procedure to display addition of two numbers.
-- [5 Marks]
-- ============================================================

CREATE OR REPLACE PROCEDURE add_two_numbers(a NUMERIC, b NUMERIC)
AS $$
DECLARE
    v_sum NUMERIC;
BEGIN
    v_sum := a + b;
    RAISE NOTICE '% + % = %', a, b, v_sum;
END;
$$ LANGUAGE plpgsql;

-- Execute: CALL add_two_numbers(10, 5);   -- Result: 15
-- Execute: CALL add_two_numbers(-3, 7);   -- Result: 4

