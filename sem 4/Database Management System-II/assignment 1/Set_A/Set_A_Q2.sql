-- ============================================================
-- Assignment 1: Stored Procedures
-- Set A - Question 2
-- ============================================================
-- Q2. Write a procedure to display division of two numbers.
--     Use RAISE to display error messages.
-- ============================================================

-- Drop existing procedure
DROP PROCEDURE IF EXISTS divide_two_numbers(NUMERIC, NUMERIC);

-- Create procedure
CREATE OR REPLACE PROCEDURE divide_two_numbers(
    IN a NUMERIC,
    IN b NUMERIC
)
LANGUAGE plpgsql
AS $$
DECLARE
    v_result NUMERIC;
BEGIN
    IF a IS NULL OR b IS NULL THEN
        RAISE EXCEPTION 'Invalid input: NULL values are not allowed';
    END IF;

    IF b = 0 THEN
        RAISE EXCEPTION 'Division by zero error: Cannot divide % by 0', a;
    END IF;

    v_result := a / b;

    RAISE NOTICE 'Division: % / % = %', a, b, ROUND(v_result, 2);
END;
$$;

-- Test: Normal division
CALL divide_two_numbers(10, 3);
CALL divide_two_numbers(100, 5);
CALL divide_two_numbers(7, 2);

-- Test: Division by zero (will raise exception)
-- Uncomment the line below to test error handling:
-- CALL divide_two_numbers(10, 0);
