-- ============================================================
-- Assignment 4: Handling Errors and Exceptions
-- Set C - Question 3
-- ============================================================
-- Q3. Write a function to accept a product name. If the product
--     name is invalid, raise a user-defined exception
--     "invalid_product_name", otherwise display the product
--     details.
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

CREATE OR REPLACE FUNCTION get_product_details(p_name VARCHAR)
RETURNS VOID AS $$
DECLARE
    v_product_no    INT;
    v_product_name  VARCHAR;
    v_rate          NUMERIC(10,2);
BEGIN
    -- Check if the product exists
    SELECT product_no, TRIM(product_name), rate
    INTO v_product_no, v_product_name, v_rate
    FROM Product
    WHERE LOWER(TRIM(product_name)) = LOWER(TRIM(p_name));

    IF NOT FOUND THEN
        RAISE EXCEPTION 'invalid_product_name: Product "%" does not exist.', p_name;
    END IF;

    RAISE NOTICE '--- Product Details ---';
    RAISE NOTICE 'Product No   : %', v_product_no;
    RAISE NOTICE 'Product Name : %', v_product_name;
    RAISE NOTICE 'Rate         : %', v_rate;
    RAISE NOTICE '-----------------------';

EXCEPTION
    WHEN OTHERS THEN
        RAISE NOTICE 'Error: %', SQLERRM;
END;
$$ LANGUAGE plpgsql;

-- ==================== Test Calls ====================

-- Valid product name
SELECT get_product_details('Rice');

-- Valid product name (case-insensitive)
SELECT get_product_details('oil');

-- Valid product name
SELECT get_product_details('Tea');

-- Invalid product name (should raise exception)
SELECT get_product_details('Butter');

-- Invalid product name (should raise exception)
SELECT get_product_details('Milk');
