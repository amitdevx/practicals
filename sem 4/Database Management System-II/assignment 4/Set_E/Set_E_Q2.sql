-- ============================================================
-- Assignment 4: Handling Errors and Exceptions
-- Set E - Question 2
-- ============================================================
-- Q2. Write a stored function to accept date and passenger name
--     and display no of berths reserved and ticket amount paid
--     by him. Raise exception if passenger name is invalid.
-- ============================================================

-- ==================== Table Creation ====================

DROP TABLE IF EXISTS TICKET CASCADE;
DROP TABLE IF EXISTS PASSENGER CASCADE;
DROP TABLE IF EXISTS TRAIN CASCADE;

CREATE TABLE TRAIN (
    train_no         INT PRIMARY KEY,
    train_name       VARCHAR(20) NOT NULL,
    depart_time      TIME,
    arrival_time     TIME,
    source_stn       VARCHAR(20),
    dest_stn         VARCHAR(20),
    no_of_res_bogies INT,
    bogie_capacity   INT
);

CREATE TABLE PASSENGER (
    passenger_id    INT PRIMARY KEY,
    passenger_name  VARCHAR(20) NOT NULL,
    address         VARCHAR(30),
    age             INT,
    gender          CHAR
);

CREATE TABLE TICKET (
    train_no       INT REFERENCES TRAIN(train_no),
    passenger_id   INT REFERENCES PASSENGER(passenger_id),
    ticket_no      INT,
    bogie_no       INT,
    no_of_berths   INT,
    tdate          DATE,
    ticket_amt     DECIMAL(7,2),
    status         CHAR CHECK (status IN ('W', 'C')),
    PRIMARY KEY (train_no, passenger_id, ticket_no)
);

-- ==================== Sample Data ====================

INSERT INTO TRAIN VALUES (1001, 'Shatabdi Express', '06:00', '12:00', 'Pune',   'Mumbai',  5, 72);
INSERT INTO TRAIN VALUES (1002, 'Rajdhani Express', '08:30', '20:30', 'Mumbai', 'Delhi',   8, 72);
INSERT INTO TRAIN VALUES (1003, 'Duronto Express',  '10:00', '22:00', 'Pune',   'Delhi',   6, 72);
INSERT INTO TRAIN VALUES (1004, 'Deccan Queen',     '07:15', '10:30', 'Pune',   'Mumbai',  4, 72);
INSERT INTO TRAIN VALUES (1005, 'Garib Rath',       '09:00', '21:00', 'Nagpur', 'Mumbai',  7, 72);

INSERT INTO PASSENGER VALUES (1, 'Amit',   'Pune',    25, 'M');
INSERT INTO PASSENGER VALUES (2, 'Priya',  'Mumbai',  30, 'F');
INSERT INTO PASSENGER VALUES (3, 'Rahul',  'Nagpur',  22, 'M');
INSERT INTO PASSENGER VALUES (4, 'Sneha',  'Delhi',   28, 'F');
INSERT INTO PASSENGER VALUES (5, 'Vikram', 'Pune',    35, 'M');
INSERT INTO PASSENGER VALUES (6, 'Neha',   'Mumbai',  27, 'F');

INSERT INTO TICKET VALUES (1001, 1, 5001, 2, 2, '2024-12-15', 450.00,  'C');
INSERT INTO TICKET VALUES (1001, 2, 5002, 3, 1, '2024-12-15', 225.00,  'C');
INSERT INTO TICKET VALUES (1002, 3, 5003, 1, 3, '2024-12-15', 1800.00, 'C');
INSERT INTO TICKET VALUES (1002, 4, 5004, 2, 1, '2024-12-16', 600.00,  'W');
INSERT INTO TICKET VALUES (1003, 5, 5005, 4, 2, '2024-12-16', 1200.00, 'C');
INSERT INTO TICKET VALUES (1004, 6, 5006, 1, 1, '2024-12-15', 180.00,  'W');
INSERT INTO TICKET VALUES (1005, 1, 5007, 3, 2, '2024-12-16', 900.00,  'C');
INSERT INTO TICKET VALUES (1003, 2, 5008, 2, 1, '2024-12-15', 600.00,  'C');

-- ==================== Function ====================

CREATE OR REPLACE FUNCTION get_passenger_booking(p_date DATE, p_name VARCHAR)
RETURNS VOID AS $$
DECLARE
    v_pid          INT;
    v_total_berths INT := 0;
    v_total_amt    DECIMAL(7,2) := 0;
BEGIN
    -- Check if the passenger exists
    SELECT passenger_id INTO v_pid
    FROM PASSENGER
    WHERE LOWER(TRIM(passenger_name)) = LOWER(TRIM(p_name));

    IF NOT FOUND THEN
        RAISE EXCEPTION 'Invalid passenger name: "%" does not exist.', p_name;
    END IF;

    -- Get total berths and amount for the given date
    SELECT COALESCE(SUM(no_of_berths), 0), COALESCE(SUM(ticket_amt), 0)
    INTO v_total_berths, v_total_amt
    FROM TICKET
    WHERE passenger_id = v_pid AND tdate = p_date;

    IF v_total_berths = 0 THEN
        RAISE NOTICE 'Passenger "%" has no bookings on %.', TRIM(p_name), p_date;
    ELSE
        RAISE NOTICE '--- Booking Details for "%" on % ---', TRIM(p_name), p_date;
        RAISE NOTICE 'Total Berths Reserved : %', v_total_berths;
        RAISE NOTICE 'Total Ticket Amount   : %', v_total_amt;
        RAISE NOTICE '--------------------------------------';
    END IF;

EXCEPTION
    WHEN OTHERS THEN
        RAISE NOTICE 'Error: %', SQLERRM;
END;
$$ LANGUAGE plpgsql;

-- ==================== Test Calls ====================

-- Valid passenger with bookings on date
SELECT get_passenger_booking('2024-12-15', 'Amit');

-- Valid passenger with bookings on different date
SELECT get_passenger_booking('2024-12-16', 'Vikram');

-- Valid passenger with no bookings on date
SELECT get_passenger_booking('2024-12-20', 'Priya');

-- Invalid passenger name (should raise exception)
SELECT get_passenger_booking('2024-12-15', 'Suresh');

-- Invalid passenger name (should raise exception)
SELECT get_passenger_booking('2024-12-15', 'Meera');
