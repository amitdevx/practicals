-- ============================================================
-- Slip 10: Book-Author Database
-- Section II: Database Management Systems-II [15 Marks]
-- ============================================================

/*
Consider the following Entities and their Relationships:

Book (b_no int, b_name varchar(20), pub_name varchar(10), b_price float)
Author (a_no int, a_name varchar(20), qualification varchar(15), address varchar(15))

Relationship:
- M-M between Book and Author

Constraints:
- Primary Key for each entity
- pub_name should not be null
*/

-- ============================================================
-- Database Setup
-- ============================================================

DROP DATABASE IF EXISTS slip_10_db;
CREATE DATABASE slip_10_db;
\c slip_10_db

-- ============================================================
-- Table Creation
-- ============================================================

DROP TABLE IF EXISTS book_author CASCADE;
DROP TABLE IF EXISTS Book CASCADE;
DROP TABLE IF EXISTS Author CASCADE;

CREATE TABLE Book (
    b_no     INT PRIMARY KEY,
    b_name   VARCHAR(20),
    pub_name VARCHAR(10) NOT NULL,
    b_price  FLOAT
);

CREATE TABLE Author (
    a_no          INT PRIMARY KEY,
    a_name        VARCHAR(20),
    qualification VARCHAR(15),
    address       VARCHAR(15)
);

CREATE TABLE book_author (
    b_no INT REFERENCES Book(b_no),
    a_no INT REFERENCES Author(a_no),
    PRIMARY KEY (b_no, a_no)
);

-- ============================================================
-- Sample Data
-- ============================================================

INSERT INTO Book VALUES (1, 'DBMS Concepts', 'Pearson', 550);
INSERT INTO Book VALUES (2, 'Data Structures', 'TMH', 1200);
INSERT INTO Book VALUES (3, 'Operating Systems', 'Wiley', 800);
INSERT INTO Book VALUES (4, 'Algorithms', 'Pearson', 1500);

INSERT INTO Author VALUES (101, 'Navathe', 'PhD', 'USA');
INSERT INTO Author VALUES (102, 'Lipschutz', 'PhD', 'USA');
INSERT INTO Author VALUES (103, 'Galvin', 'PhD', 'USA');

INSERT INTO book_author VALUES (1, 101);
INSERT INTO book_author VALUES (2, 102);
INSERT INTO book_author VALUES (3, 103);
INSERT INTO book_author VALUES (4, 101);

-- ============================================================
-- Q2.1 Option A: Write a stored function to display the book
-- details written by author. Accept Author name as input
-- parameter. Raise an exception in case of invalid author
-- name. [5 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION get_books_by_author(p_aname VARCHAR)
RETURNS VOID AS $$
DECLARE
    v_ano INT;
    rec RECORD;
    v_found BOOLEAN := FALSE;
BEGIN
    SELECT a_no INTO v_ano
    FROM Author
    WHERE a_name = p_aname;

    IF NOT FOUND THEN
        RAISE EXCEPTION 'Invalid author name: %', p_aname;
    END IF;

    FOR rec IN
        SELECT b.b_no, b.b_name, b.pub_name, b.b_price
        FROM book_author ba
        JOIN Book b ON b.b_no = ba.b_no
        WHERE ba.a_no = v_ano
    LOOP
        v_found := TRUE;
        RAISE NOTICE 'Book#: %, Name: %, Publisher: %, Price: %',
            rec.b_no, TRIM(rec.b_name), TRIM(rec.pub_name), rec.b_price;
    END LOOP;

    IF NOT v_found THEN
        RAISE NOTICE 'No books found for author: %', p_aname;
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Execute: SELECT get_books_by_author('Navathe');   -- DBMS Concepts, Algorithms
-- Execute: SELECT get_books_by_author('Lipschutz'); -- Data Structures
-- Execute: SELECT get_books_by_author('Unknown');   -- Should raise exception

-- ============================================================
-- Q2.1 Option B (OR): Write a trigger after insert on book to
-- display message "price is so high" if book price is more
-- than 1000. [5 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION check_book_price()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.b_price > 1000 THEN
        RAISE NOTICE 'price is so high';
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_book_price
AFTER INSERT ON Book
FOR EACH ROW
EXECUTE FUNCTION check_book_price();

-- Execute: INSERT INTO Book VALUES (10, 'Expensive', 'TMH', 1500);  -- Shows "price is so high"
-- Execute: INSERT INTO Book VALUES (11, 'Cheap', 'Pearson', 500);   -- No message (price <= 1000)

-- ============================================================
-- Q2.2: Write a procedure to display all even numbers from 1
-- to 50. [5 Marks]
-- ============================================================

CREATE OR REPLACE PROCEDURE display_even_1_to_50()
AS $$
DECLARE
    i INT;
BEGIN
    FOR i IN 1..50 LOOP
        IF i % 2 = 0 THEN
            RAISE NOTICE '%', i;
        END IF;
    END LOOP;
END;
$$ LANGUAGE plpgsql;

-- Execute: CALL display_even_1_to_50();  -- Displays 2, 4, 6, 8, ... 50

