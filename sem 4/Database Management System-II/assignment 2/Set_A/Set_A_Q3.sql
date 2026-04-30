-- ============================================================
-- Assignment 2: Stored Functions
-- Set A - Question 3
-- Find maximum and minimum from three numbers
-- ============================================================

-- Q3. Write a stored function to find the maximum and minimum
--     from three numbers.

CREATE OR REPLACE FUNCTION find_min_max_three(a INTEGER, b INTEGER, c INTEGER)
RETURNS VOID AS $$
DECLARE
    v_max INTEGER;
    v_min INTEGER;
BEGIN
    -- Find maximum
    IF a >= b AND a >= c THEN
        v_max := a;
    ELSIF b >= a AND b >= c THEN
        v_max := b;
    ELSE
        v_max := c;
    END IF;

    -- Find minimum
    IF a <= b AND a <= c THEN
        v_min := a;
    ELSIF b <= a AND b <= c THEN
        v_min := b;
    ELSE
        v_min := c;
    END IF;

    RAISE NOTICE 'Among %, %, %: Maximum = %, Minimum = %', a, b, c, v_max, v_min;
END;
$$ LANGUAGE plpgsql;

-- Test
SELECT find_min_max_three(10, 25, 15);
SELECT find_min_max_three(50, 30, 40);
SELECT find_min_max_three(7, 7, 7);
