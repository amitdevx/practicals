-- ============================================================
-- Assignment 4: Handling Errors and Exceptions
-- Set E - Question 3
-- ============================================================
-- Q3. Write a stored function to display the ticket details of
--     a train (Accept train name as input parameter). Raise an
--     exception in case of invalid train name.
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

CREATE OR REPLACE FUNCTION get_ticket_details_by_train(p_name VARCHAR)
RETURNS VOID AS $$
DECLARE
    v_train_no  INT;
    v_count     INT := 0;
    rec         RECORD;
BEGIN
    -- Check if the train exists
    SELECT train_no INTO v_train_no
    FROM TRAIN
    WHERE LOWER(TRIM(train_name)) = LOWER(TRIM(p_name));

    IF NOT FOUND THEN
        RAISE EXCEPTION 'Invalid train name: "%" does not exist.', p_name;
    END IF;

    -- Count tickets for the train
    SELECT COUNT(*) INTO v_count
    FROM TICKET
    WHERE train_no = v_train_no;

    IF v_count = 0 THEN
        RAISE NOTICE 'No tickets found for train "%".', TRIM(p_name);
        RETURN;
    END IF;

    RAISE NOTICE '--- Ticket Details for Train: % (%) ---', TRIM(p_name), v_train_no;

    FOR rec IN
        SELECT tk.ticket_no, p.passenger_name, tk.bogie_no, tk.no_of_berths,
               tk.tdate, tk.ticket_amt, tk.status
        FROM TICKET tk
        JOIN PASSENGER p ON tk.passenger_id = p.passenger_id
        WHERE tk.train_no = v_train_no
        ORDER BY tk.ticket_no
    LOOP
        RAISE NOTICE 'Ticket: %, Passenger: %, Bogie: %, Berths: %, Date: %, Amount: %, Status: %',
            rec.ticket_no, rec.passenger_name, rec.bogie_no, rec.no_of_berths,
            rec.tdate, rec.ticket_amt, rec.status;
    END LOOP;

    RAISE NOTICE '--- Total tickets: % ---', v_count;

EXCEPTION
    WHEN OTHERS THEN
        RAISE NOTICE 'Error: %', SQLERRM;
END;
$$ LANGUAGE plpgsql;

-- ==================== Test Calls ====================

-- Valid train name
SELECT get_ticket_details_by_train('Shatabdi Express');

-- Valid train name (different)
SELECT get_ticket_details_by_train('Rajdhani Express');

-- Valid train name (case-insensitive)
SELECT get_ticket_details_by_train('duronto express');

-- Invalid train name (should raise exception)
SELECT get_ticket_details_by_train('Mumbai Express');

-- Invalid train name (should raise exception)
SELECT get_ticket_details_by_train('Chennai Mail');
