-- ============================================================
-- Assignment 4: Handling Errors and Exceptions
-- Set C - Question 1
-- ============================================================
-- Q1. Write a function to accept quantity. The quantity must be
--     in the range 50 to 200. If the quantity is out of range,
--     raise a user-defined exception "quantity_out_of_range",
--     otherwise insert the record into the wholesaler_product
--     table.
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

CREATE OR REPLACE FUNCTION insert_wholesaler_product(
    p_wno       INT,
    p_product_no INT,
    p_quantity  INT
)
RETURNS VOID AS $$
BEGIN
    -- Validate quantity range (50 to 200)
    IF p_quantity < 50 OR p_quantity > 200 THEN
        RAISE EXCEPTION 'quantity_out_of_range: Quantity % is out of valid range (50-200).', p_quantity;
    END IF;

    -- Insert the record
    INSERT INTO wholesaler_product (w_no, product_no, quantity)
    VALUES (p_wno, p_product_no, p_quantity);

    RAISE NOTICE 'Record inserted successfully: Wholesaler=%, Product=%, Quantity=%',
        p_wno, p_product_no, p_quantity;

EXCEPTION
    WHEN OTHERS THEN
        RAISE NOTICE 'Error: %', SQLERRM;
END;
$$ LANGUAGE plpgsql;

-- ==================== Test Calls ====================

-- Valid quantity (within range)
SELECT insert_wholesaler_product(1, 201, 100);

-- Valid quantity (boundary: 50)
SELECT insert_wholesaler_product(2, 202, 50);

-- Valid quantity (boundary: 200)
SELECT insert_wholesaler_product(3, 203, 200);

-- Invalid quantity (below range - should raise exception)
SELECT insert_wholesaler_product(4, 204, 30);

-- Invalid quantity (above range - should raise exception)
SELECT insert_wholesaler_product(5, 205, 300);

-- Verify inserted records
SELECT w.w_name, p.product_name, wp.quantity
FROM wholesaler_product wp
JOIN Wholesaler w ON wp.w_no = w.w_no
JOIN Product p ON wp.product_no = p.product_no;
