-- ============================================================
-- Assignment 2: Stored Functions
-- Set B - Question 2
-- Function to find minimum loan amount approved
-- ============================================================

-- Q2. Write a function to find the minimum loan amount
--     approved from the loan_application table.

-- Bank Database Schema:
--   branch (bid, brname, brcity)
--   customer (cno, cname, caddr, city)
--   loan_application (lno, lamtrequired, lamtapproved, l_date)
--   TERNARY (bid, cno, lno)

-- Drop existing tables
DROP TABLE IF EXISTS ternary CASCADE;
DROP TABLE IF EXISTS loan_application CASCADE;
DROP TABLE IF EXISTS customer CASCADE;
DROP TABLE IF EXISTS branch CASCADE;

-- Create tables
CREATE TABLE branch (
    bid INTEGER PRIMARY KEY,
    brname CHAR(30),
    brcity CHAR(10)
);

CREATE TABLE customer (
    cno INTEGER PRIMARY KEY,
    cname CHAR(20),
    caddr CHAR(35),
    city CHAR(20)
);

CREATE TABLE loan_application (
    lno INTEGER PRIMARY KEY,
    lamtrequired MONEY,
    lamtapproved MONEY,
    l_date DATE
);

CREATE TABLE ternary (
    bid INTEGER REFERENCES branch(bid),
    cno INTEGER REFERENCES customer(cno),
    lno INTEGER REFERENCES loan_application(lno),
    PRIMARY KEY (bid, cno, lno)
);

-- Insert sample data
INSERT INTO branch VALUES (1, 'SBI Main', 'Pune');
INSERT INTO branch VALUES (2, 'HDFC Central', 'Mumbai');
INSERT INTO branch VALUES (3, 'ICICI Park', 'Pune');
INSERT INTO branch VALUES (4, 'BOI Station', 'Nagpur');
INSERT INTO branch VALUES (5, 'SBI Camp', 'Delhi');

INSERT INTO customer VALUES (101, 'Amit Sharma', '12 MG Road', 'Pune');
INSERT INTO customer VALUES (102, 'Priya Desai', '45 FC Road', 'Mumbai');
INSERT INTO customer VALUES (103, 'Rahul Patil', '78 JM Road', 'Pune');
INSERT INTO customer VALUES (104, 'Sneha Kulkarni', '23 Laxmi Nagar', 'Nagpur');
INSERT INTO customer VALUES (105, 'Vikas Joshi', '56 Civil Lines', 'Delhi');
INSERT INTO customer VALUES (106, 'Neha Mehta', '89 Andheri West', 'Mumbai');

INSERT INTO loan_application VALUES (1001, '$500000', '$450000', '2024-01-15');
INSERT INTO loan_application VALUES (1002, '$300000', '$250000', '2024-02-20');
INSERT INTO loan_application VALUES (1003, '$700000', '$600000', '2024-03-10');
INSERT INTO loan_application VALUES (1004, '$150000', '$150000', '2024-04-05');
INSERT INTO loan_application VALUES (1005, '$400000', '$350000', '2024-05-12');
INSERT INTO loan_application VALUES (1006, '$250000', '$200000', '2024-06-18');

INSERT INTO ternary VALUES (1, 101, 1001);
INSERT INTO ternary VALUES (1, 103, 1002);
INSERT INTO ternary VALUES (2, 102, 1003);
INSERT INTO ternary VALUES (2, 106, 1004);
INSERT INTO ternary VALUES (3, 101, 1005);
INSERT INTO ternary VALUES (4, 104, 1006);

-- Function
CREATE OR REPLACE FUNCTION find_min_loan_approved()
RETURNS MONEY AS $$
DECLARE
    min_loan MONEY;
BEGIN
    SELECT MIN(lamtapproved) INTO min_loan
    FROM loan_application;

    RAISE NOTICE 'Minimum loan amount approved = %', min_loan;
    RETURN min_loan;
END;
$$ LANGUAGE plpgsql;

-- Test
SELECT find_min_loan_approved();
