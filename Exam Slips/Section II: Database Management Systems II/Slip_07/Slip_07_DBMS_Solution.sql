-- Slip 07: Branch-Customer-Loan Database
-- Q2.1 OptionA: Cursor function to count customers of branch (accept branch name)
-- Q2.1 OptionB: Trigger before insert customer - if cno<=0 give message
-- Q2.2: Procedure sum of first 20 numbers using unconditional loop

-- ============================================================
-- Table Creation
-- ============================================================

DROP TABLE IF EXISTS Ternary CASCADE;
DROP TABLE IF EXISTS Loan_application CASCADE;
DROP TABLE IF EXISTS Customer CASCADE;
DROP TABLE IF EXISTS Branch CASCADE;

CREATE TABLE Branch (
    br_id   INT PRIMARY KEY,
    br_name CHAR(30),
    br_city CHAR(10)
);

CREATE TABLE Customer (
    cno    INT PRIMARY KEY,
    c_name CHAR(20),
    caddr  CHAR(35),
    city   CHAR(20)
);

CREATE TABLE Loan_application (
    lno             INT PRIMARY KEY,
    l_amt_required  NUMERIC CHECK (l_amt_required > 0),
    l_amt_approved  NUMERIC,
    l_date          DATE
);

CREATE TABLE Ternary (
    br_id INT REFERENCES Branch(br_id),
    cno   INT REFERENCES Customer(cno),
    lno   INT REFERENCES Loan_application(lno),
    PRIMARY KEY (br_id, cno, lno)
);

-- ============================================================
-- Sample Data
-- ============================================================

INSERT INTO Branch VALUES (1, 'Pune Main', 'Pune');
INSERT INTO Branch VALUES (2, 'Mumbai Central', 'Mumbai');
INSERT INTO Branch VALUES (3, 'Nashik Branch', 'Nashik');

INSERT INTO Customer VALUES (101, 'Amit', 'Kothrud, Pune', 'Pune');
INSERT INTO Customer VALUES (102, 'Neha', 'Andheri, Mumbai', 'Mumbai');
INSERT INTO Customer VALUES (103, 'Rahul', 'Deccan, Pune', 'Pune');
INSERT INTO Customer VALUES (104, 'Priya', 'Dadar, Mumbai', 'Mumbai');

INSERT INTO Loan_application VALUES (1001, 500000, 450000, '2024-01-10');
INSERT INTO Loan_application VALUES (1002, 300000, 300000, '2024-02-15');
INSERT INTO Loan_application VALUES (1003, 700000, 600000, '2024-03-20');

INSERT INTO Ternary VALUES (1, 101, 1001);
INSERT INTO Ternary VALUES (1, 103, 1002);
INSERT INTO Ternary VALUES (2, 102, 1003);
INSERT INTO Ternary VALUES (2, 104, 1003);

-- ============================================================
-- Q2.1 Option A: Cursor function to count customers of branch
-- ============================================================

CREATE OR REPLACE FUNCTION count_branch_customers(p_brname CHAR)
RETURNS INT AS $$
DECLARE
    cur CURSOR FOR
        SELECT DISTINCT c.cno, c.c_name
        FROM Ternary t
        JOIN Branch b ON b.br_id = t.br_id
        JOIN Customer c ON c.cno = t.cno
        WHERE TRIM(b.br_name) = TRIM(p_brname);
    rec RECORD;
    v_count INT := 0;
BEGIN
    OPEN cur;
    LOOP
        FETCH cur INTO rec;
        EXIT WHEN NOT FOUND;
        v_count := v_count + 1;
        RAISE NOTICE 'Customer: %', TRIM(rec.c_name);
    END LOOP;
    CLOSE cur;

    RAISE NOTICE 'Total customers in branch %: %', TRIM(p_brname), v_count;
    RETURN v_count;
END;
$$ LANGUAGE plpgsql;

-- Test: SELECT count_branch_customers('Pune Main');

-- ============================================================
-- Q2.1 Option B: Trigger before insert customer - if cno<=0 give message
-- ============================================================

CREATE OR REPLACE FUNCTION check_customer_cno()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.cno <= 0 THEN
        RAISE EXCEPTION 'Invalid customer number: cno must be greater than 0.';
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_check_cno
BEFORE INSERT ON Customer
FOR EACH ROW
EXECUTE FUNCTION check_customer_cno();

-- Test: INSERT INTO Customer VALUES (-1, 'Test', 'Test', 'Test');

-- ============================================================
-- Q2.2: Procedure sum of first 20 numbers using unconditional loop
-- ============================================================

CREATE OR REPLACE PROCEDURE sum_first_20()
AS $$
DECLARE
    i   INT := 1;
    v_sum INT := 0;
BEGIN
    LOOP
        v_sum := v_sum + i;
        i := i + 1;
        EXIT WHEN i > 20;
    END LOOP;

    RAISE NOTICE 'Sum of first 20 numbers = %', v_sum;
END;
$$ LANGUAGE plpgsql;

-- Test: CALL sum_first_20();
