-- ============================================================
-- Assignment 2: Stored Functions
-- Set A - Question 5
-- Find sum of first 20 numbers (using unconditional loop)
-- ============================================================

-- Q5. Write a stored function to find the sum of first 20
--     numbers using an unconditional loop (LOOP...EXIT WHEN).

CREATE OR REPLACE FUNCTION sum_first_20()
RETURNS VOID AS $$
DECLARE
    i INTEGER := 1;
    total INTEGER := 0;
BEGIN
    LOOP
        total := total + i;
        i := i + 1;
        EXIT WHEN i > 20;
    END LOOP;

    RAISE NOTICE 'Sum of first 20 numbers = %', total;
END;
$$ LANGUAGE plpgsql;

-- Test
SELECT sum_first_20();
