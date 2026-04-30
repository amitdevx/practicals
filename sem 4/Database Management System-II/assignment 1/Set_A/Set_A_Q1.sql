-- ============================================================
-- Assignment 1: Stored Procedures
-- Set A - Question 1
-- ============================================================
-- Q1. Write a procedure to display addition, subtraction and
--     multiplication of three numbers.
-- ============================================================

-- Drop existing procedure
DROP PROCEDURE IF EXISTS calc_three_numbers(INT, INT, INT);

-- Create procedure
CREATE OR REPLACE PROCEDURE calc_three_numbers(
    IN a INT,
    IN b INT,
    IN c INT
)
LANGUAGE plpgsql
AS $$
DECLARE
    v_add INT;
    v_sub INT;
    v_mul INT;
BEGIN
    v_add := a + b + c;
    v_sub := a - b - c;
    v_mul := a * b * c;

    RAISE NOTICE 'Numbers: %, %, %', a, b, c;
    RAISE NOTICE 'Addition       : % + % + % = %', a, b, c, v_add;
    RAISE NOTICE 'Subtraction    : % - % - % = %', a, b, c, v_sub;
    RAISE NOTICE 'Multiplication : % * % * % = %', a, b, c, v_mul;
END;
$$;

-- Test
CALL calc_three_numbers(10, 5, 3);
CALL calc_three_numbers(20, 7, 2);
CALL calc_three_numbers(0, 0, 0);
