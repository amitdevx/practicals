/*
SLIP 28 - SECTION II: DATABASE MANAGEMENT SYSTEMS II

Company(name varchar(30) PK, address varchar(50), city varchar(20), share_value numeric)
Person(pname varchar(30) PK, pcity varchar(20))
company_person(name, pname, no_of_shares int) M:M

Q2.1A: Function to update share_values by 20% for a given person (companies they invest in).
Q2.1B: Trigger before delete on company - display message.
Q2.2: Procedure for division of two numbers with raise for error (division by zero).
*/

-- Table Creation
DROP TABLE IF EXISTS company_person CASCADE;
DROP TABLE IF EXISTS Company CASCADE;
DROP TABLE IF EXISTS Person CASCADE;

CREATE TABLE Company (
    name VARCHAR(30) PRIMARY KEY,
    address VARCHAR(50),
    city VARCHAR(20),
    share_value NUMERIC
);

CREATE TABLE Person (
    pname VARCHAR(30) PRIMARY KEY,
    pcity VARCHAR(20)
);

CREATE TABLE company_person (
    name VARCHAR(30) REFERENCES Company(name),
    pname VARCHAR(30) REFERENCES Person(pname),
    no_of_shares INT,
    PRIMARY KEY (name, pname)
);

-- Sample Data
INSERT INTO Company VALUES ('TCS', 'Hinjewadi', 'Pune', 3500);
INSERT INTO Company VALUES ('Infosys', 'Electronic City', 'Bangalore', 1500);
INSERT INTO Company VALUES ('Wipro', 'Sarjapur', 'Bangalore', 450);

INSERT INTO Person VALUES ('Amit', 'Pune');
INSERT INTO Person VALUES ('Sneha', 'Mumbai');
INSERT INTO Person VALUES ('Rahul', 'Bangalore');

INSERT INTO company_person VALUES ('TCS', 'Amit', 100);
INSERT INTO company_person VALUES ('Infosys', 'Amit', 200);
INSERT INTO company_person VALUES ('Wipro', 'Sneha', 150);
INSERT INTO company_person VALUES ('TCS', 'Rahul', 50);
INSERT INTO company_person VALUES ('Infosys', 'Rahul', 300);

-- Q2.1A: Function update share_values by 20% for companies a given person invests in
CREATE OR REPLACE FUNCTION update_shares_for_person(p_pname VARCHAR)
RETURNS VOID AS $$
DECLARE
    v_count INT;
BEGIN
    UPDATE Company SET share_value = share_value * 1.20
    WHERE name IN (SELECT name FROM company_person WHERE pname = p_pname);

    GET DIAGNOSTICS v_count = ROW_COUNT;

    IF v_count = 0 THEN
        RAISE NOTICE 'No companies found for person: %', p_pname;
    ELSE
        RAISE NOTICE 'Updated share values by 20%% for % company(ies) of person %', v_count, p_pname;
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Q2.1B: Trigger before delete on company - display message
CREATE OR REPLACE FUNCTION trg_before_delete_company()
RETURNS TRIGGER AS $$
BEGIN
    RAISE NOTICE 'Company "%" is being deleted from the database', OLD.name;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_company_delete
BEFORE DELETE ON Company
FOR EACH ROW EXECUTE FUNCTION trg_before_delete_company();

-- Q2.2: Procedure for division of two numbers with error handling
CREATE OR REPLACE PROCEDURE divide_two(p_a NUMERIC, p_b NUMERIC)
LANGUAGE plpgsql AS $$
DECLARE
    v_result NUMERIC;
BEGIN
    IF p_b = 0 THEN
        RAISE EXCEPTION 'Division by zero error: cannot divide % by 0', p_a;
    END IF;
    v_result := p_a / p_b;
    RAISE NOTICE '% / % = %', p_a, p_b, v_result;
END;
$$;

-- Test Calls
SELECT update_shares_for_person('Amit');

-- Test trigger
-- DELETE FROM company_person WHERE name = 'Wipro';
-- DELETE FROM Company WHERE name = 'Wipro';

CALL divide_two(100, 5);
CALL divide_two(50, 3);
-- This should raise exception:
-- CALL divide_two(10, 0);
