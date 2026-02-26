-- ============================================================
-- Assignment 5: Triggers
-- Set A - Question 2
-- ============================================================
-- Q2. Write a trigger that is executed whenever a movie is
--     deleted from the Movie table. Display an appropriate message.
-- ============================================================

-- ========================
-- Table Creation
-- ========================
DROP TABLE IF EXISTS movie_actor CASCADE;
DROP TABLE IF EXISTS actor CASCADE;
DROP TABLE IF EXISTS movie CASCADE;

CREATE TABLE movie (
    m_name       VARCHAR(25) PRIMARY KEY,
    release_year INTEGER,
    budget       NUMERIC(12,2)
);

CREATE TABLE actor (
    a_name    VARCHAR(30) PRIMARY KEY,
    role      VARCHAR(30),
    charges   NUMERIC(12,2),
    a_address VARCHAR(30)
);

CREATE TABLE movie_actor (
    m_name VARCHAR(25) REFERENCES movie(m_name) ON DELETE CASCADE,
    a_name VARCHAR(30) REFERENCES actor(a_name) ON DELETE CASCADE,
    PRIMARY KEY (m_name, a_name)
);

-- ========================
-- Sample Data
-- ========================
INSERT INTO movie VALUES ('Inception', 2010, 16000000.00);
INSERT INTO movie VALUES ('Interstellar', 2014, 16500000.00);
INSERT INTO movie VALUES ('The Dark Knight', 2008, 18500000.00);

INSERT INTO actor VALUES ('Leonardo DiCaprio', 'Dom Cobb', 2000000.00, 'Los Angeles');
INSERT INTO actor VALUES ('Tom Hardy', 'Eames', 1500000.00, 'London');
INSERT INTO actor VALUES ('Christian Bale', 'Bruce Wayne', 2500000.00, 'New York');

INSERT INTO movie_actor VALUES ('Inception', 'Leonardo DiCaprio');
INSERT INTO movie_actor VALUES ('Inception', 'Tom Hardy');
INSERT INTO movie_actor VALUES ('The Dark Knight', 'Christian Bale');

-- ========================
-- Trigger Function & Trigger
-- ========================
DROP TRIGGER IF EXISTS trg_movie_delete ON movie;
DROP FUNCTION IF EXISTS fn_movie_delete();

CREATE OR REPLACE FUNCTION fn_movie_delete()
RETURNS TRIGGER AS $$
BEGIN
    RAISE NOTICE 'Movie "%" (Year: %, Budget: %) has been deleted from the Movie table.', OLD.m_name, OLD.release_year, OLD.budget;
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_movie_delete
    BEFORE DELETE ON movie
    FOR EACH ROW
    EXECUTE FUNCTION fn_movie_delete();

-- ========================
-- Test DML
-- ========================
-- This DELETE will fire the trigger and display a notice message
DELETE FROM movie WHERE m_name = 'Interstellar';

-- Delete a movie that has actors linked (cascade will remove from junction table)
DELETE FROM movie WHERE m_name = 'Inception';

-- Verify the movies are removed
SELECT * FROM movie;
SELECT * FROM movie_actor;
