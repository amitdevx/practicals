-- ============================================================
-- Assignment 2: Stored Functions
-- Set A - Question 1
-- Find minimum and maximum from two numbers
-- ============================================================

-- Q1. Write a stored function to find the minimum and maximum
--     from two numbers.

CREATE OR REPLACE FUNCTION find_min_max(a INTEGER, b INTEGER)
RETURNS VOID AS $$
BEGIN
    IF a > b THEN
        RAISE NOTICE 'Maximum = %, Minimum = %', a, b;
    ELSIF b > a THEN
        RAISE NOTICE 'Maximum = %, Minimum = %', b, a;
    ELSE
        RAISE NOTICE 'Both numbers are equal: %', a;
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Test
SELECT find_min_max(10, 25);
SELECT find_min_max(42, 17);
SELECT find_min_max(5, 5);
