-- ============================================================
-- Assignment 5: Triggers
-- Set D - Question 2
-- ============================================================
-- Q2. Write a trigger before deleting an account record from
--     the Account table. Raise a notice and display the message
--     "Account record is being deleted."
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
DROP TRIGGER IF EXISTS trg_account_delete_notice ON account;
DROP FUNCTION IF EXISTS fn_account_delete_notice();

CREATE OR REPLACE FUNCTION fn_account_delete_notice()
RETURNS TRIGGER AS $$
BEGIN
    RAISE NOTICE 'Account record is being deleted. Account No: %, Type: %, Balance: %', OLD.a_no, OLD.a_type, OLD.balance;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_account_delete_notice
    BEFORE DELETE ON account
    FOR EACH ROW
    EXECUTE FUNCTION fn_account_delete_notice();

-- ========================
-- Test DML
-- ========================
-- This DELETE will fire the trigger and display a notice message
DELETE FROM account WHERE a_no = 1001;

-- Delete another account
DELETE FROM account WHERE a_no = 1003;

-- Verify
SELECT * FROM account;
