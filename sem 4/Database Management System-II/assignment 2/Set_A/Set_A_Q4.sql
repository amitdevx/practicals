-- ============================================================
-- Assignment 2: Stored Functions
-- Set A - Question 4
-- Find number is even or odd
-- ============================================================

-- Q4. Write a stored function to find whether a given number
--     is even or odd.

CREATE OR REPLACE FUNCTION check_even_odd(num INTEGER)
RETURNS VOID AS $$
BEGIN
    IF num % 2 = 0 THEN
        RAISE NOTICE '% is Even', num;
    ELSE
        RAISE NOTICE '% is Odd', num;
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Test
SELECT check_even_odd(10);
SELECT check_even_odd(7);
SELECT check_even_odd(0);
