-- ============================================================
-- Slip 04: Movies-Actor-Producer Database
-- Section II: Database Management Systems-II [15 Marks]
-- ============================================================

/*
Consider the following Entities and their Relationships for Movies-Actor-Producer database.

Movies (m_name varchar(25), release_year integer, budget money)
Actor (a_name char(30), role char(30), charges money, a_address varchar(30))
Producer (producer_id integer, name char(30), p_address varchar(30))

Relationships:
- Each actor has acted in one or more movies (Actor to Movies: M-M)
- Each producer has produced many movies and each movie can be produced by more than one
  producers (Producer to Movies: M-M)
- Each movie has one or more actors acting in it, in different roles

Constraints: Primary Key constraints on all entity tables.
*/

-- ============================================================
-- Database Setup
-- ============================================================

DROP DATABASE IF EXISTS slip_04_db;
CREATE DATABASE slip_04_db;
\c slip_04_db

-- ============================================================
-- Table Creation
-- ============================================================

DROP TABLE IF EXISTS movie_producer CASCADE;
DROP TABLE IF EXISTS movie_actor CASCADE;
DROP TABLE IF EXISTS Movies CASCADE;
DROP TABLE IF EXISTS Actor CASCADE;
DROP TABLE IF EXISTS Producer CASCADE;

CREATE TABLE Movies (
    m_name       VARCHAR(25) PRIMARY KEY,
    release_year INT,
    budget       NUMERIC(12,2)
);

CREATE TABLE Actor (
    a_name    CHAR(30) PRIMARY KEY,
    role      CHAR(30),
    charges   NUMERIC(10,2),
    a_address VARCHAR(30)
);

CREATE TABLE Producer (
    producer_id INT PRIMARY KEY,
    name        CHAR(30),
    p_address   VARCHAR(30)
);

CREATE TABLE movie_actor (
    m_name VARCHAR(25) REFERENCES Movies(m_name),
    a_name CHAR(30) REFERENCES Actor(a_name),
    PRIMARY KEY (m_name, a_name)
);

CREATE TABLE movie_producer (
    m_name      VARCHAR(25) REFERENCES Movies(m_name),
    producer_id INT REFERENCES Producer(producer_id),
    PRIMARY KEY (m_name, producer_id)
);

-- ============================================================
-- Sample Data
-- ============================================================

INSERT INTO Movies VALUES ('Dangal', 2016, 70000000);
INSERT INTO Movies VALUES ('3 Idiots', 2009, 55000000);
INSERT INTO Movies VALUES ('PK', 2014, 85000000);

INSERT INTO Actor VALUES ('Aamir Khan', 'Lead', 5000000, 'Mumbai');
INSERT INTO Actor VALUES ('Kareena Kapoor', 'Lead', 3000000, 'Mumbai');

INSERT INTO Producer VALUES (1, 'Aamir Khan Productions', 'Mumbai');
INSERT INTO Producer VALUES (2, 'Vidhu Vinod Chopra', 'Mumbai');

INSERT INTO movie_actor VALUES ('Dangal', 'Aamir Khan');
INSERT INTO movie_actor VALUES ('3 Idiots', 'Aamir Khan');
INSERT INTO movie_actor VALUES ('PK', 'Aamir Khan');
INSERT INTO movie_actor VALUES ('3 Idiots', 'Kareena Kapoor');

INSERT INTO movie_producer VALUES ('Dangal', 1);
INSERT INTO movie_producer VALUES ('3 Idiots', 2);
INSERT INTO movie_producer VALUES ('PK', 1);

-- ============================================================
-- Q2.1 Option A: Write a cursor to pass actor name as input
-- parameter and return total number of movies in which given
-- actor is acting. [10 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION count_actor_movies(p_aname CHAR)
RETURNS INT AS $$
DECLARE
    cur CURSOR FOR
        SELECT m_name FROM movie_actor WHERE TRIM(a_name) = TRIM(p_aname);
    rec RECORD;
    v_count INT := 0;
BEGIN
    OPEN cur;
    LOOP
        FETCH cur INTO rec;
        EXIT WHEN NOT FOUND;
        v_count := v_count + 1;
        RAISE NOTICE 'Movie: %', rec.m_name;
    END LOOP;
    CLOSE cur;

    IF v_count = 0 THEN
        RAISE EXCEPTION 'Actor % not found in any movie.', p_aname;
    END IF;

    RAISE NOTICE 'Total movies for %: %', TRIM(p_aname), v_count;
    RETURN v_count;
END;
$$ LANGUAGE plpgsql;

-- Execute: SELECT count_actor_movies('Aamir Khan');     -- 3 movies
-- Execute: SELECT count_actor_movies('Kareena Kapoor'); -- 1 movie
-- Execute: SELECT count_actor_movies('Unknown');        -- Should raise exception

-- ============================================================
-- Q2.1 Option B (OR): Write a trigger before inserting into
-- movie table to check budget. Budget should be minimum 50
-- lakh. Display appropriate message. [10 Marks]
-- ============================================================

CREATE OR REPLACE FUNCTION check_movie_budget()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.budget < 5000000 THEN
        RAISE EXCEPTION 'Budget must be at least 50 lakh (5000000). Got: %', NEW.budget;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_check_budget
BEFORE INSERT ON Movies
FOR EACH ROW
EXECUTE FUNCTION check_movie_budget();

-- Execute: INSERT INTO Movies VALUES ('LowBudget', 2024, 1000000);  -- Should fail (< 50 lakh)
-- Execute: INSERT INTO Movies VALUES ('HighBudget', 2024, 10000000); -- Should succeed

-- ============================================================
-- Q2.2: Write a procedure to check the number is positive,
-- negative or zero. [5 Marks]
-- ============================================================

CREATE OR REPLACE PROCEDURE check_number(n NUMERIC)
AS $$
BEGIN
    IF n > 0 THEN
        RAISE NOTICE '% is Positive.', n;
    ELSIF n < 0 THEN
        RAISE NOTICE '% is Negative.', n;
    ELSE
        RAISE NOTICE 'The number is Zero.';
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Execute: CALL check_number(10);   -- Positive
-- Execute: CALL check_number(-5);   -- Negative
-- Execute: CALL check_number(0);    -- Zero

