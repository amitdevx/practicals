-- Slip 08: Train-Passenger-Ticket Database
-- Q2.1 OptionA: Function display ticket details for train name, raise exception if invalid
-- Q2.1 OptionB: Trigger after insert on passenger - if age>5 display "Age above 5 will be charged full fare"
-- Q2.2: Procedure addition of two numbers

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
-- Q2.1 Option A: Function display ticket details for train name
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

-- Test: SELECT get_ticket_details('Shatabdi');
-- Test: SELECT get_ticket_details('InvalidTrain');

-- ============================================================
-- Q2.1 Option B: Trigger after insert on passenger - age > 5 message
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

-- Test: INSERT INTO PASSENGER VALUES (5, 'Test', 'Pune', 10, 'M');

-- ============================================================
-- Q2.2: Procedure addition of two numbers
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

-- Test: CALL add_two_numbers(15, 25);
