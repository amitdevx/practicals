-- ============================================================
-- Assignment 2: Stored Functions
-- Set A - Question 8
-- Count odd numbers from given range (m to n) using for loop
-- ============================================================

-- Q8. Write a stored function to count odd numbers from a
--     given range (m to n) using a FOR loop.

CREATE OR REPLACE FUNCTION count_odd_in_range(m INTEGER, n INTEGER)
RETURNS VOID AS $$
DECLARE
    i INTEGER;
    cnt INTEGER := 0;
BEGIN
    FOR i IN m..n LOOP
        IF i % 2 != 0 THEN
            cnt := cnt + 1;
        END IF;
    END LOOP;

    RAISE NOTICE 'Count of odd numbers from % to % = %', m, n, cnt;
END;
$$ LANGUAGE plpgsql;

-- Test
SELECT count_odd_in_range(1, 20);
SELECT count_odd_in_range(10, 50);
SELECT count_odd_in_range(1, 100);
