-- ============================================================
-- Assignment 5: Triggers
-- Set A - Question 3
-- ============================================================
-- Q3. Write a trigger that is executed whenever an insertion is
--     made to the Movie table. If budget < 1,00,000 then do not
--     allow the insertion. Give an appropriate message.
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
    budget       MONEY
);

CREATE TABLE actor (
    a_name    VARCHAR(30) PRIMARY KEY,
    role      VARCHAR(30),
    charges   MONEY,
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
INSERT INTO actor VALUES ('Leonardo DiCaprio', 'Dom Cobb', 2000000.00, 'Los Angeles');
INSERT INTO actor VALUES ('Tom Hardy', 'Eames', 1500000.00, 'London');

-- ========================
-- Trigger Function & Trigger
-- ========================
DROP TRIGGER IF EXISTS trg_movie_budget_check ON movie;
DROP FUNCTION IF EXISTS fn_movie_budget_check();

CREATE OR REPLACE FUNCTION fn_movie_budget_check()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.budget < 100000::MONEY THEN
        RAISE EXCEPTION 'Insertion denied: Budget (%) for movie "%" is less than 1,00,000. Minimum budget required is 1,00,000.', NEW.budget, NEW.m_name;
    END IF;
    RAISE NOTICE 'Movie "%" inserted successfully with budget %.', NEW.m_name, NEW.budget;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_movie_budget_check
    BEFORE INSERT ON movie
    FOR EACH ROW
    EXECUTE FUNCTION fn_movie_budget_check();

-- ========================
-- Test DML
-- ========================
-- Test 1: Valid insertion (budget >= 1,00,000) — should SUCCEED
INSERT INTO movie VALUES ('Inception', 2010, 16000000.00);

-- Test 2: Valid insertion at boundary — should SUCCEED
INSERT INTO movie VALUES ('Low Budget Film', 2023, 100000.00);

-- Verify successful inserts
SELECT * FROM movie;

-- Test 3: Invalid insertion (budget < 1,00,000) — should FAIL with exception
-- Uncomment the line below to test (it will raise an exception and abort)
-- INSERT INTO movie VALUES ('Too Cheap Movie', 2024, 50000.00);
