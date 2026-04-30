-- ============================================================
-- Assignment 5: Triggers
-- Set D - Question 3
-- ============================================================
-- Q3. Write a trigger before inserting an account record in
--     the Account table and raise exception if balance is < 500.
-- ============================================================

-- ========================
-- Table Creation
-- ========================
DROP TABLE IF EXISTS account CASCADE;
DROP TABLE IF EXISTS customer CASCADE;

CREATE TABLE customer (
    cno   INTEGER PRIMARY KEY,
    cname VARCHAR(20),
    city  VARCHAR(20)
);

CREATE TABLE account (
    a_no         INT PRIMARY KEY,
    a_type       VARCHAR(10),
    opening_date DATE,
    balance      MONEY,
    cno          INTEGER REFERENCES customer(cno) ON DELETE CASCADE
);

-- ========================
-- Sample Data
-- ========================
INSERT INTO customer VALUES (1, 'Amit', 'Pune');
INSERT INTO customer VALUES (2, 'Sneha', 'Mumbai');
INSERT INTO customer VALUES (3, 'Rahul', 'Delhi');

-- ========================
-- Trigger Function & Trigger
-- ========================
DROP TRIGGER IF EXISTS trg_account_min_balance ON account;
DROP FUNCTION IF EXISTS fn_account_min_balance();

CREATE OR REPLACE FUNCTION fn_account_min_balance()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.balance < 500::MONEY THEN
        RAISE EXCEPTION 'Insertion denied: Balance (%) for account % is less than 500. Minimum opening balance must be 500.', NEW.balance, NEW.a_no;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_account_min_balance
    BEFORE INSERT ON account
    FOR EACH ROW
    EXECUTE FUNCTION fn_account_min_balance();

-- ========================
-- Test DML
-- ========================
-- Test 1: Valid insert (balance >= 500) — should SUCCEED
INSERT INTO account VALUES (1001, 'Savings', '2023-01-15', 5000.00, 1);

-- Test 2: Boundary insert (balance = 500) — should SUCCEED
INSERT INTO account VALUES (1002, 'Current', '2023-03-20', 500.00, 2);

-- Verify
SELECT * FROM account;

-- Test 3: Invalid insert (balance < 500) — should FAIL
-- Uncomment to test:
-- INSERT INTO account VALUES (1003, 'Savings', '2024-06-10', 200.00, 3);
