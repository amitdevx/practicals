-- ============================================================
-- Assignment 4: Handling Errors and Exceptions
-- Set E - Question 1
-- ============================================================
-- Q1. Write a stored function to print the details of train
--     wise confirmed bookings on a date (Accept date as input
--     parameter). Raise an error in case of invalid date.
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

CREATE OR REPLACE FUNCTION get_confirmed_bookings(p_date DATE)
RETURNS VOID AS $$
DECLARE
    v_count  INT := 0;
    rec      RECORD;
BEGIN
    -- Check if there are any confirmed bookings on the given date
    SELECT COUNT(*) INTO v_count
    FROM TICKET
    WHERE tdate = p_date AND status = 'C';

    IF v_count = 0 THEN
        RAISE EXCEPTION 'Invalid date: No confirmed bookings found on "%".', p_date;
    END IF;

    RAISE NOTICE '--- Train-wise Confirmed Bookings on % ---', p_date;

    FOR rec IN
        SELECT t.train_no, t.train_name, tk.ticket_no, p.passenger_name,
               tk.bogie_no, tk.no_of_berths, tk.ticket_amt
        FROM TICKET tk
        JOIN TRAIN t ON tk.train_no = t.train_no
        JOIN PASSENGER p ON tk.passenger_id = p.passenger_id
        WHERE tk.tdate = p_date AND tk.status = 'C'
        ORDER BY t.train_no, tk.ticket_no
    LOOP
        RAISE NOTICE 'Train: % (%), Ticket: %, Passenger: %, Bogie: %, Berths: %, Amount: %',
            rec.train_no, rec.train_name, rec.ticket_no, rec.passenger_name,
            rec.bogie_no, rec.no_of_berths, rec.ticket_amt;
    END LOOP;

    RAISE NOTICE '--- Total confirmed bookings: % ---', v_count;

EXCEPTION
    WHEN OTHERS THEN
        RAISE NOTICE 'Error: %', SQLERRM;
END;
$$ LANGUAGE plpgsql;

-- ==================== Test Calls ====================

-- Valid date with confirmed bookings
SELECT get_confirmed_bookings('2024-12-15');

-- Valid date with confirmed bookings (different)
SELECT get_confirmed_bookings('2024-12-16');

-- Invalid date (no bookings - should raise exception)
SELECT get_confirmed_bookings('2024-12-20');

-- Invalid date (no bookings - should raise exception)
SELECT get_confirmed_bookings('2025-01-01');
