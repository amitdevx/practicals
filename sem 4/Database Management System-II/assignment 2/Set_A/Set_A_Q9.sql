-- ============================================================
-- Assignment 2: Stored Functions
-- Set A - Question 9
-- Search the given number is in given range
-- ============================================================

-- Q9. Write a stored function to search whether a given number
--     is within a given range (low to high).

CREATE OR REPLACE FUNCTION search_in_range(num INTEGER, low INTEGER, high INTEGER)
RETURNS VOID AS $$
BEGIN
    IF num >= low AND num <= high THEN
        RAISE NOTICE '% is within the range [%, %]', num, low, high;
    ELSE
        RAISE NOTICE '% is NOT within the range [%, %]', num, low, high;
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Test
SELECT search_in_range(15, 10, 20);
SELECT search_in_range(25, 10, 20);
SELECT search_in_range(10, 10, 20);
