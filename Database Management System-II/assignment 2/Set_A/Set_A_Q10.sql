-- ============================================================
-- Assignment 2: Stored Functions
-- Set A - Question 10
-- Display a number in word (Using Case) and loop
-- ============================================================

-- Q10. Write a stored function to display a number in words
--      using CASE and LOOP. (e.g., 123 -> One Two Three)

CREATE OR REPLACE FUNCTION number_in_words(num INTEGER)
RETURNS VOID AS $$
DECLARE
    num_str TEXT;
    ch CHAR(1);
    word TEXT;
    result TEXT := '';
    i INTEGER;
BEGIN
    num_str := num::TEXT;

    FOR i IN 1..LENGTH(num_str) LOOP
        ch := SUBSTRING(num_str FROM i FOR 1);

        CASE ch
            WHEN '0' THEN word := 'Zero';
            WHEN '1' THEN word := 'One';
            WHEN '2' THEN word := 'Two';
            WHEN '3' THEN word := 'Three';
            WHEN '4' THEN word := 'Four';
            WHEN '5' THEN word := 'Five';
            WHEN '6' THEN word := 'Six';
            WHEN '7' THEN word := 'Seven';
            WHEN '8' THEN word := 'Eight';
            WHEN '9' THEN word := 'Nine';
            ELSE word := '';
        END CASE;

        IF result = '' THEN
            result := word;
        ELSE
            result := result || ' ' || word;
        END IF;
    END LOOP;

    RAISE NOTICE '% in words: %', num, result;
END;
$$ LANGUAGE plpgsql;

-- Test
SELECT number_in_words(123);
SELECT number_in_words(4507);
SELECT number_in_words(90210);
