-- ============================================================
-- Assignment 2: Stored Functions
-- Set A - Question 7
-- Find sum and average of first n numbers using while loop
-- ============================================================

-- Q7. Write a stored function to find the sum and average of
--     first n numbers using a WHILE loop.

CREATE OR REPLACE FUNCTION sum_avg_n(n INTEGER)
RETURNS VOID AS $$
DECLARE
    i INTEGER := 1;
    total INTEGER := 0;
    avg_val NUMERIC;
BEGIN
    WHILE i <= n LOOP
        total := total + i;
        i := i + 1;
    END LOOP;

    avg_val := total::NUMERIC / n;

    RAISE NOTICE 'Sum of first % numbers = %', n, total;
    RAISE NOTICE 'Average of first % numbers = %', n, ROUND(avg_val, 2);
END;
$$ LANGUAGE plpgsql;

-- Test
SELECT sum_avg_n(10);
SELECT sum_avg_n(20);
SELECT sum_avg_n(100);
