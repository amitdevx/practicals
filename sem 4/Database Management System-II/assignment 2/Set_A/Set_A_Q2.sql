-- ============================================================
-- Assignment 2: Stored Functions
-- Set A - Question 2
-- Check the number is positive, negative or zero
-- ============================================================

-- Q2. Write a stored function to check whether a given number
--     is positive, negative or zero.

CREATE OR REPLACE FUNCTION check_sign(num INTEGER)
RETURNS VOID AS $$
BEGIN
    IF num > 0 THEN
        RAISE NOTICE '% is Positive', num;
    ELSIF num < 0 THEN
        RAISE NOTICE '% is Negative', num;
    ELSE
        RAISE NOTICE 'The number is Zero';
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Test
SELECT check_sign(15);
SELECT check_sign(-7);
SELECT check_sign(0);
