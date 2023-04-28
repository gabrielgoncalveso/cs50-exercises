SELECT m.title FROM movies AS m LEFT JOIN ratings AS r ON r.movie_id = m.id WHERE m.id IN
(SELECT s.movie_id FROM stars AS s WHERE s.person_id IN (
SELECT p.id FROM people AS p WHERE name = 'Chadwick Boseman'
)) ORDER BY r.rating LIMIT 5;