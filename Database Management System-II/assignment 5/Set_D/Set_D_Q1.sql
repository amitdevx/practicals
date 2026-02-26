-- ============================================================
-- Assignment 5: Triggers
-- Set D - Question 1
-- ============================================================
-- Q1. Write a trigger which is executed whenever an update is
--     made to the Account table. If the balance becomes less
--     than 1000, print an error message that balance cannot be
--     less than 1000.
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

INSERT INTO account VALUES (1001, 'Savings', '2023-01-15', 5000.00, 1);
INSERT INTO account VALUES (1002, 'Current', '2023-03-20', 15000.00, 2);
INSERT INTO account VALUES (1003, 'Savings', '2024-06-10', 2000.00, 3);

-- ========================
-- Trigger Function & Trigger
-- ========================
DROP TRIGGER IF EXISTS trg_account_balance_check ON account;
DROP FUNCTION IF EXISTS fn_account_balance_check();

CREATE OR REPLACE FUNCTION fn_account_balance_check()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.balance < 1000::MONEY THEN
        RAISE EXCEPTION 'Update denied: Balance (%) for account % cannot be less than 1000.', NEW.balance, NEW.a_no;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_account_balance_check
    BEFORE UPDATE ON account
    FOR EACH ROW
    EXECUTE FUNCTION fn_account_balance_check();

-- ========================
-- Test DML
-- ========================
-- Test 1: Valid update (balance >= 1000) — should SUCCEED
UPDATE account SET balance = 3000.00 WHERE a_no = 1001;

-- Test 2: Boundary update (balance = 1000) — should SUCCEED
UPDATE account SET balance = 1000.00 WHERE a_no = 1003;

-- Verify
SELECT * FROM account;

-- Test 3: Invalid update (balance < 1000) — should FAIL
-- Uncomment to test:
-- UPDATE account SET balance = 500.00 WHERE a_no = 1002;
