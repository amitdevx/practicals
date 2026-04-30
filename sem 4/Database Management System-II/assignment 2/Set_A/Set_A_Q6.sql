-- ============================================================
-- Assignment 2: Stored Functions
-- Set A - Question 6
-- Display all even numbers from 1 to 50
-- ============================================================

-- Q6. Write a stored function to display all even numbers
--     from 1 to 50.

CREATE OR REPLACE FUNCTION display_even_1_to_50()
RETURNS VOID AS $$
DECLARE
    i INTEGER;
    result TEXT := '';
BEGIN
    FOR i IN 1..50 LOOP
        IF i % 2 = 0 THEN
            result := result || i || ' ';
        END IF;
    END LOOP;

    RAISE NOTICE 'Even numbers from 1 to 50: %', result;
END;
$$ LANGUAGE plpgsql;

-- Test
SELECT display_even_1_to_50();
