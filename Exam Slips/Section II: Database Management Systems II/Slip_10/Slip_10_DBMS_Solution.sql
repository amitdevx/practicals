-- Slip 10: Book-Author Database
-- Q2.1 OptionA: Function to display book details by author, raise exception if invalid
-- Q2.1 OptionB: Trigger after insert on book - if price>1000 display "prize is so high"
-- Q2.2: Procedure display even numbers 1 to 50

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
-- Q2.1 Option A: Function to display book details by author
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

-- Test: SELECT get_books_by_author('Navathe');
-- Test: SELECT get_books_by_author('Unknown');

-- ============================================================
-- Q2.1 Option B: Trigger after insert on book - if price > 1000
-- ============================================================

CREATE OR REPLACE FUNCTION check_book_price()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.b_price > 1000 THEN
        RAISE NOTICE 'prize is so high';
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_book_price
AFTER INSERT ON Book
FOR EACH ROW
EXECUTE FUNCTION check_book_price();

-- Test: INSERT INTO Book VALUES (5, 'Networking', 'TMH', 1500);

-- ============================================================
-- Q2.2: Procedure display even numbers 1 to 50
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

-- Test: CALL display_even_1_to_50();
