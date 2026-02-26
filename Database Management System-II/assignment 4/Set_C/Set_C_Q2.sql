-- ============================================================
-- Assignment 4: Handling Errors and Exceptions
-- Set C - Question 2
-- ============================================================
-- Q2. Write a function to accept rate. If the rate is less than
--     or equal to zero, raise a user-defined exception
--     "invalid_rate_value", otherwise display "Correct Input".
-- ============================================================

-- ==================== Table Creation ====================

DROP TABLE IF EXISTS wholesaler_product CASCADE;
DROP TABLE IF EXISTS Product CASCADE;
DROP TABLE IF EXISTS Wholesaler CASCADE;

CREATE TABLE Wholesaler (
    w_no     INT PRIMARY KEY,
    w_name   VARCHAR(30) NOT NULL,
    address  VARCHAR(50),
    city     VARCHAR(20)
);

CREATE TABLE Product (
    product_no    INT PRIMARY KEY,
    product_name  VARCHAR(30) NOT NULL,
    rate          NUMERIC(10,2)
);

CREATE TABLE wholesaler_product (
    w_no        INT REFERENCES Wholesaler(w_no),
    product_no  INT REFERENCES Product(product_no),
    quantity    INT,
    PRIMARY KEY (w_no, product_no)
);

-- ==================== Sample Data ====================

INSERT INTO Wholesaler VALUES (1, 'Sharma Traders',  'MG Road',       'Pune');
INSERT INTO Wholesaler VALUES (2, 'Gupta Supplies',  'FC Road',       'Mumbai');
INSERT INTO Wholesaler VALUES (3, 'Patel Wholesale', 'JM Road',       'Nagpur');
INSERT INTO Wholesaler VALUES (4, 'Singh Agencies',  'Laxmi Road',    'Pune');
INSERT INTO Wholesaler VALUES (5, 'Mehta Stores',    'Station Road',  'Mumbai');

INSERT INTO Product VALUES (201, 'Rice',    45.00);
INSERT INTO Product VALUES (202, 'Wheat',   38.50);
INSERT INTO Product VALUES (203, 'Sugar',   42.00);
INSERT INTO Product VALUES (204, 'Oil',     125.00);
INSERT INTO Product VALUES (205, 'Salt',    20.00);
INSERT INTO Product VALUES (206, 'Tea',     250.00);

-- ==================== Function ====================

CREATE OR REPLACE FUNCTION validate_rate(p_rate NUMERIC)
RETURNS VOID AS $$
BEGIN
    -- Check if rate is valid
    IF p_rate <= 0 THEN
        RAISE EXCEPTION 'invalid_rate_value: Rate % is not valid. Rate must be greater than zero.', p_rate;
    END IF;

    RAISE NOTICE 'Correct Input: Rate % is valid.', p_rate;

EXCEPTION
    WHEN OTHERS THEN
        RAISE NOTICE 'Error: %', SQLERRM;
END;
$$ LANGUAGE plpgsql;

-- ==================== Test Calls ====================

-- Valid rate (positive value)
SELECT validate_rate(45.00);

-- Valid rate (large value)
SELECT validate_rate(250.00);

-- Invalid rate (zero - should raise exception)
SELECT validate_rate(0);

-- Invalid rate (negative - should raise exception)
SELECT validate_rate(-15.50);

-- Valid rate (small positive)
SELECT validate_rate(0.50);
